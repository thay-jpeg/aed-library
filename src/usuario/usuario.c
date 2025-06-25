// Implementação

#include "usuario.h"
#include <stdio.h>
#include <stdlib.h>


// Entrada: Ponteiro para o arquivo de usuarios.
// Retorno: nenhum
// Pré-condição: O ponteiro de arquivo deve ser valido e aberto em "r+b".
// Pós-condição: Um novo usuario, com dados informados pelo console, eh inserido no arquivo.
void cadastrar_usuario(FILE *arq_usuarios) {
    usuario NovoUser;

    printf("\n=============================== Cadastro de Usuario ==================================\n");

    printf("\nDigite o codigo do usuario: ");
    scanf("%d%*c", &NovoUser.codigo);
    printf("Digite o nome do usuario (MAX. 50 carac.): ");
    scanf(" %50[^\n]%*c",NovoUser.nome);
    
    inserir_Usuario_Cabeca(arq_usuarios,NovoUser);

    printf("\nUsuario cadastrado com sucesso!\n");

    printf("\n======================================================================================\n");

}

// Entrada: Ponteiro para o arquivo de usuários e uma struct 'usuario' com os dados.
// Retorno: nenhum
// Pré-condição: O ponteiro de arquivo deve ser valido e aberto em "r+b". A struct 'UserParaInserir' deve estar preenchida.
// Pós-condição: O registro do usuário eh inserido no início da lista encadeada no arquivo, e o cabeçalho eh atualizado.
void inserir_Usuario_Cabeca(FILE *arq_usuarios, usuario UserParaInserir){
    
    cabecalho *cab = le_cabecalho(arq_usuarios);
    UserParaInserir.prox_pos = cab->pos_cabeca;
    if (cab->pos_livre == -1){
        escreve_usuario(arq_usuarios, &UserParaInserir, cab->pos_topo);
        cab->pos_cabeca = cab->pos_topo;
        cab->pos_topo++;
    }
    else
    {
        usuario *aux = le_usuario(arq_usuarios, cab->pos_livre);
        escreve_usuario(arq_usuarios, &UserParaInserir, cab->pos_livre);
        cab->pos_cabeca = cab->pos_livre;
        cab->pos_livre = aux->prox_pos;
        free(aux);
    }
    escreve_cabecalho(arq_usuarios, cab);
    free(cab);
}

// Entrada: Ponteiro para o arquivo de usuários e o codigo do usuário a ser buscado.
// Retorno: 1 se o usuário for encontrado, 0 caso contrário.
// Pré-condição: O ponteiro de arquivo deve ser válido e o arquivo aberto em modo de leitura ("r+b").
// Pós-condição: Nenhuma, a funçao nao modifica o arquivo de usuários.
int buscar_pos_usuario(FILE *arq_usuarios, int codigo) {
    cabecalho *c = le_cabecalho(arq_usuarios);
    if (!c) return -1;

    int pos_atual = c->pos_cabeca;
    free(c);

    while (pos_atual != -1) {
        usuario *usuario_atual = le_usuario(arq_usuarios, pos_atual);
        if (usuario_atual) {
            if (usuario_atual->codigo == codigo) {
                free(usuario_atual);
                return pos_atual;
            }
            int proxima_pos = usuario_atual->prox_pos;
            free(usuario_atual);
            pos_atual = proxima_pos;
        } else {
            pos_atual = -1; // sai do loop em caso de erro
        }
    }
    return -1; // retorna -1 se não encontrou
}

// Entrada: Ponteiro para o arquivo de usuários e o codigo do usuário a ser buscado.
// Retorno: 1 se o usuário for encontrado, 0 caso contrário.
// Pré-condição: O ponteiro de arquivo deve ser válido e o arquivo aberto em modo de leitura ("r+b").
// Pós-condição: Nenhuma, a funçao nao modifica o arquivo de usuários.
int buscar_usuario(FILE *arq_usuarios, int codigo) {
    cabecalho *c = le_cabecalho(arq_usuarios);
    if (!c) return 0;

    int pos_atual = c->pos_cabeca;
    free(c);

    while (pos_atual != -1) {
        usuario *usuario_atual = le_usuario(arq_usuarios, pos_atual);
        if (usuario_atual) {
            if (usuario_atual->codigo == codigo) {
                free(usuario_atual);
                return 1;
            }
            int proxima_pos = usuario_atual->prox_pos;
            free(usuario_atual);
            pos_atual = proxima_pos;
        } else {
            pos_atual = -1; // sai do loop em caso de erro
        }
    }
    return 0; // retorna -1 se não encontrou
}

// Entrada: Ponteiro para o arquivo de usuários e o código a ser buscado.
// Retorno: String (char*) com o nome do usuário. O chamador deve liberar a memória com free().
// Pré-condição: Arquivo deve estar aberto em modo de leitura ("r+b").
// Pós-condição: Nenhuma. A função é somente leitura.
char* buscar_nome_usuario(FILE *arq_usuarios, int codigo) {
    // Primeiro, verificamos se o usuário existe
    if (!buscar_usuario(arq_usuarios, codigo)) {
         char *nao_encontrado = malloc(strlen("Usuario Desconhecido") + 1);
         strcpy(nao_encontrado, "Usuario Desconhecido");
         return nao_encontrado;
    }

    // Se o usuário existe, leia o registro para pegar o nome
    cabecalho *c = le_cabecalho(arq_usuarios);
    int pos_atual = c->pos_cabeca;
    free(c);

    while(pos_atual != -1) {
        usuario *u = le_usuario(arq_usuarios, pos_atual);
        if (u->codigo == codigo) {
            char *nome = malloc(strlen(u->nome) + 1);
            strcpy(nome, u->nome);
            free(u);
            return nome;
        }
        pos_atual = u->prox_pos;
        free(u);
    }
    return NULL; 
}
