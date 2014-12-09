%{
#include <bits/stdc++.h>
using namespace std;

extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE *yyin;
extern int line_num;

void yyerror(const char *s);
%}

%union {
  int ival;
  double fval;
  bool bval;
  char *sval;
}

%token <ival> TokenInt
%token <fval> TokenFloat
%token <bval> TokenBool
%token <sval> TokenVar

%token TokenAdd TokenSub TokenMul TokenDiv TokenPow TokenMod TokenLB TokenRB
%token TokenEq TokenNotEq TokenLeq TokenGeq TokenLt TokenGt
%token TokenBoolNot TokenBoolOr TokenBoolAnd
%token TokenPrintln
%token TokenAtr
%token TokenIf TokenElseIf TokenElse
%token TokenWhile
%token TokenComma TokenEnd TokenSep TokenEndl

%%
prog:
;
%%

int main(int argc, char **argv){

  if(argc != 2){
    printf("Usage: %s <file name>\n", argv[0]);
    return -1;
  }
  
  FILE *fin = fopen(argv[1], "r");
  if(!fin){
    printf("File not found!\n");
    printf("Usage: %s <file name>\n", argv[0]);
    return -1;
  }
  yyin = fin;
	
  do{
    yyparse();
  }while(!feof(yyin));

  return 0;
}

void yyerror(const char *s){
  printf("EEK, parse error on line %d! Message: %s\n", line_num, s);
  exit(-1);
}
