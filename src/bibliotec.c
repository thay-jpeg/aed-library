//Implementação

#include <stdio.h>
#include "bibliotec.h"

void exibir_menu() {

    printf("\n================================================\n");
    printf("      SISTEMA DE GERENCIAMENTO DA BIBLIOTECA     \n");
    printf("\n================================================\n\n");
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
    printf("0- Sair\n\n");
    printf("\n================================================\n\n");

    printf("Digite a opcao que deseja:\n");
}

//Entrada: Valor inteiro que representa a escolha do usuário no menu
//Retorno: nenhum
//Pré-condição: nenhuma
//Pós-condição: A ação correspondente à opção será executada
void processar_sistema(FILE *arq, int opcao) {
    switch (opcao)
    {
    case 1: cadastrar_livro(arq); break;
    case 2: imprimir_dados_livro(arq); break;
    case 3: listar_livros(arq); break;
    case 4: buscar_titulo(arq); break;
    case 5: calcular_total(arq); break;
    case 6: cadastrar_usuario(arq); break;
    case 7: emprestar_livro(arq); break;
    case 8: devolver_livro(arq); break;
    case 9: listar_emprestimos(arq); break;
    case 10: carregar_lote(arq); break;
    case 0: break;
    default: printf("Opcao invalida. Tente novamente.\n"); break;
    }
}