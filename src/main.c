#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "include/functions.h"

int main() {
  int choice;
  bool shouldContinue = true;

  initMainTable();

  while (shouldContinue) {
    showMenu();
    printf("Input: ");
    scanf("%d", &choice);

    switch (choice) {
    case 0:
      shouldContinue = false;
      break;
    case 1:
      createTable();
      break;
    case 2:
      listTables();
      break;
    case 3:
      addData();
      break;
    case 4:
      listDataFromTable();
      break;
    case 5:
      deleteLine();
      break;
    case 6:
      dropTable();
      break;
    default:
      printf("Opção inválida, digite novamente:\n");
      break;
    }
  }
  return 0;
}
