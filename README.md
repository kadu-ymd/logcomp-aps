# APS - Lógica da Computação

**Desenvolvedor**: Carlos Eduardo Porciuncula Yamada

## Descrição

O seguinte projeto foi desenvolvido para a disciplina de Lógica da Computação do curso de Engenharia da Computação no Insper - 25.1.

A linguagem desenvolvida nesse projeto é uma representação em código das instruções que o usuário precisa fornecer para escapar de uma sala no estilo *Escape Room*. Para testes, uma sala predefinida será utilizada e os *outputs* se darão com base no algoritmo a ser computado.

## EBNF

```ebnf
PROGRAM = "enter", "\n", { STATEMENT }, "program", "end", "EOF";

STATEMENT = ( MOVEMENT_BLOCK | INTERACT_BLOCK | SEQUENCE_BLOCK | CONDITIONAL_BLOCK | LOOP_BLOCK | ASSIGNMENT_BLOCK | COLLECT_COMMAND | SEQUENCE_CALL ), "\n" | "EOF" | "program" | "end" ;

ASSIGNMENT_BLOCK = IDENTIFIER, "=", INTERACT_BLOCK;

MOVEMENT_BLOCK = "move", DIRECTION, FACTOR;

INTERACT_BLOCK = "interact", ( "open" | "collect" ), DIRECTION;

SEQUENCE_BLOCK = "define", "sequence", IDENTIFIER, ":", "\n", { STATEMENT }, "sequence", "end";

SEQUENCE_CALL = IDENTIFIER;

CONDITIONAL_BLOCK = "if", CONDITION, ":", "\n", { STATEMENT }, "else", ":", "\n", { STATEMENT }, "conditional", "end";

CONDITION = ( COLLECTABLE_CONDITION | OBJECT_CONDITION | FACTOR | "(", CONDITION, ")" );

COLLECTABLE_CONDITION = ( COLLECTABLE | IDENTIFIER ), RELATIONAL_OPERATOR, FACTOR;

OBJECT_CONDITION = "object", DIRECTION, RELATIONAL_BOOL, OBJECT_TARGET;

OBJECT_TARGET = ( INTERACTABLE | STATE );

LOOP_BLOCK = "while", CONDITION, ":", "\n", { STATEMENT }, "loop", "end";

COLLECT_COMMAND = "collect", COLLECTABLE, DIRECTION;

RELATIONAL_BOOL = ( "is" | "is_not" );

RELATIONAL_OPERATOR = ( ">" | "<" | ">=" | "<=" | "==" | "!=" );

IDENTIFIER = LETTER, { LETTER | DIGIT | "_" };

FACTOR = ( INT_LITERAL | BOOLEAN_LITERAL | IDENTIFIER | "(", CONDITION, ")" );

INT_LITERAL = DIGIT, { DIGIT };

DIRECTION = ( "up" | "right" | "down" | "left" );

COLLECTABLE = ( "key" | "coins" | "card" );

INTERACTABLE = ( "locker" | "closet" | "desk" | "exit_door" );

STATE = ( "locked" | "unlocked" );

BOOLEAN_LITERAL = ( "true" | "false" );

LETTER = ( "a" | ... | "z" | "A" | ... | "Z" );

DIGIT = ( "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9" );
```

## Exemplos

### Exemplo 1 - Sucesso ao escapar da sala

```txt
enter
move up 1
interact open up
collect key up
move right 0
interact open right
program end
```

### Saída do exemplo 1

```txt
[COMPILER] Saída redirecionada para 'teste.txt'

--- Compiling 'programas_teste/escape_success.txt' ---
--- Compilation successful! AST generated. ---

--- Initializing Escape Room VM ---

--- Executing compiled program on VM ---

--- Program execution finished. ---

--- Game Status ---
[GAME] Great job! You have successfully ESCAPED the room!
```

### Exemplo 2 - Falha ao escapar da sala

```txt
enter
move up 1
interact open up
collect key up
move right 0
interact open right
program end
```

### Saída do exemplo 2

```txt
[COMPILER] Saída redirecionada para 'teste.txt'

--- Compiling 'programas_teste/escape_fail.txt' ---
--- Compilation successful! AST generated. ---

--- Initializing Escape Room VM ---

--- Executing compiled program on VM ---

--- Program execution finished. ---

--- Game Status ---
[GAME] You have NOT yet escaped the room.
[GAME] Current player position: (0, 1)
[GAME] Current inventory: {}
[GAME] Keep trying to find the exit!
```

---

## Teste

Os comandos utilizados para compilar e testar a EBNF, utilizando os arquivos na pasta `programas_teste` foram, em sequência:

```
$ flex lexer.l

$ bison -d parser.y

$ gcc lex.yy.c parser.tab.c -o meu_analisador -lfl
```

## Execução

Para executar um determinado programa, é necessário executar a seguinte linha de comando:

```
$ python main.py <arquivo.txt> [arquivo_de_saida.txt]
```