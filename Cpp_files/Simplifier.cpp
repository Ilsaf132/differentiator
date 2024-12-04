#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Simplifier.h"
#include "GraphDump.h"
#include "DiffProgramm.h"

void SimplificationTree(Tree* tree) {

    printf("Trying to open counter!\n");
    int new_counter = tree -> counter;
    printf("Started Simplificacy!\n");

    while ((new_counter = SimplificationNode(tree -> root, new_counter)) != tree -> counter) {

        GraphDump(tree -> root);
        printf("Trying after counter: %d!\n\n\n", new_counter);
        tree -> counter = new_counter;

    }

}

int SimplificationNode(Node* node, int counter) {

    if(node && node -> type == OPER) {

        printf("Started simple for %p\n", node);

        Node* left = node -> left;
        Node* right = node -> right;
        if(IsBinary(node -> value)) {

            if(left -> type == NUM && right -> type == NUM) {

                LeftRightNum(node, left, right);
                printf("OPENED LEFT_RIGHT_NUM!\n");
                counter++;

            } else if(!strcmp(left -> value, "1") && !strcmp(node -> value, "*")) {

                LeftMul1(node, left, right);
                printf("OPENED LEFT_MUL1!\n");
                counter++;

            } else if(!strcmp(right -> value, "1") && (!strcmp(node -> value, "/") || !strcmp(node -> value, "*"))) {

                RightMulDiv1(node, left, right);
                printf("OPENED RIGHT_MUL_DIV1!\n");
                counter++;

            } else if(!strcmp(right -> value, "0")) {

                RightZero(node, left, right);
                printf("OPENED RIGHT_ZERO!\n");
                counter++;

            } else if(!strcmp(left -> value, "0")) {

                LeftZero(node, left, right);
                printf("OPENED LEFT_ZERO!\n");
                counter++;

            } 
            left = node -> left;
            right = node -> right;
            
        }

        counter = SimplificationNode(left, counter);
        counter = SimplificationNode(right, counter);

        printf("Ended iteration with %s\n", node -> value);

    } 
    return counter;
}

void LeftZero(Node* node, Node* left, Node* right) {
    if(!strcmp(node -> value, "/") || !strcmp(node -> value, "*")) {

        DtorNode(right);
        DtorNode(left);
        node -> type = NUM;
        node -> left = NULL;
        node -> right = NULL;
        strcpy(node -> value, "0");

    } else if(!strcmp(node -> value, "+")) {

        DtorNode(left);
        node -> type = right -> type;
        node -> value = right -> value;
        node -> type = right -> type;
        node -> left = right -> left;
        node -> right = right -> right;
        free(right);

    }
}

void RightZero(Node* node, Node* left, Node* right) {

    if(!strcmp(node -> value, "/")) {

        printf("ZERO DIV!\n");
        exit(0);

    }
    
    if(!strcmp(node -> value, "*")) {
        
        DtorNode(right);
        DtorNode(left);
        node -> type = NUM;
        strcpy(node -> value, "0");
        node -> left = NULL;
        node -> right = NULL;   

    } else if(!strcmp(node -> value, "+") || !strcmp(node -> value, "-")) {

        DtorNode(right);
        printf("value: %s, left: %p, right: %p\n", left -> value, left -> left, left -> right);
        node -> type = left -> type;
        node -> value = left -> value;
        node -> left = left -> left;
        node -> right = left -> right;
        free(left);
    }
}

void RightMulDiv1(Node* node, Node* left, Node* right) {

    node -> value = left -> value;
    node -> type = left -> type;
    node -> left = left -> left;
    node -> right = left -> right;
    free(left);
    free(right);

}

void LeftMul1(Node* node, Node* left, Node* right) {
    
        node -> value = right -> value;
        node -> type = right -> type;
        node -> left = right -> left;
        node -> right = right -> right;
        free(left);
        free(right);
}

int LeftRightNum(Node* node, Node* left, Node* right) {
    int res = 0;
    if(!strcmp(node -> value, "*")) {

        res = atoi(left -> value)*atoi(right -> value);

    } else if(!strcmp(node -> value, "/")) {

        if(!strcmp(right -> value, "0")) {
            printf("ZERO DIV!\n");
            exit(0);
        }
        res = atoi(left -> value)/atoi(right -> value);

    } else if(!strcmp(node -> value, "+")) {

        res = atoi(left -> value)+atoi(right -> value);

    } else if(!strcmp(node -> value, "-")) {

        res = atoi(left -> value)-atoi(right -> value);

    } else if(!strcmp(node -> value, "^")) {

        res = pow(atoi(left->value), atoi(right -> value));

    }
    printf("numbers: %d and %d\n", atoi(left -> value), atoi(right -> value));
    printf("AT %p RESULT: %d\n", node, res);

    snprintf(node -> value, len_value, "%d", res);
    printf("and value: %s\n", node -> value);
    node -> type = NUM;
    node -> left = NULL;
    node -> right = NULL;
    DtorNode(left);
    DtorNode(right);

    return res;
}

int IsBinary(char* value) {
    printf("oper: %s\n", value);
    if(!strcmp(value, "*") || !strcmp(value, "/") || !strcmp(value, "+") || !strcmp(value, "-") || !strcmp(value, "^")) {
        return 1;
    }
    return 0;
}