// Funções de livros

#ifndef LIVRO_H
#define LIVRO_H

#include <stdio.h>
#include "../../bin/storage.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

// Cadastra um livro
void cadastrar_livro(FILE *arq_livros);

// Imprime dados de um livro
void imprimir_dados_livro(FILE *arq_livros);

// Lista todos os livros cadastrados
void listar_livros(FILE *arq_livros);

// Busca um livro pelo título
void buscar_titulo(FILE *arq_livros);

// Calcula a quantidade total de livros
void calcular_total(FILE *arq_livros);

// Carrega um arquivo em lote de livros
void carregar_lote(database *db);

#endif