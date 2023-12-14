#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "../defs.h"
#include "funcs.h"

#define MAX_TABLE_NAME 20
#define MAX_NAMES_CONTENT 100
#define MAX_COL_TYPE 10
#define MAX_COL_NAME 25
#define MAX_FILE_NAME 25

void createTable() {
    char tableName[MAX_TABLE_NAME];
    char tableOfNamesContent[MAX_NAMES_CONTENT];
    FILE *tableOfNames;

    tableOfNames = fopen("txts/main.txt", "r+");

    //verifica se o arquivo existe
    if (tableCheckError(tableOfNames)) {
        return;
    }

    readTableContent(tableOfNames, tableOfNamesContent, sizeof(tableOfNamesContent));
    readTableName(tableName);

    if (isnameInUse("txts/main.txt", tableName)){
        printf("Nome em uso, use outro\n");
    } else {
        int fileNameSize = strlen(tableName) + 10;
        char *fileName = malloc(fileNameSize);
        FILE *newTable;

        snprintf(fileName, fileNameSize, "txts/%s.txt", tableName);
        newTable = fopen(fileName, "w");

        if (newTable == NULL) {
            printf("Erro ao criar a tabela\n");
            free(fileName);
            return;
        }

        readColumns(newTable, fileName);

        fprintf(tableOfNames, "%s\n", tableName);

        fclose(newTable);
        free(fileName);
    }

    fclose(tableOfNames);
}

void listTables(){
    //ajeitar, ignorar nova primeiras linhas
    FILE *tableNamesFile = fopen("txts/main.txt", "r");
    char text[100];

    printf("Tabelas existentes:\n");

    while(fgets(text, 100, tableNamesFile) != NULL){
        printf("%s", text);
    }

    fclose(tableNamesFile);
}

void listDataFromTable(){
    char tableName[15];
    tablechecker(char tableName);

    //importar do txt
    //printar
}

void deleteLine(char tableName[15]){
    char pk[15];
    //verificar se a pk existe
    listDataFromTable();
    //verificar se é essa msm
    //apagar linha no txt
    listDataFromTable();
}

void dropTable(){
    char tableName[15];
    char fileName[25];

    printf("Digite a tabela que deseja deletar:\n");
    scanf(" %[^\n]", tableName);

    //if (nome existe no nameOfTables) then (oq tem aqui embaixo ) else (tabela não existe)

    sprintf(fileName, "txts/%s.txt", tableName);

    if(remove(fileName) == 0){
        printf("Tabela deletada\n");
    } else {
        printf("Erro ao deletar a tabela");
    }

}

void addData(){
    char tableName[MAX_TABLE_NAME];

    listTables();
    printf("=========================================\n");
    do{
        printf("Digite o nome de uma tabela acima adicionar dados:\n");
        scanf(" %[^\n]", tableName);
    } while(!isnameInUse("txts/main.txt", tableName));
    
    //verificar se a pk já existe
    //atualizar txt
}

void searchData(){
    char tableName[15];
    char nameCol[15];
    char filter[2];
    //bater o filtro com o tipo de dado da coluna
}
void tablechecker(char tableName[15]){
    //verificar se a tabela existe
    printf("Digite o nome da tabela:");
    scanf(" %s",tableName[15]);
    FILE *tabela= fopen(tableName[15],"r");
    if {*tabela == NULL}{
        fclose(FILE *tabela);
        printf("Essa tabela não existe.\n");
        printf("Deseja criar tabela? s/n\n");
        char resposta;
        scanf(" %s",resposta);
        switch (resposta){
            case 's': createTable(),break;
            case 'n': exit:(0),break;
        }
    }
}