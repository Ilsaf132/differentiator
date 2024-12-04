#ifndef GRAPH_DUMP_
#define GRAPH_DUMP_

#include <stdio.h>
#include "Differentiator.h"

void ArrowsBtwNodes(Node* node, FILE* file_dump);
void RecursionNode(struct Node* node, FILE* file_dump);
void GraphDump(Node* node);
void MySystem(const char* str, int number_dump);
void PrintfDump(FILE* file_dump, struct Node* node, const char* type_str, const char* color);


#endif //GRAPH_DUMP_
