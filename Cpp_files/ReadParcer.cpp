#include <stdio.h>
#include <stdlib.h>
#include "Differentiator.h"
#include "ReadParcer.h"
#include "DiffProgramm.h"
#include "GraphDump.h"
#include "LexicalAnalysis.h"
#include "string.h"

//
// G := E
// E :=
//

void StartParcer(const char* file_read_expr, Tree* start_tree) {
    FILE* fr = fopen(file_read_expr, "r+");

    Reader parcer = {};
    parcer.counter = 0;

    char expr[expression_len] = {};
    fscanf(fr, "%[^\n]", expr);
    printf("str to read: %s, strlen: %d\n", expr, strlen(expr));

    Lexical* reader = (Lexical*) calloc(expression_len, sizeof(Lexical));
    parcer.reader = LexicalReadStr(expr, reader);

    start_tree -> root = GetG(&parcer);
    printf("GetG success!\n");

    GraphDump(start_tree -> root);
    printf("GraphDump at StartParcer success!\n");

    free(reader);

    fclose(fr);
} 

Node* GetG(Reader* parcer) {
    Node* val = GetE(parcer);
    Lexical oper = parcer -> reader[parcer -> counter]; 
    if(oper.type != OPER || oper.value.OPER != '$') {
        SyntaxError(__LINE__);
    }
    printf("End the process with $\n");
    parcer -> counter++;
    return val;
}

Node* GetE(Reader* parcer) {
    Node* val = GetT(parcer);
    Lexical oper = parcer -> reader[parcer -> counter]; 

    while(oper.type == OPER && (oper.value.OPER == ADD || oper.value.OPER == SUB)) {
        printf("Start + or -\n");

        parcer -> counter++;
        Node* val2 = GetT(parcer);
        
        if(oper.value.OPER == ADD) { 
            val = _ADD(val, val2);
        }
        else {
            val = _SUB(val, val2);
        }
        
        oper = parcer -> reader[parcer -> counter]; 
    }
    return val;
}

Node* GetT(Reader* parcer) {
    Node* val = GetD(parcer);
    Lexical oper = parcer -> reader[parcer -> counter]; 

    while(oper.type == OPER && (oper.value.OPER == MUL || oper.value.OPER == DIV)) {
        printf("Start * or /!\n");

        int op = oper.value.OPER;
        parcer -> counter++;

        Node* val2 = GetD(parcer);
        printf("val2 at * or /: %d\n", val2->value);
        printf("oper is: %d\n", op);
        
        if(op == MUL) { 
            val = _MUL(val,val2);
        }
        else {
            val = _DIV(val,val2);
        }

        oper = parcer -> reader[parcer -> counter]; 
    }
    return val;
}

Node* GetD(Reader* parcer) {
    Node* val = GetP(parcer);
    Lexical oper = parcer -> reader[parcer -> counter]; 
    while(oper.type == OPER && oper.value.OPER == POW) {
        printf("Start ^\n");
        parcer -> counter++;

        Node* val2 = GetP(parcer);

        val = _DEG(val, val2);

        oper = parcer -> reader[parcer -> counter]; 
    }
    return val;
}

Node* GetP(Reader* parcer) {
    Lexical oper = parcer -> reader[parcer -> counter]; 

    if(oper.type == OPER && oper.value.OPER == OPEN_BRACKET) {

        printf("open bracket at %d!\n", parcer -> counter);
        parcer -> counter++;
        Node* val = GetE(parcer);

        oper = parcer -> reader[parcer -> counter]; 

        if(oper.type == OPER && oper.value.OPER != CLOSE_BRACKET) {
            printf("NO CLOSE BRACKET!\n");
            SyntaxError(__LINE__);
        }
        printf("Ending skobka at %d!\n", parcer -> counter);

        parcer -> counter++;
        return val;

    } else if(oper.type == VAR && oper.value.VAR == 'x') {
        return GetV(parcer);
    } else {
        return GetN(parcer);
    }
}

Node* GetV(Reader* parcer) {
    parcer -> counter++; // Обработка ошибок!
    return _VAR(X_CONST);
}

Node* GetN(Reader* parcer) {
    int val = 0;
    int old_p = parcer -> counter;

    Lexical oper = parcer -> reader[parcer -> counter]; 
    if(oper.type == NUM) {

        val = oper.value.NUM;
        printf("readed number: %d\n", oper.value);
        printf("parcer counter before: %d\n", parcer -> counter);
        parcer -> counter++;
        printf("parcer counter after: %d\n", parcer -> counter);

    }

    if(old_p == parcer -> counter) {
        printf("value at syntax error: %d\n", parcer -> reader[parcer -> counter].value);
        SyntaxError(__LINE__);
    }
    return _NUM(val);
}

void SyntaxError(int line) {
    printf("Syntaxis error at line: %d\n", line);
    exit(0);
}