#include <stdio.h>
#include <stdlib.h>
#include "Differentiator.h"
#include "DiffProgramm.h"
#include "GraphDump.h"
#include "Simplifier.h"
#include "ReadParcer.h"


int main() {

    const char* file_read_expr = "Expression.txt";

    Tree* start_tree = 0;
    start_tree = CtorTree(start_tree, NULL);
    StartParcer(file_read_expr, start_tree);
    printf("Success Parcer!\n");

    SimplificationTree(start_tree);
    printf("End SimplificationTree!\n");
    GraphDump(start_tree -> root);
    printf("End graph dump!\n");

    Tree* res_tree = 0;
    Node* res = Diff(start_tree -> root);
    GraphDump(res);

    res_tree = CtorTree(res_tree, res);
    SimplificationTree(res_tree);
    printf("End res!\n");
    GraphDump(res);
    printf("End dump!\n");

    DtorTree(start_tree);
    printf("End root dtor!\n");
    DtorTree(res_tree);
    printf("End res dtor!\n");

    printf("End successfully!\n");
    return 0;
}