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

// void listar_livros(FILE *arq_livros) {}

/*no* le_no(FILE* arq, int pos) {
  no* x = malloc(sizeof(no));
  fseek(arq,sizeof(cabecalho) + pos*sizeof(no),SEEK_SET);
  fread(x,sizeof(no),1,arq);
  return x;
}*/

void buscar_titulo(FILE *arq_livros) {
    cabecalho *aux = le_cabecalho(arq_livros);
    int pos_atual = aux->pos_cabeca;
    char titulo_busca[MAX_TITULO];
    int encontrado = 0;
    printf("Digite o titulo do livro a ser buscado: ");
    scanf(" %[^\n]%*c", titulo_busca);

    while(titulo_busca != -1){
        livro *livro_atual = le_livro(arq_livros, titulo_busca);
        printf("codigo do livro: %d", livro_atual);

        if(strcmp(livro_atual->titulo, titulo_busca) == 0){
            //se encontrou impreme
            if(!encontrado){
                printf("\n--- Livro(s) Encontrado(s) ---\n");
            }
            printf("Codigo: %d | Autor: %s | Exemplares: %d\n", livro_atual->codigo,livro_atual->autor,livro_atual->exemplares);
            encontrado = 1;
        }
        int proxima_pos = livro_atual->prox_pos;
        free(livro_atual); 

        pos_atual = proxima_pos;
    }
    

    
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

// void carregar_lote(FILE *arq_livros) {}