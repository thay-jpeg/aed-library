// Implementação

#include "livro.h"
#include "../../bin/system.h"
#include "../usuario/usuario.h"
#include "../emprestimo/emprestimo.h"
#include <stdio.h>

#define MAX_FILE 260
#define MAX_BUFFER 1024


// Entrada: Ponteiro para o arquivo de livros e uma struct 'livro' com os dados.
// Retorno: Nenhum
// Pré-condição: O ponteiro de arquivo deve ser válido e aberto em "r+b",a struct 'novo' deve estar preenchida.
// Pós-condição: O registro do livro é inserido no início da lista encadeada no arquivo, e o cabeçalho é atualizado.
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

// Entrada: Ponteiro para o arquivo de livros.
// Retorno: Nenhum
// Pré-condição: O ponteiro de arquivo deve ser válido e aberto em "r+b".
// Pós-condição: Um novo livro, com dados informados pelo usuário, eh inserido no arquivo.
void cadastrar_livro(FILE *arq_livros)
{

    livro novo_livro;

    printf("\n================== Cadastro de novo livro =================\n");
    printf("\nDigite as credenciais a seguir:\n");
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
    printf("\nLivro cadastrado com sucesso!\n");
    insere_livro_cabeca(arq_livros, novo_livro);
    
    printf("\n===========================================================\n");
}

// Entrada: Ponteiro para o arquivo, a posição do registro e um ponteiro para uma struct 'livro' de destino.
// Retorno: 1 se a leitura for bem-sucedida, 0 caso contrario.
// Pré-condição: O ponteiro de arquivo deve ser válido. O ponteiro 'destino' deve apontar para uma área de memória alocada.
// Pós-condição: A struct 'destino' é preenchida com os dados lidos da posição especificada no arquivo.
static int busca_livro(FILE *arq, int pos, livro *destino)
{

    fseek(arq, sizeof(cabecalho) + pos * sizeof(livro), SEEK_SET);

    if (fread(destino, sizeof(livro), 1, arq) == 1)
        return 1;

    return 0;
}

// Entrada: Ponteiro para o arquivo de livros.
// Retorno: Nenhum
// Pré-condição:O ponteiro de arquivo deve ser valido e aberto em "r+b".
// Pós-condição: As informações completas de um livro (buscado por código) sao exibidas na tela, 
// ou uma mensagem de erro se nao for encontrado.
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
        printf("\n=========================== Livro =========================\n");
        printf("Codigo: %03d\n", aux->codigo);
        printf("Titulo: %s\n", aux->titulo);
        printf("Autor: %s\n", aux->autor);
        printf("Editora: %s\n", aux->editora);
        printf("Numero da edicao: %d\n", aux->edicao);
        printf("Ano: %d\n", aux->ano);
        printf("Quantidade de exemplares: %d", aux->exemplares);
        printf("\n===========================================================\n");

    }

    // chegou ao final da lista e nao encontrou
    else
    {
        printf("\n--> Sentimos muito, o livro com codigo '%03d' nao existe em nosso historico ou nao foi encontrado... <--\n", codigo);
    }
    free(aux);
    free(c);
}

// Entrada: Ponteiro para o arquivo de livros.
// Retorno: Nenhum
// Pré-condição: O ponteiro de arquivo deve ser válido e aberto em "r+b".
// Pós-condição: Uma lista formatada com código, título, autor e exemplares de todos os livros eh exibida na tela.
void listar_livros(FILE *arq_livros)
{
    cabecalho *aux = le_cabecalho(arq_livros);
    int i = aux->pos_cabeca;
    if (i == -1)
    {
        printf("\nNenhum livro foi cadastrado...\n");
    }
    else
    {   
        printf("\n===================== Lista de Livros =====================\n");
        printf("%s | %s | %s | %s\n", "Cod", "Titulo", "Autor", "Exemplares");
        printf("===========================================================\n");

        while (i != -1)
        {
            livro *livro_atual = le_livro(arq_livros, i);
            if (livro_atual)
            {
                printf("%03d | %s | %s | %d\n", livro_atual->codigo, livro_atual->titulo, livro_atual->autor, livro_atual->exemplares);
                i = livro_atual->prox_pos;
                free(livro_atual);
            }
            else
            {
                printf("\nFalha ao ler registro de livro na posicao %d\n", i);
                i = -1;
            }
        }
        printf("===========================================================\n");
    }
    free(aux);
}


