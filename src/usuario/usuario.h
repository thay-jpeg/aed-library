//Funções de usuário

#ifndef USUARIO_H
#define USUARIO_H

#include <stdio.h>
#include "../../bin/storage.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//Cadastra um usuário
void cadastrar_usuario(FILE *arq_usuarios);

void inserir_Usuario_Cabeca(FILE *arq_usuarios, usuario UserParaInserir);


#endif