#include "carta.h"

void inicializar_carta(Carta* carta){
    carta->valor = 0;
    carta->posicao = 0;
}

// Funcao para criar uma carta
void criar_carta(Carta *carta, char naipe, int valor, int posicao) {
    carta->naipe = naipe;
    carta->valor = valor;
    carta->posicao = posicao;
}

// Funcao para retornar o naipe da carta
char retornar_naipe(const Carta *carta) {
    return carta->naipe;
}

// Funcao para retornar o valor da carta
int retornar_valor(const Carta *carta) {
    return carta->valor;
}

// Funcao para retornar a posicao da carta
int retornar_posicao(const Carta *carta) {
    return carta->posicao;
}

// Funcao para alterar a posicao da carta
void alterar_posicao(Carta *carta) {
    if (carta->posicao == 0) {
        carta->posicao = 1; // Se a posicao for 0 (baixo), mude para 1 (cima)
    } else {
        carta->posicao = 0; // Caso contrario (posicao 1, cima), mude para 0 (baixo)
    }
}

// Funcao para verificar sequencia de mesmo naipe
bool verificar_sequencia_mesmo_naipe(const Carta *carta1, const Carta *carta2) {
    if (carta1->posicao == 1 && carta2->posicao == 1) {
        // Verifica se as cartas t�m o mesmo naipe e o valor da segunda � maior em 1
        return (carta1->naipe == carta2->naipe) && (carta1->valor + 1 == carta2->valor);
    }
    return false;
}

// Funaoo para verificar sequencia alternada
bool verificar_sequencia_alternada(const Carta *carta1, const Carta *carta2) {
    // Verifica se ambas as cartas estao viradas para cima (posicao 1)
    if (carta1->posicao == 1 && carta2->posicao == 1) {
        // Verifica se as cartas tem naipes de cores diferentes e se o valor da segunda carta
        // E maior em 1 em relacao a primeira carta.
        bool naipes_de_cores_diferentes =
            ((carta1->naipe == 'C' || carta1->naipe == 'O') && (carta2->naipe == 'P' || carta2->naipe == 'E')) ||
            ((carta1->naipe == 'P' || carta1->naipe == 'E') && (carta2->naipe == 'C' || carta2->naipe == 'O'));

        return naipes_de_cores_diferentes && (carta1->valor + 1 == carta2->valor);
    }
    return false; // Se alguma das cartas estiver virada para baixo (posicao 0), retorna falso.
}

// Funcao para exibir a carta
void exibir_carta(Carta carta) {
    if(carta.valor == 0){
        printf("[XX]");
    }
    else{
        if (carta.posicao == 1) {
        printf("[%d %c]", carta.valor, carta.naipe);
        } 
        else {
            printf("[ ]"); // Carta virada para baixo
        }
    }
    
}
