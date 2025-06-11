%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct AstNode {
    char* type;
    char* value_str;
    int value_int;
} AstNode;

AstNode* create_node_str(const char* type, const char* value) {
    AstNode* node = (AstNode*) malloc(sizeof(AstNode));
    if (!node) { perror("Failed to allocate AstNode"); exit(EXIT_FAILURE); }
    node->type = strdup(type);
    node->value_str = (value != NULL) ? strdup(value) : NULL;
    node->value_int = 0;
    return node;
}

AstNode* create_node_int(const char* type, int value) {
    AstNode* node = (AstNode*) malloc(sizeof(AstNode));
    if (!node) { perror("Failed to allocate AstNode"); exit(EXIT_FAILURE); }
    node->type = strdup(type);
    node->value_str = NULL;
    node->value_int = value;
    return node;
}

AstNode* create_node_keyword(const char* type) {
    AstNode* node = (AstNode*) malloc(sizeof(AstNode));
    if (!node) { perror("Failed to allocate AstNode"); exit(EXIT_FAILURE); }
    node->type = strdup(type);
    node->value_str = NULL;
    node->value_int = 0;
    return node;
}

extern int yylineno;

void yyerror(const char *s);
int yylex(void);
extern FILE *yyin;

%}

%union {
    int num;
    char* str;
    int num_bool;
    AstNode* node;
}

%token <str> IDENTIFIER DIRECTION COLLECTABLE INTERACTABLE STATE
%token <num> INT_LITERAL
%token <num_bool> BOOL_LITERAL

%token ENTER PROGRAM_KEYWORD END MOVE INTERACT OPEN COLLECT_KEYWORD DEFINE SEQUENCE IF_KEYWORD ELSE CONDITIONAL WHILE LOOP OBJECT IS IS_NOT
%token GE LE EQ NE GT LT
%token ASSIGN COLON NEWLINE

%token LBRACE RBRACE LPAREN RPAREN

%type <node> program statements statement assignment_block movement_block interact_block sequence_block conditional_block condition collectable_condition object_target object_condition loop_block relational_bool relational_operator collect_command sequence_call factor collectable_or_identifier multiple_newlines_optional

%start program

%%

program:
    ENTER NEWLINE statements PROGRAM_KEYWORD END multiple_newlines_optional YYEOF
    { printf("DEBUG PARSER: Programa parseado com sucesso.\n"); YYACCEPT; }
    ;

statements:
    /* vazio */ { $$ = NULL; }
    | statements statement
    ;

statement:
    movement_block NEWLINE          { $$ = $1; }
    | interact_block NEWLINE        { $$ = $1; }
    | assignment_block NEWLINE      { $$ = $1; }
    | sequence_block NEWLINE        { $$ = $1; }
    | conditional_block NEWLINE     { $$ = $1; }
    | loop_block NEWLINE            { $$ = $1; }
    | collect_command NEWLINE       { $$ = $1; }
    | sequence_call NEWLINE         { $$ = $1; }
    ;

multiple_newlines_optional:
    /* vazio */ { $$ = NULL; }
    | multiple_newlines_optional NEWLINE
    ;

assignment_block:
    IDENTIFIER ASSIGN interact_block
    { printf("DEBUG PARSER: Assignment Block: %s = INTERACT_BLOCK\n", $1); $$ = create_node_str("ASSIGNMENT_BLOCK", $1); }
    ;

movement_block:
    MOVE DIRECTION factor
    { printf("DEBUG PARSER: Movement Block: move %s by value/iden\n", $2); $$ = create_node_str("MOVEMENT_BLOCK", $2); }
    ;

interact_block:
    INTERACT OPEN DIRECTION
    { printf("DEBUG PARSER: Interact Block: interact open %s\n", $3); $$ = create_node_str("INTERACT_BLOCK_OPEN", $3); }
    | INTERACT COLLECT_KEYWORD DIRECTION
    { printf("DEBUG PARSER: Interact Block: interact collect %s\n", $3); $$ = create_node_str("INTERACT_BLOCK_COLLECT", $3); }
    ;

sequence_block:
    DEFINE SEQUENCE IDENTIFIER COLON NEWLINE statements SEQUENCE END
    { printf("DEBUG PARSER: Sequence Block defined: %s\n", $3); $$ = create_node_str("SEQUENCE_BLOCK_DEF", $3); }
    ;

sequence_call:
    IDENTIFIER
    { printf("DEBUG PARSER: Sequence Call: %s\n", $1); $$ = create_node_str("SEQUENCE_CALL", $1); }
    ;

conditional_block:
    IF_KEYWORD condition COLON NEWLINE statements ELSE COLON NEWLINE statements CONDITIONAL END
    { printf("DEBUG PARSER: Conditional Block parsed.\n"); $$ = create_node_keyword("CONDITIONAL_BLOCK"); }
    ;

