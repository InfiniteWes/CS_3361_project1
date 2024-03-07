/*
    Wesley Spangler Lexical Analyzer. R#11736897
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "dcooke_anaylzer.h"
#include "parser.h"

int nextToken;

static int charClass;
static char lexeme [100];
static char nextChar;
static int lexlen;
static FILE *in_fp;

static void addChar();
static void getChar();
static void getNonBlank();

int main()
{
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
            nextToken = LESSER_OP;
            break;
        case '>':
            addChar();
            nextToken = GREATER_OP;
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
            nextToken = ADD_OP;
            break;
        case '-':
            addChar();
            nextToken = SUB_OP;
            break;
        case '*':
            addChar();
            nextToken = MULTIPLY_OP;
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

    }
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

static void getChar() {
    if ((nextChar = getc(in_fp)) != EOF) {
        if (isalpha(nextChar))
            charClass = LETTER;
        else if (isdigit(nextChar))
            charClass = DIGIT;
        else charClass = UNKNOWN;
    } else {
        charClass = EOF;
    }
}

static void getNonBlank() {
    while (isspace(nextChar)) getChar();
}

int doubleChar(char* str) {
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
            lexeme[lexlen] = 0;
            nextToken = doubleChar(lexeme);
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

    printf("%s          %d", lexeme, nextToken);
    return nextToken;

}
