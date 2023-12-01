#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "defs.h"
#include "funcs.h"

void createTable(){
    char tableName[15];
    //verificar se já existe tabela com esse nome
    printf("Digite o nome da tabela:");
    scanf(" %s",tableName);
    FILE *tabela = fopen(tableName,"r");
    if (tabela!=NULL){
        printf("Tabela já existe.\n");
    }
    //salvar em .txt
}

void listTables(){
    char tableName[15];
    tablechecker(char tableName);
}

void listDataFromTable(){
    char tableName[15];
    tablechecker(char tableName);

    //importar do txt
    //printar
}

void deleteLine(char tableName[15]){
    tablechecker(char tableName);
    char pk[15];
    //verificar se a pk existe
    listDataFromTable()
    //verificar se é essa msm
    //apagar linha no txt
    listDataFromTable()
}

void dropTable(char tableName[15]){
    tablechecker(char tableName);
    //apagar .txt
}

void addData(char tableName[15]){
    
    listDataFromTable();
    //verificar se a pk já existe
    //atualizar txt
}

void searchData(char tableName[15]){
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
        switch (resposta){
            case 's': createTable(),break;
            case 'n': exit:(0),break;
        }
    }
}