//Implementação

#include "emprestimo.h"
#include <stdio.h>
#include <time.h> 
#include <string.h>
#include "../livro/livro.h"
#include "../../bin/system.h"


void emprestar_livro(FILE *arq_livros, FILE *arq_usuarios, FILE *arq_emprestimos) {
   int codigo_livro, codigo_usuario;
    (void)arq_usuarios; // evita warning de parâmetro não usado por enquanto (se tirar da warning)

    printf("\n=========== Emprestar Livro ===========\n");

    printf("Digite o codigo do livro: ");
    scanf("%d%*c", &codigo_livro);
    printf("Digite o codigo do usuario: ");
    scanf("%d%*c", &codigo_usuario);

    // busca a posição do livro no arquivo para poder atualizar
    int pos_livro = buscar_pos_livro(arq_livros, codigo_livro);

    if (pos_livro == -1) {
        printf("ERRO: Livro com codigo %d nao encontrado.\n", codigo_livro);
        return;
    }

    // Le o livro da posicoe encontrada para verificar os exemplares
    livro *livro_para_emprestar = le_livro(arq_livros, pos_livro);

    // "caso n haja exemplares disponiveis, uma mensagem do tipo 'Não há exemplares disponíveis' deve ser mostrada" 
    if (livro_para_emprestar->exemplares <= 0) {
        printf("\nNao ha exemplares disponiveis\n"); 
        free(livro_para_emprestar);
        return;
    }

    // se as validacoes passaram, o empristimo pode ser feito
    // diminuindo de 1 o numero de exemplares disponveis do respectivo livroo 
    livro_para_emprestar->exemplares--; 
    escreve_livro(arq_livros, livro_para_emprestar, pos_livro);
    
    //prepara o novo registro de emprestimo
    emprestimo novo_emprestimo;
    novo_emprestimo.codigo_livro = codigo_livro;
    novo_emprestimo.codigo_usuario = codigo_usuario;
    strcpy(novo_emprestimo.data_devolucao, ""); // Deixa a data de devolução vazia

    //obtem a data atual do sistema, conforme requisito 
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    

    //usa strftime, a função ideal para formatar data/hora de forma segura
    strftime(novo_emprestimo.data_emprestimo, sizeof(novo_emprestimo.data_emprestimo), "%d/%m/%Y", &tm);
    
    // "registra o emprestimo"  no final do arquivo
    fseek(arq_emprestimos, 0, SEEK_END);
    fwrite(&novo_emprestimo, sizeof(emprestimo), 1, arq_emprestimos);

    printf("\n>>> Emprestimo realizado com sucesso! <<<\n");
    printf("Livro '%s' emprestado em %s.\n", livro_para_emprestar->titulo, novo_emprestimo.data_emprestimo);

    free(livro_para_emprestar);      
}

// Entrada: Ponteiros para os arquivos de livros, usuários e emprestimos.
// Retorno: nenhum
// Pré-condição: Os ponteiros de arquivo devem ser válidos e abertos em "r+b".
// Pós-condição: O registro do emprestimo eh atualizado com a data de devolução
// e o estoque do livro eh incrementado, ou uma mensagem de erro eh exibida.
//void devolver_livro(FILE *arq_emprestimos) {}


// Entrada: Ponteiros para os arquivos de livros, usuários e emprestimos.
// Retorno: nenhum
// Pré-condição: Os ponteiros de arquivo devem ser vzlidos e abertos em "r+b".
// Pós-condição: Uma lista de empréstimos ativos eh exibida na tela, com os
//  nomes dos usuários e titulos dos livros. 
void listar_emprestimos(FILE *arq_emprestimos) {
    
}