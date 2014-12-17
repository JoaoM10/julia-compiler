%{
#include <bits/stdc++.h>
#include "ast.h"
#include "icg.h"
using namespace std;

extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE *yyin;
extern int line_num;

Prgm *root;

void yyerror(const char *s);
%}

%union {
  int ival;
  double fval;
  bool bval;
  char *sval;
  
  Prgm *pg;
  Cmd *cm;
  ElseIf *eif;
  Lst *ls;
  Exp *xp;
}
                        
%token  <ival>          TokenInt
%token  <fval>          TokenFloat
%token  <bval>          TokenBool
%token  <sval>          TokenVar

%token                  TokenAdd TokenSub TokenMul TokenDiv TokenPow TokenMod TokenLB TokenRB
%token                  TokenEq TokenNotEq TokenLeq TokenGeq TokenLt TokenGt
%token                  TokenBoolNot TokenBoolOr TokenBoolAnd
%token                  TokenPrintln
%token                  TokenAtr
%token                  TokenIf TokenElseIf TokenElse
%token                  TokenWhile
%token                  TokenComma TokenEnd TokenSep TokenEndl
%token                  TokenFunction
                        
%nonassoc               TokenGt TokenLt TokenLeq TokenGeq TokenEq TokenNotEq TokenBoolNot
%left                   TokenBoolOr
%left                   TokenBoolAnd
%left                   TokenAdd TokenSub
%left                   TokenMul TokenDiv TokenMod
%left                   TokenPow
%left                   TokenEndl TokenSep TokenComma

%type   <pg>            Prgm
%type   <cm>            Cmd
%type   <eif>           IfExp
%type   <ls>            ListExp
%type   <xp>            Exp
%type   <xp>            NumExp 
%type   <xp>            BoolExp
                                                
%%

Prgm:
                Cmd                                                           { $$ = new Prgm($1); root = $$; }
        |       /*epsilon*/                                                   { root = NULL; }
                ;

Cmd:
                TokenIf BoolExp TokenEndl Cmd TokenEnd                        { $$ = new Cmd_If($2, $4); }
        |       TokenIf BoolExp TokenEndl Cmd IfExp TokenEnd                  { $$ = new Cmd_If($2, $4, $5); }                
        |       TokenIf BoolExp TokenEndl Cmd TokenElse Cmd TokenEnd          { $$ = new Cmd_IfElse($2, $4, $6); }
        |       TokenIf BoolExp TokenEndl Cmd IfExp TokenElse Cmd TokenEnd    { $$ = new Cmd_IfElse($2, $4, $5, $7); }
        |       TokenWhile BoolExp TokenEndl Cmd TokenEnd                     { $$ = new Cmd_While($2, $4); }
        |       TokenVar TokenAtr Exp                                         { $$ = new Cmd_Atr(new Var($1), $3); }
        |       TokenPrintln TokenLB ListExp TokenRB                          { $$ = new Cmd_Print($3); }
        |       Cmd TokenEndl Cmd                                             { $$ = new Cmd_Seq($1, $3); }
        |       Cmd TokenEndl                                                 { $$ = $1; }
        |       TokenEndl Cmd                                                 { $$ = $2; }
        |       Cmd TokenSep Cmd                                              { $$ = new Cmd_Seq($1, $3); }
        |       Cmd TokenSep                                                  { $$ = $1; }
                ;

IfExp:
                TokenElseIf BoolExp TokenEndl Cmd IfExp                       { $$ = new ElseIf($2, $4, $5); }
        |       TokenElseIf BoolExp TokenEndl Cmd                             { $$ = new ElseIf($2, $4); } 
                ;

ListExp:
                Exp TokenComma ListExp                                        { $$ = new Lst($1, $3); }
        |       Exp                                                           { $$ = new Lst($1); }
        |       /* epsilon */                                                 { $$ = NULL; }
                ;

Exp:
                NumExp TokenAdd NumExp                                        { $$ = new Exp_Add($1, $3); }
        |       NumExp TokenSub NumExp                                        { $$ = new Exp_Sub($1, $3); }
        |       NumExp TokenMul NumExp                                        { $$ = new Exp_Mul($1, $3); }
        |       NumExp TokenDiv NumExp                                        { $$ = new Exp_Div($1, $3); }
        |       NumExp TokenPow NumExp                                        { $$ = new Exp_Pow($1, $3); }
        |       NumExp TokenMod NumExp                                        { $$ = new Exp_Mod($1, $3); }
        |       TokenLB NumExp TokenRB                                        { $$ = $2; }
        |       BoolExp TokenBoolAnd BoolExp                                  { $$ = new Exp_And($1, $3); }
        |       BoolExp TokenBoolOr BoolExp                                   { $$ = new Exp_Or($1, $3); }
        |       NumExp TokenEq NumExp                                         { $$ = new Exp_Eq($1, $3); }
        |       NumExp TokenNotEq NumExp                                      { $$ = new Exp_Neq($1, $3); }
        |       BoolExp TokenEq BoolExp                                       { $$ = new Exp_Eq($1, $3); }
        |       BoolExp TokenNotEq BoolExp                                    { $$ = new Exp_Neq($1, $3); }
        |       NumExp TokenLt NumExp                                         { $$ = new Exp_Lt($1, $3); }
        |       NumExp TokenGt NumExp                                         { $$ = new Exp_Gt($1, $3); }
        |       NumExp TokenLeq NumExp                                        { $$ = new Exp_Leq($1, $3); }
        |       NumExp TokenGeq NumExp                                        { $$ = new Exp_Geq($1, $3); }
        |       TokenBoolNot BoolExp                                          { $$ = new Exp_Not($2); }
        |       TokenLB BoolExp TokenRB                                       { $$ = $2; }
        |       TokenSub NumExp                                               { $$ = new Exp_Min($2); }
        |       TokenInt                                                      { $$ = new Exp_Val(new Int($1)); }
        |       TokenFloat                                                    { $$ = new Exp_Val(new Float($1)); }
        |       TokenBool                                                     { $$ = new Exp_Val(new Bool($1)); }
        |       TokenVar                                                      { $$ = new Exp_Val(new Var($1)); }
                ;

