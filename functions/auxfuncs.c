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

void rewindFile(FILE *file) {
    if (file != NULL) {
        fseek(file, 0, SEEK_SET);
    } else {
        printf("Erro ao abrir o arquivo (rewindFile)\n");
    }
}

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
    table = fopen(fileName, "r+");

    if (tableCheckError(table)) {
        return;
    }

    char line[MAX_NAMES_CONTENT];
    int current = 0, newQnt;
    long position;

    if (strcmp(colOrRow, "col") == 0) {
        position = ftell(table);
        fgets(line, sizeof(line), table);
        if (sscanf(line, "ColsQnt: %d", &current) != 1) {
            printf("Erro ao ler a quantidade de colunas\n");
            return;
        }
        newQnt = addOrDropValue + current;

        fseek(table, position, SEEK_SET);
        fprintf(table, "ColsQnt: %d\n", newQnt);
    } else if (strcmp(colOrRow, "row") == 0) {
        // Avança para a próxima linha que contém "RowsQnt:"
        while (fgets(line, sizeof(line), table) != NULL && strncmp(line, "RowsQnt:", 8) != 0) {
            position = ftell(table);
        }

        if (sscanf(line, "RowsQnt: %d", &current) != 1) {
            printf("Erro ao ler a quantidade de linhas\n");
            return;
        }

        newQnt = addOrDropValue + current;

        fseek(table, position, SEEK_SET); // Retrocede para o início da linha "RowsQnt:"
        fprintf(table, "RowsQnt: %d\n", newQnt);
    }
    fclose(table);
}

bool isnameInUse(char *fileName, char *targetWord){
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return false;
    }

    char line[100];

    while (fgets(line, sizeof(line), file) != NULL) {
        // Remove o caractere de nova linha, se existir
        line[strcspn(line, "\n")] = '\0';

        // Usa strtok para dividir a linha em palavras separadas por espaços
        char *token = strtok(line, " ");
        while (token != NULL) {
            // Compara a palavra com cada palavra na linha
            if (strcmp(token, targetWord) == 0) {
                fclose(file);
                return true;
            }
            token = strtok(NULL, " ");
        }
    }

    fclose(file);
    return false;
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

void updatePrimaryKey(char *fileName, char *newPrimaryKey){
    FILE *file = fopen(fileName, "r+");  // Abre o arquivo para leitura e escrita

    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    char line[100];
    long primaryKeyStartPosition = -1;

    // Procura pela linha que começa com "PrimaryKey:"
    while (fgets(line, sizeof(line), file) != NULL) {
        if (strncmp(line, "PrimaryKey:", strlen("PrimaryKey:")) == 0) {
            primaryKeyStartPosition = ftell(file);
            break;
        }
    }

    if (primaryKeyStartPosition != -1) {
        // Posiciona o cursor no início do campo PrimaryKey
        fseek(file, primaryKeyStartPosition - 1, SEEK_SET);

        // Escreve a nova chave primária no arquivo
        fprintf(file, "%s\n", newPrimaryKey);
    } else {
        printf("Campo PrimaryKey não encontrado no arquivo.\n");
    }

    fclose(file);
}

void readColumns(FILE *table, char fileName[MAX_FILE_NAME]){
    char colType[MAX_COL_TYPE];
    char colName[MAX_COL_NAME];
    char primaryKey[MAX_COL_NAME];
    int counter = 0;
    char colNamesArray[100][100];

    fprintf(table, "ColsQnt: 0\n");
    fprintf(table, "RowsQnt: 0\n");
    fprintf(table, "PrimaryKey: \n");
    fprintf(table, "=========================================\n");

    printf("Digite respectivamente o tipo e nome da coluna:\n");
    printf("E stop para finalizar a leitura\n");

    while (true) {
        scanf("%s", colType);

        if (strcmp("stop", colType) == 0) {
            fprintf(table, "=========================================\n");

            printf("Digite qual dos atributos será a Chave Primária:\n");
            for(int i = 0; i < counter; i++){
                if(i+1 < counter){
                    printf("%s - ", colNamesArray[i]);
                } else {
                    printf("%s\n", colNamesArray[i]);
                }
            }
            do{
                printf("(Repetirá até digitar um dos argumentos acima)\n");
                scanf(" %[^\n]", primaryKey);

                if (isnameInUse(fileName, primaryKey)) {
                    break;
                }
            } while(true);
            break;
        }
        scanf("%s", colName);
        
        if (typeAllowed(colType)) {
            char content[MAX_NAMES_CONTENT];
            readTableContent(table, content, sizeof(content));

            if (isnameInUse(fileName, colName)){//ajeitar
                printf("Nome de coluna já em uso\n");
            } else {
                //colNamesArray = realloc(colNamesArray, (counter + 1) * sizeof(char *));
                //colNamesArray[counter] = strdup(colName);
                // addColumnToFile(table, colType, colName);
                strcpy(colNamesArray[counter], colName);
                fprintf(table, "%s - %s\n", colType, colName);
                counter++;
            }
        } else {
            printf("Digite um tipo válido\n");
        }

    }
    

    /*for (int i = 0; i < counter; i++) {
        free(colNamesArray[i]);
    }*/
    //free(colNamesArray);
    updatePrimaryKey(fileName, primaryKey);
    changeColRowQuantity(fileName, counter, "col");
}