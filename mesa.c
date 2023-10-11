#include "mesa.h"

// Funcao para inicializar a mesa
void inicializar_mesa(mesa* mesa){

//Alocacao de memoria para os ponteiros da estrutura mesa
    
    mesa->baralho = (lista*)malloc(sizeof(lista));
    for (int i = 0; i < 4; i++) {
        mesa->base[i] = (lista*)malloc(sizeof(lista));
    }
    for (int i = 0; i < 7; i++) {
        mesa->tableau[i] = (lista*)malloc(sizeof(lista));
    }
    mesa->descarte = (lista*)malloc(sizeof(lista));

//Inicializando a estrutura mesa de acordo com a funcao
   
    criar_lista(mesa->baralho);
    criar_lista(mesa->descarte);
    
    for(int i = 0; i<4; i++){
        criar_lista(mesa->base[i]); // Cria as bases
    }
    for(int i = 0; i<7; i++){
        criar_lista(mesa->tableau[i]); // Cria as colunas do tableau
    }
    mesa->pontuacao = 0; // Incializa a pontuacao da mesa com 0
}

// Funcao para criar e embaralhar o baralho do jogo interativo
void carregar_baralho_aleatorio(mesa* mesa){
    Carta carta;
    for(int i = 1; i<=4; i++){ // Loop para os naipes (1 a 4)
        for(int j = 1; j <=13; j++){ // Loop para os valores das cartas (1 a 13)
            switch (i){
                case 1:
                    criar_carta(&carta, 'C', j, 0); // Cria uma carta de valor j do naipe C, virada para baico
                    break;
                case 2:
                    criar_carta(&carta, 'O', j, 0); // Cria uma carta de valor j do naipe O, virada para baico
                    break;
                case 3:
                    criar_carta(&carta, 'E', j, 0); // Cria uma carta de valor j do naipe E, virada para baico
                    break;
                case 4:
                    criar_carta(&carta, 'P', j, 0); // Cria uma carta de valor j do naipe P, virada para baico
                    break;
                default:
                    break;
            }
            adicionar_topo(mesa->baralho, carta); // Adiciona a carta ao baralho 
        }
    }
    embaralha(mesa->baralho);  // Chama a funcao embaralha e realiza o embaralhamento do baralho
}

// Funcao para preparar a mesa do jogo
//Retirar o topo do baralho e colocar a quantidade adequada de cartas em cada local do tableau, virando a ultima
void preparar_mesa(mesa* mesa){
    
    Carta carta;
    
    for(int i = 0; i<7; i++){ // Loop para as colunas do tableau (0 a 6)
        for(int j = 0; j<i; j++){
            retirar_topo(mesa->baralho, &carta); // Retira uma carta do topo do baralho
            adicionar_topo(mesa->tableau[i], carta); // Adiciona a carta retirada no topo da coluna i do tableau
        }
        retirar_topo(mesa->baralho, &carta); // Retira uma carta do topo do baralho
        alterar_posicao(&carta); // Altera a posicao da carta para cima (1)
        adicionar_topo(mesa->tableau[i], carta); // Adiciona a carta virada para cima ao topo da coluna i do tableau
    }
}

// 1 para vitoria e 0 para nao vitoria
int verificar_vitoria(mesa* mesa){
    Carta carta;
    int v = 0;
    for(int i = 0; i<4; i++){ // Loop para as colunas da base (0 a 3)
        retornar_topo(mesa->base[i], &carta); // Obtem a carta no topo da coluna atual
        if((retornar_valor(&carta))==13){ // Verifica se o valor da carta do topo eh 13 (um rei)
            v++; // Incremente a contagem se a carta for um rei
        }
    }
    if(v==4){ // Se todas as quatro colunas tiverem um rei no topo
        return 1; // Retorna 1, indicando vitoria
    }
    else{
        return 0; // Retorna 0, indicando derrota
    }
    
}

