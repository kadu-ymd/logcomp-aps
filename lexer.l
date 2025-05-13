%{
#include "parser.tab.h"
#include <string.h>
%}

DIGIT      [0-9]
LETTER     [a-zA-Z]
ID         {LETTER}({LETTER}|{DIGIT}|_)*

%%

"enter"             { return ENTER; }
"end"               { return END; }
"move"              { return MOVE; }
"interact"          { return INTERACT; }
"open"              { return OPEN; }
"collect"           { return COLLECT; }
"define"            { return DEFINE; }
"sequence"          { return SEQUENCE; }
"if"                { return IF; }
"else"              { return ELSE; }
"conditional"       { return CONDITIONAL; }
"while"             { return WHILE; }
"loop"              { return LOOP; }

"object"            { return OBJECT; }

"is"                { return IS; }
"is not"            { return ISNOT; }

">="                { return GE; }
"<="                { return LE; }
"=="                { return EQ; }
"!="                { return NE; }
">"                 { return GT; }
"<"                 { return LT; }

"="                 { return ASSIGN; }
":"                 { return COLON; }
"\n"                { return NEWLINE; }

"up"                { yylval.str = strdup(yytext); return DIRECTION; }
"down"              { yylval.str = strdup(yytext); return DIRECTION; }
"left"              { yylval.str = strdup(yytext); return DIRECTION; }
"right"             { yylval.str = strdup(yytext); return DIRECTION; }

"key"               { yylval.str = strdup(yytext); return COLLECTABLE; }
"coins"             { yylval.str = strdup(yytext); return COLLECTABLE; }
"card"              { yylval.str = strdup(yytext); return COLLECTABLE; }

"locker"            { yylval.str = strdup(yytext); return INTERACTABLE; }
"closet"            { yylval.str = strdup(yytext); return INTERACTABLE; }
"desk"              { yylval.str = strdup(yytext); return INTERACTABLE; }
"exit_door"         { yylval.str = strdup(yytext); return INTERACTABLE; }

"locked"            { yylval.str = strdup(yytext); return STATE; }
"unlocked"          { yylval.str = strdup(yytext); return STATE; }

{ID}                { yylval.str = strdup(yytext); return IDENTIFIER; }
{DIGIT}+            { yylval.num = atoi(yytext); return VALUE; }

[ \t\r]+            ;   // ignorar espaços em branco
.                   { return yytext[0]; }

%%
