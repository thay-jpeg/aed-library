// Implementação

#include "livro.h"
#include "../../bin/system.h"
#include <stdio.h>

static void insere_livro_cabeca(FILE *arq, livro novo)
{

    cabecalho *cab = le_cabecalho(arq);
    novo.prox_pos = cab->pos_cabeca;

    if (cab->pos_livre == -1)
    { // sem livros para reciclar a posicao
        escreve_livro(arq, &novo, cab->pos_topo);
        cab->pos_cabeca = cab->pos_topo; // a cabeca da lista agora eh a onde colocamos o novo livro
        cab->pos_topo++;
    }
    else
    {
        livro *aux = le_livro(arq, cab->pos_livre);
        escreve_livro(arq, &novo, cab->pos_livre);
        cab->pos_cabeca = cab->pos_livre;
        cab->pos_livre = aux->prox_pos;
        free(aux);
    }
    escreve_cabecalho(arq, cab);
    free(cab);
}

void cadastrar_livro(FILE *arq_livros)
{

    livro novo_livro;

    printf("\n===== Cadastro de novo livro =====\n");
    printf("Digite as credenciais a seguir:\n");
    printf("Codigo: ");
    scanf("%d%*c", &novo_livro.codigo);
    printf("Titulo (MAX. 150 carac.): ");
    scanf("%150[^\n]%*c", novo_livro.titulo);
    printf("Autor (MAX. 200 carac.): ");
    scanf("%200[^\n]%*c", novo_livro.autor);
    printf("Editora (MAX. 50 carac.): ");
    scanf("%50[^\n]%*c", novo_livro.editora);
    printf("Numero da edicao: ");
    scanf("%d%*c", &novo_livro.edicao);
    printf("Ano: ");
    scanf("%d%*c", &novo_livro.ano);
    printf("Quantidade de exemplares: ");
    scanf("%d%*c", &novo_livro.exemplares);
    printf("====================================\n");

    insere_livro_cabeca(arq_livros, novo_livro);

    printf("\n Livro cadastrado com sucesso!\n");
}

static int busca_livro(FILE *arq, int pos, livro *destino)
{

    fseek(arq, sizeof(cabecalho) + pos * sizeof(livro), SEEK_SET);

    if (fread(destino, sizeof(livro), 1, arq) == 1)
        return 1;

    return 0;
}

void imprimir_dados_livro(FILE *arq_livros)
{

    int codigo;

    printf("\nInsira o codigo do livro que esta buscando: ");
    scanf("%d%*c", &codigo);

    cabecalho *c = le_cabecalho(arq_livros);

    if (!c)
    {
        printf("ERRO: Nao foi possivel ler o arquivo de livros.\n");
        return;
    }

    int pos = c->pos_cabeca;
    int flag = 0;
    livro *aux = (livro *)malloc(sizeof(livro));

    // enquanto a lista nao chegar ao fim, a busca do livro nao for bem sucedida e o codigo nao for igual, a pos recebe a prox pos da lista
    while (pos != -1 && !flag)
    {

        if (busca_livro(arq_livros, pos, aux))
        {
            if (aux->codigo == codigo)
                flag = 1;
            else
                pos = aux->prox_pos;
        }
        else
            pos = -1;
    }

    // quer dizer que encontrou o codigo na lista
    if (flag == 1)
    {
        printf("\n=========== Livro ===========\n");
        printf("Codigo : %d\n", aux->codigo);
        printf("Titulo: %s\n", aux->titulo);
        printf("Autor: %s\n", aux->autor);
        printf("Editora: %s\n", aux->editora);
        printf("Numero da edicao: %d\n", aux->edicao);
        printf("Ano: %d\n", aux->ano);
        printf("Quantidade de exemplares: %d", aux->exemplares);
        printf("\n=============================\n");
    }

    // chegou ao final da lista e nao encontrou
    else
    {
        printf("\n--> Sentimos muito, o livro com codigo '%d' nao existe em nosso historico ou nao foi encontrado... <--\n", codigo);
    }
    free(aux);
    free(c);
}

