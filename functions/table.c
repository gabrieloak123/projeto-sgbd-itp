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

//só lê o arquivo main linha por linha mesmo
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

    //importar do txt
    //printar
}

void deleteLine(){
    char tableName[15];
    char pk[15];
    //verificar se a pk existe
    listDataFromTable();
    //verificar se é essa msm
    //apagar linha no txt
    listDataFromTable();
}

/*verifica se a tabela digitada existe no arquivo main e, caso
positivo, cria um arquivo temp com todas as tabelas antigas menos
a indesejada, daí apaga o main antigo e renomeia o temp*/
void dropTable() {
    char tableName[15];
    char fileName[25];
    char confirmDrop;

    listTables();
    printf("\n");
    printf("Digite a tabela que deseja deletar:\n");
    scanf(" %[^\n]", tableName);

    sprintf(fileName, "txts/%s.txt", tableName);
    if (access(fileName, F_OK) != -1) {
        printf("Tem certeza que deseja deletar a tabela %s? (S/N)\n", tableName);
        scanf(" %c", &confirmDrop);

        if (confirmDrop == 'S' || confirmDrop == 's') {
            if (remove(fileName) == 0) {
                printf("Tabela deletada\n");

                FILE *tableOfNames, *temp;
                char buffer[MAX_NAMES_CONTENT];
                char tableContent[MAX_NAMES_CONTENT];
                
                tableOfNames = fopen("txts/main.txt", "r");
                tableCheckError(tableOfNames);

                temp = fopen("txts/temp.txt", "w");
                tableCheckError(tableOfNames);

                readTableContent(tableOfNames, tableContent, sizeof(tableContent));
                
                char *tableStart = strstr(tableContent, tableName);
                if (tableStart != NULL) {
                    char *tableEnd = strchr(tableStart, '\n');
                    if (tableEnd != NULL) {
                        // Copiar a parte antes da tabela para o arquivo temporário
                        fwrite(tableContent, sizeof(char), tableStart - tableContent, temp);
                        // Copiar a parte após a tabela para o arquivo temporário
                        fwrite(tableEnd + 1, sizeof(char), strlen(tableEnd + 1), temp);
                    }
                }
                fclose(tableOfNames);
                fclose(temp);

                remove("txts/main.txt");
                rename("txts/temp.txt", "txts/main.txt");
            } else {
                printf("Erro ao deletar a tabela\n");
            }
        } else {
            printf("Operacao cancelada\n");
        }
    } else {
        printf("Tabela nao encontrada\n");
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