NumExp:
                NumExp TokenAdd NumExp                                        { $$ = new Exp_Add($1, $3); }
        |       NumExp TokenSub NumExp                                        { $$ = new Exp_Sub($1, $3); }
        |       NumExp TokenMul NumExp                                        { $$ = new Exp_Mul($1, $3); }
        |       NumExp TokenDiv NumExp                                        { $$ = new Exp_Div($1, $3); }
        |       NumExp TokenPow NumExp                                        { $$ = new Exp_Pow($1, $3); }
        |       NumExp TokenMod NumExp                                        { $$ = new Exp_Mod($1, $3); }
        |       TokenLB NumExp TokenRB                                        { $$ = $2; }
        |       TokenSub NumExp                                               { $$ = new Exp_Min($2); }
        |       TokenInt                                                      { $$ = new Exp_Val(new Int($1)); }
        |       TokenFloat                                                    { $$ = new Exp_Val(new Float($1)); }
        |       TokenVar                                                      { $$ = new Exp_Val(new Var($1)); }
                ;

BoolExp:
                BoolExp TokenBoolAnd BoolExp                                  { $$ = new Exp_And($1, $3); }
        |       BoolExp TokenBoolOr BoolExp                                   { $$ = new Exp_Or($1, $3); }
        |       NumExp TokenEq NumExp                                         { $$ = new Exp_Eq($1, $3); }
        |       NumExp TokenNotEq NumExp                                      { $$ = new Exp_Neq($1, $3); }
        |       BoolExp TokenEq BoolExp                                       { $$ = new Exp_Eq($1, $3); }
        |       BoolExp TokenNotEq BoolExp                                    { $$ = new Exp_Neq($1, $3); }
        |       NumExp TokenLt NumExp                                         { $$ = new Exp_Lt($1, $3); }
        |       NumExp TokenGt NumExp                                         { $$ = new Exp_Gt($1, $3); }
        |       NumExp TokenLeq NumExp                                        { $$ = new Exp_Leq($1, $3); }
        |       NumExp TokenGeq NumExp                                        { $$ = new Exp_Geq($1, $3); }
        |       TokenBoolNot BoolExp                                          { $$ = new Exp_Not($2); }
        |       TokenLB BoolExp TokenRB                                       { $$ = $2; }
        |       TokenBool                                                     { $$ = new Exp_Val(new Bool($1)); }
        |       TokenVar                                                      { $$ = new Exp_Val(new Var($1)); }
                ;

%%

int main(int argc, char **argv){
    
  char out_file[73] = "a";
  bool show_tac = false;
  for(int i = 1; i < argc; i ++)
    if(!strcmp(argv[i], "--print-tac"))
      show_tac = true;
    else if(i < argc - 1 && !strcmp(argv[i], "-o") && strlen(argv[i + 1]) < 20)
      strcpy(out_file, argv[i + 1]);
    else if(!strcmp(argv[i], "-h")){
      printf("Usage: %s <file name> <options>\n", argv[0]);
      printf("Options:\n");  
      printf("\t-o <file name>\tName the generated MIPS file.\n");  
      printf("\t--print-tac\tPrint the generated Three Address Code.\n");  
      return 0;
    }

  if(argc < 2){
    printf("Usage: %s <file name> <options>\n", argv[0]);
    printf("Use -h flag to see all options.\n");
    return -1;
  }

  strcat(out_file, ".asm");
  
  FILE *fin = fopen(argv[1], "r");
  if(!fin){
    printf("File not found!\n");
    printf("Usage: %s <file name>\n", argv[0]);
    return -1;
  }
  yyin = fin;
	
  yyparse();

  if(!root->semantic_analysis())
      exit(-1);
  
  compile(root, show_tac, out_file);
  
  return 0;
}

void yyerror(const char *s){
  fprintf(stderr, "ERROR, parse error on line %d! Message: %s\n", line_num, s);
  exit(-1);
}
