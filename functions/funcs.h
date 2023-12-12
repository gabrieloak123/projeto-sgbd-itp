#include <stdbool.h>
#ifndef FUNCS
#define FUNCS

#define MAX_TABLE_NAME 20
#define MAX_NAMES_CONTENT 100
#define MAX_COL_TYPE 10
#define MAX_COL_NAME 25
#define MAX_FILE_NAME 25

void printLine(int size);
void showMenu();

//main functions
void initMainTable();
void createTable();
void listTables();
void listDataFromTable();
void deleteLine();
void dropTable();
void addData();
void searchData();

//auxiliar functions
void showMenu();
bool typeAllowed(char *maybeType);
bool isnameInUse(char *fileName, char *targetWord);
int tableCheckError(FILE *tableName);
void readTableName(char *tableName);
void changeColRowQuantity(char fileName[MAX_FILE_NAME], int addOrDropValue, char colOrRow[4]);
void readTableContent(FILE *table, char *tableContent, int maxSize);
void readColumns(FILE *table, char fileName[MAX_FILE_NAME]);
void addColumnToFile(FILE *table, char *colType, char *colName);

#endif