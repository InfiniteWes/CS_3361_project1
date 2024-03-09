/*
    Wesley Spangler Lexical Analyzer. R#11736897
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "dcooke_analyzer.h"
#include "parser.h"

int nextToken;

static int charClass;
static char lexeme [100];
static char nextChar;
static int lexlen;
static FILE *in_fp;

static void addChar();
static int getChar();
static void getNonBlank();

int main()
{
    printf("DCooke Analyzer :: R11736897\n\n");
    if ((in_fp = fopen("test.dc", "r")) == NULL) {
        printf("Error - cannot open test file\n");
    } 
    else {
        getChar();
        do {
            lex();
            expr();
        } while (nextToken != EOF);
    }

    return 0;
}

static int lookup(char ch) {

    switch (ch) {
        case '<':
            addChar();
            if (getChar() == '>') {
                addChar();
                nextToken = NEQUAL_OP;
            } else {
                addChar();
                nextToken = LESSER_OP;
            }
            break;
        case '>':
            addChar();
            nextToken = GREATER_OP;
            break;
        case ':':
            addChar();
            if (getChar() == '=') {
                addChar();
                nextToken = ASSIGN_OP;
            } else {
                nextToken = COLON;
            }
            break;
        case ';':
            addChar();
            nextToken = SEMICOLON;
            break;
        case '=':
            addChar();
            nextToken = EQUAL_OP;
            break;
        case '(':
            addChar();
            nextToken = LEFT_PAREN;
            break;
        case ')':
            addChar();
            nextToken = RIGHT_PAREN;
            break;
        case '+':
            addChar();
            if (getChar() == '+') {
                addChar();
                nextToken = INC_OP;
            } else {
                nextToken = ADD_OP;
            }
            break;
        case '-':
            addChar();
            if (getChar() == '-') {
                addChar();
                nextToken = DEC_OP;
            } else {
                nextToken = SUB_OP;
            }
            break;
        case '*':
            addChar();
            nextToken = MULT_OP;
            break;
        case '/':
            addChar();
            nextToken = DIV_OP;
            break;
        case '%':
            addChar();
            nextToken = MOD_OP;
            break;
        default:
            addChar();
            nextToken = EOF;
            break;

    };
    return nextToken;
}

static void addChar() {
    if (lexlen <= 98) {
        lexeme[lexlen++] = nextChar;
        lexeme[lexlen] = 0;
    } else {
        printf("Error - the lexeme is to long. \n");
    }
}

int getChar() {
    if ((nextChar = getc(in_fp)) != EOF) {
        if (isalpha(nextChar))
            charClass = LETTER;
        else if (isdigit(nextChar))
            charClass = DIGIT;
        else charClass = UNKNOWN;
    } else {
        charClass = EOF;
    }
    return nextChar;
}

static void getNonBlank() {
    while (isspace(nextChar)) getChar();
}

static void getTokenName(int nextToken) {
    switch (nextToken) {
        case LETTER:
            printf("LETTER");
            break;
        case DIGIT:
            printf("DIGIT");
            break;
        case ASSIGN_OP:
            printf("ASSIGN_OP");
            break;
        case LESSER_OP:
            printf("LESSER_OP");
            break;
        case GREATER_OP:
            printf("GREATER_OP");
            break;
        case EQUAL_OP:
            printf("EQUAL_OP");
            break;
        case NEQUAL_OP:
            printf("NEQUAL_OP");
            break;
        case LEQUAL_OP:
            printf("LEQUAL_OP");
            break;
        case GEQUAL_OP:
            printf("GEQUAL_OP");
            break;
        case LEFT_PAREN:
            printf("LEFT_PAREN");
            break;
        case RIGHT_PAREN:
            printf("RIGHT_PAREN");
            break;
        case ADD_OP:
            printf("ADD_OP");
            break;
        case SUB_OP:
            printf("SUB_OP");
            break;
        case MULT_OP:
            printf("MULT_OP");
            break;
        case DIV_OP:
            printf("DIV_OP");
            break;
        case MOD_OP:
            printf("MOD_OP");
            break;
        case INC_OP:
            printf("INC_OP");
            break;
        case DEC_OP:
            printf("DEC_OP");
            break;
        case SEMICOLON:
            printf("SEMICOLON");
            break;
        case COLON:
            printf("COLON");
            break;
        case KEY_ELSE:
            printf("KEY_ELSE");
            break;
        case KEY_FI:
            printf("KEY_FI");
            break;
        case KEY_IF:
            printf("KEY_IF");
            break;
        case KEY_READ:
            printf("KEY_READ");
            break;
        case KEY_THEN:
            printf("KEY_THEN");
            break;
        case KEY_WRITE:
            printf("KEY_WRITE");
            break;
        case IDENT:
            printf("IDENT");
            break;
        case INT_LIT:
            printf("INT_LIT");
            break;
        default:
            printf("UNKNOWN");
            break;
    }
}

int isKeyword(char* str) {
    if (!strcmp(str, "if")) return KEY_IF;
    if (!strcmp(str, "else")) return KEY_ELSE;
    if (!strcmp(str, "read")) return KEY_READ;
    if (!strcmp(str, "write")) return KEY_WRITE;
    if (!strcmp(str, "fi")) return KEY_FI;

    return IDENT;
}

int lex() {
    lexlen = 0;
    getNonBlank();

    switch (charClass) {
        // Parse Identifiers
        case LETTER:
            addChar();
            getChar();
            while (charClass == LETTER || charClass == DIGIT) {
                addChar();
                getChar();
            }
            nextToken = isKeyword(lexeme);
            break;
        case DIGIT:
            addChar();
            getChar();
            while (charClass == DIGIT) {
                addChar();
                getChar();
            }
            nextToken = INT_LIT;
            break;
        case UNKNOWN:
            lookup(nextChar);
            getChar();
            break;
        case EOF:
            nextToken = EOF;
            lexeme[0] = 'E';
            lexeme[1] = 'O';
            lexeme[2] = 'F';
            lexeme[3] = 0;
            break;
    }

    printf("%-10s",lexeme);
    getTokenName(nextToken);
    printf("\n");
    return nextToken;

}
