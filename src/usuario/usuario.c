//Implementação

#include "usuario.h"
#include "../../bin/system.h"
#include <stdio.h>
#include <stdlib.h> 

/*Propósito: Serve como a interface para o usuário do sistema registrar um novo
    usuário. A função solicita o código e o nome, e em seguida chama a
    função auxiliar 'inserir_Usuario_Cabeca' para salvar os dados no arquivo.
    
Pré-condições:
    - O ponteiro 'arq_usuarios' deve ser válido e o arquivo deve estar aberto em
    modo que permita leitura e escrita (ex: "r+b").
    - A função 'inserir_Usuario_Cabeca' deve estar implementada e acessível.

Pós-condições:
    - Um novo registro de usuário é inserido no arquivo 'arq_usuarios' através da
    chamada da função 'inserir_Usuario_Cabeca'.
    - Mensagens de interação e de sucesso são exibidas na tela para o usuário.
*/
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


/*
Propósito: Insere um registro de usuário no início da lista encadeada dentro
    do arquivo binário. Esta função gerencia a lógica de reutilização de
    espaços (lista de livres) ou de inserção no final do arquivo (topo).

Pré-condições:
    - O ponteiro 'arq_usuarios' deve ser válido e o arquivo estar aberto em "r+b".
    - O arquivo deve ter um cabeçalho ('cabecalho') formatado corretamente.
    - A struct 'UserParaInserir' deve conter os dados do usuário a ser salvo.

Pós-condições:
    - O registro contido em 'UserParaInserir' é salvo no arquivo 'arq_usuarios'.
    - O cabeçalho do arquivo é atualizado para refletir a nova cabeça da lista('pos_cabeca') 
    e, se aplicável, o novo topo ('pos_topo') ou a nova cabeçada lista de livres ('pos_livre').
*/
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