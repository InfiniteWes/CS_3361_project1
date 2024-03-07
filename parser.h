#ifndef PARSER_H
#define PARSER_H

void program();
void statement();
void c();
void expr();
void term();
void factor();
void operator();
void variable();
void number();

extern int nextToken;
#endif