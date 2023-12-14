#include "funcs.h"
#include "../defs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char tableNames[MAX_TABLE_NAME][MAX_NUM_TABLES];
int numTables = 0;

Type stringToType(char *type) {
    if (strcmp(type, "INT") == 0) {
        return INT;
    } else if (strcmp(type, "FLOAT") == 0) {
        return FLOAT;
    } else if (strcmp(type, "DOUBLE") == 0) {
        return DOUBLE;
    } else if (strcmp(type, "CHAR") == 0) {
        return CHAR;
    } else if (strcmp(type, "STRING") == 0) {
        return STRING;
    }
    return -1;  // Se o tipo de dado não for reconhecido
}

void readMain() {
    FILE *file = fopen("txts/main.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo main.txt\n");
        return;
    }
    char tableName[MAX_TABLE_NAME];
    int i = 0;

    while (fscanf(file, "%s", tableName) != EOF) {
        strcpy(tableNames[i], tableName);
        i++;
    }
    numTables = i;

    fclose(file);
}

void writeMain() {
    FILE *file = fopen("txts/main.txt", "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo main.txt\n");
        return;
    }

    for (int i = 0; i < numTables; i++) {
        fprintf(file, "%s\n", tableNames[i]);
    }

    fclose(file);
}

void readTable(Table *table, char *tableName) {
    char filename[MAX_TABLE_NAME + 4];
    sprintf(filename, "txts/%s.txt", tableName);

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo %s\n", filename);
        return;
    }

    // Leitura do cabeçalho
    fscanf(file, "Número de Colunas: %d\n", &(table->numColumns));
    fscanf(file, "Número de Registros: %d\n", &(table->numRows));
    fscanf(file, "Chave Primária: %d\n", &(table->primaryKeyIndex));

    // Leitura do nome das colunas
    char line[MAX_STRING_SIZE];
    fgets(line, MAX_STRING_SIZE, file);
    char *token = strtok(line, ",");
    for (int i = 0; i < table->numColumns; i++) {
        // Remove espaços em branco no início e no final do token
        token += strspn(token, " ");
        char *end = token + strlen(token) - 1;
        while(end > token && isspace((unsigned char)*end)) end--;
        end[1] = '\0';

        // Copia o nome da coluna para a estrutura da tabela
        strcpy(table->columns[i].name, token);
        token = strtok(NULL, ",");
    }
    // Leitura do tipo das colunas
    fgets(line, MAX_STRING_SIZE, file);
    token = strtok(line, ",");
    for (int i = 0; i < table->numColumns; i++) {
        // Remove espaços em branco no início e no final do token
        token += strspn(token, " ");
        char *end = token + strlen(token) - 1;
        while(end > token && isspace((unsigned char)*end)) end--;
        end[1] = '\0';

        // Converte a string do tipo de dados para o enum correspondente e armazena na estrutura da tabela
        table->columns[i].type = stringToType(token);
        if (table->columns[i].type == -1) {
            printf("Tipo de dado não reconhecido na coluna %d.\n", i);
            return;
        }
        token = strtok(NULL, ",");
    }

    // Leitura dos dados com base no modelo atual de colunas
    for (int i = 0; i < table->numRows; i++) {
        // Lê uma linha do arquivo (Esse MAX_STRING_SIZE deve ser mudado visto que a linha pode ser gigantesca)
        char line[MAX_STRING_SIZE];
        fgets(line, MAX_STRING_SIZE, file);

        // Separa a linha em tokens separados por vírgula e armazena na tabela
        char *token = strtok(line, ",");
        for (int j = 0; j < table->numColumns; j++) {
            // Converte o token para o tipo de dados da Tabela
            switch (table->columns[j].type) {
                case INT:
                    table->columns[j].Data.intData[i] = atoi(token);
                    break;
                case FLOAT:
                    table->columns[j].Data.floatData[i] = atof(token);
                    break;
                case DOUBLE:
                    table->columns[j].Data.doubleData[i] = atof(token);
                    break;
                case CHAR:
                    table->columns[j].Data.charData[i] = token[0];
                    break;
                case STRING:
                    // Remove os espaços em branco no início e no final do token
                    token += strspn(token, " ");
                    char *end = token + strlen(token) - 1;
                    while (end > token && isspace((unsigned char) *end)) end--;
                    end[1] = '\0';

                    // Copia o token para a tabela
                    strcpy(table->columns[j].Data.stringData[i], token);
                    break;
            }
            token = strtok(NULL, ",");
        }
    }
    fclose(file);
}

void writeTable(Table *table, char *tableName) {
    char filename[MAX_TABLE_NAME + 4];
    sprintf(filename, "txts/%s.txt", tableName);

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo %s\n", filename);
        return;
    }

    // Escreve o cabeçalho
    fprintf(file, "Número de Colunas: %d\n", table->numColumns);
    fprintf(file, "Número de Registros: %d\n", table->numRows);
    fprintf(file, "Chave Primária: %d\n", table->primaryKeyIndex);

    // Escreve os nomes das colunas
    for (int i = 0; i < table->numColumns; i++) {
        fprintf(file, "%s", table->columns[i].name);
        if (i < table->numColumns - 1) {
            fprintf(file, ", ");
        }
    }
    fprintf(file, "\n");

    // Escreve os tipos das colunas
    for (int i = 0; i < table->numColumns; i++) {
        switch (table->columns[i].type) {
            case INT:
                fprintf(file, "INT");
                break;
            case FLOAT:
                fprintf(file, "FLOAT");
                break;
            case DOUBLE:
                fprintf(file, "DOUBLE");
                break;
            case CHAR:
                fprintf(file, "CHAR");
                break;
            case STRING:
                fprintf(file, "STRING");
                break;
        }
        if (i < table->numColumns - 1) {
            fprintf(file, ", ");
        }
    }
    fprintf(file, "\n");

    // Escreve os dados
    for (int i = 0; i < table->numRows; i++) {
        for (int j = 0; j < table->numColumns; j++) {
            switch (table->columns[j].type) {
                case INT:
                    fprintf(file, "%d", table->columns[j].Data.intData[i]);
                    break;
                case FLOAT:
                    fprintf(file, "%f", table->columns[j].Data.floatData[i]);
                    break;
                case DOUBLE:
                    fprintf(file, "%lf", table->columns[j].Data.doubleData[i]);
                    break;
                case CHAR:
                    fprintf(file, "%c", table->columns[j].Data.charData[i]);
                    break;
                case STRING:
                    fprintf(file, "%s", table->columns[j].Data.stringData[i]);
                    break;
            }
            if (j < table->numColumns - 1) {
                fprintf(file, ", ");
            }
        }
        fprintf(file, "\n");
    }

    fclose(file);
}