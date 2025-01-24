#ifndef DIFFER_
#define DIFFER_

const int len_value = 50;
const int len_start_str = 60;

enum TYPES {
    VAR,
    NUM,
    OPER
};

enum OPERATION {
    ADD,
    DIV,
    SUB,
    MUL,
    POW,
    OPEN_BRACKET,
    CLOSE_BRACKET,
    SIN,
    COS,
    LN,
    OPERATION_NUMBER
};

union VALUE {
    int OPER;
    int VAR;
    int NUM;
};

struct Node {
    TYPES type;
    VALUE value;
    Node* left;
    Node* right;
};

struct Tree {
    Node* root;
};

#endif //DIFFER_