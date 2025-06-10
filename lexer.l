%{
#include "parser.tab.h"
#include <string.h>
#include <stdio.h> // Adicionado para printf

// Opcional: Adicione esta função para depurar yywrap
int yywrap() {
    return 1;
}
%}

DIGIT       [0-9]
LETTER      [a-zA-Z]
ID          {LETTER}({LETTER}|{DIGIT}|_)*

%%

"enter"             { printf("DEBUG FLEX: Recognized ENTER\n"); return ENTER; }
"end"               { printf("DEBUG FLEX: Recognized END\n"); return END; }
"move"              { printf("DEBUG FLEX: Recognized MOVE\n"); return MOVE; }
"interact"          { printf("DEBUG FLEX: Recognized INTERACT\n"); return INTERACT; }
"open"              { printf("DEBUG FLEX: Recognized OPEN\n"); return OPEN; }
"collect"           { printf("DEBUG FLEX: Recognized COLLECT\n"); return COLLECT; }
"define"            { printf("DEBUG FLEX: Recognized DEFINE\n"); return DEFINE; }
"sequence"          { printf("DEBUG FLEX: Recognized SEQUENCE\n"); return SEQUENCE; }
"if"                { printf("DEBUG FLEX: Recognized IF\n"); return IF; }
"else"              { printf("DEBUG FLEX: Recognized ELSE\n"); return ELSE; }
"conditional"       { printf("DEBUG FLEX: Recognized CONDITIONAL\n"); return CONDITIONAL; }
"while"             { printf("DEBUG FLEX: Recognized WHILE\n"); return WHILE; }
"loop"              { printf("DEBUG FLEX: Recognized LOOP\n"); return LOOP; }
"object"            { printf("DEBUG FLEX: Recognized OBJECT\n"); return OBJECT; }
"is"                { printf("DEBUG FLEX: Recognized IS\n"); return IS; }
"is_not"            { printf("DEBUG FLEX: Recognized ISNOT\n"); }
">="                { printf("DEBUG FLEX: Recognized GE\n"); return GE; }
"<="                { printf("DEBUG FLEX: Recognized LE\n"); return LE; }
"=="                { printf("DEBUG FLEX: Recognized EQ\n"); return EQ; }
"!="                { printf("DEBUG FLEX: Recognized NE\n"); return NE; }
">"                 { printf("DEBUG FLEX: Recognized GT\n"); return GT; }
"<"                 { printf("DEBUG FLEX: Recognized LT\n"); return LT; }
"="                 { printf("DEBUG FLEX: Recognized ASSIGN\n"); return ASSIGN; }
":"                 { printf("DEBUG FLEX: Recognized COLON\n"); return COLON; }
"\n"                { printf("DEBUG FLEX: Recognized NEWLINE\n"); return NEWLINE; }

"up"                { printf("DEBUG FLEX: Recognized DIRECTION (%s)\n", yytext); yylval.str = strdup(yytext); return DIRECTION; }
"down"              { printf("DEBUG FLEX: Recognized DIRECTION (%s)\n", yytext); yylval.str = strdup(yytext); return DIRECTION; }
"left"              { printf("DEBUG FLEX: Recognized DIRECTION (%s)\n", yytext); yylval.str = strdup(yytext); return DIRECTION; }
"right"             { printf("DEBUG FLEX: Recognized DIRECTION (%s)\n", yytext); yylval.str = strdup(yytext); return DIRECTION; }

"key"               { printf("DEBUG FLEX: Recognized COLLECTABLE (%s)\n", yytext); yylval.str = strdup(yytext); return COLLECTABLE; }
"coins"             { printf("DEBUG FLEX: Recognized COLLECTABLE (%s)\n", yytext); yylval.str = strdup(yytext); return COLLECTABLE; }
"card"              { printf("DEBUG FLEX: Recognized COLLECTABLE (%s)\n", yytext); yylval.str = strdup(yytext); return COLLECTABLE; }

"locker"            { printf("DEBUG FLEX: Recognized INTERACTABLE (%s)\n", yytext); yylval.str = strdup(yytext); return INTERACTABLE; }
"closet"            { printf("DEBUG FLEX: Recognized INTERACTABLE (%s)\n", yytext); yylval.str = strdup(yytext); return INTERACTABLE; }
"desk"              { printf("DEBUG FLEX: Recognized INTERACTABLE (%s)\n", yytext); yylval.str = strdup(yytext); return INTERACTABLE; }
"exit_door"         { printf("DEBUG FLEX: Recognized INTERACTABLE (%s)\n", yytext); yylval.str = strdup(yytext); return INTERACTABLE; }

"locked"            { printf("DEBUG FLEX: Recognized STATE (%s)\n", yytext); yylval.str = strdup(yytext); return STATE; }
"unlocked"          { printf("DEBUG FLEX: Recognized STATE (%s)\n", yytext); yylval.str = strdup(yytext); return STATE; }

{ID}                { printf("DEBUG FLEX: Recognized IDENTIFIER (%s)\n", yytext); yylval.str = strdup(yytext); return IDENTIFIER; }
{DIGIT}+            { printf("DEBUG FLEX: Recognized VALUE (%s)\n", yytext); yylval.num = atoi(yytext); return VALUE; }

[ \t\r]+            ;  // ignorar espaços em branco
.                   { fprintf(stderr, "DEBUG FLEX: UNKNOWN character: '%c' (0x%x)\n", yytext[0], yytext[0]); return yytext[0]; }
%%