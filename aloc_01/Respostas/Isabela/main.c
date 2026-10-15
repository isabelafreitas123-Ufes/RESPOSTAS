#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    int tam;
    int *vetor;
    scanf("%d", &tam);
    vetor = CriaVetor(tam);
    LeVetor(vetor, tam);
    printf("%.2f", CalculaMedia(vetor, tam));
    LiberaVetor(vetor);

    return 0;
}