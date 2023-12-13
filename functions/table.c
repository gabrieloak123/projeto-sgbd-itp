#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../defs.h"
#include "funcs.h"

/*#define MAX_TABLE_NAME 20
#define MAX_NAMES_CONTENT 100
#define MAX_COL_TYPE 10
#define MAX_COL_NAME 25
#define MAX_FILE_NAME 25*/

extern char tableNames[MAX_TABLE_NAME][MAX_NUM_TABLES];
extern int numTables;

void createTable() {
    char tableName[MAX_TABLE_NAME];
    Table newTable;
    newTable.numColumns = 0;
    newTable.numRows = 0;
    readMain();

    printf("Digite o nome da tabela:\n");
    scanf(" %[^\n]", tableName);
    while (isTableNameInUse(tableName) == 1){
        printf("Nome já em uso, digite outro:\n");
        scanf(" %[^\n]", tableName);
    }

    strcpy(tableNames[numTables], tableName);
    numTables++;
    readColumns(&newTable);
    writeMain();
    writeTable(&newTable, tableName);
}

void listTables(){
    readMain();     // Eu acho que é melhor a gente não chamar essa função dentro de outras, mas sim na main
    for(int i = 0; i < numTables; i++){
        printf("%s\n", tableNames[i]);
    }
}

void listDataFromTable(){
    char tableName[MAX_TABLE_NAME];
    Table readingTable;

    printf("Digite o nome da tabela:\n");
    scanf(" %[^\n]", tableName);

    readTable(&readingTable, tableName);

    printf("Tabela: %s\n", tableName);
    for(int i = 0; i < readingTable.numColumns; i++){
        printf("%-15s", readingTable.columns[i].name);
    }
    printf("\n");

    for(int i = 0; i < readingTable.numColumns; i++){
        for(int j = 0; j < 15; j++) printf("-");
    }
    printf("\n");

    for(int i = 0; i < readingTable.numRows; i++){
        for(int j = 0; j < readingTable.numColumns; j++){
            switch(readingTable.columns[j].type){
                case INT:
                    printf("%-15d", readingTable.columns[j].Data.intData[i]);
                    break;
                case FLOAT:
                    printf("%-15.2f", readingTable.columns[j].Data.floatData[i]);
                    break;
                case DOUBLE:
                    printf("%-15.2lf", readingTable.columns[j].Data.doubleData[i]);
                    break;
                case CHAR:
                    printf("%-15c", readingTable.columns[j].Data.charData[i]);
                    break;
                case STRING:
                    printf("%-15s", readingTable.columns[j].Data.stringData[i]);
                    break;
            }
        }
        printf("\n");
    }
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