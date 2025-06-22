//Funções de usuário

#ifndef USUARIO_H
#define USUARIO_H

#include <stdio.h>
#include "../../bin/storage.h"
#include "../../bin/system.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//Cadastra um usuário
void cadastrar_usuario(FILE *arq_usuarios);

//Função auxiliar para cadastrar_usuario
void inserir_Usuario_Cabeca(FILE *arq_usuarios, usuario UserParaInserir);

//Verifica se um usuário existe a partir do seu código
int buscar_usuario(FILE *arq_usuarios, int codigo);

#endif