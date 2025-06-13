//Implementação

#include "livro.h"
#include <stdio.h>

void cadastrar_livro(FILE *arq_livros) {

    cabecalho cab;

    fseek(arq_livros, 0, SEEK_SET);
    fread(&cab, sizeof(cabecalho), 1, arq_livros);

    livro novo_livro;

    printf("\n===== Cadastro de novo livro =====\n");
    printf("Digite as credenciais a seguir:\n");
    printf("Codigo: ");
    scanf("%d%*c", &novo_livro.codigo);
    printf("Titulo (MAX. 150 carac.): ");
    scanf("%150[^\n]%*c", novo_livro.titulo);
    printf("Autor (MAX. 200 carac.): ");
    scanf("%200[^\n]%*c", novo_livro.autor);
    printf("Editora (MAX. 50 carac.): ");
    scanf("%50[^\n]%*c", novo_livro.editora);
    printf("Numero da edicao: ");
    scanf("%d%*c", &novo_livro.edicao);
    printf("Ano: ");
    scanf("%d%*c", &novo_livro.ano);
    printf("Quantidade de exemplares: ");
    scanf("%d%*c", &novo_livro.exemplares);
    printf("====================================\n");

    //Inserção na cabeça
    novo_livro.prox_pos = cab.pos_cabeca;

    fseek(arq_livros, cab.pos_topo, SEEK_SET);
    fwrite(&novo_livro, sizeof(livro), 1, arq_livros);

    cab.pos_cabeca = cab.pos_topo;
    cab.pos_topo = ftell(arq_livros);

    fseek(arq_livros, 0, SEEK_SET);
    fwrite(&cab, sizeof(cabecalho), 1, arq_livros);

    printf("\n Livro cadastrado com sucesso!\n");
}

//void imprimir_dados_livro(FILE *arq_livros) {}

//void listar_livros(FILE *arq_livros) {}
 
//void buscar_titulo(FILE *arq_livros) {}

//void calcular_total(FILE *arq_livros) {}

//void carregar_lote(FILE *arq_livros) {}