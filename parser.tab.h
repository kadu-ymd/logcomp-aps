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
    VALUE = 263,                   /* VALUE  */
    ENTER = 264,                   /* ENTER  */
    END = 265,                     /* END  */
    MOVE = 266,                    /* MOVE  */
    INTERACT = 267,                /* INTERACT  */
    OPEN = 268,                    /* OPEN  */
    COLLECT = 269,                 /* COLLECT  */
    DEFINE = 270,                  /* DEFINE  */
    SEQUENCE = 271,                /* SEQUENCE  */
    IF = 272,                      /* IF  */
    ELSE = 273,                    /* ELSE  */
    CONDITIONAL = 274,             /* CONDITIONAL  */
    WHILE = 275,                   /* WHILE  */
    LOOP = 276,                    /* LOOP  */
    OBJECT = 277,                  /* OBJECT  */
    IS = 278,                      /* IS  */
    ISNOT = 279,                   /* ISNOT  */
    GE = 280,                      /* GE  */
    LE = 281,                      /* LE  */
    EQ = 282,                      /* EQ  */
    NE = 283,                      /* NE  */
    GT = 284,                      /* GT  */
    LT = 285,                      /* LT  */
    ASSIGN = 286,                  /* ASSIGN  */
    COLON = 287,                   /* COLON  */
    NEWLINE = 288                  /* NEWLINE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 11 "parser.y"

    int num;
    char* str;

#line 102 "parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
