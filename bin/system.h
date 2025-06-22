// Delegação

#ifndef SYSTEM_H
#define SYSTEM_H

#include "storage.h"
#include "../src/livro/livro.h"
#include "../src/emprestimo/emprestimo.h"
#include "../src/usuario/usuario.h"

// Abre um arquivo binário e o inicializa com um cabeçalho de lista vazia
FILE *abrir_arquivo(const char *nome_arquivo);

// Abre todos os arquivos de dados necessários para o sistema
int abrir_database(database *db);

// Fecha todos os arquivos de dados abertos
void fechar_database(database *db);

// Escreve o registro de cabeçalho no início de um arquivo
void escreve_cabecalho(FILE *arq, cabecalho *cab);

// Lê o registro de cabeçalho do início de um arquivo
cabecalho *le_cabecalho(FILE *arq);

// Cria e escreve um cabeçalho que representa uma lista vazia
void cria_lista_vazia(FILE *arq);

// Lê um registro de livro de uma posição específica do arquivo
livro *le_livro(FILE *arq, int pos);

// Lê um registro de usuário de uma posição específica do arquivo
usuario *le_usuario(FILE *arq, int pos);

emprestimo *le_emprestimo(FILE *arq, int pos);

// Escreve um registro de livro em uma posição específica do arquivo
void escreve_livro(FILE *arq, livro *novo, int pos);

// Escreve um registro de usuário em uma posição específica do arquivo
void escreve_usuario(FILE *arq, usuario *novo_user, int pos);

void escreve_emprestimo(FILE *arq, emprestimo *novo, int pos);

// Inicia o sistema e gerencia escolhas do usuário
void iniciar_sistema(database *db);

// Delega os módulos corretos de acordo com a opção do usuário
void processar_sistema(database *db, int opcao);

// Exibe o menu principal para o usuário
void exibir_menu();

#endif