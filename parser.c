#include <stdio.h>
#include "parser.h"
#include "dcooke_anaylzer.h"

static void error();

void program() {
    statement();
}

void statement() {

    if (nextToken == IDENT) {
        lex();
        if (nextToken == ASSIGN_OP) {
            lex();
            expr();
        }
    } else if (nextToken == KEY_READ) {
        lex();
        if (nextToken == LEFT_PAREN) {
            lex();
            if (nextToken == IDENT) {
                lex();
                if (nextToken == RIGHT_PAREN) {
                    lex();
                }
            }
        }
    } else if (nextToken == KEY_WRITE) {
        lex();
        if (nextToken == LEFT_PAREN) {
            lex();
            expr();
            if (nextToken == RIGHT_PAREN) {
                lex();
            }
        }
    } else if (nextToken == KEY_IF) {
        lex();
        c();
        if (nextToken == SEMICOLON) {
            lex();
            if (nextToken == KEY_THEN) {
                lex();
                statement();
                if (nextToken == KEY_FI) {
                    lex();
                }
            }
        }
    } else if (nextToken == KEY_IF) {
        lex();
        c();
        if (nextToken == SEMICOLON) {
            lex();
            if (nextToken == KEY_THEN) {
                lex();
                statement();
                if (nextToken == KEY_ELSE) {
                    lex();
                    statement();
                    if (nextToken == KEY_FI) {
                        lex();
                    }
                }
            }
        }
    } else if (nextToken == SEMICOLON) {
        lex();
        statement();
    }

    statement();
}

void c() {

    expr();
    if (nextToken == LESSER_OP) {
        lex();
        expr();
    } else if (nextToken == GREATER_OP) {
        lex();
        expr();
    } else if (nextToken == EQUAL_OP) {
        lex();
        expr();
    } else if (nextToken == NEQUAL_OP) {
        lex();
        expr();
    } else if (nextToken == LEQUAL_OP) {
        lex();
        expr();
    } else if (nextToken == GEQUAL_OP) {
        lex();
        expr();
    }
}

void expr()
{
    term();

    while (nextToken == ADD_OP || nextToken == SUB_OP) {
        lex();
        term();
    }
}

void term()
{
    factor();

    while (nextToken == MULTIPLY_OP || nextToken == DIV_OP || nextToken == MOD_OP) {
        lex();
        factor();
    }
}

void factor()
{
    if (nextToken == IDENT || nextToken == INT_LIT) {
        lex();    
    }
    else if (nextToken == LEFT_PAREN) {
        lex();
        expr();

        if (nextToken == RIGHT_PAREN) {
            lex();
        } else {
            error();
        }
    }
    else 
    {
        error();
    }

    void error();
}

static void error() 
{
    printf("Error (more is desired, but not implemented).\n");
}