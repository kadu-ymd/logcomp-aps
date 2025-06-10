%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definir a estrutura de um nó da AST (simplificado para demonstração)
// Em um compilador real, cada tipo de bloco ou expressão teria sua própria struct
// com os campos específicos (e.g., um campo 'direction' para MovementBlock,
// um campo 'operator' para BinaryOp, uma lista de 'statements' para um Block).
// Por simplicidade aqui, vamos apenas mostrar que os valores estão sendo passados.
typedef struct AstNode {
    char* type; // Tipo do nó (ex: "MOVEMENT_BLOCK", "IDENTIFIER", "COLLECTABLE_CONDITION")
    char* value_str; // Valor string (para IDENTIFIER, DIRECTION, etc.)
    int value_int;   // Valor inteiro (para VALUE_LITERAL, BOOLEAN_LITERAL)
    // Para nós complexos como blocos, você teria uma lista de ponteiros para AstNode
    // struct AstNode** children;
    // int num_children;
} AstNode;

// Função de criação de nós (simplificada)
AstNode* create_node_str(char* type, char* value) {
    AstNode* node = (AstNode*) malloc(sizeof(AstNode));
    node->type = strdup(type);
    node->value_str = strdup(value);
    node->value_int = 0; // Default
    return node;
}

AstNode* create_node_int(char* type, int value) {
    AstNode* node = (AstNode*) malloc(sizeof(AstNode));
    node->type = strdup(type);
    node->value_str = NULL;
    node->value_int = value;
    return node;
}

AstNode* create_node_keyword(char* type) {
    AstNode* node = (AstNode*) malloc(sizeof(AstNode));
    node->type = strdup(type);
    node->value_str = NULL;
    node->value_int = 0; // Default
    return node;
}


void yyerror(const char *s);
int yylex(void);
extern FILE *yyin;

%}

// Definição da união para os valores semânticos passados entre lexer e parser
%union {
    int num;        // Para VALUE_LITERAL
    char* str;      // Para IDENTIFIER, DIRECTION, COLLECTABLE, etc.
    int num_bool;   // Para TRUE_LITERAL, FALSE_LITERAL (0 ou 1)
    AstNode* node;  // Para passar nós da AST entre as regras
}

// Tokens com seus tipos semânticos
%token <str> IDENTIFIER DIRECTION COLLECTABLE INTERACTABLE STATE
%token <num> VALUE_LITERAL          // Renomeado
%token <num_bool> TRUE_LITERAL FALSE_LITERAL // Novos tokens booleanos

// Tokens de palavras-chave sem valor semântico
%token ENTER END MOVE INTERACT OPEN COLLECT_KEYWORD DEFINE SEQUENCE IF_KEYWORD ELSE CONDITIONAL WHILE LOOP OBJECT IS IS_NOT
%token GE LE EQ NE GT LT
%token ASSIGN COLON NEWLINE
%token LBRACE RBRACE LPAREN RPAREN // Novos tokens para '{', '}', '(', ')'

// O tipo do valor semântico para os não-terminais que construirão a AST
%type <node> program statements statement assignment_block movement_block interact_block sequence_block conditional_block if_condition collectable_condition object_condition_end object_condition loop_block loop_condition relational_bool relational_operator collect_command sequence_call term_primitive

// O símbolo de início da gramática
%start program

%%

// --- Regras Gramaticais da EBNF ---

program:
    ENTER NEWLINE statements program_end_tags optional_final_newline YYEOF
    { printf("DEBUG PARSER: Programa parseado com sucesso.\n"); YYACCEPT; }
    ;

program_end_tags: // Agrupando 'program end'
    SEQUENCE END { /* Nenhuma ação especial aqui além de reconhecer */ }
    | PROGRAM END { /* Aceitar 'program end' ou 'sequence end' para o final do programa, dependendo da sua EBNF */ }
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
    movement_block NEWLINE            { $$ = $1; }
    | interact_block NEWLINE          { $$ = $1; }
    | assignment_block NEWLINE        { $$ = $1; }
    | sequence_block NEWLINE          { $$ = $1; }
    | conditional_block NEWLINE       { $$ = $1; }
    | loop_block NEWLINE              { $$ = $1; }
    | collect_command NEWLINE         { $$ = $1; }
    | sequence_call NEWLINE           { $$ = $1; } // Novo: Chamada de sequência como statement
    | NEWLINE                         { /* EMPTY_STATEMENT para linhas vazias */ } // Corresponde ao λ na EBNF, se uma linha vazia é um statement válido
    ;

assignment_block:
    IDENTIFIER ASSIGN interact_block
    { printf("DEBUG PARSER: Assignment Block: %s = INTERACT_BLOCK\n", $1); $$ = create_node_str("ASSIGNMENT_BLOCK", $1); /* $3 é o nó do interact_block */ }
    ;

movement_block:
    MOVE DIRECTION term_primitive
    { printf("DEBUG PARSER: Movement Block: move %s by value/iden\n", $2); $$ = create_node_str("MOVEMENT_BLOCK", $2); /* $3 é o nó do valor/iden */ }
    ;

interact_block:
    INTERACT OPEN DIRECTION
    { printf("DEBUG PARSER: Interact Block: interact open %s\n", $3); $$ = create_node_str("INTERACT_BLOCK_OPEN", $3); }
    | INTERACT COLLECT_KEYWORD DIRECTION
    { printf("DEBUG PARSER: Interact Block: interact collect %s\n", $3); $$ = create_node_str("INTERACT_BLOCK_COLLECT", $3); }
    ;

