all: clean
	flex scanner.lex
	bison -d parser.ypp
	g++ -o hw5 *.c *.cpp
clean:
	rm -f lex.yy.c
	rm -f parser.tab.*pp
	rm -f hw5

debug:	clean
		flex scanner.lex
		bison -d parser.ypp
		g++ -DDEBUG -g -o hw5 *.c *.cpp