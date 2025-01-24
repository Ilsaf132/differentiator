#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GraphDump.h"

const char* file_name_dump = "Dump.dot";
const char* dump_html_name = "Dump.html";

void ArrowsBtwNodes(Node* node, FILE* file_dump) {
    if(node) {
        if(node -> left) {
            fprintf(file_dump, "    \"%p\" -> \"%p\"[label = \"left\", fillcolor = \"red\"]\n", node, node -> left);
            fprintf(file_dump, "    \"%p\" -> \"%p\"[label = \"right\", fillcolor = \"green\"]\n", node, node -> right);
        }
        
        ArrowsBtwNodes(node -> left, file_dump);
        ArrowsBtwNodes(node -> right, file_dump);
    }
}

void RecursionNode(struct Node* node, FILE* file_dump) {

    if(node) {

        if(node -> type == OPER) {

            PrintfDump(file_dump, node, "OPERATION", "red");

        } else if(node -> type == VAR) {

            PrintfDump(file_dump, node, "VARIABLE", "grey");

        } else if(node -> type == NUM) {

            PrintfDump(file_dump, node, "NUMBER", "green");

        }


        RecursionNode(node -> left, file_dump);
        RecursionNode(node -> right, file_dump);
    }

}

void PrintfDump(FILE* file_dump, struct Node* node, const char* type_str, const char* color) {
    fprintf(file_dump, "    \"%p\" [shape = Mrecord, style = \"filled\", label = \" { address = %p | { type = %s | ", node, node, type_str);

    if(!strcmp(type_str, "NUMBER")) {

        fprintf(file_dump, "value = %d }", node -> value.NUM); // Написать функцию перевода из enum в oper, num, var

    } else if (!strcmp(type_str, "VARIABLE")) {

        fprintf(file_dump, "value = x }");

    } else {

        fprintf(file_dump, "value = %s }", GetFuncPrintf(node -> value.OPER));

    }
    fprintf(file_dump, " | { left = %p | right = %p } } \", fillcolor = \"%s\"]\n", node -> left, node -> right, color);
}

const char* GetFuncPrintf(int oper) {
    const char* operations[] = {"+", "/", "-", "*", "^", "(", ")", "sin", "cos", "ln"};
    return operations[oper];
}

void GraphDump(Node* node) {
    FILE* file_dump = fopen(file_name_dump, "w");
    
    fprintf(file_dump, "digraph tree {\n");

    RecursionNode(node, file_dump);
    ArrowsBtwNodes(node, file_dump);

    fprintf(file_dump, "}");

    fclose(file_dump);

    static int number_dump = 0;

    MySystem("dot Dump.dot -Tpng -o Graphs\\Dump%02d.png", number_dump);

    FILE* dump_html = fopen(dump_html_name, "w+");

    if(number_dump == 0) {
        fprintf(dump_html, "<pre>\n");
    }

    fprintf(dump_html, "\n<img src = \"Graphs\\Dump%02d.png\"/>\n", number_dump);
    number_dump++;


}

void MySystem(const char* str, int number_dump) {
    char command_dot[52] = "";

    sprintf(command_dot, str, number_dump);

    system(command_dot);
}