sequence_block:
    DEFINE SEQUENCE IDENTIFIER COLON NEWLINE inner_statements SEQUENCE END
    { printf("DEBUG PARSER: Sequence Block defined: %s\n", $3); $$ = create_node_str("SEQUENCE_BLOCK_DEF", $3); /* $6 é a lista de statements */ }
    ;

// Regra auxiliar para o corpo de blocos que não são statements, para não duplicar o NEWLINE.
inner_statements:
    /* vazio */
    | inner_statements statement_no_newline
    ;

statement_no_newline: // Versão de statement sem o NEWLINE final
    movement_block
    | interact_block
    | assignment_block
    | sequence_block
    | conditional_block
    | loop_block
    | collect_command
    | sequence_call
    | NEWLINE { /* Linhas vazias dentro de blocos */ }
    ;


sequence_call: // Nova regra para chamar uma sequência
    IDENTIFIER
    { printf("DEBUG PARSER: Sequence Call: %s\n", $1); $$ = create_node_str("SEQUENCE_CALL", $1); }
    ;


conditional_block:
    IF_KEYWORD if_condition COLON NEWLINE true_statements ELSE COLON NEWLINE false_statements CONDITIONAL END
    { printf("DEBUG PARSER: Conditional Block parsed.\n"); $$ = create_node_keyword("CONDITIONAL_BLOCK"); /* Incluir $2, $5, $9 como filhos em um ASTNode mais complexo */ }
    ;

true_statements: // Statements dentro do bloco TRUE do condicional
    /* vazio */
    | true_statements statement_no_newline
    ;

false_statements: // Statements dentro do bloco FALSE do condicional
    /* vazio */
    | false_statements statement_no_newline
    ;


if_condition:
    collectable_condition     { $$ = $1; }
    | object_condition        { $$ = $1; }
    | BOOLEAN_LITERAL         { printf("DEBUG PARSER: If Condition: BOOLEAN_LITERAL (%d)\n", $1); $$ = create_node_int("BOOLEAN_LITERAL_NODE", $1); }
    | IDENTIFIER              { printf("DEBUG PARSER: If Condition: IDENTIFIER (%s)\n", $1); $$ = create_node_str("IDENTIFIER_NODE", $1); }
    | LPAREN if_condition RPAREN { printf("DEBUG PARSER: If Condition: Grouped\n"); $$ = $2; }
    ;

collectable_condition:
    IDENTIFIER relational_operator term_primitive
    { printf("DEBUG PARSER: Collectable Condition: %s %s value/iden\n", $1, ($2->value_str)); $$ = create_node_str("COLLECTABLE_CONDITION", $1); /* $2, $3 são nós */ }
    ;

object_condition_end:
    INTERACTABLE
    { printf("DEBUG PARSER: Object Condition End: INTERACTABLE (%s)\n", $1); $$ = create_node_str("INTERACTABLE_NODE", $1); }
    | STATE
    { printf("DEBUG PARSER: Object Condition End: STATE (%s)\n", $1); $$ = create_node_str("STATE_NODE", $1); }
    ;

object_condition:
    OBJECT DIRECTION relational_bool object_condition_end
    { printf("DEBUG PARSER: Object Condition: object %s %s %s\n", $2, ($3->value_str), ($4->value_str)); $$ = create_node_keyword("OBJECT_CONDITION"); /* $2, $3, $4 são nós */ }
    ;

loop_block:
    WHILE loop_condition COLON NEWLINE loop_statements LOOP END
    { printf("DEBUG PARSER: Loop Block parsed.\n"); $$ = create_node_keyword("LOOP_BLOCK"); /* Incluir $2, $5 como filhos */ }
    ;

loop_statements: // Statements dentro do bloco do loop
    /* vazio */
    | loop_statements statement_no_newline
    ;

loop_condition:
    collectable_condition     { $$ = $1; }
    | object_condition        { $$ = $1; }
    | BOOLEAN_LITERAL         { printf("DEBUG PARSER: Loop Condition: BOOLEAN_LITERAL (%d)\n", $1); $$ = create_node_int("BOOLEAN_LITERAL_NODE", $1); }
    | IDENTIFIER              { printf("DEBUG PARSER: Loop Condition: IDENTIFIER (%s)\n", $1); $$ = create_node_str("IDENTIFIER_NODE", $1); }
    | LPAREN loop_condition RPAREN { printf("DEBUG PARSER: Loop Condition: Grouped\n"); $$ = $2; }
    ;

relational_bool:
    IS
    { printf("DEBUG PARSER: Relational Bool: IS\n"); $$ = create_node_keyword("REL_BOOL_IS"); }
    | IS_NOT // Corrigido
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
    { printf("DEBUG PARSER: Collect Command: collect %s %s\n", $2, $3); $$ = create_node_str("COLLECT_COMMAND", $2); /* $3 é o nó da direção */ }
    ;

// Nova regra para `VALUE` que pode ser um literal ou um IDENTIFIER
term_primitive:
    VALUE_LITERAL
    { printf("DEBUG PARSER: Term Primitive: VALUE_LITERAL (%d)\n", $1); $$ = create_node_int("VALUE_LITERAL_NODE", $1); }
    | IDENTIFIER
    { printf("DEBUG PARSER: Term Primitive: IDENTIFIER (%s)\n", $1); $$ = create_node_str("IDENTIFIER_NODE", $1); }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Erro de sintaxe na linha %d: %s, token '%s'\n", yylineno, s, yytext); // yylineno e yytext são do Flex
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

    if (argc > 1) {
        fclose(yyin);
    }
    return 0;
}