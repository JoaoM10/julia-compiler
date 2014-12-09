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

[0-9]+                                  { return TokenInt; }
[0-9]+\.[0-9]+                          { return TokenFloat; }
true                                    { return TokenBoolT; }
false                                   { return TokenBoolF; }
[a-zA-Z\_][a-zA-Z0-9\_\!]*              { return TokenVar; }

   /* Ignore everything else */

.                                       ;

%%
