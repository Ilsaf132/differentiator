#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Simplifier.h"
#include "GraphDump.h"
#include "DiffProgramm.h"

void SimplificationTree(Tree* tree) {

    printf("\n\n\nStarted Simplificacy!\n");
    int new_counter = 0;

    while ((new_counter = SimplificationNode(tree -> root)) != 0) {

        GraphDump(tree -> root);
        printf("Trying after counter: %d!\n\n\n", new_counter);
        new_counter = 0;

    }

    printf("END SIMPLIFICATION!\n\n\n");

}


int SimplificationNode(Node* node) {

    int counter = 0;

    if(node && node -> type == OPER) {
        

        printf("Started simple for %p\n", node);

        Node* left = node -> left;
        Node* right = node -> right;

        if(IsBinary(node -> value)) {

            if(left -> type == NUM && right -> type == NUM) {

                printf("OPENED LEFT_RIGHT_NUM!\n");
                LeftRightNum(node, left, right);
                counter++;

            } else if(left -> type == NUM && left -> value.NUM == 1 && node -> value.OPER == MUL) {

                printf("OPENED LEFT_MUL1!\n");
                LeftMul1(node, left, right);
                counter++;

            } else if(right -> type == NUM && right -> value.NUM == 1 && (node -> value.OPER == DIV || node -> value.OPER == MUL)) {

                printf("OPENED RIGHT_MUL_DIV1!\n");
                RightMulDiv1(node, left, right);
                counter++;

            } else if(right -> type == NUM && right -> value.NUM == 0) {

                printf("OPENED RIGHT_ZERO!\n");
                RightZero(node, left, right);
                counter++;

            } else if(left -> type == NUM && left -> value.NUM == 0) {

                printf("OPENED LEFT_ZERO!\n");
                LeftZero(node, left, right);
                counter++;

            } 
            
        } else {

            if (node -> value.OPER == POW && left -> type == NUM && left -> value.NUM == 1) {
                LnLeft1(node, left, right);
            }

        }
        left = node -> left;
        right = node -> right;

        counter += SimplificationNode(left);
        counter += SimplificationNode(right);

        printf("Ended iteration with %d\n", node -> value.NUM);

    } 
    return counter;
}

void LnLeft1(Node* node, Node* left, Node* right) {

    DtorNode(right);
    DtorNode(left);
    node -> type = NUM;
    node -> left = NULL;
    node -> right = NULL;
    node -> value.NUM = 0;

}

void LeftZero(Node* node, Node* left, Node* right) {
    if(node -> value.OPER == DIV || node -> value.OPER == MUL) {

        DtorNode(right);
        DtorNode(left);
        node -> type = NUM;
        node -> left = NULL;
        node -> right = NULL;
        node -> value.NUM = 0;

    } else if(node -> value.OPER == ADD) {

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

    if(node -> value.OPER == DIV) {

        printf("ZERO DIV!\n");
        exit(0);

    }
    
    if(node -> value.OPER == MUL) {
        
        DtorNode(right);
        DtorNode(left);
        node -> type = NUM;
        node -> value.NUM = 0;
        node -> left = NULL;
        node -> right = NULL;   

    } else if(node -> value.OPER == ADD || node -> value.OPER == SUB) {

        DtorNode(right);
        printf("value: %d, left: %p, right: %p\n", left -> value.OPER, left -> left, left -> right);
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
    if(node -> value.OPER == MUL) {

        res = left -> value.NUM*right -> value.NUM;

    } else if(node -> value.OPER == DIV) {

        if(right -> value.NUM == 0) {
            printf("ZERO DIV!\n");
            exit(0);
        }
        res = left -> value.NUM / right -> value.NUM;

    } else if(node -> value.OPER == ADD) {

        res = left -> value.NUM + right -> value.NUM;

    } else if(node -> value.OPER == SUB) {

        res = left -> value.NUM - right -> value.NUM;

    } else if(node -> value.OPER == POW) {

        res = (int) pow(left->value.NUM, right -> value.NUM);

    }
    printf("numbers: %d and %d\n", left -> value.NUM, right -> value.NUM);
    printf("AT %p RESULT: %d\n", node, res);

    node -> value.NUM = res;
    printf("and value: %d\n", node -> value.NUM);
    node -> type = NUM;
    node -> left = NULL;
    node -> right = NULL;
    DtorNode(left);
    DtorNode(right);

    return res;
}

int IsBinary(VALUE value) {
    printf("oper: %d\n", value.OPER);
    if(value.OPER == MUL || value.OPER == DIV || value.OPER == ADD  || value.OPER == SUB || value.OPER == POW) {
        return 1;
    }
    return 0;
}