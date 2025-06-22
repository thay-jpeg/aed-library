// Implementação

#include "emprestimo.h"
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "../livro/livro.h"
#include "../usuario/usuario.h"
#include "../usuario/usuario.h"
#include "../../bin/system.h"


// Entrada: Ponteiro para o arquivo de empréstimos e uma struct 'emprestimo' com os dados.
// Retorno: nenhum
// Pré-condição: O ponteiro de arquivo deve ser valido e aberto em "r+b". A struct 'novo' deve estar preenchida.
// Pós-condição: O registro do empréstimo eh inserido no início da lista encadeada no arquivo e o cabeçalho eh atualizado.
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

// Entrada: Ponteiro para a 'database', códigos do livro e usuário, e strings para as datas.
// Retorno: nenhum
// Pré-condição: Ponteiro 'db' deve ser válido. As strings de data podem ser vazias.
// Pós-condição: Valida e registra a transação de empréstimo, seja de forma interativa (data atual) ou em lote (data pré-definida).
void registra_emprestimo(database *db, int codigo_livro, int codigo_usuario, char *data_emprestimo, char *data_devolucao)
{

    int pos_usuario = buscar_pos_usuario(db->arq_usuarios, codigo_usuario);

    if (pos_usuario == -1)
    {
        printf("\nERRO: Usuario com codigo %03d nao encontrado.\n", codigo_usuario);
        return;
    }

    int pos_livro = buscar_pos_livro(db->arq_livros, codigo_livro);

    if (pos_livro == -1)
    {
        printf("\nERRO: Livro com codigo %03d nao encontrado.\n", codigo_livro);
        return;
    }

    if (buscar_pos_emprestimo(db->arq_emprestimos, codigo_livro, codigo_usuario) != -1)
    {
        printf("\nERRO: Este usuario ja possui um emprestimo ativo para este livro e nao pode empresta-lo novamente.\n");
        return; // impede o novo empréstimo
    }

    livro *livro_para_emprestar = le_livro(db->arq_livros, pos_livro);

    if (livro_para_emprestar->exemplares <= 0)
    {
        printf("\nSentimos muito, mas nao ha exemplares do livro '%s' disponiveis para emprestimo.\n", livro_para_emprestar->titulo);
        free(livro_para_emprestar);
        return;
    }

    livro_para_emprestar->exemplares--;
    escreve_livro(db->arq_livros, livro_para_emprestar, pos_livro);

    emprestimo novo_emprestimo;
    novo_emprestimo.codigo_livro = codigo_livro;
    novo_emprestimo.codigo_usuario = codigo_usuario;

    if (strcmp(data_emprestimo, "") == 0)
    {

        // obtem a data atual do sistema, conforme requisito
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);

        // para formatar data
        strftime(novo_emprestimo.data_emprestimo, sizeof(novo_emprestimo.data_emprestimo), "%d/%m/%Y", &tm);
    }

    else
    {
        strcpy(novo_emprestimo.data_emprestimo, data_emprestimo);
    }

    strcpy(novo_emprestimo.data_devolucao, data_devolucao);

    insere_emprestimo_cabeca(db->arq_emprestimos, novo_emprestimo);

    printf("\n>>> Emprestimo realizado com sucesso! <<<\n");
    printf("Livro '%s' emprestado em %s.\n", livro_para_emprestar->titulo, novo_emprestimo.data_emprestimo);

    free(livro_para_emprestar);
    free(livro_para_emprestar);
}

// Entrada: Ponteiro para a struct 'database'.
// Retorno: nenhum
// Pré-condição: O ponteiro 'db' deve ser valido e os arquivos dentro dele abertos.
// Pós-condição: Solicita os códigos ao usuario e chama 'registra_emprestimo' para executar a logica do emprestimo.
void emprestar_livro(database *db)
{

    int codigo_livro, codigo_usuario;

    printf("\n===================== Emprestar Livro =====================\n");

    printf("Digite o codigo do livro: ");
    scanf("%d%*c", &codigo_livro);
    printf("Digite o codigo do usuario: ");
    scanf("%d%*c", &codigo_usuario);

    registra_emprestimo(db, codigo_livro, codigo_usuario, "", "");

    printf("===========================================================\n");
}

