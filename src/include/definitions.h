#include <stdbool.h>
#include <string.h>

#ifndef DEFS
#define DEFS

#define MAX_TABLE_NAME 100
#define MAX_COLUMNS 10
#define MAX_COLUMN_TYPE 10
#define MAX_COLUMN_NAME 100
#define MAX_NUM_TABLES 100
#define MAX_REGISTER_SIZE 10
#define MAX_STRING_SIZE 200
#define MAX_OPTION_SIZE 5
#define DEFAULT_LINE_LENGTH 55

static const char mainTxtPath[18] = "../txts/main.txt";

typedef enum {
  INT,
  FLOAT,
  DOUBLE,
  CHAR,
  STRING,
} Type;

typedef struct {
  char name[MAX_COLUMN_NAME];
  Type type;
  bool isEmpty[MAX_REGISTER_SIZE];

  union {
    int intData[MAX_REGISTER_SIZE];
    float floatData[MAX_REGISTER_SIZE];
    double doubleData[MAX_REGISTER_SIZE];
    char charData[MAX_REGISTER_SIZE];
    char stringData[MAX_REGISTER_SIZE][MAX_STRING_SIZE];
  } Data;
} Column;

typedef struct {
  char name[MAX_TABLE_NAME];
  Column columns[MAX_COLUMNS];
  int numColumns;
  int numRows;
  int primaryKeyIndex;
} Table;

#endif
