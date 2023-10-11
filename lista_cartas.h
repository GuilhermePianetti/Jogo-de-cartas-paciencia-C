#ifndef _lista_cartas
#define _lista_cartas
#include <stdlib.h>
#include <stdio.h>
#include "carta.h"

typedef struct Celula{
    Carta carta;
    struct Celula* prox;
}celula;

typedef struct{
    celula* primeiro;
    celula* ultimo;
}lista;

// Funcao usada para criar uma lista
void criar_lista(lista* l);

// Funcao usada para retornar o tamanho de uma lista de cartas
int retornar_tam(lista* l);

// Funcao usada para conferir se uma lista esta ou nao vazia
int lista_e_vazia(lista* l);

// Funcao usada para retornar a carta que esta no topo de uma lista
int retornar_topo(lista* l, Carta* carta_saida);

// Funcao usada para retorna uma carta, que esteja virada para cima, de alguma lista de cartas
int retornar_carta_qualquer(lista* l, Carta* carta_saida, int n);

// Funcao usada para adicionar uma carta ao topo de uma lista
void adicionar_topo(lista* l, Carta nova_carta);

// Funcao usada para retirar uma carta do topo de uma lista
int retirar_topo(lista* l, Carta* carta_retirada);

// Funcao usada para transferir uma ou mais cartas, virada para cima, de uma lista para outra
int transferir_cartas(lista* l_saida, lista* l_entrada, int quantidade);

// Funcao usada para embaralhar as cartas so baralho aleatoriamente
int embaralha(lista* l);

// Funcao usada para imprimir uma lista de cartas
void imprime_lista(lista* l);



#endif
