#include "mesa.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(){

    mesa mesa;
    inicializar_mesa(&mesa);
    int modo;

    //Metodo usado para o usuario escolher o modo de jogo que deseja executar
    while (1) { // Loop infinito ate que o usuario forneca uma entrada valida
        printf("\nInsira o modo de jogo (0 interativo // 1 arquivo): ");
        scanf("%d", &modo);

        if (modo == 0 || modo == 1) {
            break; // Sai do loop se o modo de jogo for 0 ou 1
        } else {
            printf("Entrada invalida. Por favor, escolha 0 ou 1.\n");
        }
    }

    // Executa o bloco do jogo interativo
    if(modo == 0){
        printf("\n\nModo de jogo:\n\nO jogo funciona com base em codigos, sendo eles:\nCC: Comprar carta\nDB: Mover do Descarte para a Base\nDT: Mover do Descarte para o Tableau\nTB: Mover do Tableau para a Base\nBT: Mover da Base para o Tableau\nTT: Mover dentro do Tableau\nEX: Desistir do jogo\n");
        char jogada[3];
        carregar_baralho_aleatorio(&mesa);
        preparar_mesa(&mesa);

        char cc[3] = {'C', 'C'};
        char db[3] = {'D', 'B'};
        char dt[3] = {'D', 'T'};
        char tb[3] = {'T', 'B'};
        char bt[3] = {'B', 'T'};
        char tt[3] = {'T', 'T'};
        char ex[3] = {'E', 'X'};

        exibir_mesa(&mesa);

        //Inicia o jogo e so sera encerrado quando a condicao de vitoria for alcancada
        while(verificar_vitoria(&mesa) == 0){
            
            int condicao = 0;
            int func = 0;

            //Meio pelo qual o usuario escolhera qual acao realizar
            printf("Insira sua jogada: ");
            scanf("%s", jogada);
            
            //Se o usuario digitar CC ele comprara uma carta do baralho
            if((strcmp(cc, jogada) == 0)){
                comprar_carta(&mesa); // Chama a funcao comprar carta
                condicao++; // Icrementa a condicao se for verdadeiro
            }

            //Se o usuacrio digitar DB ele move uma carta do descarte para a base
            else if(strcmp(db, jogada) == 0){
                func = mov_descarte_base(&mesa); // Chama a funcao para mover do descarte para base
                if(func!=0){
                    mesa.pontuacao = mesa.pontuacao + 10; // Se a acao for feita acrescenta 10 pontos na pontuacao
                    condicao++; // Incrementa a condicao se for verdadeiro
                }
            }

            //Se o usuacrio digitar DT ele move uma carta do descarte para a tableau
            else if(strcmp(dt, jogada) == 0){
                int coluna;
                printf("Insira a coluna de destino: ");
                scanf("%d", &coluna); // Le qual coluna de destino o usuario deseja
                func = mov_descarte_tableau(&mesa, coluna); // Chama a funcao para mover do descarte para o tableau
                if(func!=0){
                    mesa.pontuacao = mesa.pontuacao + 5; // Acrescenta 5 pontos na pontuacao se a funcao retornar verdadeiro
                    condicao++; // Incrmente a condicao se a funcao for realizada
                }
                
                
            }

            //Se o usuacrio digitar TB ele move uma carta do tableau para a base
            else if(strcmp(tb, jogada) == 0){
                int coluna;
                printf("Insira a coluna de saida: "); // Le de qual coluna vai ser retirada a carta
                scanf("%d", &coluna);
                func = mov_tableau_base(&mesa, coluna); // Chama a funcao para mover do tableau para bae
                if(func!=0){
                    mesa.pontuacao = mesa.pontuacao + 10; // Se a funcao for realizada acrescenta 10 pontos na pontuacao
                    condicao++; // Incremente a condicao se a funcao for realizada
                }
                
            }

            //Se o usuacrio digitar BT ele move uma carta da base para o tableau
            else if(strcmp(bt, jogada) == 0){
                char n;
                int coluna;
                printf("Insira o naipe e a coluna de destino: ");
                scanf(" %c %d", &n, &coluna); // Le qual o naipe da carta a ser retirada da base e para qual coluna vai ser movida
                func = mov_base_tableau(&mesa, n, coluna); // Chama a funcao para mover de uma base para o tableau
                if(func!=0){
                    mesa.pontuacao = mesa.pontuacao - 15; // Se a funcao for realizada descresce 5 pontos na pontuacao
                    condicao++; // Incrementa a condicao se a funcao retornar verdadeiro
                }

            }

            //Se o usuacrio digitar TT ele move carta da coluna de um tableau para outra coluna do tableau
            else if(strcmp(tt, jogada) == 0){
                int quant;
                int coluna_s;
                int coluna_e;
                printf("Insira a quantidade de cartas para transferir, coluna de saida, coluna de entrada: ");
                scanf("%d%d%d", &quant, &coluna_s, &coluna_e); // Le a quantidade de cartas a serem retiradas, a sua origem e seu destino
                func = mov_dentro_tableau(&mesa, quant, coluna_s, coluna_e); // Chama a funcao para mover entre colunas do tableu
                if(func!=0){
                    condicao++; // Incrementa a condicao se a funcao for realizada 
                }
                
            }

            //Se a jogada for EX havera a desistencia do jogador
            else if(strcmp(ex, jogada) == 0){
                condicao++; // Incrementa a condicao caso o jogador resolva desistir
                break;
            }
            
            //Caso o jogador realize alguma jogada invalida essa informacao sera imprimida no terminal
            if((condicao == 0) && func == 0){
                printf("Jogada invalida\n");
            }

            //Exibe como a mesa ficou apos cada jogada do usuario
            exibir_mesa(&mesa);
        }
        
        //Apos a meta de vencer o jogo for alcancada pelo usuario, sera exibido essa mensagemno terminal
        if(verificar_vitoria(&mesa)){
            printf("Muito bem, voce ganhou!!!\nSua pontuacao foi de: %d\nObrigado por jogar!", mesa.pontuacao);
        }
        //Caso as condicoes de vitoria nao sejam alcancadas sera impresso essa mensagem
        else{
            printf("Que pena :(\nNao foi dessa vez, tente na proxima\nObrigado por jogar\n");
        }

    // Executa o bloco de codigo do modo arquivo
    }else if(modo == 1){
        char caminho_arquivo[256]; // Declara um vetor para armazenar o caminho do arquivo
        FILE* arquivo; // Inicializa um ponteiro para o tipo arquivo

        //Usuario digitara no terminal o caminho para se acessar o arquivo desejado
        printf("\nInforme o caminho do arquivo: ");
        scanf("%255s", caminho_arquivo);

        //Aqui sera feito a leitura do arquivo
        arquivo = fopen(caminho_arquivo, "r");

        //Caso o caminho esteja errado ou nao exista o arquivo sera impresso esta mensagem
        if (arquivo == NULL) {
            perror("Erro ao abrir o arquivo");
            return EXIT_FAILURE;
        }

        carregar_baralho(arquivo, &mesa); // Carrega o baralho da mesa atraves da funcao
        preparar_mesa(&mesa); // Prepara a mesa
        printf("\nMesa Inicial:\n");
        exibir_mesa(&mesa); // Exibe o estado inicial da mesa, logo apos a distribuicao do baralho

        //A diante ficam os comando utilizados pelo usuario apos a leitura e execucao do arquivo
        char acao[3];

        // Esse loop le as  palavras do arquivo ate que encontre a palavra "X" ou ate que ocorra uma falha na leitura.
        while (fscanf(arquivo, "%s", acao) == 1 && strcmp(acao, "X") != 0) {

            //Se o usuario digitar CC ele comprara uma carta do baralho
            if (strcmp(acao, "CC") == 0) {
                comprar_carta(&mesa); // Chama a funcao para comprar uma carta
            
            //Se o usuario digitar DB ele move uma carta do descarte para a base
            } else if (strcmp(acao, "DB") == 0) {
                mov_descarte_base(&mesa); // Chama a funcao para mover do descarte para base
                if(mov_descarte_base){
                    mesa.pontuacao += 10; // Se a funcao for realizada adiciona 10 pontas na pontuacao
                }
            
            //Se o usuario digitar DT ele move uma carta do descarte para a tableau
            } else if (strcmp(acao, "DT") == 0) {
                int indice;
                fscanf(arquivo, "%d", &indice); // Ler o indice da coluna do tableau
                mov_descarte_tableau(&mesa, indice);    
                atualizar_mesa(&mesa);
                if (mov_descarte_tableau){
                    mesa.pontuacao += 5;
                }
            
            //Se o usuario digitar TB ele move uma carta do tableau para a base
            } else if (strcmp(acao, "TB") == 0) {
                int indice;
                fscanf(arquivo, "%d", &indice); // Ler o indice da coluna do tableau
                mov_tableau_base(&mesa, indice);
                atualizar_mesa(&mesa);
                if (mov_tableau_base){
                    mesa.pontuacao +=10;
                }
            
            //Se o usuacrio digitar BT ele move uma carta da base para o tableau
            } else if (strcmp(acao, "BT") == 0) {
                char naipe;
                int indice;
                fscanf(arquivo, " %c %d", &naipe, &indice); // Ler o naipe e o indice do tableau
                mov_base_tableau(&mesa, naipe, indice); // Chama a funcao para mover da base para o tableau
                atualizar_mesa(&mesa); // Atualiza a disposicao da mesa
                if (mov_base_tableau){
                    mesa.pontuacao -= 15; // Caso a funcao tenha sido realizada decrementa 15 pontos da pontuacao
                }
            
            //Se o usuacrio digitar TT ele move carta da coluna de um tableau para outra coluna do tableau
            } else if (strcmp(acao, "TT") == 0) {
                int quantidade, origem, destino;
                fscanf(arquivo, "%d%d%d", &quantidade, &origem, &destino);  // Le a quantidade de cartas a serem transferidas, sua origem e seu destino          
                mov_dentro_tableau(&mesa, quantidade, origem, destino); // Chama a funcao para mover cartas entre o tableau
                atualizar_mesa(&mesa); // Atualiza a disposicao da mesa
                if (mov_dentro_tableau){
                    atualizar_mesa(&mesa); // Caso seja realizada a funcao atualiza a mesa como uma segunda verificacao,
                }                          //  caso seja revelada uma carta do tableu durante o movimento, assim acrescenta 5 pontos na pontuacao
            
            //Caso digite uma acao nao existente no codigo sera impresso a seguinte frase
            } else {
                printf("Acao desconhecida: %s\n", acao);
                exit(EXIT_FAILURE); // O programa sera encerrado
            }
        }
    
    //Impressao da mesa apos a execucao de todos os comandos feitos pelo jogador
    printf("\nMesa Final:\n ");
    exibir_mesa(&mesa); // Mostra a disposicao final da mesa
        
        //Funcao utilizada para fechar o arquivo
        fclose(arquivo);

        //Caso o usuario tenha feito todas as jogadas da maneira correta sera impresso a seguinte mensagem
        if(verificar_vitoria(&mesa)){
            printf("Muito bem, voce ganhou!!!\nSua pontuacao foi de: %d\nObrigado por jogar!\n", mesa.pontuacao);
        }

        //Caso contrario sera impresso esta mensagem
        else{
            printf("Que pena :(\nNao foi dessa vez, tente na proxima\nObrigado por jogar\n\n");
        }

    //Caso o usuario digite algo diferente de 1 ou 0 sera pedido para que escolha novamente entre as 2 opcoes
    }else{
        printf("Modo de jogo invalido\n");
        printf("\nInsira o modo de jogo (0 interativo // 1 arquivo): ");
        scanf("%d", &modo);
    }

    return 0;
}