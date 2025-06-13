//Cabeçalho

#ifndef BIBLIOTEC_H
#define BIBLIOTEC_H

#include "..\bin\storage.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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
    long prox_pos; //Posição do próximo livro no arquivo
} livro;

//Armazena todas as informações de cada usuário da biblioteca
typedef struct {
    int codigo;
    char nome[TAM];
    long prox_pos;
} usuario;

//Armazena todas as informações de cada empréstimo de livros
typedef struct {
    int codigo_usuario;
    int codigo_livro;
    char data_emprestimo[MAX]; //Formato DD/MM/AAAA + '\0'
    char data_devolucao[MAX]; //Formato DD/MM/AAAA + '\0'
    long prox_pos;
} emprestimo;

//Gerencia o menu e chama as funções corretas
void processar_sistema(FILE *arq, int opcao);

//Exibe o menu principal para o usuário
void exibir_menu();

//Cadastra um livro
void cadastrar_livro(FILE *arq);

//Imprime dados de um livro
void imprimir_dados_livro(FILE *arq);

//Lista todos os livros cadastrados
void listar_livros(FILE *arq);

//Busca um livro pelo título
void buscar_titulo(FILE *arq);

//Calcula a quantidade total de livros
void calcular_total(FILE *arq);

//Cadastra um usuário
void cadastrar_usuario(FILE *arq);

//Faz o empréstimo de um livro
void emprestar_livro(FILE *arq);

//Faz a devolução de um livro
void devolver_livro(FILE *arq);

//Lista todos os livros com empréstimo
void listar_emprestimos(FILE *arq);

//Carrega um arquivo em lote de livros
void carregar_lote(FILE *arq_bin);

#endif