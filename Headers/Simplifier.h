#ifndef SIMPLIFIER_
#define SIMPLIFIER_

#include <stdio.h>
#include "Differentiator.h"

void SimplificationTree(Tree* tree);
int SimplificationNode(Node* node);
void LeftZero(Node* node, Node* left, Node* right);
void RightZero(Node* node, Node* left, Node* right);
void RightMulDiv1(Node* node, Node* left, Node* right);
void LeftMul1(Node* node, Node* left, Node* right);
int LeftRightNum(Node* node, Node* left, Node* right);
int IsBinary(VALUE value);
void LnLeft1(Node* node, Node* left, Node* right);

#endif //SIMPLIFIER_