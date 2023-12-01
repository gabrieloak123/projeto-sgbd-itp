#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "./functions/funcs.h"

int main(){
    FILE *tableNames;

    tableNames = fopen("txts/main.txt", "w");
    fprintf(tableNames, "hello world!\n");
    fclose(tableNames);

    int choice;
    bool shouldContinue = true;

    while(shouldContinue){
        showMenu();
        scanf("%d", &choice);
        
        switch (choice){
        case 1:
            createTable();
            break;
        case 2:
            listTables(tableNames);
            break;
        case 3:
            addData();
            break;
        case 4:
            listDataFromTable();
            break;
        case 5:
            searchData();
            break;
        case 6:
            deleteLine();
            break;
        case 7:
            dropTable();
            break;
        case 8:
            shouldContinue = false;
            break;
        
        default:
            printf("Opção inválida, digite novamente:\n");
            break;
        }
    }
    return 0;
}