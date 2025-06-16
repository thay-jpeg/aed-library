// Declaração de estruturas

#ifndef STORAGE_H
#define STORAGE_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAX_NOME 51
#define MAX_EDITORA 51
#define MAX_DATA 11
#define MAX_TITULO 151
#define MAX_AUTOR 201

// Cabeçalho do arquivo
typedef struct
{
    int pos_cabeca;
    int pos_topo;
    int pos_livre;
} cabecalho;

// Banco de dados
typedef struct
{
    FILE *arq_livros;
    FILE *arq_usuarios;
    FILE *arq_emprestimos;
} database;

// Armazena todas as informações de cada livro
typedef struct
{
    int codigo;
    char titulo[MAX_TITULO];
    char autor[MAX_AUTOR];
    char editora[MAX_EDITORA];
    int edicao;
    int ano;
    int exemplares;
    long prox_pos; // Posição do próximo livro no arquivo
} livro;

// Armazena todas as informações de cada usuário da biblioteca
typedef struct
{
    int codigo;
    char nome[MAX_NOME];
    long prox_pos;
} usuario;

// Armazena todas as informações de cada empréstimo de livros
typedef struct
{
    int codigo_usuario;
    int codigo_livro;
    char data_emprestimo[MAX_DATA]; // Formato DD/MM/AAAA + '\0'
    char data_devolucao[MAX_DATA];  // Formato DD/MM/AAAA + '\0'
    long prox_pos;
} emprestimo;

#endif