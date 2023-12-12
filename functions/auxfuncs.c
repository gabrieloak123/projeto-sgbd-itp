#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "funcs.h"

#define MAX_TABLE_NAME 20
#define MAX_NAMES_CONTENT 100
#define MAX_COL_TYPE 10
#define MAX_COL_NAME 25
#define MAX_FILE_NAME 25

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

void changeTablesQuantity(int addOrDropValue){
    FILE *tableOfNames;
    tableOfNames = fopen("txts/main.txt", "r");

    tableCheckError(tableOfNames);

    char line[15];
    fgets(line, sizeof(line), tableOfNames);

    int current, newTablesQnt;
    if(sscanf(line, "Qnt: %d", &current) != 1){
        printf("Erro ao ler a quantidade de tabelas\n");
        return;
    }
    newTablesQnt = addOrDropValue + current;

    fseek(tableOfNames, 0, SEEK_SET);
    fprintf(tableOfNames, "TablesQnt: %d\n", newTablesQnt);
    fclose(tableOfNames);
}

int isnameInUse(char *tableName, char *content){
    char *subString = strtok(content, "\n");

    while (subString != NULL){
        char *nameInUse = strstr(subString, tableName);

        if(nameInUse != NULL){
            return 1;
        }
        subString = strtok(NULL, "\n");
    }
    return 0;
}

int tableCheckError(FILE *tableName){
    if(tableName == NULL){
        perror("Erro ao abrir o arquivo de nomes de tabela");
        fclose(tableName);
        return 1;
    }
    return 0;
}

bool verifyTableExistence(char *tableName){

}