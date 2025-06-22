// Implementação

#include "usuario.h"
#include <stdio.h>
#include <stdlib.h>

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