// Funcao para exibir a mesa
void exibir_mesa(mesa* mesa){
    
    // Criacao da estrutura carta 
    Carta aux;
    Carta base_1;
    Carta base_2;
    Carta base_3;
    Carta base_4;
    Carta baralho_1;
    Carta descarte_1; 
    
    // Inicializam as cartas com valor nulo
    inicializar_carta(&base_1);
    inicializar_carta(&base_2);
    inicializar_carta(&base_3);
    inicializar_carta(&base_4);
    inicializar_carta(&baralho_1);
    inicializar_carta(&descarte_1);

    // Retorna o topo de casa coluna presente na mesa (base, tableau, baralho e descarte)
    retornar_topo(mesa->base[0], &base_1);
    retornar_topo(mesa->base[1], &base_2);
    retornar_topo(mesa->base[2], &base_3);
    retornar_topo(mesa->base[3], &base_4);
    retornar_topo(mesa->baralho, &baralho_1);
    retornar_topo(mesa->descarte, &descarte_1);

    // Faz a impressao da mesa com uma disposicao horizontal
    printf("\n");
    printf("==========================================================================\n\n");
    printf("Baralho:  ");
    exibir_carta(baralho_1);
    printf("  ");
    printf("Descarte:  ");
    exibir_carta(descarte_1);
    printf("\n");
    printf("\n");
    printf("Base:\n");
    exibir_carta(base_1);
    printf("  ");
    exibir_carta(base_2);
    printf("  ");
    exibir_carta(base_3);
    printf("  ");
    exibir_carta(base_4);
    printf("\n");
    printf("\n");
    printf("Tableau:\n");
    
    // Loop para perccorer as listas do tableau da mesa
    for(int i = 0; i<7; i++){
        inicializar_carta(&aux); //Inicializa a carta auxiliar com valor 0
        retornar_topo(mesa->tableau[i], &aux); // Verifica o topo da coluna do tableau
        if((retornar_posicao(&aux) == 0) && (lista_e_vazia(mesa->tableau[i]) == 0)){ // Verifica se a posicao da carta é 0 (para baixo) e se a lista nao esta vazia
            retirar_topo(mesa->tableau[i], &aux); // Retira o topo da carta de cada coluna e altera sua posicao 
            alterar_posicao(&aux);                //e depois adiciona novamente, e logo em seguida atualiza a pontuacao
            adicionar_topo(mesa->tableau[i], aux);
            mesa->pontuacao = mesa->pontuacao + 5;
        }
        imprime_lista(mesa->tableau[i]);
        printf("\n");
    }
    if(mesa->pontuacao < 0){ // Verifica se a pontuacao eh menor que 0
        mesa->pontuacao = 0; // Caso seja, é reiniciada para 0, uma vez que eh a pontuacao minima
    }
    printf("\nPontuacao: %d\n", mesa->pontuacao);
    printf("\n");
    printf("==========================================================================\n");
}

// Funcao para comprar uma carta do baralho
int comprar_carta(mesa* mesa){
    // Verifica se o baralho e o descarte estao vazios 
    if(lista_e_vazia(mesa->baralho) && lista_e_vazia(mesa->descarte)){ // Nesse caso nao ha o que comprar
        return 0;
    }
    
    else{
        Carta carta;
        if(lista_e_vazia(mesa->baralho)){ // Se o baralho estiver vazio, mas houver cartas no descarte
            for(int i = 0; i<retornar_tam(mesa->descarte); i++){ // Pecorre a lista do descarte
                retirar_topo(mesa->descarte, &carta); // Retira as carta do descarte
                alterar_posicao(&carta); // Altera a posicao (vai virar para baixo novamente)
                adicionar_topo(mesa->baralho, carta); // Adiciona as cartas no baralho
            }
            mesa->pontuacao = mesa->pontuacao - 50; // Penaliza a pontuacao por reiniciar o baralho
        }
        // Se o baralho nao estiver vazio
        retirar_topo(mesa->baralho, &carta); // Retira a carta do baralho
        alterar_posicao(&carta); // Altera a posicao (vai virar para cima)
        adicionar_topo(mesa->descarte, carta); // Adiciona a carta no topo do descarte
        return 1; // Retorna 1 para um movimento valido
    }

}

