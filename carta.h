#ifndef CARTA
#define CARTA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Definicao da estrutura Carta
typedef struct {
    char naipe;
    int valor;
    int posicao;
} Carta;

//Funcao parainicializar uma carta
void inicializar_carta(Carta* carta);

// Funcao para criar uma carta
void criar_carta(Carta *carta, char naipe, int valor, int posicao);

// Funcao para retornar o naipe da carta
char retornar_naipe(const Carta *carta);

// Funcao para retornar o valor da carta
int retornar_valor(const Carta *carta);

// Funcao para retornar a posicao da carta
int retornar_posicao(const Carta *carta);

// Funcao para alterar a posicao da carta
void alterar_posicao(Carta *carta);

// Funcao para verificar sequencia de mesmo naipe
bool verificar_sequencia_mesmo_naipe(const Carta *carta1, const Carta *carta2);

// Funcao para verificar sequencia alternada
bool verificar_sequencia_alternada(const Carta *carta1, const Carta *carta2);

// Funcao para exibir a carta
void exibir_carta(Carta carta);

#endif
