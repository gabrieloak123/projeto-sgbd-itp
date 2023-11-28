#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "./functions/funcs.h"

int main(){
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
            listTables();
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
            printf("Opção inválida, digite novamente:");
            break;
        }
    }
    return 0;
}