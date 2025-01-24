#ifndef LEXICAL_ANALYSIS_
#define LEXICAL_ANALYSIS_

#include "Differentiator.h"

struct Lexical {
    TYPES type;
    VALUE value;
};

Lexical* LexicalReadStr(char* expr, Lexical* reader);   
bool ReadNum(char* expr, int* cnt_str, int* read_num);



#endif //LEXICAL_ANALYSIS_