condition:
    collectable_condition       { $$ = $1; }
    | object_condition          { $$ = $1; }
    | factor                    { $$ = $1; }
    ;

collectable_condition:
    collectable_or_identifier relational_operator factor
    {
        printf("DEBUG PARSER: Collectable Condition: %s (%s) %s (%s) factor\n",
               $1->type, ($1->value_str ? $1->value_str : "NULL"),
               $2->type, ($2->value_str ? $2->value_str : "NULL"));
        $$ = create_node_keyword("COLLECTABLE_CONDITION");
    }
    ;

collectable_or_identifier:
    COLLECTABLE { $$ = create_node_str("COLLECTABLE_TOKEN", $1); }
    | IDENTIFIER { $$ = create_node_str("IDENTIFIER_TOKEN", $1); }
    ;

object_target:
    INTERACTABLE
    { printf("DEBUG PARSER: Object Target: INTERACTABLE (%s)\n", $1); $$ = create_node_str("INTERACTABLE_NODE", $1); }
    | STATE
    { printf("DEBUG PARSER: Object Target: STATE (%s)\n", $1); $$ = create_node_str("STATE_NODE", $1); }
    ;

object_condition:
    OBJECT DIRECTION relational_bool object_target
    {
        printf("DEBUG PARSER: Object Condition: object %s %s (%s) %s (%s)\n",
               $2,
               $3->type, ($3->value_str ? $3->value_str : "NULL"),
               $4->type, ($4->value_str ? $4->value_str : "NULL"));
        $$ = create_node_keyword("OBJECT_CONDITION");
    }
    ;

loop_block:
    WHILE condition COLON NEWLINE statements LOOP END
    { printf("DEBUG PARSER: Loop Block parsed.\n"); $$ = create_node_keyword("LOOP_BLOCK"); }
    ;

relational_bool:
    IS
    { printf("DEBUG PARSER: Relational Bool: IS\n"); $$ = create_node_keyword("REL_BOOL_IS"); }
    | IS_NOT
    { printf("DEBUG PARSER: Relational Bool: IS_NOT\n"); $$ = create_node_keyword("REL_BOOL_ISNOT"); }
    ;

relational_operator:
    GT { printf("DEBUG PARSER: Relational Operator: GT\n"); $$ = create_node_keyword("REL_OP_GT"); }
    | LT { printf("DEBUG PARSER: Relational Operator: LT\n"); $$ = create_node_keyword("REL_OP_LT"); }
    | GE { printf("DEBUG PARSER: Relational Operator: GE\n"); $$ = create_node_keyword("REL_OP_GE"); }
    | LE { printf("DEBUG PARSER: Relational Operator: LE\n"); $$ = create_node_keyword("REL_OP_LE"); }
    | EQ { printf("DEBUG PARSER: Relational Operator: EQ\n"); $$ = create_node_keyword("REL_OP_EQ"); }
    | NE { printf("DEBUG PARSER: Relational Operator: NE\n"); $$ = create_node_keyword("REL_OP_NE"); }
    ;

collect_command:
    COLLECT_KEYWORD COLLECTABLE DIRECTION
    { printf("DEBUG PARSER: Collect Command: collect %s %s\n", $2, $3); $$ = create_node_str("COLLECT_COMMAND", $2); }
    ;

factor:
    INT_LITERAL
    { printf("DEBUG PARSER: Factor: INT_LITERAL (%d)\n", $1); $$ = create_node_int("INT_LITERAL_NODE", $1); }
    | BOOL_LITERAL
    { printf("DEBUG PARSER: Factor: BOOL_LITERAL (%d)\n", $1); $$ = create_node_int("BOOL_LITERAL_NODE", $1); }
    | IDENTIFIER
    { printf("DEBUG PARSER: Factor: IDENTIFIER (%s)\n", $1); $$ = create_node_str("IDENTIFIER_NODE", $1); }
    | LPAREN condition RPAREN
    { printf("DEBUG PARSER: Factor: Grouped Condition\n"); $$ = $2; }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Erro de sintaxe na linha %d: %s\n", yylineno, s);
}

int main(int argc, char **argv) {
    if (argc > 1) {
        FILE *f = fopen(argv[1], "r");
        if (!f) {
            perror(argv[1]);
            return 1;
        }
        yyin = f;
    } else {
        printf("Uso: %s <nome_do_arquivo_de_codigo>\n", argv[0]);
        return 1;
    }

    yyparse();

    printf("Parsing completed. Check for syntax errors above.\n");

    if (argc > 1) {
        fclose(yyin);
    }
    return 0;
}