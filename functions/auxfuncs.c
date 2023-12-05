#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "funcs.h"

int nameInUse(char *tableName, char *content){
    char *subString = strtok(content, "\n");

    while (subString != NULL){
        char *nameInUse = strstr(subString, tableName);

        if(nameInUse != NULL){
            return 1;
        }
        subString = strtok(NULL, "\n");
    }
    return 0;
}

int tableCheckError(FILE *tableName){
    if(tableName == NULL){
        perror("Erro ao abrir o arquivo de nomes de tabela");
        fclose(tableName);
        return 1;
    }
    return 0;
}

bool verifyTableExistence(char *tableName){

}