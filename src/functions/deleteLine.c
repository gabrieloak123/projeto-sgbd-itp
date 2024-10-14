#include "../include/definitions.h"
#include "../include/functions.h"

extern char tableNames[MAX_TABLE_NAME][MAX_NUM_TABLES];
extern int numTables;

void replaceValues(Table *table, int primaryKeyIndex) {
  for (int i = 0; i < table->numColumns; i++) {
    switch (table->columns[i].type) {
    case INT:
      table->columns[i].Data.intData[primaryKeyIndex] =
          table->columns[i].Data.intData[table->numRows - 1];
      return;
    case FLOAT:
      table->columns[i].Data.floatData[primaryKeyIndex] =
          table->columns[i].Data.floatData[table->numRows - 1];
      return;
    case DOUBLE:
      table->columns[i].Data.doubleData[primaryKeyIndex] =
          table->columns[i].Data.doubleData[table->numRows - 1];
      return;
    case CHAR:
      table->columns[i].Data.charData[primaryKeyIndex] =
          table->columns[i].Data.charData[table->numRows - 1];
      return;
    case STRING:
      strcpy(table->columns[i].Data.stringData[primaryKeyIndex],
             table->columns[i].Data.stringData[table->numRows - 1]);
      return;
    }
  }
}

void deleteLine() {
  char tableName[MAX_TABLE_NAME];
  int primaryKey;
  int primaryKeyIndex;
  Table table;

  printf("Digite a tabela que deseja deletar dados:\n");
  scanf(" %[^\n]", tableName);

  if (isTableNameInUse(tableName) == 0) {
    printf("Tabela não encontrada\n");
    return;
  }

  readTable(&table, tableName);

  listDataFrom(tableName);
  printf("Digite a Chave Primária referente à linha que será deletada:\n");
  scanf("%d", &primaryKey);

  if (!validPrimaryKeyValue(table, primaryKey, &primaryKeyIndex)) {
    printf("Chave primária inválida.\n");
    return;
  }

  // Replaces the values from the line to be deleted for the ones on the last
  replaceValues(&table, primaryKeyIndex);

  table.numRows--;
  writeTable(&table, tableName);
}
