#include <stdbool.h>
#ifndef FUNCS
#define FUNCS

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
int isnameInUse(char *tableName, char *content);
int tableCheckError(FILE *tableName);
void readTableName(char *tableName);
void changeTablesQuantity(int addOrDropValue);
void readTableContent(FILE *table, char *tableContent, int maxSize);
void readColumns(FILE *newTable);
void addColumnToFile(FILE *table, char *colType, char *colName);

// file Op functions
void readMain();
void writeMain();
void readTable();
void writeTable();

#endif