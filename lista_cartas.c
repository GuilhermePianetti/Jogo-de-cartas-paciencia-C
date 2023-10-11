#include "lista_cartas.h"
#include <time.h>

// Funcao para criar uma lista vazia
void criar_lista(lista* l){
    l->primeiro = NULL;
    l->ultimo = NULL;
}


// Funcao para verificar se a lista esta vazia (retorna 1 se vazia, 0 se nao vazia)
int lista_e_vazia(lista* l){
    if(l->primeiro == NULL){
        return 1; // Lista esta vazia
    }
    else{
        return 0; // Lista nao esta vazia
    }
}

// Funcao para retornar o tamanho da lista
int retornar_tam(lista* l){
    if(lista_e_vazia(l)){
        return 0; // Lista esta vazia, tamanho e 0
    }
    else{
        int a = 1;
        celula* aux = l->primeiro;
        while(aux->prox != NULL){
            a++;
            aux = aux->prox;
        }
        return a; // Retorna o tamanho da lista
    }
}

// Funcao para retornar o topo da lista (primeira carta)
int retornar_topo(lista* l, Carta* carta_saida){
    if(lista_e_vazia(l)){
        return 0; // Lista esta vazia, nao e possivel retornar o topo
    }
    else{
        *carta_saida = l->primeiro->carta;
        return 1; // Retorna o topo com sucesso
    }
}

// Funcao para retornar a carta em uma posicao especifica da lista (Fazer verificacao se a posicao e maior que o tamanho da listam ou se for menor)
// Refere-se a carta da posicao n
int retornar_carta_qualquer(lista* l, Carta* carta_saida, int n){
    if(lista_e_vazia(l) || n>(retornar_tam(l))){
        return 0; // Lista esta vazia, nao e possivel retornar a carta
    }
    else{
        celula* aux = l->primeiro;
        for(int i = 1; i < n; i++){
            aux = aux->prox;
        }
        *carta_saida = aux->carta;
        return 1; // Retorna a carta com sucesso
    }
}

// Funcao para adicionar uma carta no topo da lista
void adicionar_topo(lista* l, Carta nova_carta){
    if(lista_e_vazia(l)){
        celula* nova_c = (celula*)malloc(sizeof(celula));
        nova_c->carta = nova_carta;
        nova_c->prox = l->primeiro;
        l->primeiro = nova_c;
        l->ultimo = nova_c;
    }
    else{
        celula* nova_c = (celula*)malloc(sizeof(celula));
        nova_c->carta = nova_carta;
        nova_c->prox = l->primeiro;
        l->primeiro = nova_c;
    }
}

// Funcao para retirar a carta no topo da lista e armazena-la em carta_retirada
/* Precisa de um ponteiro para a Carta para receber a carta retirada */
int retirar_topo(lista* l, Carta* carta_retirada){
    if(lista_e_vazia(l)){
        return 0; // Lista esta vazia, nao e possivel retirar o topo
    }
    else{
        celula* aux = l->primeiro;
        *carta_retirada = l->primeiro->carta;
        l->primeiro = aux->prox;
        free(aux); // Libera a memoria da celula retirada
        if(lista_e_vazia(l)){
            l->ultimo = NULL;
        }
        return 1; // Retira o topo com sucesso
    }
}

/*
1: Verificacao se a operacao e possivel
2: Criacao de dois ponteiros para auxiliar nas trocas entre as listas e uma
    variavel 'a' que guarda o parametro se a lista receptora esta ou nao vazia
    para que ao final o valor ultimo seja ou nao alterado.
3: Um for para percorrer a lista encadeada e apontar para o ultimo elemento a ser transportado.
4: Operacoes de redirecionamento do trecho da lista.
5: Caso a lista receptora fosse vazia no inicio, atualiza o valor do ponteiro ultimo
*/

// Funcao para transferir um numero especifico de cartas de l_saida para l_entrada
int transferir_cartas(lista* l_saida, lista* l_entrada, int quantidade){
    if((lista_e_vazia(l_saida)) || (quantidade > retornar_tam(l_saida))){
        return 0; // Nao e possivel transferir as cartas
    }
    else{
        celula* aux_primeiro_entrada = l_entrada->primeiro;
        celula* aux_ultima_saida;
        int estado_inicial_l_entrada = 0;
        if(lista_e_vazia(l_entrada)){
            estado_inicial_l_entrada++;
        }
        l_entrada->primeiro = l_saida->primeiro;
        for(int i = 1; i < quantidade; i++){
            l_saida->primeiro = l_saida->primeiro->prox;
        }
        aux_ultima_saida = l_saida->primeiro;
        aux_ultima_saida = l_saida->primeiro;
        l_saida->primeiro = l_saida->primeiro->prox;
        aux_ultima_saida->prox = aux_primeiro_entrada;
        if(estado_inicial_l_entrada != 0){
            l_entrada->ultimo = aux_ultima_saida;
        }
        if(lista_e_vazia(l_saida)){
            l_saida->ultimo = NULL;
        }
        return 1; // Transferencia de cartas bem-sucedida
    }
}

// Funcao para embaralhar as cartas na lista
int embaralha(lista* l) {
    if (lista_e_vazia(l)) {
        return 0;
    } else {
        int tamanho = retornar_tam(l);
        celula* aux = l->primeiro;
        Carta* p = (Carta*)malloc(tamanho * sizeof(Carta));

        for (int i = 0; i < tamanho; i++) {
            p[i] = aux->carta;
            aux = aux->prox;
        }

        srand(time(NULL)); // Inicializa o gerador de numeros aleatarios

        for (int i = tamanho - 1; i > 0; i--) {
            int j = rand() % (i + 1);
            Carta temp = p[i];
            p[i] = p[j];
            p[j] = temp;
        }

        aux = l->primeiro;
        for (int i = 0; i < tamanho; i++) {
            aux->carta = p[i];
            aux = aux->prox;
        }

        free(p); // Libera a memoria alocada para p
        return 1; // Indica que o embaralhamento foi bem-sucedido
    }
}

// Funcao para imprimir a lista de cartas
void imprime_lista(lista* l){
    if(lista_e_vazia(l)){
        printf("[XX]");
    }
    else{
        for(celula* aux = l->primeiro; aux != NULL; aux = aux->prox){
            exibir_carta(aux->carta);
        }
    }
}

