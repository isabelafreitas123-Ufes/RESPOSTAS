#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
    int col, lin;
    int**matrix;
    scanf("%d %d\n", &lin, &col);
    matrix = CriaMatriz(lin, col);
    LeMatriz(matrix, lin, col);
    ImprimeMatrizTransposta(matrix, lin, col);
    LiberaMatriz(matrix, lin);

    return 0;
}