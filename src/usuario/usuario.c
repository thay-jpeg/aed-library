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
    printf("\n=========== Cadastro de Usuario ===========\n");
    printf("\nDigite o codigo do usuario: ");
    scanf("%d%*c", &NovoUser.codigo);
    printf("Digite o nome do usuario (MAX. 50 carac.): ");
    scanf(" %50[^\n]%*c",NovoUser.nome);

    printf("\n===========================================\n");

    inserir_Usuario_Cabeca(arq_usuarios,NovoUser);
    printf("\nUsuario cadastrado com sucesso...\n");
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

