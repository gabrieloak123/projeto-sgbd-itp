#include <stdbool.h>
#include <stdio.h>

#include "definitions.h"

#ifndef FUNCS
#define FUNCS

// Main functions
void initMainTable();
void createTable();
void listTables();
void listDataFromTable();
void deleteLine();
void dropTable();
void addData();
void searchData();

// Auxiliar functions
bool typeAllowed(char *maybeType);
bool isTableNameInUse(char *tableName);
bool isCollumnNameInUse(char *columnName, Table *table);
bool areTheSame(char *input, char *expected);
bool validPrimaryKeyValue(Table table, int primaryKeyValue,
                          int *primaryKeyValueIndex);
bool tableCheckError(FILE *tableName);
int verifyHowManyColsOfType(Table *table, Type type);
char *dataTypeToString(Type type);
void readTableName(char *tableName);
void changeTablesQuantity(int addOrDropValue);
void readTableContent(FILE *table, char *tableContent, int maxSize);
void readColumns(Table *Table);
void addColumnToFile(FILE *table, char *colType, char *colName);
void listDataFrom(char tableName[MAX_TABLE_NAME]);
void showMenu();
void setValueBasedOnType(Table *table, int i, char value[MAX_STRING_SIZE]);
void replaceValues(Table *table, int primaryKeyIndex);
void printLineAndBreak(size_t size, char character);
void breakLine();

// File Operation functions
void readMain();
void writeMain();
void readTable();
void writeTable();

// Auxiliar functions
void writeHeader(FILE *file, Table *table);
void writeCols(FILE *file, Table *table);
void writeTypes(FILE *file, Table *table);
void writeData(FILE *file, Table *table);

#endif
