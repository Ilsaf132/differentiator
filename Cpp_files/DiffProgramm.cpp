#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Differentiator.h"
#include "DiffProgramm.h"

#define _ENTER_VALUE(type) new_node -> value.type = value; 

Tree* CtorTree(Tree* tree, Node* root) {
    tree = (Tree*) calloc(1, sizeof(Tree));
    tree -> root = root;
    return tree;
}

void DtorTree(Tree* tree) {
    DtorNode(tree -> root);
    free(tree);
}

void DtorNode(Node* node) {
    if(node) {
        DtorNode(node -> right);
        DtorNode(node -> left);
        free(node);
    }
}

Node* NewNode(TYPES type, int value, Node* left, Node* right) {
    Node* new_node = (Node*) calloc(1, sizeof(Node));

    new_node -> type = type;
    if(type == VAR) {
        _ENTER_VALUE(VAR);
    } else if(type == NUM) {
        _ENTER_VALUE(NUM);
    } else {
        _ENTER_VALUE(OPER);
    }
    new_node -> left = left;
    new_node -> right = right;

    return new_node;
}

Node* Diff(Node* node) {

    if(node -> type == NUM) {
        return _NUM(0);
    } 

    if(node -> type == VAR) {
        return _NUM(1);
    }

    switch(node -> value.OPER) {

        case ADD:
            return _ADD(Diff(node -> left), Diff(node -> right));

        case SUB: 
            return _SUB(Diff(node -> left), Diff(node -> right));

        case MUL:
            return MultiplyDiv(node, "*");

        case DIV:
            return MultiplyDiv(node, "/");
 
        case POW:
            return ExponentialDiff(node);

        default:
            printf("No such function\n");
    }
    return NULL;
}

Node* ExponentialDiff(Node* node) {
    
    //разбиение на показательную и степенную
    Node* left = node -> left;
    Node* right = node -> right;

    Node* copy_node = CopyNode(node);

    Node* left_diff = DiffLn(left);
    Node* right_diff = Diff(right);
    Node* left_copy = _LN(CopyNode(left));
    Node* right_copy = CopyNode(right);

    Node* diff_degree = _ADD(_MUL(left_diff, right_copy), _MUL(left_copy, right_diff));

    return _MUL(copy_node, diff_degree);

}

Node* DiffLn(Node* node) {
    return _DIV(Diff(node), node);
}

Node* CopyNode(Node* node) {

    if(!node) {
        printf("Null node!\n");
        return NULL;
    }

    Node* copy_node = (Node*) calloc(1, sizeof(Node));

    copy_node -> type = node -> type;
    copy_node -> value = node -> value;
    copy_node -> left = CopyNode(node -> left);
    copy_node -> right = CopyNode(node -> right);

    return copy_node;
}



Node* MultiplyDiv(Node* node, const char* oper) {

    if(!node) {
        printf("Null node!\n");
        return NULL;
    }

    Node* diff_left = Diff(node -> left);
    Node* diff_right = Diff(node -> right);
    Node* copy_left = CopyNode(node -> left);
    Node* copy_right = CopyNode(node -> right);

    if(!strcmp(oper, "*")) {
        return _ADD(_MUL(diff_left, copy_right), _MUL(diff_right, copy_left));
    }
    if(!strcmp(oper, "/")) {
        return _DIV(_SUB(_MUL(diff_left, copy_right), _MUL(diff_right, copy_left)), _MUL(CopyNode(node -> right), CopyNode(node -> right)));
    } else {
        printf("Not DIV or MUL. Check sending operations!\n");
        return NULL;
    }
}