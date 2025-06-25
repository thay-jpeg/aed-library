// Arquivo principal

#include <stdio.h>
#include "../bin/system.h"


int main()
{
    system("cls");
    database db;

    if (!abrir_database(&db))
    {
        printf("ERRO CRITICO: Nao foi possivel iniciar os arquivos de dados.\n");
        return 1;
    }

    printf("\nSistema de biblioteca iniciado com sucesso.\n");

    iniciar_sistema(&db);

    fechar_database(&db);
    printf("\nSistema encerrado. Dados salvos.\n\n");

    system("pause");
    return 0;
}