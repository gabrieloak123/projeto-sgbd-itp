#ifndef DEFS
#define DEFS

// Alocar dinâmicamente se quiser
#define MAX_TABLE_NAME 100
#define MAX_COLUMNS 100
#define MAX_COLUMN_NAME 100
#define MAX_NUM_TABLES 100
#define MAX_REGISTER_SIZE 100
#define MAX_STRING_SIZE 200

typedef enum{
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

/* Versão Alternativa 1:
typedef struct {
    char name[MAX_COLUMN_NAME];
    Type type;
    bool isEmpty[MAX_REGISTER_SIZE];
    char stringData[MAX_REGISTER_SIZE][MAX_STRING_SIZE];
} Column;
 * A ideia dessa versão é salvar tudo em string e converter conforme o necessário
 */

/* Versão Alternativa 2:
typedef struct {
    union {
        int intValue;
        float floatValue;
        double doubleValue;
        char charValue;
        char stringValue[MAX_STRING_SIZE];
    } value;
    Type type;
} Cell;

typedef struct {
    Value values[MAX_COLUMNS];
    int numValues;
} Row;
 * A ideia dessa versão é usar uma estrutura de dados para a linha
*/

typedef struct {
    char name[MAX_TABLE_NAME];
    Column columns[MAX_COLUMNS];
    int numColumns;
    int numRows;
    int primaryKeyIndex;
} Table;

#endif