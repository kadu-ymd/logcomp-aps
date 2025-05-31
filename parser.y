%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void yyerror(const char *s);
int yylex(void);
extern FILE *yyin;
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
    ENTER NEWLINE statements END optional_final_newline YYEOF
    ;

optional_final_newline:
    /* vazio */
    | NEWLINE
    ;

statements:
    /* vazio */
    | statements statement
    ;

statement:
    block_statement NEWLINE
    ;

block_statement:
    /* vazio */
    | movement_block
    | interact_block
    | assignment_block
    | sequence_block
    | conditional_block
    | loop_block
    | collect_command
    ;

assignment_block:
    IDENTIFIER ASSIGN interact_block
    ;

movement_block:
    MOVE DIRECTION VALUE
    ;

interact_block:
    INTERACT OPEN DIRECTION
    | INTERACT COLLECT DIRECTION
    ;

sequence_block:
    DEFINE SEQUENCE IDENTIFIER COLON NEWLINE statements SEQUENCE END
    ;

conditional_block:
    IF if_condition COLON NEWLINE statements ELSE COLON NEWLINE statements CONDITIONAL END
    ;

if_condition:
    collectable_condition
    | object_condition
    ;

collectable_condition:
    IDENTIFIER relational_operator VALUE
    ;

object_condition_end:
    INTERACTABLE
    | STATE
    ;

object_condition:
    OBJECT DIRECTION relational_bool object_condition_end
    ;

loop_block:
    WHILE loop_condition COLON NEWLINE statements LOOP END
    ;

loop_condition:
    collectable_condition
    | object_condition
    ;

relational_bool:
    IS
    | ISNOT
    ;

relational_operator:
    GT | LT | GE | LE | EQ | NE
    ;

collect_command:
    COLLECT COLLECTABLE VALUE
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Erro de sintaxe: %s\n", s);
}

int main(int argc, char **argv) {
    if (argc > 1) {
        FILE *f = fopen(argv[1], "r");
        if (!f) {
            perror(argv[1]);
            return 1;
        }
        yyin = f;
    }

    yyparse();

    if (argc > 1) {
        fclose(yyin);
    }
    return 0;
}