// Funcao para mover carta do descarte para uma base
int mov_descarte_base(mesa* mesa){
    
    int condicao = 0; // Variavel para verificar se o movimento eh valido
    int n = -1; // Variavel para armazenar o indice da coluna da base correspondente
    
    Carta c_saida;
    Carta c_anterior;
    
    //Inicializa as cartas como valor nulo
    inicializar_carta(&c_anterior);
    inicializar_carta(&c_saida);
    
    //Retorna a primeira carta do descarta
    retornar_topo(mesa->descarte, &c_saida);
    
    switch (retornar_naipe(&c_saida)) { 
    case 'C':
        n = 0; // Define o indice da coluna da base como 0 para o naipe 'C'
        break;
    case 'P':
        n = 1; // Define o indice da coluna da base como 1 para o naipe 'P'
        break;
    case 'O':
        n = 2; // Define o indice da coluna da base como 2 para o naipe 'o'
        break;
    case 'E':
        n = 3; // Define o índice da coluna da base como 3 para o naipe 'E'
        break;
    
    default:
        break;
    }
    
    // Retorna a primeira carta da base
    retornar_topo(mesa->base[n], &c_anterior);

    // Verifica se a lista da base eh vazia da e se a carta do tableau eh um As (valor 1)
    if(lista_e_vazia(mesa->base[n]) && (retornar_valor(&c_saida) == 1)){
        condicao++; // Incrementa a condicao para indicar um movimento valido
    }
    // Verifica se a lista nao esta vazia e verifica se as cartas seguem a sequencia do mesmo naipe
    else if((retornar_valor(&c_anterior) != 0) && verificar_sequencia_mesmo_naipe(&c_anterior, &c_saida)){
        condicao++; // Incrementa a condicao para indicar um movimento valido
    }
    if(condicao != 0){
        retirar_topo(mesa->descarte, &c_saida);
        adicionar_topo(mesa->base[n], c_saida);
        return 1; // Retorna 1 para indicar um movimento valido
    }
    else{
        return 0; // Retorna 0 para indicar um movimento invalido
    }
    
}

int mov_tableau_base(mesa* mesa, int coluna_tableau){
    
    int condicao = 0; // Variável para verificar se o movimento eh valido
    
    // Verifica se a coluna do tableau esta dentro dos limites (1 a 7 no jogo)
    if(coluna_tableau < 0 || coluna_tableau > 7){
        return 0;
    }
    coluna_tableau--; // Decrementa o valor em 1 para fazer a correspondencia no indice do vetor
    Carta c_saida; // Cria um carta para representar o tableau
    Carta c_anterior; // Cria um carta para representar a base
    
    // Inicializa as cartas com valor nulo
    inicializar_carta(&c_anterior);
    inicializar_carta(&c_saida);
    
    // Retorna o topo da coluna do tableau
    retornar_topo(mesa->tableau[coluna_tableau], &c_saida);
    
    int coluna_base;
    switch (retornar_naipe(&c_saida)) // Mapeia o naipe para o indice da coluna base (0 a 3)
    {
    case 'C':
        coluna_base = 0;
        break;
    case 'P':
        coluna_base = 1;
        break;
    case 'O':
        coluna_base = 2;
        break;
    case 'E':
        coluna_base = 3;
        break;
    
    default:
        break;
    }

    // Retornar o topo da base
    retornar_topo(mesa->base[coluna_base], &c_anterior);

    // Verifica se a lista da base eh vazia da e se a carta do tableau eh um As (valor 1)
    if(lista_e_vazia(mesa->base[coluna_base]) && (c_saida.valor == 1)){
        condicao++; // Incrementa a condicao para indicar um movimento valido
    }
    // Verifica se a lista nao esta vazia e verifica se as cartas seguem a sequencia do mesmo naipe
    else if((c_anterior.valor != 0) && verificar_sequencia_mesmo_naipe(&c_anterior, &c_saida)){
        condicao++; // Incrementa a condicao para indicar um movimento valido
    }
      // Se a condição for diferente de zero, significa que o movimento e valido e a funcao eh executada
    if(condicao != 0){
        retirar_topo(mesa->tableau[coluna_tableau], &c_saida); // Retira a carta da coluna do tableau
        adicionar_topo(mesa->base[coluna_base], c_saida); // Insere a carta na base
        return 1;  // Retorna 1 para indicar um movimento valido
    }
    else{
        return 0; // Retorna 0 para indicar um movimento invalido
    }
}

