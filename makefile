CC=gcc

all: parser

parser: dcooke_analyzer.o parser.o
	$(CC) -Wall dcooke_analyzer.o parser.o -o parser	

.c.o:
	$(CC) -Wall -c $<


test: parser test.dc
	./parser

clean:
	$(RM) parser.o dcooke_analyzer.o parser
