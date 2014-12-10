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

%nonassoc TokenGt TokenLt TokenLeq TokenGeq TokenEq TokenNotEq TokenBoolNot
%left TokenBoolOr
%left TokenBoolAnd
%left TokenAdd TokenSub
%left TokenMul TokenDiv TokenMod
%left TokenPow
%left TokenEndl TokenSep TokenComma

%%

Cmd:
  TokenIf BoolExp TokenEndl Cmd IfExp TokenEnd                  { /**/ }
| TokenIf BoolExp TokenEndl Cmd IfExp TokenElse Cmd TokenEnd    { /**/ }
| TokenWhile BoolExp TokenEndl Cmd TokenEnd                     { /**/ }
| TokenVar TokenAtr Exp                                         { /**/ }
| TokenPrintln TokenLB ListExp TokenRB                          { /**/ }
| Cmd TokenEndl Cmd                                             { /**/ }
| Cmd TokenEndl                                                 { /**/ }
| TokenEndl Cmd                                                 { /**/ }
| Cmd TokenSep Cmd                                              { /**/ }
| Cmd TokenSep                                                  { /**/ }
;

IfExp:
  TokenElseIf BoolExp TokenEndl Cmd IfExp                       { /**/ }
| TokenElseIf BoolExp TokenEndl Cmd                             { /**/ } 
| /*epsilon*/                                                   { /**/ }
;

ListExp:
  Exp TokenComma ListExp                                        { /**/ }
| Exp                                                           { /**/ }
;

Exp:
  NumExp                                                        { /**/ }
| BoolExp                                                       { /**/ }
;

NumExp:
  NumExp TokenAdd NumExp                                        { /**/ }
| NumExp TokenSub NumExp                                        { /**/ }
| NumExp TokenMul NumExp                                        { /**/ }
| NumExp TokenDiv NumExp                                        { /**/ }
| NumExp TokenPow NumExp                                        { /**/ }
| NumExp TokenMod NumExp                                        { /**/ }
| TokenLB NumExp TokenRB                                        { /**/ }
| TokenInt                                                      { /**/ }
| TokenFloat                                                    { /**/ }
| TokenBool                                                     { /**/ }
| TokenVar                                                      { /**/ }
;

BoolExp:
  BoolExp TokenBoolAnd BoolExp                                  { /**/ }
| BoolExp TokenBoolOr BoolExp                                   { /**/ }
| TokenBoolNot BoolExp                                          { /**/ }
| BoolExp TokenEq BoolExp                                       { /**/ }
| BoolExp TokenNotEq BoolExp                                    { /**/ }
| BoolExp TokenLt BoolExp                                       { /**/ }
| BoolExp TokenGt BoolExp                                       { /**/ }
| BoolExp TokenLeq BoolExp                                      { /**/ }
| BoolExp TokenGeq BoolExp                                      { /**/ }
| TokenLB NumExp TokenRB                                        { /**/ }
| TokenInt                                                      { /**/ }
| TokenBool                                                     { /**/ }
| TokenVar                                                      { /**/ }
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
