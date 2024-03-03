#include <stdio.h>
#include <parser.h>
#include <dcooke_anaylzer.h>

static void error();

void expr()
{
    term();

    while (nextToken == ADD_OP || nextToken == SUB_OP || nextToken ==) {
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