int buscar_pos_emprestimo(FILE *arq_emprestimo, int codigo_livro, int codigo_usuario)
{

    cabecalho *c = le_cabecalho(arq_emprestimo);
    if (!c)
        return -1;

    int pos_atual = c->pos_cabeca;
    free(c);

    while (pos_atual != -1)
    {

        emprestimo *emprestimo_atual = le_emprestimo(arq_emprestimo, pos_atual);

        if (emprestimo_atual)
        {
            if (emprestimo_atual->codigo_livro == codigo_livro && emprestimo_atual->codigo_usuario == codigo_usuario)
            {
                if (strlen(emprestimo_atual->data_devolucao) == 0)
                {

                    free(emprestimo_atual);
                    return pos_atual; // Retorna a posição se encontrou
                }
            }
            int proxima_pos = emprestimo_atual->prox_pos;
            free(emprestimo_atual);
            pos_atual = proxima_pos;
        }
        else
        {
            pos_atual = -1; // Sai do loop em caso de erro
        }
    }
    return -1; // Retorna -1 se não encontrou
}

static void registra_devolucao(database *db, int codigo_livro, int codigo_usuario)
{

    int pos_usuario = buscar_pos_usuario(db->arq_usuarios, codigo_usuario);

    if (pos_usuario == -1)
    {
        printf("\nERRO: Usuario com codigo %03d nao encontrado.\n", codigo_usuario);
        return;
    }

    int pos_livro = buscar_pos_livro(db->arq_livros, codigo_livro);

    if (pos_livro == -1)
    {
        printf("\nERRO: Livro com codigo %03d nao encontrado.\n", codigo_livro);
        return;
    }

    usuario *usuario_devolucao = le_usuario(db->arq_usuarios, pos_usuario);
    livro *livro_devolucao = le_livro(db->arq_livros, pos_livro);
    livro_devolucao->exemplares++;

    int pos_emprestimo = buscar_pos_emprestimo(db->arq_emprestimos, codigo_livro, codigo_usuario);

    if (pos_emprestimo == -1)
    {
        printf("\nERRO: Nao foi possivel encontrar o emprestimo de %s do livro '%s'.\n", usuario_devolucao->nome, livro_devolucao->titulo);
        free(livro_devolucao);
        free(usuario_devolucao);
        return;
    }

    emprestimo *devolucao = le_emprestimo(db->arq_emprestimos, pos_emprestimo);

    // obtem a data atual do sistema, conforme requisito
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    // para formatar data
    strftime(devolucao->data_devolucao, sizeof(devolucao->data_devolucao), "%d/%m/%Y", &tm);

    escreve_livro(db->arq_livros, livro_devolucao, pos_livro);
    escreve_emprestimo(db->arq_emprestimos, devolucao, pos_emprestimo);

    printf("\n>>> Devolucao realizada com sucesso! <<<\n");
    printf("Livro '%s' devolvido em %s.\n", livro_devolucao->titulo, devolucao->data_devolucao);

    free(livro_devolucao);
    free(usuario_devolucao);
    free(devolucao);
}

// Entrada: Ponteiro para a struct 'database'.
// Retorno: nenhum
// Pré-condição: O ponteiro 'db' e os arquivos dentro dele devem ser válidos e abertos.
// Pós-condição: O registro do empréstimo eh atualizado com a data de devolução e o estoque do livro eh incrementado.
void devolver_livro(database *db)
{

    int codigo_livro, codigo_usuario;

    printf("\n===================== Devolver Livro ======================\n");

    printf("Digite o codigo do livro: ");
    scanf("%d%*c", &codigo_livro);
    printf("Digite o codigo do usuario: ");
    scanf("%d%*c", &codigo_usuario);

    registra_devolucao(db, codigo_livro, codigo_usuario);

    printf("===========================================================\n");
}

// Entrada: Ponteiro para a struct 'database' contendo os arquivos de dados abertos.
// Retorno: nenhum
// Pré-condição: O ponteiro 'db' e os ponteiros de arquivo dentro dele devem ser válidos e os arquivos devem estar abertos.
// Pós-condição: Uma lista formatada de todos os empréstimos ativos eh exibida na tela, incluindo dados do usuário e do livro. Nenhum arquivo eh modificado.
// void listar_emprestimos(FILE *arq_emprestimos) {}