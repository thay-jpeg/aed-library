//Cabeçalho

#ifndef BIBLIOTEC_H
#define BIBLIOTEC_H

#include "..\bin\storage.h"

#define TAM 51
#define MAX 11

//Armazena todas as informações de cada livro
typedef struct {
    int codigo;
    char titulo[151];
    char autor[201];    
    char editora[TAM];
    int edicao;
    int ano;
    int exemplares;
} livro;

//Armazena todas as informações de cada usuário da biblioteca
typedef struct {
    int codigo;
    char nome[TAM];
} usuario;

//Armazena todas as informações de cada empréstimo de livros
typedef struct {
    int codigo_usuario;
    int codigo_livro;
    char data_emprestimo[MAX]; //Formato DD/MM/AAAA + '\0'
    char data_devolucao[MAX]; //Formato DD/MM/AAAA + '\0'
} emprestimo;

//Processa a opção que o usuario escolhe no menu
//void processar_sistema(int opção);

#endif