#ifndef _mesa
#define _mesa
#include "lista_cartas.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    lista* baralho;
    lista* descarte;
    lista* base[4];
    lista* tableau[7];
    int pontuacao;
}mesa;

//Funcao usada para inicializar a mesa do jogo
void inicializar_mesa(mesa* mesa);

//Funcao usada para criar o baralho e embaralhar as cartas, detribuindo na mesa do jogo
void carregar_baralho_aleatorio(mesa* mesa);

//Funcao usada para distribuir cartas em suas respectivas listas e inverter a posicoes necessarias
void preparar_mesa(mesa* mesa);

//Funcao usada para verificar se todas as quatro bases tem os naipes diferentes e todas as 13 cartas
int verificar_vitoria(mesa* mesa);

//Funcao usada para imprimir a mesa do jogo no terminal
void exibir_mesa(mesa* mesa);

//Funcao usada para comprar uma carta do baralho, virada para baixo, e coloca-la virada para cima no descarte
int comprar_carta(mesa* mesa);

//Funcao usada para mover uma carta do descarte para a base
int mov_descarte_base(mesa* mesa);//requer qual a base a ser passada (valores entre 1 e 4)

//Funcao usada para mover uma carta do descarte para o tableau
int mov_descarte_tableau(mesa* mesa, int coluna_tableau);

//Funcao usada para mover uma carta do tableau para a base
int mov_tableau_base(mesa* mesa, int coluna_tableau);

//Funcao usada para mover uma carta da base para o tableau
int mov_base_tableau(mesa* mesa, char naipe, int coluna_base);

//Funcao usada para mover uma ou mais cartas de uma coluna do tableau para outra coluna do tableau
int mov_dentro_tableau(mesa* mesa, int quantidade_cartas, int coluna_saida, int coluna_entrada);

//Funcao usada para carregar uma baralho de um arquivo
void carregar_baralho(FILE* arquivo, mesa* m);

//Funcao usada para imprimir no terminal no inicio e no final de um jogo do arquivo
void atualizar_mesa(mesa * mesa);

#endif