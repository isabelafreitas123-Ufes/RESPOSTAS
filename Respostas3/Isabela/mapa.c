#include "mapa.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "celula.h"

/**
 * Mapa linear (trilha) composto por células. As células informadas são numeradas de 1 a N.
 * O Início (casa 0) e o Fim (casa N + 1) não possuem ação e não são armazenados como células.
 */
struct Mapa
{
    Celula **listaDeCelulas;
    int qntCelulas;
};

/**
 * @brief Aloca dinamicamente um mapa sem nenhuma célula (vetor de células NULL e quantidade 0)
 * @return Ponteiro para o mapa criado
 */
Mapa *criaMapa()
{
    Mapa *m = (Mapa *)calloc(1, sizeof(Mapa));
    m->qntCelulas = 1;
    m->listaDeCelulas = (Celula**) calloc (m->qntCelulas, sizeof(Celula*));
    m->listaDeCelulas[0] = NULL;
    return m;
}

/**
 * @brief Cria uma célula com a ação e as funções de callback informadas (criaCelula), aumenta o
 * vetor de células do mapa em uma posição (realloc) e coloca a nova célula no final. A primeira
 * célula inserida corresponde à casa 1, a segunda à casa 2 e assim por diante.
 * @param m Mapa
 * @param acao Uma ação genérica (considerando que existe mais de um tipo de ação)
 * @param executa Função de callback que executa a ação sobre um jogador
 * @param imprime Função de callback que imprime a ação
 * @param desaloca Função de callback que desaloca a ação
 */
void insereCelulaMapa(Mapa *m, void *acao, func_ptr_executa executa, func_ptr_imprime imprime, func_ptr_desaloca desaloca)
{
    Celula *c = criaCelula(acao, executa, imprime, desaloca);
    m->qntCelulas++;
    m->listaDeCelulas = (Celula **)realloc(m->listaDeCelulas, m->qntCelulas * sizeof(Celula *));
    // =============== DEIXO A CASA 0 SEM NADA???????? ===================//
    m->listaDeCelulas[m->qntCelulas - 1] = c;
}

/**
 * @brief Retorna a quantidade N de células informadas do mapa (sem contar Início e Fim)
 * @param m Mapa
 * @return Quantidade de células
 */
int obtemQtdCelulasMapa(Mapa *m)
{
    return m->qntCelulas - 1;
}

/**
 * @brief Retorna o número da casa do Fim do mapa, que é N + 1
 * @param m Mapa
 * @return Posição do Fim
 */
int obtemPosicaoFimMapa(Mapa *m)
{
    return m->qntCelulas;
}

/**
 * @brief Retorna a célula correspondente à casa informada. Como as casas começam em 1, a casa
 * 'posicao' fica no índice 'posicao - 1' do vetor. Para o Início (0), o Fim (N + 1) ou qualquer
 * posição fora do intervalo de 1 a N, retorna NULL.
 * @param m Mapa
 * @param posicao Casa desejada (1 a N)
 * @return Célula da casa ou NULL se a posição for o Início, o Fim ou inválida
 */
Celula *obtemCelulaMapa(Mapa *m, int posicao)
{
    if (posicao < 1 || posicao >= m->qntCelulas)
    {
        return NULL;
    }
    return m->listaDeCelulas[posicao];
}

/**
 * @brief Retorna o jogador que ocupa a casa informada. Se a casa não for uma célula válida
 * (Início, Fim ou fora do mapa), retorna NULL, ou seja, o Início e o Fim nunca são considerados ocupados.
 * @param m Mapa
 * @param posicao Casa desejada
 * @return Jogador ocupante ou NULL
 */
Jogador *obtemOcupanteMapa(Mapa *m, int posicao)
{
    if (posicao < 1 || posicao >= m->qntCelulas)
    {
        return NULL;
    }
    return obtemOcupanteCelula(m->listaDeCelulas[posicao]);
}

/**
 * @brief Retira o jogador de sua célula atual, caso a célula exista e o ocupante dela seja esse
 * jogador. Não altera a posição armazenada no jogador.
 * @param m Mapa
 * @param j Jogador
 */
void retiraJogadorMapa(Mapa *m, Jogador *j)
{
    if(obtemOcupanteMapa(m, obtemPosicaoJogador(j))){
        // se o nome do jogador ocupante da celula que consta a posicao do jogador dado é igual ao nome do jogador dado eu desocupo
        if (strcmp(obtemNomeJogador(obtemOcupanteCelula(m->listaDeCelulas[obtemPosicaoJogador(j)])), obtemNomeJogador(j)) == 0)
        {
            // DESOCUPA A CÉLULA
            defineOcupanteCelula(m->listaDeCelulas[obtemPosicaoJogador(j)], NULL);
        }
    }
}

/**
 * @brief Move o jogador para a casa informada: retira o jogador da célula atual (retiraJogadorMapa),
 * atualiza a posição do jogador e, se a nova casa for uma célula (1 a N), marca o jogador como seu
 * ocupante. Não verifica disputas nem executa ações.
 * @param m Mapa
 * @param j Jogador
 * @param posicao Casa de destino (0 a N + 1)
 */
void moveJogadorMapa(Mapa *m, Jogador *j, int posicao)
{
    retiraJogadorMapa(m, j);
    definePosicaoJogador(j, posicao);
    if (posicao >= 1 && posicao < m->qntCelulas)
    {
        defineOcupanteCelula(m->listaDeCelulas[posicao], j);
    }
}

/**
 * @brief Aplica a regra de recuo: começando na casa 'origem - 1', vai voltando uma casa enquanto a
 * casa estiver ocupada e for maior que 0. O jogador é movido (moveJogadorMapa) para a primeira casa
 * livre encontrada ou para o Início (casa 0). O recuo não dispara ações nem disputas.
 * @param m Mapa
 * @param j Jogador que deve recuar
 * @param origem Casa a partir da qual o jogador recua (a casa em que ele estava)
 */
void recuaJogadorMapa(Mapa *m, Jogador *j, int origem)
{
    if (origem < 1 || origem >= m->qntCelulas)
    {
        printf("ERRO\n");
    }
    int i;
    for (i = origem - 1; i > 0; i--)
    {
        if (!estaOcupadaCelula(m->listaDeCelulas[i]))
        {
            moveJogadorMapa(m, j, i);
            break;
        }
    }
    if (i < 1)
    {
        moveJogadorMapa(m, j, 0);
    }
}

/**
 * @brief Percorre as células do mapa, da casa 1 até a casa N, imprimindo cada uma com imprimeCelula
 * @param m Mapa
 */
void imprimeCelulasMapa(Mapa *m)
{
    int i;
    for (i = 1; i < m->qntCelulas; i++)
    {
        imprimeCelula(m->listaDeCelulas[i], i);
    }
}

/**
 * @brief Desaloca cada célula do mapa (desalocaCelula), o vetor de células e o próprio mapa.
 * Os jogadores ocupantes não são desalocados.
 * @param m Mapa
 */
void desalocaMapa(Mapa *m)
{
    if (m)
    {
        if (m->listaDeCelulas)
        {
            for (int i = 1; i < m->qntCelulas; i++)
            {
                    desalocaCelula(m->listaDeCelulas[i]);
            }
        }
        free(m->listaDeCelulas);
        free(m);
    }
}