// Entrada: Ponteiro para o arquivo de livros
// Retorno: Nenhum
// Pré-condição: O ponteiro de arquivo deve ser valido e aberto em "r+b".
// Pós-condição: As informacoes completas de todos os livros que correspondem a um titulo sao exibidas na tela.
void buscar_titulo(FILE *arq_livros)
{

    cabecalho *aux = le_cabecalho(arq_livros);
    int pos_atual = aux->pos_cabeca; // posicao inicial para a busca

    char titulo_busca[MAX_TITULO];
    int encontrado = 0; // flag para verificar se pelo menos um livro foi encontrado

    printf("\nDigite o titulo do livro a ser buscado: ");
    scanf(" %[^\n]%*c", titulo_busca);
    while (pos_atual != -1)
    {
        livro *livro_atual = le_livro(arq_livros, pos_atual);
        // compara o título do livro lido com o titulo buscado pelo usuario
        if (strcmp(livro_atual->titulo, titulo_busca) == 0)
        {
            // se os títulos forem iguais, o livro foi encontrado
            // imprime um cabeçalho apenas na primeira vez que um livro eh encontrado
            if (!encontrado)
            {   
                printf("\n================== Livro(s) Encontrado(s) =================\n");
                encontrado = 1; // atualiza a flag
            }
            printf("Codigo: %03d\n", livro_atual->codigo);
            printf("Titulo: %s\n", livro_atual->titulo);
            printf("Autor: %s\n", livro_atual->autor);
            printf("Editora: %s\n", livro_atual->editora);
            printf("Edicao: %d\n", livro_atual->edicao);
            printf("Ano: %d\n", livro_atual->ano);
            printf("Exemplares: %d", livro_atual->exemplares);
            printf("\n===========================================================\n");
        }
        // guarda a posição do proximo livro na lista
        int proxima_pos = livro_atual->prox_pos;

        free(livro_atual);

        // atualiza a posição atual para continuar
        pos_atual = proxima_pos;
    }
    if (!encontrado)
    {
        printf("\nNenhum livro com o titulo '%s' foi encontrado.\n", titulo_busca);
    }

    free(aux);
}

// Entrada: Ponteiro para o arquivo de livros.
// Retorno: Nenhum
// Pré-condição: O ponteiro de arquivo deve ser valido e aberto em "r+b".
// Pós-condição: O numero total de livros cadastrados (excluindo os da lista de livres) eh exibido na tela.
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
    printf("\n===========================================================\n");
    printf("               Total de livros cadastrados: %d         ", total_topo - temp);
    printf("\n===========================================================\n");
    free(cab);
}

// Entrada: Ponteiro para o arquivo de livros e o codigo a ser buscado.
// Retorno: A posição (inteiro >= 0) do livro se encontrado, -1 caso contrario;
// Pré-condição: O ponteiro de arquivo deve ser valido e aberto em "r+b".
// Pós-condição: Nenhuma
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

// Entrada: Ponteiro para uma string (token).
// Retorno: Ponteiro para o inicio da string sem espaços nas bordas.
// Pré-condição: A entrada deve ser uma string C valida (terminada em nulo).
// Pós-condição: A string original eh modificada no local, removendo espaços do inicio e do fim.
static char *remove_espacos(char *token)
{

    char *final;

    // se for um espaço, avança ->
    while (isspace((unsigned char)*token))
        token++;

    // se for um token só de espaços, só retorna
    if (*token == 0)
        return token;

    // vai para o final da string token
    final = token + strlen(token) - 1;

    // se o ponteiro ainda nao ter chegado no comeco da string e for um espaço, avança <-
    while (final > token && isspace((unsigned char)*final))
        final--;

    // novo '\0'
    *(final + 1) = '\0';

    return token;
}

