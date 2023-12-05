#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "./functions/funcs.h"

int main(){
    FILE *tableOfNames;
    //char *stringTeste = "hello\nworld\nhelloworld\n";

    tableOfNames = fopen("txts/tableNames.txt", "w");
    //fwrite(stringTeste, sizeof(char), strlen(stringTeste), tableOfNames);
    fclose(tableOfNames);

    //lembrar de usar o system("clear")

    int choice;
    bool shouldContinue = true;

    while(shouldContinue){
        showMenu();
        scanf("%d", &choice);
        
        switch (choice){
        case 0:
            shouldContinue = false;
            break;
        case 1:
            createTable();
            break;
        case 2:
            listTables(tableOfNames);
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
        default:
            printf("Opção inválida, digite novamente:\n");
            break;
        }
    }
    return 0;
}