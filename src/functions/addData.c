#include <stdlib.h>

#include "../include/definitions.h"
#include "../include/functions.h"

extern char tableNames[MAX_TABLE_NAME][MAX_NUM_TABLES];
extern int numTables;

void setValueBasedOnType(Table *table, int i, char value[MAX_STRING_SIZE]) {
  switch (table->columns[i].type) {
  case INT:
    table->columns[i].Data.intData[table->numRows] = atoi(value);
    return;
  case FLOAT:
    table->columns[i].Data.floatData[table->numRows] = atof(value);
    return;
  case DOUBLE:
    table->columns[i].Data.doubleData[table->numRows] = atof(value);
    return;
  case CHAR:
    table->columns[i].Data.charData[table->numRows] = value[0];
    return;
  case STRING:
    strcpy(table->columns[i].Data.stringData[table->numRows], value);
    return;
  }
}

void addData() {
  char tableName[MAX_TABLE_NAME];
  Table table;

  printf("Digite o nome da tabela:\n");
  scanf(" %[^\n]", tableName);

  if (isTableNameInUse(tableName)) {
    printf("Tabela não encontrada\n");
    return;
  }

  // Load on the memory whats written on the table file
  readTable(&table, tableName);

  for (int i = 0; i < table.numColumns; i++) {
    printf("Digite o valor da coluna %s (%s):\n", table.columns[i].name,
           dataTypeToString(table.columns[i].type));
    char value[MAX_STRING_SIZE];
    scanf(" %[^\n]", value);

    while (strlen(value) > MAX_STRING_SIZE || strlen(value) == 0) {
      printf("Valor muito grande ou vazio, digite novamente:\n");
      scanf(" %[^\n]", value);
    }

    setValueBasedOnType(&table, i, value);
  }

  for (int i = 0; i < table.numRows; i++) {
    if (table.columns[table.primaryKeyIndex].Data.intData[i] ==
            table.columns[table.primaryKeyIndex].Data.intData[table.numRows] ||
        table.columns[table.primaryKeyIndex].Data.intData[table.numRows] < 0) {
      printf("Chave primária já existente, digite novamente:\n");
      return;
    }
  }

  table.numRows++;

  writeTable(&table, tableName);
}
