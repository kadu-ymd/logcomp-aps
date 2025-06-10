%{
#include "parser.tab.h" // Inclui o cabeçalho gerado pelo Bison/YACC, que contém as definições dos tokens
#include <string.h>    // Para strdup
#include <stdio.h>     // Para printf e fprintf (depuração e erros)
#include <stdlib.h>    // Para atoi (para converter string para int)

// Função opcional: Necessária para Flex se não estiver usando um driver C padrão.
// Retorna 1 para indicar que não há mais entrada.
int yywrap() {
    return 1;
}

// Variáveis e funções externas que podem ser necessárias no parser.y
extern int yylex(); // A função principal do lexer
extern int yyparse(); // A função principal do parser

%}

// Definições de expressões regulares (regex)
DIGIT       [0-9]
LETTER      [a-zA-Z]
ID          {LETTER}({LETTER}|{DIGIT}|_)*

%%

// Palavras-chave e Tokens Reservados (prioridade por ordem de aparição e comprimento)
// As palavras mais específicas ou longas devem vir antes das mais genéricas (como ID).

"enter"             { printf("DEBUG FLEX: Recognized ENTER\n"); return ENTER; }
"end"               { printf("DEBUG FLEX: Recognized END\n"); return END; }
"move"              { printf("DEBUG FLEX: Recognized MOVE\n"); return MOVE; }
"interact"          { printf("DEBUG FLEX: Recognized INTERACT\n"); return INTERACT; }
"open"              { printf("DEBUG FLEX: Recognized OPEN\n"); return OPEN; }
"collect"           { printf("DEBUG FLEX: Recognized COLLECT_KEYWORD\n"); return COLLECT_KEYWORD; } // Renomeado para evitar conflito com COLLECTABLE
"define"            { printf("DEBUG FLEX: Recognized DEFINE\n"); return DEFINE; }
"sequence"          { printf("DEBUG FLEX: Recognized SEQUENCE\n"); return SEQUENCE; }
"if"                { printf("DEBUG FLEX: Recognized IF_KEYWORD\n"); return IF_KEYWORD; } // Renomeado para evitar conflito com IF no parser (regra gramatical)
"else"              { printf("DEBUG FLEX: Recognized ELSE\n"); return ELSE; }
"conditional"       { printf("DEBUG FLEX: Recognized CONDITIONAL\n"); return CONDITIONAL; }
"while"             { printf("DEBUG FLEX: Recognized WHILE\n"); return WHILE; }
"loop"              { printf("DEBUG FLEX: Recognized LOOP\n"); return LOOP; }
"object"            { printf("DEBUG FLEX: Recognized OBJECT\n"); return OBJECT; }

// Literais Booleanos
"true"              { printf("DEBUG FLEX: Recognized TRUE_LITERAL\n"); yylval.num_bool = 1; return TRUE_LITERAL; }
"false"             { printf("DEBUG FLEX: Recognized FALSE_LITERAL\n"); yylval.num_bool = 0; return FALSE_LITERAL; }

// Operadores Relacionais e Atribuição
"is_not"            { printf("DEBUG FLEX: Recognized IS_NOT\n"); return IS_NOT; } // Corrigido o retorno
"is"                { printf("DEBUG FLEX: Recognized IS\n"); return IS; }
">="                { printf("DEBUG FLEX: Recognized GE\n"); return GE; }
"<="                { printf("DEBUG FLEX: Recognized LE\n"); return LE; }
"=="                { printf("DEBUG FLEX: Recognized EQ\n"); return EQ; }
"!="                { printf("DEBUG FLEX: Recognized NE\n"); return NE; }
">"                 { printf("DEBUG FLEX: Recognized GT\n"); return GT; }
"<"                 { printf("DEBUG FLEX: Recognized LT\n"); return LT; }
"="                 { printf("DEBUG FLEX: Recognized ASSIGN\n"); return ASSIGN; }

// Símbolos
":"                 { printf("DEBUG FLEX: Recognized COLON\n"); return COLON; }
"\n"                { printf("DEBUG FLEX: Recognized NEWLINE\n"); return NEWLINE; }
"{"                 { printf("DEBUG FLEX: Recognized LBRACE\n"); return LBRACE; } // Chave de abertura
"}"                 { printf("DEBUG FLEX: Recognized RBRACE\n"); return RBRACE; } // Chave de fechamento
"("                 { printf("DEBUG FLEX: Recognized LPAREN\n"); return LPAREN; } // Parêntese de abertura
")"                 { printf("DEBUG FLEX: Recognized RPAREN\n"); return RPAREN; } // Parêntese de fechamento

// Direções
"up"                { printf("DEBUG FLEX: Recognized DIRECTION (%s)\n", yytext); yylval.str = strdup(yytext); return DIRECTION; }
"down"              { printf("DEBUG FLEX: Recognized DIRECTION (%s)\n", yytext); yylval.str = strdup(yytext); return DIRECTION; }
"left"              { printf("DEBUG FLEX: Recognized DIRECTION (%s)\n", yytext); yylval.str = strdup(yytext); return DIRECTION; }
"right"             { printf("DEBUG FLEX: Recognized DIRECTION (%s)\n", yytext); yylval.str = strdup(yytext); return DIRECTION; }

// Coletáveis
"key"               { printf("DEBUG FLEX: Recognized COLLECTABLE (%s)\n", yytext); yylval.str = strdup(yytext); return COLLECTABLE; }
"coins"             { printf("DEBUG FLEX: Recognized COLLECTABLE (%s)\n", yytext); yylval.str = strdup(yytext); return COLLECTABLE; }
"card"              { printf("DEBUG FLEX: Recognized COLLECTABLE (%s)\n", yytext); yylval.str = strdup(yytext); return COLLECTABLE; }

// Itens Interagíveis
"locker"            { printf("DEBUG FLEX: Recognized INTERACTABLE (%s)\n", yytext); yylval.str = strdup(yytext); return INTERACTABLE; }
"closet"            { printf("DEBUG FLEX: Recognized INTERACTABLE (%s)\n", yytext); yylval.str = strdup(yytext); return INTERACTABLE; }
"desk"              { printf("DEBUG FLEX: Recognized INTERACTABLE (%s)\n", yytext); yylval.str = strdup(yytext); return INTERACTABLE; }
"exit_door"         { printf("DEBUG FLEX: Recognized INTERACTABLE (%s)\n", yytext); yylval.str = strdup(yytext); return INTERACTABLE; }

// Estados de Objeto
"locked"            { printf("DEBUG FLEX: Recognized STATE (%s)\n", yytext); yylval.str = strdup(yytext); return STATE; }
"unlocked"          { printf("DEBUG FLEX: Recognized STATE (%s)\n", yytext); yylval.str = strdup(yytext); return STATE; }

// IDENTIFIER e VALUE devem vir depois de todas as palavras reservadas
{DIGIT}+            { printf("DEBUG FLEX: Recognized VALUE_LITERAL (%s)\n", yytext); yylval.num = atoi(yytext); return VALUE_LITERAL; } // Renomeado para evitar conflito
{ID}                { printf("DEBUG FLEX: Recognized IDENTIFIER (%s)\n", yytext); yylval.str = strdup(yytext); return IDENTIFIER; }


// Ignorar espaços em branco, tabs e retornos de carro.
[ \t\r]+            ;

// Qualquer outro caractere é um erro.
.                   { fprintf(stderr, "DEBUG FLEX: Caractere UNKNOWN: '%c' (0x%x) na linha %d\n", yytext[0], yytext[0], yylineno); /*yyerror("Caractere inválido");*/ return yytext[0]; } // yylineno é uma variável global do Flex.
%%