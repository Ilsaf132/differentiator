#ifndef DIFF_
#define DIFF_

#include "Differentiator.h"

#define _NUM(value) NewNode(NUM, value, NULL, NULL)
#define _VAR(value) NewNode(VAR, 'x', NULL, NULL)
#define _DEG(left, right) NewNode(OPER, POW, left, right)
#define _LN(node) NewNode(OPER, LN, node, NewNode(NUM, 0, NULL, NULL))
#define _ADD(left, right) NewNode(OPER, ADD, left, right)
#define _DIV(left, right) NewNode(OPER, DIV, left, right)
#define _SUB(left, right) NewNode(OPER, SUB, left, right)
#define _MUL(left, right) NewNode(OPER, MUL, left, right)

Node* NewNode(TYPES type, int value, Node* left, Node* right);
Node* Diff(Node* node);
Node* DiffLn(Node* node);
Tree* CtorTree(Tree* tree, Node* root);
Node* CopyNode(Node* node);
Node* MultiplyDiv(Node* node, const char* oper);
Node* ExponentialDiff(Node* node);
void DtorTree(Tree* tree);
void DtorNode(Node* node);

#endif // DIFF_