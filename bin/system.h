//Delegação

#ifndef SYSTEM_H
#define SYSTEM_H

#include "storage.h"
#include "../src/livro/livro.h"
#include "../src/emprestimo/emprestimo.h"
#include "../src/usuario/usuario.h"

FILE *abrir_arquivo(const char* nome_arquivo);

int abrir_database(database *db);

void fechar_database(database *db);

//Inicia o sistema e gerencia escolhas do usuário
void iniciar_sistema(database *db);

//Delega os módulos corretos de acordo com a opção do usuário
void processar_sistema(database *db, int opcao);

//Exibe o menu principal para o usuário
void exibir_menu();

#endif