#ifndef DIFFER_
#define DIFFER_

const int len_value = 50;

enum TYPES {
    VAR,
    NUM,
    OPER
};

struct Node {
    TYPES type;
    char* value;
    Node* left;
    Node* right;
};

struct Tree {
    Node* root;
    int counter;
};

#endif //DIFFER_