// Entrada: Ponteiro para a struct 'database' com todos os arquivos abertos;
// Retorno: nenhum
// Pré-condição: O ponteiro 'db' e os ponteiros de arquivo dentro dele devem ser validos.
// Pós-condição: Os dados do arquivo texto sao lidos e inseridos nos arquivos binarios correspondentes;
void carregar_lote(database *db)
{

    char nome_arquivo[MAX_FILE]; // 255 carac. + '.txt' + '\0'
    char buffer[MAX_BUFFER];
    FILE *arq_lote;
    printf("\n============= Sistema de Carregamento em Lote =============\n\n");
    printf("Bem-vindo(a), Usuario! Antes de prosseguirmos, para realizar o carregamento de seu arquivo com sucesso:\n");
    printf("- O nome de seu arquivo texto deve ter, no maximo, 255 caracteres -\n\n");

    printf("Digite o nome do seu arquivo de lote (ex: dados): ");
    scanf("%255[^\n]%*c", nome_arquivo);
    strcat(nome_arquivo, ".txt");

    arq_lote = fopen(nome_arquivo, "r");

    if (!arq_lote)
    {
        printf("ERRO CRITICO: Nao foi possivel abrir o arquivo de lote '%s'.\n", nome_arquivo);
        return;
    }

    int count = 0;

    while (fgets(buffer, sizeof(buffer), arq_lote))
    {

        // caso tiver, remover quebra de linha do buffer
        buffer[strcspn(buffer, "\r\n")] = 0;
        char *ptr_choose = buffer;

        //se for um espaço, avança
        while(*ptr_choose && isspace((unsigned char)*ptr_choose)) ptr_choose++; 
        //se a linha for vazia, avança
        if(*ptr_choose == '\0') continue;

        char choose = *ptr_choose;
        char *token;
        
        // leitura entre ;
        token = strtok(buffer, ";");

        // caso de linhas vazias
        if (!token)
            continue;

        switch (choose)
        {

        case 'L':
        {

            livro novo;
            // para guardar os ponteiros de cada parte do token
            char *pieces[7];

            for (int i = 0; i < 7; i++)
            {
                token = strtok(NULL, ";");
                // se um dos tokens for nulo, preenche o array com string vazia
                pieces[i] = token ? remove_espacos(token) : "";
            }

            novo.codigo = atoi(pieces[0]);
            strcpy(novo.titulo, pieces[1]);
            strcpy(novo.autor, pieces[2]);
            strcpy(novo.editora, pieces[3]);
            novo.edicao = atoi(pieces[4]);
            novo.ano = atoi(pieces[5]);
            novo.exemplares = atoi(pieces[6]);

            insere_livro_cabeca(db->arq_livros, novo);
            count++;
            break;
        }
        case 'U':
        {

            usuario novo;
            // para guardar os ponteiros de cada parte do token
            char *pieces[2];

            for (int i = 0; i < 2; i++)
            {
                token = strtok(NULL, ";");
                // se um dos tokens for nulo, preenche o array com string vazia
                pieces[i] = token ? remove_espacos(token) : "";
            }

            novo.codigo = atoi(pieces[0]);
            strcpy(novo.nome, pieces[1]);

            inserir_Usuario_Cabeca(db->arq_usuarios, novo);
            count++;
            break;
        }
        case 'E': {

            emprestimo novo;

            char *pieces[4];

            for(int i = 0; i < 4; i++) {
                token = strtok(NULL, ";");
                // se um dos tokens for nulo, preenche o array com string vazia
                pieces[i] = token ? remove_espacos(token) : "";
            }

            novo.codigo_usuario = atoi(pieces[0]);
            novo.codigo_livro = atoi(pieces[1]);
            strcpy(novo.data_emprestimo, pieces[2]);
            strcpy(novo.data_devolucao, pieces[3]);

            registra_emprestimo(db, novo.codigo_livro, novo.codigo_usuario, novo.data_emprestimo, novo.data_devolucao);
            count++;
            break;
        }

        default:
            printf("AVISO: Linha com tipo de registro desconhecido ('%c'), linha ignorada.\n", choose);
            break;
        }
    }
    printf("\nCarregamento em lote concluido! %d registros processados.\n", count);
    printf("\n===========================================================\n\n");
}

// Entrada: Ponteiro para o arquivo de livros e o código do livro a ser buscado.
// Retorno: Ponteiro para uma string (char*) alocada dinamicamente, contendo o
// título do livro ou "Titulo Desconhecido". O chamador da função é responsável por liberar esta memória com free().
// Pré-condição: O ponteiro de arquivo 'arq_livros' deve ser válido e o arquivo deve estar aberto em modo de leitura.
// Pós-condição: Nenhuma. A função nao modifica o arquivo de livros.
char* buscar_titulo_livro(FILE *arq_livros, int codigo) {
    int pos = buscar_pos_livro(arq_livros, codigo);
    if (pos != -1) {
        livro *l = le_livro(arq_livros, pos);
        if (l) {
            char *titulo = malloc(strlen(l->titulo) + 1);
            strcpy(titulo, l->titulo);
            free(l);
            return titulo;
        }
    }
    char *nao_encontrado = malloc(strlen("Titulo Desconhecido") + 1);
    strcpy(nao_encontrado, "Titulo Desconhecido");
    return nao_encontrado;
}