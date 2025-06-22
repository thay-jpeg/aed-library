// Implementação

#include "system.h"
#include <stdio.h>


// Entrada: nenhuma
// Retorno: nenhum
// Pré-condição: nenhuma
// Pós-condição: O menu principal com as opcoes do sistema eh exibido na tela.
void exibir_menu()
{
    printf("\n===========================================================\n");
    printf("           SISTEMA DE GERENCIAMENTO DA BIBLIOTECA         ");
    printf("\n===========================================================\n\n");
    printf("1- Cadastrar livro.\n");
    printf("2- Informacoes de um respectivo livro.\n");
    printf("3- Listar todos os livros cadastrados.\n");
    printf("4- Busca por titulo.\n");
    printf("5- Calcular total de livros cadastrados.\n");
    printf("6- Cadastrar usuario.\n");
    printf("7- Emprestimo de livro.\n");
    printf("8- Devolucao de livro.\n");
    printf("9- Listar todos os livros emprestados.\n");
    printf("10- Carregar arquivo em Lote.\n");
    printf("0- Sair\n");
    printf("\n===========================================================\n");

    printf("Digite a opcao que deseja:\n");
}

// Entrada: Ponteiro para a struct 'database' com os arquivos ja abertos.
// Retorno: nenhum
// Pré-condição: O ponteiro 'db' e os ponteiros de arquivo dentro dele devem ser validos.
// Pós-condição: O menu eh exibido e as opcoees do usuario sao processadas em loop ate a escolha de sair (0).
void iniciar_sistema(database *db)
{

    int escolha;

    do
    {
        exibir_menu();
        scanf("%d%*c", &escolha);

        processar_sistema(db, escolha);
    } while (escolha != 0);
}

// Entrada: Valor inteiro que representa a escolha do usuário no menu
// Retorno: nenhum
// Pré-condição: nenhuma
// Pós-condição: A acoes correspondente à opção será executada
void processar_sistema(database *db, int opcao)
{
    switch (opcao)
    {
    case 1: cadastrar_livro(db->arq_livros); break;
    case 2: imprimir_dados_livro(db->arq_livros); break;
    case 3: listar_livros(db->arq_livros); break;
    case 4: buscar_titulo(db->arq_livros); break;

    case 5:
        calcular_total(db->arq_livros);
        break;
    case 6: 
        cadastrar_usuario(db->arq_usuarios); 
        break;
    case 7: 
        emprestar_livro(db->arq_livros, db->arq_usuarios, db->arq_emprestimos);
        break;
    // case 8: devolver_livro(db->arq_emprestimos); break;
    // case 9: listar_emprestimos(db->arq_emprestimos); break;
    case 10: carregar_lote(db); break;
    case 0: break;
    default: printf("Opcao invalida. Tente novamente.\n"); break;
    }
}

// Entrada: Ponteiro para um arquivo e para a struct de cabeçalho com os novos dados.
// Retorno: nenhum
// Pré-condição: O ponteiro de arquivo deve ser válido e aberto em "r+b". O ponteiro 'cab' deve ser válido.
// Pós-condição: O conteúdo da struct 'cab' é escrito no início do arquivo.
void escreve_cabecalho(FILE *arq, cabecalho *cab)
{

    fseek(arq, 0, SEEK_SET);
    fwrite(cab, sizeof(cabecalho), 1, arq);
}

// Entrada: Ponteiro para um arquivo.
// Retorno: Ponteiro para uma struct 'cabecalho' alocada dinamicamente.
// Pré-condição: O ponteiro de arquivo deve ser válido e aberto em modo de leitura.
// Pós-condição: O cabeçalho é lido do arquivo e retornado, o chamador 
//  da função eh responsável por liberar a memoria.
cabecalho *le_cabecalho(FILE *arq)
{

    cabecalho *cab = (cabecalho *)malloc(sizeof(cabecalho));
    fseek(arq, 0, SEEK_SET);
    fread(cab, sizeof(cabecalho), 1, arq);
    return cab;
}

// Entrada: Ponteiro para um arquivo.
// Retorno: nenhum
// Pré-condição: O ponteiro de arquivo deve ser válido e aberto em modo de escrita.
// Pós-condição: Um cabeçalho que representa uma lista vazia eh escrito no início do arquivo.
void cria_lista_vazia(FILE *arq)
{

    cabecalho *cab = (cabecalho *)malloc(sizeof(cabecalho));
    cab->pos_cabeca = -1;
    cab->pos_topo = 0;
    cab->pos_livre = -1;

    escreve_cabecalho(arq, cab);
    free(cab);
}

