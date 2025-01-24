#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Differentiator.h"
#include "LexicalAnalysis.h"

#define READ_INSERT(insert_oper, insert_type)   reader[cnt_arr].type = insert_type;\
                                                reader[cnt_arr++].value.insert_type = insert_oper;


Lexical* LexicalReadStr(char* expr, Lexical* reader) {   

    const char* operations[] = {"+", "/", "-", "*", "^", "(", ")", "sin", "cos", "ln"};

    int cnt_str = 0;
    int cnt_arr = 0;
    int read_num = 0;
    int end_marker = 1;
    int len_expr = strlen(expr);

    while(cnt_str < len_expr && end_marker) {
        int is_not_oper = 1;

        for (int i = 0; i < OPERATION_NUMBER; i++) {
            // printf("operation: %s\n", operations[i]);
            if (!strncmp(operations[i], expr + cnt_str, strlen(operations[i]))) {

                // printf("I am here with strlen %d!\n", strlen(operations[i]));
                READ_INSERT(i, OPER);
                cnt_str += strlen(operations[i]);
                is_not_oper = 0;
                printf("isn`t_oper: %d symbol: %s\n", is_not_oper, operations[i]);
                break;

            }
        }

        printf("symbol: %c\n", expr[cnt_str]);

        if(is_not_oper) {

            switch (expr[cnt_str]) {
                case 'x':
                    printf("found x!\n");
                    READ_INSERT('x', VAR);
                    cnt_str++;
                    break;

                case ' ':

                    cnt_str++;
                    break;

                case '$':

                    READ_INSERT('$', OPER);
                    end_marker = 0;
                    printf("end of lexical analysis!\n");
                    break;

                default:

                    if(ReadNum(expr, &cnt_str, &read_num)) {

                        reader[cnt_arr].type = NUM;
                        reader[cnt_arr++].value.NUM = read_num;
                        read_num = 0;

                    } else {

                        printf("wrong symbol!\n");

                    }
                    break;
            }  

        }
    }
    printf("End Lexical Reading succesfully!\n");

    for (int i = 0; i < cnt_arr; ++i) {
       printf("function after end value: %d, type %d\n", reader[i].value, reader[i].type);
    }
    
    return reader;

}

bool ReadNum(char* expr, int* cnt_str, int* read_num) {

    if(expr[*cnt_str] >= '0' && expr[*cnt_str] <= '9') {

        printf("number: %c\n", expr[*cnt_str]);
    
        while(expr[*cnt_str] >= '0' && expr[*cnt_str] <= '9') {

            *read_num = 10*(*read_num) + expr[*cnt_str] - '0';
            (*cnt_str)++;

        }
        return true;
    
    }
    return false;
}