//Funcao para mover cartas entre colunas do tableau
int mov_dentro_tableau(mesa* mesa, int quantidade_cartas, int coluna_saida, int coluna_entrada){
    
    int condicao = 0; // Variável para verificar se o movimento eh valido
    
    if(coluna_saida > 7  || coluna_entrada > 7){   // Verifica se as colunas de saida e entrada estao dentro dos parametros
        return 0;
    }
    
    coluna_entrada --; // Decrementa o valor em 1 para fazer a correspondencia no indice do vetor
    coluna_saida --; // Decrementa o valor em 1 para fazer a correspondencia no indice do vetor
    
    Carta c_saida; // Cria uma carta para representar a coluna do qual a carta vai ser retirada
    Carta c_anterior; // Cria uma carta para representar a coluna do qual a carta vai ser recebida
    
    // Inicializa as cartas com valor nulo 
    inicializar_carta(&c_anterior);
    inicializar_carta(&c_saida);
    
    // Retorna a primeira carta da lista das colunas do tableau
    retornar_carta_qualquer(mesa->tableau[coluna_saida], &c_saida, quantidade_cartas);
    retornar_topo(mesa->tableau[coluna_entrada], &c_anterior);
    
    // Verifica se a lista esta vazia e se a carta a ser movida eh um rei (valor 13)
    if((retornar_valor(&c_anterior) == 0) && (retornar_valor(&c_saida) == 13)){
        condicao++; // Incrementa a condicao para indicar um movimento valido
    }
    // Verifica se as cartas nao sao vazias e verifica se as cartas seguem a sequencia alternada
    else if((((retornar_valor(&c_anterior) != 0) && (retornar_valor(&c_saida) != 0))) && (verificar_sequencia_alternada(&c_saida, &c_anterior))){
        condicao++; // Incrementa a condicao para indicar um movimento valido
    }
     // Se a condição for diferente de zero, significa que o movimento e valido e a funcao eh executada
    if(condicao != 0){
        // Faz a transferencia de cartas de uma coluna do tableau para a outra
        transferir_cartas(mesa->tableau[coluna_saida], mesa->tableau[coluna_entrada], quantidade_cartas);
        return 1; // Retorna 1 para indicar um movimento valido
    }
    else{
        return 0; // Retorna 0 para indicar um movimento invalido
    }
}

