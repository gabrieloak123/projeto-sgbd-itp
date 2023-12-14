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

    listDataFrom(tableName);
}

void addData() {
    char tableName[MAX_TABLE_NAME];
    Table table;

    printf("Digite o nome da tabela:\n");
    scanf(" %[^\n]", tableName);

    readTable(&table, tableName);

    for (int i = 0; i < table.numColumns; i++) {
        printf("Digite o valor da coluna %s (%s):\n", table.columns[i].name, dataTypeToString(table.columns[i].type));
        char value[MAX_STRING_SIZE];
        scanf(" %[^\n]", value);

        while (strlen(value) > MAX_STRING_SIZE || strlen(value) == 0) {
            printf("Valor muito grande ou vazio, digite novamente:\n");
            scanf(" %[^\n]", value);
        }

        switch (table.columns[i].type) {
            case INT:
                table.columns[i].Data.intData[table.numRows] = atoi(value);
                break;
            case FLOAT:
                table.columns[i].Data.floatData[table.numRows] = atof(value);
                break;
            case DOUBLE:
                table.columns[i].Data.doubleData[table.numRows] = atof(value);
                break;
            case CHAR:
                table.columns[i].Data.charData[table.numRows] = value[0];
                break;
            case STRING:
                strcpy(table.columns[i].Data.stringData[table.numRows], value);
                break;
        }
    }

    for (int i = 0; i < table.numRows; i++) {
        if (table.columns[table.primaryKeyIndex].Data.intData[i] == table.columns[table.primaryKeyIndex].Data.intData[table.numRows]
            || table.columns[table.primaryKeyIndex].Data.intData[table.numRows] < 0) {
            printf("Chave primária já existente, digite novamente:\n");
            return;
        }
    }

    table.numRows++;

    writeTable(&table, tableName);
}

void deleteLine(){
    char tableName[MAX_TABLE_NAME];
    int primaryKey;
    int primaryKeyIndex;
    Table table;

    printf("Digite a tabela que deseja deletar dados:\n");
    scanf(" %[^\n]", tableName);
    readTable(&table, tableName);

    listDataFrom(tableName);
    printf("Digite a Chave Primária referente à linha que será deletada:\n");
    scanf("%d", &primaryKey);

    // Verifica se a chave primária é válida
    if (!validPrimaryKeyValue(table, primaryKey, &primaryKeyIndex)) {
        printf("Chave primária inválida.\n");
        return;
    }

    // Substitui os valores na linha a ser deletada pelos valores na última linha
    for (int i = 0; i < table.numColumns; i++) {
        switch (table.columns[i].type) {
            case INT:
                table.columns[i].Data.intData[primaryKeyIndex] = table.columns[i].Data.intData[table.numRows - 1];
                break;
            case FLOAT:
                table.columns[i].Data.floatData[primaryKeyIndex] = table.columns[i].Data.floatData[table.numRows - 1];
                break;
            case DOUBLE:
                table.columns[i].Data.doubleData[primaryKeyIndex] = table.columns[i].Data.doubleData[table.numRows - 1];
                break;
            case CHAR:
                table.columns[i].Data.charData[primaryKeyIndex] = table.columns[i].Data.charData[table.numRows - 1];
                break;
            case STRING:
                strcpy(table.columns[i].Data.stringData[primaryKeyIndex], table.columns[i].Data.stringData[table.numRows - 1]);
                break;
        }
    }

    // Decrementa o número de linhas
    table.numRows--;

    // Grava a tabela atualizada de volta ao arquivo
    writeTable(&table, tableName);
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

void searchData(){
    char tableName[15];
    char nameCol[15];
    char filter[2];
    //bater o filtro com o tipo de dado da coluna
}