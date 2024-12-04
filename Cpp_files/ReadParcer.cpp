#include <stdio.h>
#include <stdlib.h>
#include "Differentiator.h"
#include "ReadParcer.h"
#include "DiffProgramm.h"
#include "GraphDump.h"

void StartParcer(const char* file_read_expr, Tree* start_tree) {
    FILE* fr = fopen(file_read_expr, "r+");

    Reader parcer = {};
    parcer.counter = 0;
    fscanf(fr, "%s", parcer.expr);
    printf("str to read: %s\n", parcer.expr);

    start_tree -> root = GetG(&parcer);
    printf("GetG success!\n");

    GraphDump(start_tree -> root);
    printf("GraphDump at StartParcer success!\n");
} 

Node* GetG(Reader* parcer) {
    Node* val = GetE(parcer);
    if(parcer -> expr[parcer -> counter] != '$') {
        SyntaxError();
    }
    printf("End the process with $\n");
    parcer -> counter++;
    return val;
}

Node* GetE(Reader* parcer) {
    Node* val = GetT(parcer);
    while(parcer -> expr[parcer -> counter] == '+' || parcer -> expr[parcer -> counter] == '-') {
        int op = parcer -> expr[parcer -> counter];
        parcer -> counter++;
        Node* val2 = GetT(parcer);
        
        if(op == '+') { 
            val = _ADD(val, val2);
        }
        else {
            val = _SUB(val, val2);
        }
    }
    return val;
}

Node* GetT(Reader* parcer) {
    Node* val = GetD(parcer);
    while(parcer -> expr[parcer -> counter] == '*' || parcer -> expr[parcer -> counter] == '/') {
        int op = parcer -> expr[parcer -> counter];
        parcer -> counter++;
        Node* val2 = GetD(parcer);
        
        if(op == '*') { 
            val = _MUL(val,val2);
        }
        else {
            val = _DIV(val,val2);
        }
    }
    return val;
}

Node* GetD(Reader* parcer) {
    Node* val = GetP(parcer);
    while(parcer -> expr[parcer -> counter] == '^') {
        parcer -> counter++;

        Node* val2 = GetP(parcer);

        val = _DEG(val, val2);
    }
    return val;
}

Node* GetP(Reader* parcer) {
    if(parcer -> expr[parcer -> counter] == '(') {
        printf("skobka at %d!\n", parcer -> counter);
        parcer -> counter++;
        Node* val = GetE(parcer);

        if(parcer -> expr[parcer -> counter] != ')') {
            SyntaxError();
        }
        printf("Ending skobka at %d!\n", parcer -> counter);
        printf("next symbol is: %c\n", parcer -> expr[parcer -> counter + 1]);

        parcer -> counter++;
        return val;

    } else if(parcer -> expr[parcer -> counter] == 'x') {
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

    while('0' <= parcer -> expr[parcer -> counter] && parcer -> expr[parcer -> counter] <= '9') {

        val = val*10 + parcer -> expr[parcer -> counter] - '0';
        parcer -> counter++;

    }

    if(old_p == parcer -> counter) {
        SyntaxError();
    }
    char val_str[len_value] = {};
    sprintf(val_str, "%d", val);

    return _NUM(val_str);
}

void SyntaxError() {
    printf("Syntaxis error!\n");
    exit(0);
}