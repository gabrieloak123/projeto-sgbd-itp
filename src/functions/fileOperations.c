#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/definitions.h"
#include "../include/functions.h"

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
  return -1; // Just to satisfy the return in all cases
}

void readMain() {
  FILE *file = fopen(mainTxtPath, "r");
  if (!tableCheckError(file)) {
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
  FILE *file = fopen(mainTxtPath, "w");
  if (!tableCheckError(file)) {
    return;
  }

  for (int i = 0; i < numTables; i++) {
    fprintf(file, "%s\n", tableNames[i]);
  }

  fclose(file);
}

void readTable(Table *table, char *tableName) {
  char filename[MAX_TABLE_NAME + 4];
  sprintf(filename, "../txts/%s.txt", tableName);

  FILE *file = fopen(filename, "r");
  if (!tableCheckError(file)) {
    printf("Erro ao abrir o arquivo %s\n", filename);
    return;
  }

  // Reads the header
  fscanf(file, "Número de Colunas: %d\n", &(table->numColumns));
  fscanf(file, "Número de Registros: %d\n", &(table->numRows));
  fscanf(file, "Chave Primária: %d\n", &(table->primaryKeyIndex));

  // Reads the name of the collumns
  char line[MAX_STRING_SIZE];
  fgets(line, MAX_STRING_SIZE, file);
  char *token = strtok(line, ",");

  for (int i = 0; i < table->numColumns; i++) {
    // Trim
    token += strspn(token, " ");
    char *end = token + strlen(token) - 1;
    while (end > token && isspace((unsigned char)*end))
      end--;
    end[1] = '\0';

    // Copies data to memory
    strcpy(table->columns[i].name, token);
    token = strtok(NULL, ",");
  }

  // Reads collumn types
  fgets(line, MAX_STRING_SIZE, file);
  token = strtok(line, ",");

  for (int i = 0; i < table->numColumns; i++) {
    // Trim
    token += strspn(token, " ");
    char *end = token + strlen(token) - 1;
    while (end > token && isspace((unsigned char)*end))
      end--;
    end[1] = '\0';

    // Converts string to type and copies to memory
    table->columns[i].type = stringToType(token);
    if (table->columns[i].type == -1) {
      printf("Tipo de dado não reconhecido na coluna %d.\n", i);
      return;
    }
    token = strtok(NULL, ",");
  }

  // Reads the data based on the actual model of collumns
  for (int i = 0; i < table->numRows; i++) {
    char line[MAX_STRING_SIZE];
    fgets(line, MAX_STRING_SIZE, file);

    // Extracts the data from file to memory
    char *token = strtok(line, ",");

    for (int j = 0; j < table->numColumns; j++) {
      // Converts the data
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
        // Trim
        token += strspn(token, " ");
        char *end = token + strlen(token) - 1;
        while (end > token && isspace((unsigned char)*end))
          end--;
        end[1] = '\0';

        // Copies the token to the memory
        strcpy(table->columns[j].Data.stringData[i], token);
        break;
      }
      token = strtok(NULL, ",");
    }
  }
  fclose(file);
}

// Aux functions
void writeHeader(FILE *file, Table *table) {
  fprintf(file, "Número de Colunas: %d\n", table->numColumns);
  fprintf(file, "Número de Registros: %d\n", table->numRows);
  fprintf(file, "Chave Primária: %d\n", table->primaryKeyIndex);
}

void writeCols(FILE *file, Table *table) {
  for (int i = 0; i < table->numColumns; i++) {
    fprintf(file, "%s", table->columns[i].name);

    if (i < table->numColumns - 1) {
      fprintf(file, ", ");
    }
  }
  fprintf(file, "\n");
}

void writeTypes(FILE *file, Table *table) {
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
}

void writeData(FILE *file, Table *table) {
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
}

// Main function
void writeTable(Table *table, char *tableName) {
  char filename[MAX_TABLE_NAME + 4];
  sprintf(filename, "../txts/%s.txt", tableName);

  FILE *file = fopen(filename, "w");
  if (!tableCheckError(file)) {
    printf("Erro ao abrir o arquivo %s\n", filename);
    return;
  }

  writeHeader(file, table);
  writeCols(file, table);
  writeTypes(file, table);
  writeData(file, table);

  // Writes the types
  // Writes data
  fclose(file);
}
