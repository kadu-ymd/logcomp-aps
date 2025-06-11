/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    IDENTIFIER = 258,              /* IDENTIFIER  */
    DIRECTION = 259,               /* DIRECTION  */
    COLLECTABLE = 260,             /* COLLECTABLE  */
    INTERACTABLE = 261,            /* INTERACTABLE  */
    STATE = 262,                   /* STATE  */
    INT_LITERAL = 263,             /* INT_LITERAL  */
    BOOL_LITERAL = 264,            /* BOOL_LITERAL  */
    ENTER = 265,                   /* ENTER  */
    PROGRAM_KEYWORD = 266,         /* PROGRAM_KEYWORD  */
    END = 267,                     /* END  */
    MOVE = 268,                    /* MOVE  */
    INTERACT = 269,                /* INTERACT  */
    OPEN = 270,                    /* OPEN  */
    COLLECT_KEYWORD = 271,         /* COLLECT_KEYWORD  */
    DEFINE = 272,                  /* DEFINE  */
    SEQUENCE = 273,                /* SEQUENCE  */
    IF_KEYWORD = 274,              /* IF_KEYWORD  */
    ELSE = 275,                    /* ELSE  */
    CONDITIONAL = 276,             /* CONDITIONAL  */
    WHILE = 277,                   /* WHILE  */
    LOOP = 278,                    /* LOOP  */
    OBJECT = 279,                  /* OBJECT  */
    IS = 280,                      /* IS  */
    IS_NOT = 281,                  /* IS_NOT  */
    GE = 282,                      /* GE  */
    LE = 283,                      /* LE  */
    EQ = 284,                      /* EQ  */
    NE = 285,                      /* NE  */
    GT = 286,                      /* GT  */
    LT = 287,                      /* LT  */
    ASSIGN = 288,                  /* ASSIGN  */
    COLON = 289,                   /* COLON  */
    NEWLINE = 290,                 /* NEWLINE  */
    LBRACE = 291,                  /* LBRACE  */
    RBRACE = 292,                  /* RBRACE  */
    LPAREN = 293,                  /* LPAREN  */
    RPAREN = 294                   /* RPAREN  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 47 "parser.y"

    int num;
    char* str;
    int num_bool;
    AstNode* node;

#line 110 "parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