// Funcao para mover uma carta da base para o tableau
int mov_base_tableau(mesa* mesa, char naipe, int coluna_tableau){

    int coluna_base;
    switch (naipe)  // Mapeia o naipe para o indice da coluna base (0 a 3)
    {
    case 'C':
        coluna_base = 0;
        break;
    case 'P':
        coluna_base = 1;
        break;
    case 'O':
        coluna_base = 2;
        break;
    case 'E':
        coluna_base = 3;
        break;

    default:
        break;
    }


    int condicao = 0; // Variável para verificar se o movimento eh valido
     // Verifica se a coluna_tableau e a coluna_base estão dentro dos limites
    if (coluna_tableau < 0 || coluna_base < 0 || coluna_tableau > 7 || coluna_base > 4){
        return 0;
    }

    coluna_tableau--; // Decrementa o valor em 1 para fazer a correspondencia no indice do vetor
    Carta c_base; // Cria para representar a base
    Carta c_tableau; // Cria carta para representar o tableau
    //Inicializa a carta com valor nulo
    inicializar_carta(&c_base);
    inicializar_carta(&c_tableau);
    // Retorna a primeira carta da base e da coluna do tableau
    retornar_topo(mesa->base[coluna_base], &c_base);
    retornar_topo(mesa->tableau[coluna_tableau], &c_tableau);

    // Verifica se a lista do tableau esta vazia e se a carta da base eh um rei (valor 13)
    if (lista_e_vazia(mesa->tableau[coluna_tableau])&& (retornar_valor(&c_base) == 13)){
        condicao++;
    }
     // Verifica se a lista nao esta vazia e e verifica a sequencia entre as cartar do tableu e do descarte
    else if((retornar_valor(&c_base)!= 0) && verificar_sequencia_alternada(&c_base, &c_tableau)){
        condicao++; // Incrementa a condicao para indicar um movimento valido
    }
    // Se a condição for diferente de zero, significa que o movimento e valido e a funcao eh executada
    if(condicao != 0){
            retirar_topo(mesa->base[coluna_base], &c_base); // Remove a carta da base
            adicionar_topo(mesa->tableau[coluna_tableau], c_base); //Adiciona a carta na coluna do tableau
            return 1; // Retorna 1 para indicar um movimento valido

    }else{
        return 0; // Retorna 0 para indicar um movimento invalido
    }
}

// Funcao para mover uma carta do descarte para a mesa
int mov_descarte_tableau(mesa* mesa, int coluna_tableau){
    
    int condicao = 0; // Variável para verificar se o movimento eh valido
    if(coluna_tableau < 0 || coluna_tableau > 7){ // Verifica se os parametros passados estao no padrao esperado
        return 0; // Retorna 0 para um movimento invalido
    }

    coluna_tableau--; // Decrementa o valor em 1 para fazer a correspondencia no indice do vetor

    Carta c_saida; // Cria carta para representar a do descarte
    Carta c_anterior; // Cria carta para representar a carta da coluna do tableau
    // Inicializa uma carta com valor nulo
    inicializar_carta(&c_anterior); 
    inicializar_carta(&c_saida);
    // Retorna a primeira carta do descarte e da coluna do tableau
    retornar_topo(mesa->descarte, &c_saida); 
    retornar_topo(mesa->tableau[coluna_tableau], &c_anterior);

     // Verifica se a lista do tableau esta vazia e se a carta do descarte e um rei (valor 13)
    if(lista_e_vazia(mesa->tableau[coluna_tableau]) && (retornar_valor(&c_saida) == 13)){
        condicao++; // Incrementa a condicao para indicar um movimento válido
    }
    // Verifica se a lista nao esta vazia e e verifica a sequencia entre as cartar do tableu e do descarte
    else if((retornar_valor(&c_anterior)!= 0) && verificar_sequencia_alternada(&c_saida, &c_anterior)){
        condicao++; // Incrementa a condicao para indicar um movimento válido

    }
    // Se a condição for diferente de zero, significa que o movimento e valido e a funcao eh executada
    if(condicao != 0){
        retirar_topo(mesa->descarte, &c_saida); // Remove a carta do descarte
        adicionar_topo(mesa->tableau[coluna_tableau], c_saida); // Adiciona a carta na lista do tableau
        return 1; // Retorna 1 para indicar um movimento valido 
    }
    else{
        return 0; // Retorna 0 para indicar um movimento invalido
    }
}

