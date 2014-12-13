CCC = g++
CCFLAGS= -O2
LEX = flex
LFLAGS= -8     
YACC= bison 
YFLAGS= -d -t -y

RM = /bin/rm -f

compiler: y.tab.o lex.yy.o ast.o
	${CCC} ${CCFLAGS} lex.yy.o y.tab.o ast.o -o compiler -lfl

ast.o: ast.cpp ast.h
	${CCC} -c ast.cpp

y.tab.o: parser.y
	${YACC} ${YFLAGS} parser.y
	${CCC} ${CCFLAGS} y.tab.c -c

lex.yy.o: lexer.l
	${LEX} $(LFLAGS) lexer.l
	${CCC} ${CCFLAGS} lex.yy.c -c 

clean:
	/bin/rm -f lex.yy.* y.tab.* *.o compiler
