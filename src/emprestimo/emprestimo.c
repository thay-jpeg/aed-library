//Implementação

#include "emprestimo.h"
#include <stdio.h>
#include <time.h> 
#include <string.h>
#include "../livro/livro.h"
#include "../usuario/usuario.h"
#include "../../bin/system.h"

/*Propósito: Orquestra o processo completo de empréstimo de um livro.
    A funçãosolicita os códigos do livro e do usuário, valida a existência e a
    disponibilidade do livro, decrementa o estoque de exemplares e registra a
    transação de empréstimo com a data atual do sistema

Pré-condições:
    - Os ponteiros de arquivo ('arq_livros', 'arq_usuarios', 'arq_emprestimos')devem ser
    válidos e apontar para arquivos abertos em modo de leitura eescrita (ex: "r+b").
    - O arquivo 'arq_livros' deve estar formatado com um cabeçalho válido.
    - As funções auxiliares (buscar_pos_livro, le_livro, escreve_livro) devem estar implementadas e acessíveis.

Pós-condições:
    - Se o emprestimo for bem-sucedido:
    - O número de exemplares do livro eh decrementado em 1 em 'arq_livros'
    - Um novo registro de empréstimo eh adicionado ao final de 'arq_emprestimos' 
    - Uma mensagem de sucesso eh exibida na tela
    - Se o livro nao for encontrado ou não tiver exemplares:
    - Nenhum arquivo eh modificado.
    - Uma mensagem de erro apropriada é exibida na tela. 
 */

static void insere_emprestimo_cabeca(FILE *arq, emprestimo novo)
{

    cabecalho *cab = le_cabecalho(arq);
    novo.prox_pos = cab->pos_cabeca;

    if (cab->pos_livre == -1)
    { // sem emprestimos para reciclar a posicao
        escreve_emprestimo(arq, &novo, cab->pos_topo);
        cab->pos_cabeca = cab->pos_topo; // a cabeca da lista agora eh a onde colocamos o novo emprestimo
        cab->pos_topo++;
    }
    else
    {
        emprestimo *aux = le_emprestimo(arq, cab->pos_livre);
        escreve_emprestimo(arq, &novo, cab->pos_livre);
        cab->pos_cabeca = cab->pos_livre;
        cab->pos_livre = aux->prox_pos;
        free(aux);
    }
    escreve_cabecalho(arq, cab);
    free(cab);
}

void registra_emprestimo(database *db, int codigo_livro, int codigo_usuario, char* data_emprestimo, char *data_devolucao) {

    if (!buscar_usuario(db->arq_usuarios, codigo_usuario)) {
        printf("\nERRO: Usuario com codigo %03d nao encontrado.\n", codigo_usuario);
        return;
    }

    int pos_livro = buscar_pos_livro(db->arq_livros, codigo_livro);

    if (pos_livro == -1) {
        printf("\nERRO: Livro com codigo %03d nao encontrado.\n", codigo_livro);
        return;
    }

    livro *livro_para_emprestar = le_livro(db->arq_livros, pos_livro);

    if (livro_para_emprestar->exemplares <= 0) {
        printf("\nSentimos muito, mas nao ha exemplares do livro '%s' disponiveis para emprestimo.\n", livro_para_emprestar->titulo); 
        free(livro_para_emprestar);
        return;
    }

    livro_para_emprestar->exemplares--; 
    escreve_livro(db->arq_livros, livro_para_emprestar, pos_livro);
    
    emprestimo novo_emprestimo;
    novo_emprestimo.codigo_livro = codigo_livro;
    novo_emprestimo.codigo_usuario = codigo_usuario;
    
    if(strcmp(data_emprestimo, "") == 0) {

        //obtem a data atual do sistema, conforme requisito 
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        
        //para formatar data
        strftime(novo_emprestimo.data_emprestimo, sizeof(novo_emprestimo.data_emprestimo), "%d/%m/%Y", &tm);
    }

    else {
        strcpy(novo_emprestimo.data_emprestimo, data_emprestimo);
    }

    strcpy(novo_emprestimo.data_devolucao, data_devolucao);
    
    insere_emprestimo_cabeca(db->arq_emprestimos, novo_emprestimo);

    printf("\n>>> Emprestimo realizado com sucesso! <<<\n");
    printf("Livro '%s' emprestado em %s.\n", livro_para_emprestar->titulo, novo_emprestimo.data_emprestimo);

    free(livro_para_emprestar);
}

void emprestar_livro(database *db) {

    int codigo_livro, codigo_usuario;

    printf("\n============= Emprestar Livro =============\n");

    printf("Digite o codigo do livro: ");
    scanf("%d%*c", &codigo_livro);
    printf("Digite o codigo do usuario: ");
    scanf("%d%*c", &codigo_usuario);
    
    registra_emprestimo(db, codigo_livro, codigo_usuario, "", "");

    printf("\n===========================================\n");
}

//void devolver_livro(FILE *arq_emprestimos) {}

//void listar_emprestimos(FILE *arq_emprestimos) {}