// Funcao para carregar baralho do arquivo
void carregar_baralho(FILE* arquivo, mesa* m) {

    int numCartasArquivo;
    if (fscanf(arquivo, "%d", &numCartasArquivo) != 1) { // Leitura da quantidade de cartas que o baralho vai ter
        perror("Erro ao ler o numero de cartas do arquivo"); // Exibe uma mensagem de erro caso nao consiga ler o numero de cartas
        exit(EXIT_FAILURE); // Sai do programa caso nao consiga ler
    }

    if (numCartasArquivo < 28 || numCartasArquivo > 52) { // Verifica os parametros necessarios para execucao do jogo
        printf("Numero de cartas invalido no arquivo: %d\n", numCartasArquivo); // Mensagem informando o erro
        exit(EXIT_FAILURE); // Sai do programa
    }

    for (int i = 0; i < numCartasArquivo; i++) { // Faz um looping com a quantidade de cartas fornecidas
        char naipe;
        int valor;
        if (fscanf(arquivo, " (%d %c)", &valor, &naipe) != 2) { // Le as cartas do arquivo
            perror("Erro ao ler carta do arquivo"); // Mensagem caso a carta nao siga os parametros informados
            exit(EXIT_FAILURE); // Sai do programa
        }

        // Verifique se o naipe e o valor estao dentro dos limites permitidos
        if ((naipe != 'C' && naipe != 'P' && naipe != 'O' && naipe != 'E') ||
            (valor < 1 || valor > 13)) {
            printf("Carta invalida no arquivo: (%d %c)\n", valor, naipe); // Mensagem caso os valores nao estejam de acordo
            exit(EXIT_FAILURE); // Sai do programa
        }

        Carta nova_carta; // Criacao de uma estrutura carta
        criar_carta(&nova_carta, naipe, valor, 0); // Cria as cartas de acordo com o que foi lido e define a posicao como 0 (para baixo)
        adicionar_topo(m->baralho, nova_carta); // Adiciona as cartas no baralho
    }
    
}

void atualizar_mesa(mesa * mesa){
   
    Carta aux;
    Carta base_1;
    Carta base_2;
    Carta base_3;
    Carta base_4;
    Carta baralho_1;
    Carta descarte_1; 
    
    // Inicializa uma carta nula
    inicializar_carta(&base_1);
    inicializar_carta(&base_2);
    inicializar_carta(&base_3);
    inicializar_carta(&base_4);
    inicializar_carta(&baralho_1);
    inicializar_carta(&descarte_1);
    
    // Retorna a primeira carta de cada lista pertecente da mesa
    retornar_topo(mesa->base[0], &base_1);
    retornar_topo(mesa->base[1], &base_2);
    retornar_topo(mesa->base[2], &base_3);
    retornar_topo(mesa->base[3], &base_4);
    retornar_topo(mesa->baralho, &baralho_1);
    retornar_topo(mesa->descarte, &descarte_1);

   // Loop para perccorer as listas do tableau da mesa
   for(int i = 0; i<7; i++){
        inicializar_carta(&aux); //Inicializa a carta auxiliar com valor 0
        retornar_topo(mesa->tableau[i], &aux); // Verifica o topo da coluna do tableau
        if((retornar_posicao(&aux) == 0) && (lista_e_vazia(mesa->tableau[i]) == 0)){ // Verifica se a posicao da carta é 0 (para baixo) e se a lista nao esta vazia
            retirar_topo(mesa->tableau[i], &aux);  // Retira o topo da carta de cada coluna e altera sua posicao 
            alterar_posicao(&aux);                 //e depois adiciona novamente, e logo em seguida atualiza a pontuacao
            adicionar_topo(mesa->tableau[i], aux);
            mesa->pontuacao = mesa->pontuacao + 5;
        }
    }
    if(mesa->pontuacao < 0){ // Verifica se a pontuacao da mesa eh menor que 0
        mesa->pontuacao = 0; // Caso seja, sera resetada para 0, uma vez que o valor minimo para ela eh 0
    }
   
}