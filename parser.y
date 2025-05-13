%{
#include <stdio.h>
#include <stdlib.h>

void yyerror(const char *s);
int yylex(void);
%}

%union {
    int num;
    char* str;
}

%token <str> IDENTIFIER DIRECTION COLLECTABLE INTERACTABLE STATE
%token <num> VALUE
%token ENTER END MOVE INTERACT OPEN COLLECT DEFINE SEQUENCE IF ELSE CONDITIONAL WHILE LOOP
%token OBJECT IS ISNOT
%token GE LE EQ NE GT LT
%token ASSIGN COLON NEWLINE

%start program

%%

program:
    ENTER NEWLINE statements END
    ;

statements:
    /* vazio */
    | statements statement
    ;

statement:
      NEWLINE
    | movement_block NEWLINE
    | interact_block NEWLINE
    | assignment NEWLINE
    | sequence NEWLINE
    | conditional NEWLINE
    | loop NEWLINE
    ;

assignment:
    IDENTIFIER ASSIGN interact_block
    ;

movement_block:
    MOVE DIRECTION VALUE
    ;

interact_block:
    INTERACT (OPEN | COLLECT) DIRECTION
    ;

sequence:
    DEFINE SEQUENCE IDENTIFIER COLON NEWLINE statements SEQUENCE END
    ;

conditional:
    IF if_condition COLON NEWLINE statements ELSE COLON statements CONDITIONAL END
    ;

if_condition:
    collectable_condition
    | interactable_condition
    ;

collectable_condition:
    COLLECTABLE relational_operator VALUE
    ;

interactable_condition:
    OBJECT DIRECTION relational_bool INTERACTABLE
    ;

loop:
    WHILE loop_condition COLON NEWLINE statements LOOP END
    ;

loop_condition:
    collectable_condition
    | interactable_condition
    | OBJECT DIRECTION relational_bool STATE
    ;

relational_bool:
    IS
    | ISNOT
    ;

relational_operator:
    GT | LT | GE | LE | EQ | NE
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Erro: %s\n", s);
}
