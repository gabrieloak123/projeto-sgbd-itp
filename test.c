//
// Created by dio on 11/12/23.
//


#include "funcs.h"
#include "defs.h"
#include <stdio.h>
#include <string.h>

extern char TableNames[MAX_TABLE_NAME][MAX_NUM_TABLES];

/*void test_readMain() {
    readMain();
    for (int i = 0; i < MAX_NUM_TABLES; i++) {
        if (TableNames[i][0] != '\0') {
            printf("Nome da Tabela %d: %s\n", i, TableNames[i]);
        }
    }
} */

void test_readTable() {
    Table table;
    readTable(&table, "testTable");
    printf("Nome da Tabela: %s\n", table.name);
    printf("Número de Colunas: %d\n", table.numColumns);
    printf("Número de Registros: %d\n", table.numRows);
    printf("Chave Primária: %d\n", table.primaryKeyIndex);
    for (int i = 0; i < table.numColumns; i++) {
        printf("Nome da Coluna %d: %s\n", i, table.columns[i].name);
        printf("Tipo da Coluna %d: %d\n", i, table.columns[i].type);
        for (int j = 0; j < table.numRows; j++) {
            switch (table.columns[i].type) {
                case INT:
                    printf("Dado %d: %d\n", j, table.columns[i].Data.intData[j]);
                    break;
                case FLOAT:
                    printf("Dado %d: %f\n", j, table.columns[i].Data.floatData[j]);
                    break;
                case DOUBLE:
                    printf("Dado %d: %lf\n", j, table.columns[i].Data.doubleData[j]);
                    break;
                case CHAR:
                    printf("Dado %d: %c\n", j, table.columns[i].Data.charData[j]);
                    break;
                case STRING:
                    printf("Dado %d: %s\n", j, table.columns[i].Data.stringData[j]);
                    break;
            }
        }
    }
}

int main() {
    //printf("Testando readMain:\n");
    //test_readMain();
    printf("\nTestando readTable:\n");
    test_readTable();
    return 0;
}