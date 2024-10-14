#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>

#include "../include/definitions.h"
#include "../include/functions.h"

extern char tableNames[MAX_TABLE_NAME][MAX_NUM_TABLES];
extern int numTables;

// Aux functions
bool isCollumnNameInUse(char *columnName, Table *table) {
  for (int i = 0; i < table->numColumns; i++) {
    if (strcmp(table->columns[i].name, columnName) == 0) {
      return true;
    }
  }
  return false;
}

int verifyHowManyColsOfType(Table *table, Type type) {
  int counter = 0;
  for (size_t i = 0; i < table->numColumns; i++) {
    if (table->columns[i].type == type) {
      counter++;
    }
  }

  return counter;
}

void createArbitraryIdCollumn(Table *table) {
  strcpy(table->columns[table->numColumns].name, "id");
  table->columns[table->numColumns].type = INT;
  table->primaryKeyIndex = table->numColumns++;
}

void setPrimaryKey(Table *table) {
  if (isCollumnNameInUse("id", table)) {
    for (int i = 0; i < table->numColumns; i++) {
      if (areTheSame(table->columns[i].name, "id")) {
        table->primaryKeyIndex = i;

        printf("Foi encontrada uma coluna id, esta será a primary key\n");

        printLineAndBreak(DEFAULT_LINE_LENGTH, '=');
        return;
      }
    }
  }

  switch (verifyHowManyColsOfType(table, INT)) {
  case 0:
    char option[MAX_OPTION_SIZE];

    printf("Não há colunas cadastradas que possam ser definidas como\n"
           "chave primária, deseja criar uma coluna id?(y/n)\n");

    while (true) {
      breakLine();
      printf("Input: ");
      scanf("%s", option);
      getchar();

      if (areTheSame(option, "yes") || areTheSame(option, "y")) {
        createArbitraryIdCollumn(table);

        printLineAndBreak(DEFAULT_LINE_LENGTH, '=');
        printf("Coluna id criada!\n");
        printLineAndBreak(DEFAULT_LINE_LENGTH, '=');
        // Pk arbitrarily created
        return;
      } else if (areTheSame(option, "no") || areTheSame(option, "n")) {
        char colName[MAX_COLUMN_NAME];

        printLineAndBreak(DEFAULT_LINE_LENGTH, '=');
        printf("Nesse caso, crie a nova coluna(int) que será a primary "
               "key\n");
        while (true) {
          breakLine();
          printf("Input: ");
          scanf("%s", colName);
          getchar();

          if (isCollumnNameInUse(colName, table)) {
            printLineAndBreak(DEFAULT_LINE_LENGTH, '=');
            printf("O nome da coluna digitada já está em uso\n");
          } else {
            strcpy(table->columns[table->numColumns].name, colName);
            table->columns[table->numColumns].type = INT;
            table->primaryKeyIndex = table->numColumns++;

            // Pk manually created
            return;
          }
        }
      }
      printLineAndBreak(DEFAULT_LINE_LENGTH, '=');
      printf("Digite uma opção válida\n");
    }
    break;
  default:
    char useAlreadyCreatedCollumn[MAX_OPTION_SIZE];

    printf("As colunas que podem ser primary key são as seguintes:\n");

    for (int i = 0; i < table->numColumns; i++) {
      if (table->columns[i].type == INT) {
        printf("%s\n", table->columns[i].name);
      }
    }

    breakLine();
    printf("Deseja usar alguma dessas como primary key?(y/n)\n");

    while (true) {
      breakLine();
      printf("Input: ");
      scanf(" %[^\n]", useAlreadyCreatedCollumn);
      /*scanf("%s", useAlreadyCreatedCollumn);*/
      getchar();

      if (areTheSame(useAlreadyCreatedCollumn, "yes") ||
          areTheSame(useAlreadyCreatedCollumn, "y")) {

        printLineAndBreak(DEFAULT_LINE_LENGTH, '=');
        printf("Qual?\n");

        while (true) {
          int counter = 0;
          int collumn;

          breakLine();

          for (int i = 0; i < table->numColumns; i++) {
            if (table->columns[i].type == INT) {
              printf("%d - %s\n", counter++, table->columns[i].name);
            }
          }

          printf("Input: ");
          scanf("%d", &collumn);
          getchar();

          if (table->columns[collumn].type == INT) {
            table->primaryKeyIndex = collumn;

            printLineAndBreak(DEFAULT_LINE_LENGTH, '=');
            printf("Coluna %s definida como primary key\n",
                   table->columns[collumn].name);
            printLineAndBreak(DEFAULT_LINE_LENGTH, '=');
            // A existing collumn was chossen to be the primary key
            return;
          }
          printLineAndBreak(DEFAULT_LINE_LENGTH, '=');
          printf("Escolha uma coluna válida!\n");
        }
      } else if (areTheSame(useAlreadyCreatedCollumn, "no") ||
                 areTheSame(useAlreadyCreatedCollumn, "n")) {
        createArbitraryIdCollumn(table);
        printLineAndBreak(DEFAULT_LINE_LENGTH, '=');
        printf("Foi criada uma coluna id arbitrária\n");

        // Id collumn created
        return;
      }

      printLineAndBreak(DEFAULT_LINE_LENGTH, '=');
      printf("Digite uma opção válida!\n");

      break;
    }
  }
}

