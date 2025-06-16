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
    
}