#ifndef FRONT
#define FRONT

// Character Classes
#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99

// Token Codes
#define ASSIGN_OP
#define LESSER_OP
#define GREATER_OP
#define EQUAL_OP
#define NEQUAL_OP
#define LEQUAL_OP
#define GEQUAL_OP
#define LEFT_PAREN
#define RIGHT_PAREN
#define ADD_OP
#define SUB_OP
#define MULTIPLY_OP
#define DIV_OP
#define MOD_OP
#define INC_OP
#define DEC_OP
#define SEMICOLON
#define COLON
#define KEY_READ
#define KEY_WRITE
#define KEY_IF
#define KEY_FI
#define KEY_ELSE
#define KEY_THEN
#define IDENT
#define INT_LIT

int lex();

#endif