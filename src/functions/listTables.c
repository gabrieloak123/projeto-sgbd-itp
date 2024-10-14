#include "../include/definitions.h"
#include "../include/functions.h"
#include <stdio.h>

extern char tableNames[MAX_TABLE_NAME][MAX_NUM_TABLES];
extern int numTables;

void listTables() {
  readMain();

  printLineAndBreak(DEFAULT_LINE_LENGTH, '=');
  printf("As tabelas registradas são as seguintes:\n");
  breakLine();

  for (int i = 0; i < numTables; i++) {
    printf("%s\n", tableNames[i]);
  }
}
