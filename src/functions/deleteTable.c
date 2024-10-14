#include <unistd.h>

#include "../include/definitions.h"
#include "../include/functions.h"

extern char tableNames[MAX_TABLE_NAME][MAX_NUM_TABLES];
extern int numTables;

void dropTable() {
  char tableName[15];
  char fileName[25];
  char confirmDrop;

  listTables();
  printf("\n");
  printf("Digite a tabela que deseja deletar:\n");
  scanf(" %[^\n]", tableName);

  sprintf(fileName, "txts/%s.txt", tableName);
  if (access(fileName, F_OK) != -1) {
    printf("Tem certeza que deseja deletar a tabela %s? (S/N)\n", tableName);
    scanf(" %c", &confirmDrop);

    if (confirmDrop == 'S' || confirmDrop == 's') {
      if (remove(fileName) == 0) {
        printf("Tabela deletada\n");

        FILE *tableOfNames, *temp;
        char buffer[256];
        char tableContent[256];

        tableOfNames = fopen("txts/main.txt", "r");
        tableCheckError(tableOfNames);

        temp = fopen("txts/temp.txt", "w");
        tableCheckError(tableOfNames);

        readTableContent(tableOfNames, tableContent, sizeof(tableContent));

        char *tableStart = strstr(tableContent, tableName);
        if (tableStart != NULL) {
          char *tableEnd = strchr(tableStart, '\n');
          if (tableEnd != NULL) {
            // Copies the section before the table to a temp file
            fwrite(tableContent, sizeof(char), tableStart - tableContent, temp);
            // Copies the section after the table to a temp file
            fwrite(tableEnd + 1, sizeof(char), strlen(tableEnd + 1), temp);
          }
        }
        fclose(tableOfNames);
        fclose(temp);

        remove("../txts/main.txt");
        rename("../txts/temp.txt", "../txts/main.txt");
      } else {
        printf("Erro ao deletar a tabela\n");
      }
    } else {
      printf("Operacao cancelada\n");
    }
  } else {
    printf("Tabela nao encontrada\n");
  }
}
