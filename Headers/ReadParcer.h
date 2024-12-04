#ifndef READ_PARECER_
#define READ_PARCER_

#include "Differentiator.h"

const int expression_len = 100;

struct Reader {
    char expr[expression_len];
    int counter;
};

void StartParcer(const char* file_read, Tree* start_tree);
Node* GetG(Reader* parcer);
Node* GetE(Reader* parcer);
Node* GetV(Reader* parcer);
Node* GetD(Reader* parcer);
Node* GetP(Reader* parcer);
Node* GetN(Reader* parcer);
Node* GetT(Reader* parcer);
void SyntaxError();


#endif //READ_PARCER_