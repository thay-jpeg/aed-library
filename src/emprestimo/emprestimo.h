//Funções de empréstimo

#ifndef EMPRESTIMO_H
#define EMPRESTIMO_H

#include <stdio.h>
#include "../../bin/storage.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//Faz o empréstimo de um livro
void emprestar_livro(database *db);

//Faz a devolução de um livro
void devolver_livro(database *db);

//Lista todos os livros com empréstimo
void listar_emprestimos(database *db);

// Função auxiliar que valida e salva a transação de empréstimo
void registra_emprestimo(database *db, int codigo_livro, int codigo_usuario, char* data_emprestimo, char *data_devolucao);

#endif