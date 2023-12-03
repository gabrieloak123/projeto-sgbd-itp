#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../defs.h"
#include "funcs.h"

void createTable(){
    char tableName[15];
    char attribute[25];

    FILE *tableOfNames;
    char content[100];
    
    tableOfNames = fopen("txts/tableNames.txt", "r++");
    
    printf("Digite o nome da tabela:");
    scanf(" %[^\n]", tableName);
    fread(&content, sizeof(char), 100, tableOfNames);

    if(nameInUse(tableName, content)){
        printf("Nome em uso, use outro\n");
    } else {
        //escrever adicionar o nome da tabela no txt
    }

    fclose(tableOfNames);
    

    //verificar se o nome já existe no tableNamesFile
    //se existir pedir outro nome
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
    //apagar .txt
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