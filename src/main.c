//Arquivo principal

#include <stdio.h>
#include "bibliotec.h"

#define MAX 270

int main() {
    char nome[MAX];
    printf("Digite o nome que deseja para o arquivo (MAX. 255 caract., sem espacamentos):\n");
    fgets(nome, 255, stdin);
    nome[strcspn(nome, '\n')] = 0; //remover o \n do fgets

    strcat(nome, ".bin");

    const char *nome_arquivo = nome;
    FILE *arq;

    arq = fopen(nome_arquivo, "rb+");

    //Verifica se o arquivo é nulo
    if(!arq) {
        printf("Arquivo de dados nao encontrado. Criando um novo...\n");
        arq = fopen(nome_arquivo, "wb+");
        if(!arq) {
            printf("ERRO CRITICO: Nao foi possivel criar o arquivo de dados.\n");
        return 1;
    }

    //Inicializando cabeçalho do arquivo bin
    cabecalho cab_inicial;

    //A lista de livros começa vazia
    cab_inicial.pos_cabeca = -1;
    
    //A próxima posição livre do arquivo será após a quantidade de bytes utilizada para armazenar o topo (cabeçalho)
    cab_inicial.pos_topo = sizeof(cabecalho);

    //A lista de posições livres (para os registros deletados) começa vazia
    cab_inicial.pos_livre = -1;

    fwrite(&cab_inicial, sizeof(cabecalho), 1, arq);
    printf("Arquivo '%s' criado e inicializado com sucesso.\n", nome_arquivo);
    }
    
    int escolha;

    do {
        exibir_menu();
        scanf("%d%*c", &escolha);
        
        processar_sistema(arq, escolha);
    }
    while(escolha != 0);

    printf("Salvando dados e encerrando o programa...\n");
    fclose(arq);
    
    return 0;
}