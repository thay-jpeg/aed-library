//Implementação

#include "usuario.h"
#include <stdio.h>

void cadastrar_usuario(FILE *arq_usuarios) {
    usuario NovoUser;
    
    printf("Codigo: ");
    scanf("%d", NovoUser.codigo);
    printf("\nNome: ");
    scanf("%[^\n]%*c ",NovoUser.nome);

    inserir_Usuario_Cabeca(arq_usuarios,NovoUser);
}

void inserir_Usuario_Cabeca(FILE *arq_usuarios, usuario UserParaInserir){
    cabecalho *cab = le_cabecalho(arq_usuarios);
    UserParaInserir.prox_pos = cab->pos_cabeca;
    if (cab->pos_livre == -1){
        escreve_usuario(arq_usuarios, &UserParaInserir, cab->pos_topo);
        cab->pos_cabeca = cab->pos_topo;
        cab->pos_topo++;
    }else{
        usuario *aux = le_usuario(arq_usuarios, cab->pos_livre);
        escreve_usuario(arq_usuarios, &UserParaInserir, cab->pos_livre);
        cab->pos_cabeca = cab->pos_livre;
        cab->pos_livre = aux->prox_pos;
        free(aux);
    }
    escreve_cabecalho(arq_usuarios, cab);
    free(cab);
}