# APS - Lógica da Computação

## Projeto da disciplina de Lógica da Computação de Engenharia da Computação, Insper - 25.1


A seguinte linguagem consiste em facilitar o processo de criar eventos em uma agenda, além de gerá-la através de programação. Com isso, uma pessoa que não possui experiência em programação deveria conseguir montar sua rotina ao longo de um determinado período de tempo e gerar uma representação visual das tarefas e eventos que criou ao longo do código.

Para isso, um possível modelo inicial para a EBNF da linguagem pode ser dado por:

**Letras e digitos**

```
decimal_digit   = "0" ... "9"
```

**Palavras reservadas (keywords)**: palavras que nao podem ser usadas como identificadores

```
timeout hour    min     month   date
insert  if      else    while
```

**Tipos**

```
task    event   time    timeout
```

**Constantes**

```
"jan" "feb" "mar" "apr" "may" "jun" "jul" "aug" "sep" "oct" "nov" "dec"
```

**Funções**

```
insert      remove      generate
```

`insert(Identificador)`: inserir eventos/tarefas na agenda antes de gerá-la
`remove(Identificador)`: remover eventos/tarefas na agenda antes de gerá-la
`generate()`: gera a agenda final

**Bloco**: um bloco de código pode ser definido pela seguinte sintaxe

```
Bloco               = "{" SequenciaDeCodigo "}"
SequenciaDeCodigo   = { Codigo }
```

**Declaração de variáveis**

```
Declaracao  = Tipo Identificador DecTempo "=" Inteiro
DecTempo    = hour | min | month
```