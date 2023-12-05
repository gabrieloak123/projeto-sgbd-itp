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
        printf("Erro ao deletar a tabela")
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