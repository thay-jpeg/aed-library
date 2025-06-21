// Implementação

#include "system.h"
#include <stdio.h>

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
// Pós-condição: A ação correspondente à opção será executada
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

void escreve_cabecalho(FILE *arq, cabecalho *cab)
{

    fseek(arq, 0, SEEK_SET);
    fwrite(cab, sizeof(cabecalho), 1, arq);
}

cabecalho *le_cabecalho(FILE *arq)
{

    cabecalho *cab = (cabecalho *)malloc(sizeof(cabecalho));
    fseek(arq, 0, SEEK_SET);
    fread(cab, sizeof(cabecalho), 1, arq);
    return cab;
}

void cria_lista_vazia(FILE *arq)
{

    cabecalho *cab = (cabecalho *)malloc(sizeof(cabecalho));
    cab->pos_cabeca = -1;
    cab->pos_topo = 0;
    cab->pos_livre = -1;

    escreve_cabecalho(arq, cab);
    free(cab);
}

livro *le_livro(FILE *arq, int pos)
{

    livro *novo = malloc(sizeof(livro));
    fseek(arq, sizeof(cabecalho) + pos * sizeof(livro), SEEK_SET);
    fread(novo, sizeof(livro), 1, arq);
    return novo;
}

usuario *le_usuario(FILE *arq, int pos)
{

    usuario *aux = malloc(sizeof(usuario));
    fseek(arq, sizeof(cabecalho) + pos * sizeof(usuario), SEEK_SET);
    fread(aux, sizeof(usuario), 1, arq);
    return aux;
}

void escreve_livro(FILE *arq, livro *novo, int pos)
{
    fseek(arq, sizeof(cabecalho) + pos * sizeof(livro), SEEK_SET);
    fwrite(novo, sizeof(livro), 1, arq);
}

void escreve_usuario(FILE *arq, usuario *novo_user, int pos){
    fseek(arq, sizeof(cabecalho) + pos * sizeof(usuario), SEEK_SET);
    fwrite(novo_user, sizeof(usuario), 1, arq);
}

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

int abrir_database(database *db)
{
    db->arq_livros = abrir_arquivo("livros.bin");
    db->arq_emprestimos = abrir_arquivo("emprestimos.bin");
    db->arq_usuarios = abrir_arquivo("usuarios.bin");

    if (!db->arq_livros || !db->arq_emprestimos || !db->arq_usuarios)
        return 0;

    return 1;
}

void fechar_database(database *db)
{
    if (db->arq_livros)
        fclose(db->arq_livros);
    if (db->arq_emprestimos)
        fclose(db->arq_emprestimos);
    if (db->arq_usuarios)
        fclose(db->arq_usuarios);
}
