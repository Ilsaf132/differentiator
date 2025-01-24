#ifndef READ_PARECER_
#define READ_PARCER_

#include "Differentiator.h"
#include "LexicalAnalysis.h"

const int expression_len = 100;

struct Reader {
    Lexical* reader;
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
void SyntaxError(int line);


#endif //READ_PARCER_