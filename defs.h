#ifndef TABLE
#define TABLE

#define TAMMAX 100

typedef struct {
    union{
        int attrbI;
        float attrbF;
        char attrbC;
        char attrbS[15];
    }
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