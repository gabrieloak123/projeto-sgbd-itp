#ifndef FUNCS
#define FUNCS

void printLine(int size);
void showMenu();

//main functions
void createTable();
void listTables(FILE *tableNamesFile);
void listDataFromTable();
void deleteLine();
void dropTable();
void addData();
void searchData();

//auxiliar functions
int nameInUse(char *tableName, char *content);
int tableCheckError(FILE *tableName);
bool typeAllowed(char *maybeType);

#endif