// Entrada: Ponteiro para o arquivo e a posição (índice) do registro.
// Retorno: Ponteiro para uma struct 'livro' alocada dinamicamente.
// Pré-condição: O ponteiro de arquivo deve ser válido e 'pos' deve ser um índice existente.
// Pós-condição: O registro do livro na posição especificada eh lido e retornado, o chamador é responsável por liberar a memória.
livro *le_livro(FILE *arq, int pos)
{

    livro *novo = malloc(sizeof(livro));
    fseek(arq, sizeof(cabecalho) + pos * sizeof(livro), SEEK_SET);
    fread(novo, sizeof(livro), 1, arq);
    return novo;
}

// Entrada: Ponteiro para o arquivo e a posição (índice) do registro.
// Retorno: Ponteiro para uma struct 'usuario' alocada dinamicamente.
// Pré-condição: O ponteiro de arquivo deve ser válido e 'pos' deve ser um índice existente.
// Pós-condição: O registro do usuário na posição especificada é lido e retornado, o chamador eh responsavel por liberar a memória.
usuario *le_usuario(FILE *arq, int pos)
{

    usuario *aux = malloc(sizeof(usuario));
    fseek(arq, sizeof(cabecalho) + pos * sizeof(usuario), SEEK_SET);
    fread(aux, sizeof(usuario), 1, arq);
    return aux;
}

// Entrada: Ponteiro para o arquivo, ponteiro para a struct 'livro' e a posição (índice) para escrever.
// Retorno: nenhum
// Pré-condição: Os ponteiros devem ser válidos e 'pos' deve ser um índice existente.
// Pós-condição: O conteúdo da struct 'livro' é escrito na posição especificada do arquivo.
void escreve_livro(FILE *arq, livro *novo, int pos)
{
    fseek(arq, sizeof(cabecalho) + pos * sizeof(livro), SEEK_SET);
    fwrite(novo, sizeof(livro), 1, arq);
}

// Entrada: Ponteiro para o arquivo, ponteiro para a struct 'usuario' e a posição (índice) para escrever.
// Retorno: nenhum
// Pré-condição: Os ponteiros devem ser válidos e 'pos' deve ser um índice existente.
// Pós-condição: O conteúdo da struct 'usuario' eh escrito na posição especificada do arquivo.
void escreve_usuario(FILE *arq, usuario *novo_user, int pos){
    fseek(arq, sizeof(cabecalho) + pos * sizeof(usuario), SEEK_SET);
    fwrite(novo_user, sizeof(usuario), 1, arq);
}

// Entrada: String com o nome do arquivo a ser aberto.
// Retorno: Ponteiro para o arquivo aberto (FILE*) ou NULL em caso de erro.
// Pré-condição: nenhuma
// Pós-condição: O arquivo eh criado (se não existir) com uma lista vazia e seu ponteiro eh retornado.
FILE *abrir_arquivo(const char *nome_arquivo)
{
    FILE *arq = fopen(nome_arquivo, "wb+");

    if (!arq)
    {
        printf("ERRO CRITICO: Nao foi possivel criar o arquivo de dados.\n");
        return NULL;
    }
    printf("Criando um novo arquivo '%s'...\n", nome_arquivo);

    cria_lista_vazia(arq);

    return arq;
}

// Entrada: Ponteiro para a struct 'database'.
// Retorno: 1 se todos os arquivos foram abertos com sucesso, 0 caso contrário.
// Pré-condição: O ponteiro 'db' deve ser válido.
// Pós-condição: Os ponteiros de arquivo dentro da struct 'db' são inicializados.
int abrir_database(database *db)
{
    db->arq_livros = abrir_arquivo("livros.bin");
    db->arq_emprestimos = abrir_arquivo("emprestimos.bin");
    db->arq_usuarios = abrir_arquivo("usuarios.bin");

    if (!db->arq_livros || !db->arq_emprestimos || !db->arq_usuarios)
        return 0;

    return 1;
}

// Entrada: Ponteiro para a struct 'database' com os arquivos abertos.
// Retorno: nenhum
// Pré-condição: Os ponteiros de arquivo dentro de 'db' são válidos ou NULL.
// Pós-condição: Todos os arquivos abertos são fechados.
void fechar_database(database *db)
{
    if (db->arq_livros)
        fclose(db->arq_livros);
    if (db->arq_emprestimos)
        fclose(db->arq_emprestimos);
    if (db->arq_usuarios)
        fclose(db->arq_usuarios);
}
