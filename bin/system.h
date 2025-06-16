// Delegação

#ifndef SYSTEM_H
#define SYSTEM_H

#include "storage.h"
#include "../src/livro/livro.h"
#include "../src/emprestimo/emprestimo.h"
#include "../src/usuario/usuario.h"

FILE *abrir_arquivo(const char *nome_arquivo);

int abrir_database(database *db);

void fechar_database(database *db);

void escreve_cabecalho(FILE *arq, cabecalho *cab);

cabecalho *le_cabecalho(FILE *arq);

void cria_lista_vazia(FILE *arq);

livro *le_livro(FILE *arq, int pos);

void escreve_livro(FILE *arq, livro *novo, int pos);

// Inicia o sistema e gerencia escolhas do usuário
void iniciar_sistema(database *db);

// Delega os módulos corretos de acordo com a opção do usuário
void processar_sistema(database *db, int opcao);

// Exibe o menu principal para o usuário
void exibir_menu();

#endif