void readColumns(Table *table) {
  char colType[MAX_COLUMN_TYPE];
  char colName[MAX_COLUMN_NAME];
  int colsCounter = 0;

  printLineAndBreak(DEFAULT_LINE_LENGTH, '=');
  printf("Digite respectivamente o tipo e nome da coluna:\n");
  printf("E stop para finalizar a leitura\n");
  printf("(Tipos disponíveis: int, float, double, char e string)\n");
  breakLine();

  while (true) {
    printf("Input: ");
    scanf("%s", colType);
    getchar();

    if (areTheSame(colType, "stop")) {
      // yes
      if (colsCounter == 0) {
        // You cant create a table without collumns
        printLineAndBreak(DEFAULT_LINE_LENGTH, '=');
        printf("Você não pode criar uma tabela sem colunas!\n");
        breakLine();
      } else {
        // Table created but without pk
        printLineAndBreak(DEFAULT_LINE_LENGTH, '=');

        return;
      }
    } else {
      // no
      if (typeAllowed(colType)) {
        scanf("%s", colName);
        getchar();

        while (isCollumnNameInUse(colName, table)) {
          printLineAndBreak(DEFAULT_LINE_LENGTH, '=');
          printf("Nome de coluna em uso, digite outro:\n");
          breakLine();
          printf("Input: ");
          scanf(" %[^\n]", colName);
          getchar();
        }

        // Sets the name of the collumn
        strcpy(table->columns[colsCounter].name, colName);

        if (areTheSame(colType, "int")) {
          table->columns[colsCounter].type = INT;
        } else if (areTheSame(colType, "float")) {
          table->columns[colsCounter].type = FLOAT;
        } else if (areTheSame(colType, "double")) {
          table->columns[colsCounter].type = DOUBLE;
        } else if (areTheSame(colType, "char")) {
          table->columns[colsCounter].type = CHAR;
        } else if (areTheSame(colType, "string")) {
          table->columns[colsCounter].type = STRING;
        }
        colsCounter++;
        table->numColumns = colsCounter;

        printLineAndBreak(DEFAULT_LINE_LENGTH, '=');
        printf("Coluna %s criada com sucesso!\n", colName);
        printLineAndBreak(DEFAULT_LINE_LENGTH, '=');
      } else {
        printLineAndBreak(DEFAULT_LINE_LENGTH, '=');
        printf("Digite um tipo válido!\n");
        breakLine();
      }
    }
  }
}
// Main function
void createTable() {
  char tableName[MAX_TABLE_NAME];
  Table newTable;
  newTable.numColumns = 0;
  newTable.numRows = 0;

  readMain();

  printLineAndBreak(DEFAULT_LINE_LENGTH, '=');
  printf("Digite o nome da tabela:\n");
  breakLine();

  printf("Input: ");
  scanf(" %[^\n]", tableName);
  getchar();

  while (isTableNameInUse(tableName) == 1) {
    printLineAndBreak(DEFAULT_LINE_LENGTH, '=');
    printf("Nome já em uso, digite outro:\n");
    breakLine();
    printf("Input: ");
    scanf(" %[^\n]", tableName);
    getchar();
  }

  strcpy(tableNames[numTables], tableName);
  numTables++;

  readColumns(&newTable);
  setPrimaryKey(&newTable);
  writeMain();
  writeTable(&newTable, tableName);
}