void listar_livros(FILE *arq_livros) {
    cabecalho *aux = le_cabecalho(arq_livros);
    int i = aux->pos_cabeca;
    if (i == -1) {
        printf("\nNenhum livro foi cadastrados...\n");
    } else {
        printf("\n===================== LISTA DE LIVROS =====================\n");
        printf("%s | %s | %s | %s\n", "Cod", "Titulo", "Autor", "Exemplares");
        printf("===========================================================\n");

        while (i != -1) {
            livro *livro_atual = le_livro(arq_livros, i);
            if (livro_atual) {
                printf("%d | %s | %s | %d\n", livro_atual->codigo,livro_atual->titulo, livro_atual->autor, livro_atual->exemplares);
                i = livro_atual->prox_pos;
                free(livro_atual);
            } else {
                printf("\nFalha ao ler registro de livro na posicao %d\n", i);
                i = -1; 
            }
        }
        printf("===========================================================\n");
    }
    free(aux);
}


void buscar_titulo(FILE *arq_livros) {

    cabecalho *aux = le_cabecalho(arq_livros);
    int pos_atual = aux->pos_cabeca; // posicao inicial para a busca

    char titulo_busca[MAX_TITULO]; 
    int encontrado = 0; // flag para verificar se pelo menos um livro foi encontrado

    printf("Digite o titulo do livro a ser buscado: ");
    scanf(" %[^\n]%*c", titulo_busca);
    while(pos_atual != -1){
        livro *livro_atual = le_livro(arq_livros, pos_atual);
        // compara o título do livro lido com o titulo buscado pelo usuario
        if(strcmp(livro_atual->titulo, titulo_busca) == 0){
            // se os títulos forem iguais, o livro foi encontrado
            // imprime um cabeçalho apenas na primeira vez que um livro eh encontrado
            if(!encontrado){
            printf("\n======== Livro(s) Encontrado(s) =========\n");
                encontrado = 1; //atualiza a flag
            }
            printf("=========================================\n");
            printf("Codigo: %d\n", livro_atual->codigo);
            printf("Titulo: %s\n", livro_atual->titulo);
            printf("Autor: %s\n", livro_atual->autor);
            printf("Editora: %s\n", livro_atual->editora);
            printf("Edicao: %d\n", livro_atual->edicao);
            printf("Ano: %d\n", livro_atual->ano);
            printf("Exemplares: %d\n", livro_atual->exemplares);
            printf("=========================================\n");
        }
        // guarda a posição do proximo livro na lista
        int proxima_pos = livro_atual->prox_pos;

        free(livro_atual);

        // atualiza a posição atual para continuar 
        pos_atual = proxima_pos;
    }
    if (!encontrado) {
        printf("\nNenhum livro com o titulo '%s' foi encontrado.\n", titulo_busca);
    }

    free(aux);
}


void calcular_total(FILE *arq_livros)
{

    cabecalho *cab = le_cabecalho(arq_livros);

    int temp = 0;
    int total_topo = cab->pos_topo;
    int livre_atual = cab->pos_livre;
    livro aux;

    while (livre_atual != -1)
    {

        if (busca_livro(arq_livros, livre_atual, &aux))
        {
            temp++;
            livre_atual = aux.prox_pos;
        }
        else
        {
            printf("ERRO: Nao foi possivel acessar o arquivo de dados...\n");
            livre_atual = -1;
        }
    }

    printf("\n===================================\n");
    printf("    Total de livros cadastrados: %d   ", total_topo - temp);
    printf("\n===================================\n");

    free(cab);
}


/*Propósito: Busca um livro no arquivo binário pelo seu código e retorna a sua posição (índice) no arquivo.

Pré-condições:
    - O ponteiro 'arq_livros' deve ser válido e o arquivo deve estar aberto em modo que permita leitura (ex: "r+b").
    - O arquivo deve ter um cabeçalho formatado corretamente na primeira posição. 

Pós-condições (Retorno):
    - Retorna a posição (um inteiro >= 0) do livro no arquivo se ele for encontrado.
    - Retorna -1 se o livro com o código especificado não for encontrado na lista ou se ocorrer um erro de leitura.*/
int buscar_pos_livro(FILE *arq_livros, int codigo) {
    cabecalho *c = le_cabecalho(arq_livros);
    if (!c) return -1;

    int pos_atual = c->pos_cabeca;
    free(c);

    while (pos_atual != -1) {
        livro *livro_atual = le_livro(arq_livros, pos_atual);
        if (livro_atual) {
            if (livro_atual->codigo == codigo) {
                free(livro_atual);
                return pos_atual; // Retorna a posição se encontrou
            }
            int proxima_pos = livro_atual->prox_pos;
            free(livro_atual);
            pos_atual = proxima_pos;
        } else {
            pos_atual = -1; // Sai do loop em caso de erro
        }
    }
    return -1; // Retorna -1 se não encontrou
}

// void carregar_lote(FILE *arq_livros) {}