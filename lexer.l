%{
typedef struct AstNode {
    char* type;
    char* value_str;
    int value_int;
} AstNode;

AstNode* create_node_str(const char* type, const char* value);
AstNode* create_node_int(const char* type, int value);
AstNode* create_node_keyword(const char* type);

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "parser.tab.h"

int yywrap() {
    return 1;
}

extern int yylex();
extern int yyparse();

extern int yylineno;

%}
DIGIT       [0-9]
LETTER      [a-zA-Z]
ID          {LETTER}({LETTER}|{DIGIT}|_)*
%%
"enter"             { return ENTER; }
"program"           { return PROGRAM_KEYWORD; }
"end"               { return END; }
"move"              { return MOVE; }
"interact"          { return INTERACT; }
"open"              { return OPEN; }
"collect"           { return COLLECT_KEYWORD; }
"define"            { return DEFINE; }
"sequence"          { return SEQUENCE; }
"if"                { return IF_KEYWORD; }
"else"              { return ELSE; }
"conditional"       { return CONDITIONAL; }
"while"             { return WHILE; }
"loop"              { return LOOP; }
"object"            { return OBJECT; }
"true"              { yylval.num_bool = 1; return BOOL_LITERAL; }
"false"             { yylval.num_bool = 0; return BOOL_LITERAL; }
"is_not"            { return IS_NOT; }
"is"                { return IS; }
">="                { return GE; }
"<="                { return LE; }
"=="                { return EQ; }
"!="                { return NE; }
">"                 { return GT; }
"<"                 { return LT; }
"="                 { return ASSIGN; }
":"                 { return COLON; }
"\n"                { yylineno++; return NEWLINE; }
"{"                 { return LBRACE; }
"}"                 { return RBRACE; }
"("                 { return LPAREN; }
")"                 { return RPAREN; }
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

{DIGIT}+            { yylval.num = atoi(yytext); return INT_LITERAL; }
{ID}                { yylval.str = strdup(yytext); return IDENTIFIER; }

[ \t\r]+            ;

.                   { fprintf(stderr, "DEBUG FLEX: Caractere UNKNOWN: '%s' (0x%x) na linha %d\n", yytext, yytext[0], yylineno); return yytext[0]; }
%%