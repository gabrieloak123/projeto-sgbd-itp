#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "../include/definitions.h"
#include "../include/functions.h"

extern char tableNames[MAX_TABLE_NAME][MAX_NUM_TABLES];
extern int numTables;

void showMenu() {
  printLineAndBreak(DEFAULT_LINE_LENGTH, '=');

  printf("Digite o número correspondente à operação:\n");
  breakLine();
  printf("0. Sair\n");
  printf("1. Criar tabela\n");
  printf("2. Listar tabelas\n");
  printf("3. Adicionar dados\n");
  printf("4. Listar dados\n");
  printf("5. Apagar linha\n");
  printf("6. Apagar tabela\n");
  printf("7. Mostrar alguma coisa q eu esqueci\n");

  breakLine();
}

bool tableCheckError(FILE *tableName) {
  if (tableName == NULL) {
    printf("Erro ao abrir o arquivo de nomes de tabela");
    fclose(tableName);
    return true;
  }
  return false;
}

bool isTableNameInUse(char *tableName) {
  for (int i = 0; i < numTables; i++) {
    if (strcmp(tableNames[i], tableName) == 0) {
      return true;
    }
  }
  return false;
}

void printLineAndBreak(size_t size, char character) {
  for (size_t i = 0; i < size; i++) {
    printf("%c", character);
  }
  printf("\n");
}

void breakLine() { printf("\n"); }

void initMainTable() {
  FILE *tableOfNames = fopen(mainTxtPath, "r");

  if (!tableCheckError(tableOfNames)) {
    tableOfNames = fopen(mainTxtPath, "w");
  }

  fclose(tableOfNames);
}

bool areTheSame(char *input, char *expected) {
  return strcasecmp(input, expected) == 0;
}

void readTableContent(FILE *table, char *tableContent, int maxSize) {
  int bytesRead = fread(tableContent, sizeof(char), maxSize - 1, table);
  tableContent[bytesRead] = '\0';
}

bool typeAllowed(char *maybeType) {
  char allowedTypes[5][8] = {"int", "float", "double", "char", "string"};

  for (int i = 0; i < 5; i++) {
    if (areTheSame(maybeType, allowedTypes[i])) {
      return true;
    }
  }
  return false;
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

bool validPrimaryKeyValue(Table table, int primaryKeyValue,
                          int *primaryKeyValueIndex) {
  for (int i = 0; i < table.numRows; i++) {
    if (primaryKeyValue ==
        table.columns[table.primaryKeyIndex].Data.intData[i]) {
      *primaryKeyValueIndex = i;

      return true;
    }
  }

  return false;
}
