%{
#include <bits/stdc++.h>
#include "parser.tab.h"
using namespace std;

#define YY_DECL extern "C" int yylex()

int line_num;
%}
%%

   /* Arithmetic operators */

\+                                      { return TokenAdd; }
\-                                      { return TokenSub; }
\*                                      { return TokenMul; }
\/                                      { return TokenDiv; }
\^                                      { return TokenPow; }
\%                                      { return TokenMod; }
\(                                      { return TokenLB; }
\)                                      { return TokenRB; }

   /* Boolean comparators */

\=\=                                    { return TokenEq; }
\!\=                                    { return TokenNotEq; }
\<\=                                    { return TokenLeq; }
\>\=                                    { return TokenGeq; }
\<                                      { return TokenLt; }
\>                                      { return TokenGt; }

   /* Boolean operators */

\!                                      { return TokenBoolNot; }
\|\|                                    { return TokenBoolOr; }
\&\&                                    { return TokenBoolAnd; }

   /* Methods */

println                                 { return TokenPrintln; }

   /* Atribution */

\=                                      { return TokenAtr; }

   /* Ifs */

if                                      { return TokenIf; }
elseif                                  { return TokenElseIf; }
else                                    { return TokenElse; }

   /* Whiles */

while                                   { return TokenWhile; }

   /* Others */

\,                                      { return TokenComma; }
end                                     { return TokenEnd; }
\;                                      { return TokenSep; }
\n                                      { line_num ++; return TokenEndl; }

   /* Types and Vars */

[0-9]+\.[0-9]+                          { yylval.fval = atof(yytext); return TokenFloat; }
[0-9]+                                  { yylval.ival = atoi(yytext); return TokenInt; }
true                                    { yylval.bval = (yytext[0] == 't'); return TokenBool; }
false                                   { yylval.bval = (yytext[0] == 't'); return TokenBool; }
[a-zA-Z\_][a-zA-Z0-9\_\!]*              { yylval.sval = strdup(yytext); return TokenVar; }

   /* Ignore everything else */

.                                       ;

%%