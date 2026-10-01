#include "tela.h"
#include "botao.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void SalvarDados(){
    printf("- Botao de SALVAR dados ativado!\n");
}
void ExcluirDados(){
    printf("- Botao de EXCLUIR dados ativado!\n");
    
}
void AbrirMenu(){
    printf("- Botao de OPCOES ativado!\n");
    
}

int main(){
    char texto[MAX_TAM_TEXTO], cor[7];
    Botao b1, b2, b3;
    Tela t;
    strcpy(texto, "Salvar");
    strcpy(cor, "FFF");
    //botao salvar
    b1 = CriarBotao(texto, 12, cor, CLICK, SalvarDados);
    strcpy(texto, "Excluir");
    strcpy(cor, "000");
    b2 = CriarBotao(texto, 18, cor, CLICK, ExcluirDados);
    strcpy(texto, "Opcoes");
    strcpy(cor, "FF0000");
    b3 = CriarBotao(texto, 10, cor, LONGO_CLICK, AbrirMenu);
    
    t = CriarTela(200, 400);
    RegistraBotaoTela(&t, b1);
    RegistraBotaoTela(&t, b2);
    RegistraBotaoTela(&t, b3);

    DesenhaTela(t);
    OuvidorEventosTela(t);



    return 0;
}