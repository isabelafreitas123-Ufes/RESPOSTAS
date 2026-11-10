#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "mapa.h"
#include "celula.h"

#define INICIO_LEITURA_MAPA "INICIO MAPA"
#define FIM_LEITURA_MAPA "FIM MAPA"
#define CADASTRAR_JOGADOR "J"
#define ROLAGEM "ROLAGEM"
#define NOVA_ACAO "E"
#define THE_END "F"

int main()
{
        // ================== CADASTRO DO MAPA ================== //
        // Ler "INICIO MAPA\n"
        Mapa* mapa = criaMapa();
        //ler o mapa = ler as celulas do mapa
        //ate ler "FIM MAPA\n"

        // ================== CADASTRO DOS JOGADORES ================== //
        char indicie[30];
        //ler um indicie
        while(1){
                scanf("%s", indicie);
                if(indicie == THE_END){
                        break;
                }
                if(indicie == CADASTRAR_JOGADOR){

                }
                if(indicie == ROLAGEM){
                        //ler quantas rolagens
                        int qntRolagens;
                        scanf("%d\n", &qntRolagens);
                        
                }
                if(indicie == NOVA_ACAO){
                        //ler qual acao (estado ou relatorio)
                }
        }


        // ================== EXECUCAO DAS ROLAGENS =================== //


        // ================== OUTRAS ACOES ================= //

        return 0;
}