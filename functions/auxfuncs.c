#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
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

void changeColRowQuantity(char fileName[25], int addOrDropValue, char colOrRow[4]){
    FILE *table;
    table = fopen(fileName, "r");

    tableCheckError(table);
    
    char line[MAX_NAMES_CONTENT];
    fgets(line, sizeof(line), table);

    int current, newQnt;

    if (strcmp(colOrRow, "row") == 0) {
        if (sscanf(line, "RowsQnt: %d", &current) != 1) {
            printf("Erro ao ler a quantidade de linhas\n");
            return;
        }
        newQnt = addOrDropValue + current;

        fseek(table, 0, SEEK_SET);
        fprintf(table, "RowsQnt: %d\n", newQnt);
    } else if (strcmp(colOrRow, "col") == 0) {
    // Avança para a próxima linha que contém "ColsQnt:"
        while (fgets(line, sizeof(line), table) != NULL && strncmp(line, "ColsQnt:", 8) != 0) {
            // Não faz nada enquanto não encontra a linha correta
        }

        if (sscanf(line, "ColsQnt: %d", &current) != 1) {
            printf("Erro ao ler a quantidade de colunas\n");
            return;
        }

        newQnt = addOrDropValue + current;

        fseek(table, -strlen(line), SEEK_CUR); // Retrocede para o início da linha "ColsQnt:"
        fprintf(table, "ColsQnt: %d", newQnt);
    }
    fclose(table);
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

bool typeAllowed(char *maybeType){
    char allowedTypes[5][8] = {"int", "float", "double", "char", "string"};

    for(int i = 0; i < 5; i++){
        if(strcasecmp(maybeType, allowedTypes[i]) == 0){
            return true;
        }
    }
    return false;
}

void readTableName(char *tableName){
    printf("Digite o nome da tabela:");
    scanf(" %[^\n]", tableName);
}

void readTableContent(FILE *table, char *tableContent, int maxSize){
    int bytesRead = fread(tableContent, sizeof(char), maxSize - 1, table);
    tableContent[bytesRead] = '\0';
}

void addColumnToFile(FILE *table, char *colType, char *colName){
    char format[MAX_COL_NAME + MAX_COL_TYPE + 5]; // 5 = strlen(" - \n") + 1 (null terminator)
    snprintf(format, sizeof(format), "%s - %s\n", colType, colName);
    if (table != NULL) {
        fwrite(format, sizeof(char), strlen(format), table);
    } else {
        printf("Erro ao abrir o arquivo (addColumnToFile)\n");
    }
}

void readColumns(FILE *table, char fileName[MAX_FILE_NAME]){
    char colType[MAX_COL_TYPE];
    char colName[MAX_COL_NAME];
    char primaryKey[MAX_COL_NAME];
    int counter = 0;
    char **colNamesArray;

    fprintf(table, "ColsQnt: 0\n");
    fprintf(table, "RowsQnt: 0\n");
    fprintf(table, "PrimaryKey: \n");
    fprintf(table, "=========================\n");

    printf("Digite respectivamente o tipo e nome da coluna:\n");
    printf("E stop para finalizar a leitura\n");

    while (true) {
        scanf("%s", colType);

        if (strcmp("stop", colType) == 0) {
            fprintf(table, "=========================\n");

            printf("Digite qual dos atributos será a Chave Primária:\n");
            for(int i = 0; i < counter; i++){
                if(i+1 < counter){
                    printf("%s - ", colNamesArray[i]);
                } else {
                    printf("%s\n", colNamesArray[i]);
                }
            }
            do{
                scanf(" %[^\n]", primaryKey);
            } while(isnameInUse(fileName, primaryKey) == false);
            break;
        }
        scanf("%s", colName);
        
        if (typeAllowed(colType)) {
            char content[MAX_NAMES_CONTENT];
            readTableContent(table, content, sizeof(content));

            if (isnameInUse(fileName, colName)){//ajeitar
                printf("Nome de coluna já em uso\n");
            } else {
                colNamesArray = realloc(colNamesArray, (counter + 1) * sizeof(char *));
                 colNamesArray[counter] = strdup(colName);
                // addColumnToFile(table, colType, colName);
                fprintf(table, "%s - %s\n", colType, colName);
                counter++;
            }
        } else {
            printf("Digite um tipo válido\n");
        }

    }
    changeColRowQuantity(fileName, counter, "col");

    for (int i = 0; i < counter; i++) {
        free(colNamesArray[i]);
    }
    free(colNamesArray);
}