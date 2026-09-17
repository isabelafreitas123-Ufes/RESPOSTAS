#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

// --------- ANOTACOES AULA PONTEIROS ---------

// & pergunta onde fica essa varavel na memoria

// * acessa o conteudo que o ponteiro esta apontando

// int main()
//     int nota, *pNota;
//     nota = 10;
//     pNota = &nota;
//     printf("- Conteúdo apontado por pNota: %d\n", *pNota);
//     *pNota = 8;
//     printf("- Valor de nota: %d\n", nota);
//

//*pNota = 8 é a mesma coisa que nota = 8

// int *pNota = NULL; -> boa pratica

// --------- EXERCICIO ---------

// Defina e implemente TrocaInterios

int main()
{
    int n1, n2;

    while (scanf("%d %d", &n1, &n2) == 2)
    {
        if (TrocaInterios(&n1, &n2))
        {
            printf("TROCADO: %d %d\n", n1, n2);
        }
        else
        {
            printf("ORIGINAL: %d %d\n", n1, n2);
        }
    }

    return 0;
}


// int main(){
//     int a = 10, *pA = NULL;
//     float vFloat = 31.54;

//     pA = &a;


//     return 0;
// }
