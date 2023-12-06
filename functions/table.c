#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../defs.h"
#include "funcs.h"

void createTable(){
    char tableName[15];
    char tableOfNamesContent[100];
    FILE *tableOfNames;
    
    //é melhor só adicionar o nome da tabela no fim, pra garantir que tabelas abortadas n salvem
    tableOfNames = fopen("txts/tableNames.txt", "r+");

    //verifica se abriu direito
    if(tableCheckError(tableOfNames)){
        return;
    };
    
    readTableName(tableName);
    

    //verifica se o nome digitado já está em uso
    if(nameInUse(tableName, tableOfNamesContent)){
        printf("Nome em uso, use outro\n");
    } else {
        FILE *newTable;
        char colType[10];
        char colName[25];
        char fileName[25];

        //manipula o nome do arquivo
        sprintf(fileName, "txts/%s.txt", tableName);
        newTable = fopen(fileName, "r+");

        //input genérico só pra ver se o arquivo funciona
        char format[30];
        sprintf(format, "%s\n", tableName);
        fwrite(format, sizeof(char), strlen(format), newTable);

        format = "===============================\n";
        fwrite(format, sizeof(char), strlen(format), newTable);

        //adiciona o nome da tabela no arquivo de nomes(tem que ajeitar o \n)
        fwrite(strcat(tableName, "\n"), sizeof(char), strlen(tableName), tableOfNames);
        fclose(tableOfNames);

        //cadastrar os atributos
        while(true){
            scanf("%s %s", colType, colName);

            if(strcmp("stop", colType) == 0){
                break;
            }

            if(typeAllowed(colType)){
                //função q verifica o nome das colunas
                if(nameInUse(colName, newTable)){
                    char text[25];
                    sprintf(text, "%s - %s\n", colType, colName);
                } else {
                    printf("Nome de coluna já em uso\n");
                }

            } else {
                printf("Digite um tipo válido");
            }
        }

        fwrite(format, sizeof(char), strlen(format), newTable);


        fclose(newTable);
    }
}

void listTables(FILE *tableNamesFile){
    tableNamesFile = fopen("txts/tableNames.txt", "r");
    char text[100];

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
    char tableName[15];
    
    listDataFromTable();
    //verificar se a pk já existe
    //atualizar txt
}

void searchData(){
    char tableName[15];
    char nameCol[15];
    char filter[2];
    //bater o filtro com o tipo de dado da coluna
}