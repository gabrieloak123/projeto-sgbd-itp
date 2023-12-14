#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "./functions/funcs.h"

int main(){
    int choice;
    bool shouldContinue = true;
    
    initMainTable();
    
    while(shouldContinue){
        showMenu();
        scanf("%d", &choice);
        
        switch (choice){
        case 0:
            system("clear");
            shouldContinue = false;
            break;
        case 1:
            system("clear");
            createTable();
            break;
        case 2:
            system("clear");
            listTables();
            break;
        case 3:
            system("clear");
            addData();
            break;
        case 4:
            system("clear");
            listDataFromTable();
            break;
        case 5:
            system("clear");
            deleteLine();
            break;
        case 6:
            system("clear");
            dropTable();
            break;
        default:
            system("clear");
            printf("Opção inválida, digite novamente:\n");
            break;
        }
    }
    return 0;
}