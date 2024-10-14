#include "../include/definitions.h"
#include "../include/functions.h"

extern char tableNames[MAX_TABLE_NAME][MAX_NUM_TABLES];
extern int numTables;

// Aux functions
void listDataFrom(char tableName[MAX_TABLE_NAME]) {
  Table readingTable;

  readTable(&readingTable, tableName);

  printf("Tabela: %s\n", tableName);
  for (int i = 0; i < readingTable.numColumns; i++) {
    printf("%-15s", readingTable.columns[i].name);
  }
  printf("\n");

  for (int i = 0; i < readingTable.numColumns; i++) {
    for (int j = 0; j < 15; j++)
      printf("-");
  }
  printf("\n");

  for (int i = 0; i < readingTable.numRows; i++) {
    for (int j = 0; j < readingTable.numColumns; j++) {
      switch (readingTable.columns[j].type) {
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

// Main function
void listDataFromTable() {
  char tableName[MAX_TABLE_NAME];
  Table readingTable;

  printf("Digite o nome da tabela:\n");
  scanf(" %[^\n]", tableName);

  listDataFrom(tableName);
}
