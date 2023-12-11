#ifndef TABLE
#define TABLE

#define TAMMAX 100

typedef enum{
    EMPTY,
    INT,
    FLOAT,
    DOUBLE,
    CHAR,
    STRING,
} Type;

typedef struct {
    Type type;
    union{
        int intValue;
        float floatValue;
        char charValue;
        char *stringValue;
    } value;
} Column;

typedef struct {
    unsigned int pk;
    Column col[TAMMAX];
} Row;

typedef struct {
    char name[15];
    char colname[TAMMAX][15];
    Row row[TAMMAX];
} Table;

#endif