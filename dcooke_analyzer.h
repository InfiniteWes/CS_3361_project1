#ifndef FRONT
#define FRONT

// Character Classes
#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99

// Token Codes
#define ASSIGN_OP 20
#define LESSER_OP 28
#define GREATER_OP 29
#define EQUAL_OP 30
#define NEQUAL_OP 31
#define LEQUAL_OP 32
#define GEQUAL_OP 33
#define LEFT_PAREN 26
#define RIGHT_PAREN 27
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define MOD_OP 25
#define INC_OP 34
#define DEC_OP 35
#define SEMICOLON 36
#define COLON 37
#define KEY_READ 38
#define KEY_WRITE 39
#define KEY_IF 40
#define KEY_FI 41
#define KEY_ELSE 42
#define KEY_THEN 43
#define IDENT 11
#define INT_LIT 10

int lex();

#endif