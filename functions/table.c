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
    
    tableOfNames = fopen("txts/tableNames.txt", "r++");

    //verifica se abriu direito
    tableCheckError(tableOfNames);
    
    printf("Digite o nome da tabela:");
    scanf(" %[^\n]", tableName);

    //verificar se o conteúdo foi lido direito
    if(fread(&tableOfNamesContent, sizeof(char), 100, tableOfNames) == 0){
        perror("Erro ao ler o conteúdo");
        fclose(tableOfNames);
        return;
    }

    //verifica se o nome digitado já está em uso
    if(nameInUse(tableName, tableOfNamesContent)){
        printf("Nome em uso, use outro\n");
    } else {
        FILE *newTable;

        //manipula o nome do arquivo
        char fileName[25];
        sprintf(fileName, "txts/%s.txt", tableName);
        newTable = fopen(fileName, "w");

        //input genérico só pra ver se o arquivo funciona
        char *text = "olá mundo";
        fwrite(text, sizeof(char), strlen(text), newTable);

        //adiciona o nome da tabela no arquivo de nomes(tem que ajeitar o \n)
        fwrite(strcat(tableName, "\n"), sizeof(char), strlen(tableName), tableOfNames);
        fclose(tableOfNames);

        char colType[10];
        char colName[25];
        while(strcmp("stop", colName)){
            scanf("%s %s", colType, colName);

        }
        fclose(newTable);
    }

    //adicionar o nome no tableNamesFile
    //caso não exista entrar no loop de declaração de atributos
        //criar o arquivo daquela tabela
        //verificar se o tipo é válido
        //verificar se o nome já existe


    // while(strcmp("stop", attribute)){
    //     //ler nome do atributo
    // }
    
    //verificar se já existe tabela com esse nome

    //salvar em .txt
}

void listTables(){
    char tableName[15];
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

void dropTable(char tableName[15]){
    //apagar .txt
}

void addData(char tableName[15]){
    
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