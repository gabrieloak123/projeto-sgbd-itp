#include <stdio.h>
#include <string.h>
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

int tableCheckError(FILE *tableName){
    if(tableName == NULL){
        printf("Erro ao abrir o arquivo de nomes de tabela");
        fclose(tableName);
        return 1;
    }
    return 0;
}

void initMainTable() {
    FILE *tableOfNames = fopen("txts/main.txt", "r");

    if (tableOfNames == NULL) {
        tableOfNames = fopen("txts/main.txt", "w");
    }
    fclose(tableOfNames);
}

// Generalizar essa e a próxima
int isTableNameInUse(char *tableName){
    for(int i = 0; i < numTables; i++){
        if(strcmp(tableNames[i], tableName) == 0){
            return 1;
        }
    }
    return 0;
}

int isColumnNameInUse(char *columnName, Table *table){
    for(int i = 0; i < table->numColumns; i++){
        if(strcmp(table->columns[i].name, columnName) == 0){
            return 1;
        }
    }
    return 0;
}

bool typeAllowed(char *maybeType){
    char allowedTypes[5][8] = {"int", "float", "double", "char", "string"};

    for(int i = 0; i < 5; i++){
        if(strcasecmp(maybeType, allowedTypes[i]) == 0){
            return true;
        }
    }
    return false;
}

void readColumns(Table *table){
    char colType[MAX_COLUMN_TYPE];
    char colName[MAX_COLUMN_NAME];
    int counter = 0, columnsIndex = 0;
    printf("Digite respectivamente o tipo e nome da coluna:\n");
    printf("E stop para finalizar a leitura\n");

    while (true) {
        scanf("%s", colType);

        // O que tu acha de colocar como obrigatório pelo menos uma coluna do tipo int?

        if (strcasecmp(colType, "stop") == 0 && counter > 1) {
            printf("Digite qual dos atributos será a Chave primária:\n");
            for (int i = 0; i < counter; i++) {
                if (table->columns[i].type == INT) {
                    printf("%d - %s\n", i, table->columns[i].name);
                }
            }
            scanf("%d", &(table->primaryKeyIndex));
            while (table->primaryKeyIndex >= counter || table->primaryKeyIndex < 0) {
                printf("Digite um número válido\n");
                scanf("%d", &(table->primaryKeyIndex));
            }

            return;
        } else if (strcasecmp(colType, "stop") == 0) {
            table->primaryKeyIndex = 0;
            return;
        }
        scanf("%s", colName);

        while (isColumnNameInUse(colName, table) == 1){
            printf("Nome de coluna em uso, digite outro:\n");
            scanf(" %[^\n]", colName);
        }

        if (typeAllowed(colType)) {
            strcpy(table->columns[counter].name, colName);
            if (strcasecmp(colType, "int") == 0) {
                table->columns[counter].type = INT;
            } else if (strcasecmp(colType, "float") == 0) {
                table->columns[counter].type = FLOAT;
            } else if (strcasecmp(colType, "double") == 0) {
                table->columns[counter].type = DOUBLE;
            } else if (strcasecmp(colType, "char") == 0) {
                table->columns[counter].type = CHAR;
            } else if (strcasecmp(colType, "string") == 0) {
                table->columns[counter].type = STRING;
            }
            counter++;
            table->numColumns = counter;
        } else {
            printf("Digite um tipo válido\n");
        }
    }
}

void listDataFrom(char tableName[MAX_TABLE_NAME]){
    Table readingTable;

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

char *dataTypeToString(Type type) {
    switch (type) {
        case INT:
            return "int";
        case FLOAT:
            return "float";
        case DOUBLE:
            return "double";
        case CHAR:
            return "char";
        case STRING:
            return "string";
    }
}

bool validPrimaryKeyValue(Table table, int primaryKeyValue, int *primaryKeyValueIndex){
    for(int i = 0; i < table.numRows; i++){
        if(primaryKeyValue == table.columns[table.primaryKeyIndex].Data.intData[i]){
            *primaryKeyValueIndex = i;
            return true;
        }
    }
    return false;
}