/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

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


#line 117 "parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_IDENTIFIER = 3,                 /* IDENTIFIER  */
  YYSYMBOL_DIRECTION = 4,                  /* DIRECTION  */
  YYSYMBOL_COLLECTABLE = 5,                /* COLLECTABLE  */
  YYSYMBOL_INTERACTABLE = 6,               /* INTERACTABLE  */
  YYSYMBOL_STATE = 7,                      /* STATE  */
  YYSYMBOL_INT_LITERAL = 8,                /* INT_LITERAL  */
  YYSYMBOL_BOOL_LITERAL = 9,               /* BOOL_LITERAL  */
  YYSYMBOL_ENTER = 10,                     /* ENTER  */
  YYSYMBOL_PROGRAM_KEYWORD = 11,           /* PROGRAM_KEYWORD  */
  YYSYMBOL_END = 12,                       /* END  */
  YYSYMBOL_MOVE = 13,                      /* MOVE  */
  YYSYMBOL_INTERACT = 14,                  /* INTERACT  */
  YYSYMBOL_OPEN = 15,                      /* OPEN  */
  YYSYMBOL_COLLECT_KEYWORD = 16,           /* COLLECT_KEYWORD  */
  YYSYMBOL_DEFINE = 17,                    /* DEFINE  */
  YYSYMBOL_SEQUENCE = 18,                  /* SEQUENCE  */
  YYSYMBOL_IF_KEYWORD = 19,                /* IF_KEYWORD  */
  YYSYMBOL_ELSE = 20,                      /* ELSE  */
  YYSYMBOL_CONDITIONAL = 21,               /* CONDITIONAL  */
  YYSYMBOL_WHILE = 22,                     /* WHILE  */
  YYSYMBOL_LOOP = 23,                      /* LOOP  */
  YYSYMBOL_OBJECT = 24,                    /* OBJECT  */
  YYSYMBOL_IS = 25,                        /* IS  */
  YYSYMBOL_IS_NOT = 26,                    /* IS_NOT  */
  YYSYMBOL_GE = 27,                        /* GE  */
  YYSYMBOL_LE = 28,                        /* LE  */
  YYSYMBOL_EQ = 29,                        /* EQ  */
  YYSYMBOL_NE = 30,                        /* NE  */
  YYSYMBOL_GT = 31,                        /* GT  */
  YYSYMBOL_LT = 32,                        /* LT  */
  YYSYMBOL_ASSIGN = 33,                    /* ASSIGN  */
  YYSYMBOL_COLON = 34,                     /* COLON  */
  YYSYMBOL_NEWLINE = 35,                   /* NEWLINE  */
  YYSYMBOL_LBRACE = 36,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 37,                    /* RBRACE  */
  YYSYMBOL_LPAREN = 38,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 39,                    /* RPAREN  */
  YYSYMBOL_YYACCEPT = 40,                  /* $accept  */
  YYSYMBOL_program = 41,                   /* program  */
  YYSYMBOL_statements = 42,                /* statements  */
  YYSYMBOL_statement = 43,                 /* statement  */
  YYSYMBOL_multiple_newlines_optional = 44, /* multiple_newlines_optional  */
  YYSYMBOL_assignment_block = 45,          /* assignment_block  */
  YYSYMBOL_movement_block = 46,            /* movement_block  */
  YYSYMBOL_interact_block = 47,            /* interact_block  */
  YYSYMBOL_sequence_block = 48,            /* sequence_block  */
  YYSYMBOL_sequence_call = 49,             /* sequence_call  */
  YYSYMBOL_conditional_block = 50,         /* conditional_block  */
  YYSYMBOL_condition = 51,                 /* condition  */
  YYSYMBOL_collectable_condition = 52,     /* collectable_condition  */
  YYSYMBOL_collectable_or_identifier = 53, /* collectable_or_identifier  */
  YYSYMBOL_object_target = 54,             /* object_target  */
  YYSYMBOL_object_condition = 55,          /* object_condition  */
  YYSYMBOL_loop_block = 56,                /* loop_block  */
  YYSYMBOL_relational_bool = 57,           /* relational_bool  */
  YYSYMBOL_relational_operator = 58,       /* relational_operator  */
  YYSYMBOL_collect_command = 59,           /* collect_command  */
  YYSYMBOL_factor = 60                     /* factor  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   108

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  40
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  21
/* YYNRULES -- Number of rules.  */
#define YYNRULES  44
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  96

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   294


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    71,    71,    76,    77,    81,    82,    83,    84,    85,
      86,    87,    88,    92,    93,    97,   102,   107,   109,   114,
     119,   124,   129,   130,   131,   135,   145,   146,   150,   152,
     157,   168,   173,   175,   180,   181,   182,   183,   184,   185,
     189,   194,   196,   198,   200
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "IDENTIFIER",
  "DIRECTION", "COLLECTABLE", "INTERACTABLE", "STATE", "INT_LITERAL",
  "BOOL_LITERAL", "ENTER", "PROGRAM_KEYWORD", "END", "MOVE", "INTERACT",
  "OPEN", "COLLECT_KEYWORD", "DEFINE", "SEQUENCE", "IF_KEYWORD", "ELSE",
  "CONDITIONAL", "WHILE", "LOOP", "OBJECT", "IS", "IS_NOT", "GE", "LE",
  "EQ", "NE", "GT", "LT", "ASSIGN", "COLON", "NEWLINE", "LBRACE", "RBRACE",
  "LPAREN", "RPAREN", "$accept", "program", "statements", "statement",
  "multiple_newlines_optional", "assignment_block", "movement_block",
  "interact_block", "sequence_block", "sequence_call", "conditional_block",
  "condition", "collectable_condition", "collectable_or_identifier",
  "object_target", "object_condition", "loop_block", "relational_bool",
  "relational_operator", "collect_command", "factor", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-61)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-44)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
       4,   -18,    33,   -61,   -61,    27,    14,    36,    46,    -4,
      47,    35,    -2,    -2,   -61,    16,    19,    25,    28,    30,
      31,    39,    40,    63,   -61,     1,    74,    77,    80,    83,
     -26,   -61,   -61,   -61,    91,    -2,    64,   -61,    62,   -61,
     -61,    65,   -61,   -61,   -61,   -61,   -61,   -61,   -61,   -61,
     -61,     2,   -61,   -61,   -61,   -61,   -61,    67,    -5,    57,
      68,   -61,   -61,   -61,   -61,   -61,   -61,     1,    69,   -61,
     -61,    70,   -61,   -61,    17,   -61,   -61,   -61,   -61,   -61,
     -61,   -61,   -61,    42,    12,    54,    72,    85,    88,    73,
     -61,   -61,   -61,    66,    90,   -61
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     3,     1,     0,    20,     0,     0,     0,
       0,     0,     0,     0,     4,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    13,     0,     0,     0,     0,     0,
      27,    26,    41,    42,     0,     0,     0,    22,     0,    23,
      24,     0,     7,     5,     6,     8,    12,     9,    10,    11,
      15,     0,    43,    16,    17,    18,    40,     0,     0,     0,
       0,    36,    37,    38,    39,    34,    35,     0,     0,     2,
      14,     0,    32,    33,     0,    44,     3,    25,     3,     3,
      28,    29,    30,     0,     0,     0,     0,     0,     0,     0,
      31,    19,     3,     0,     0,    21
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -61,   -61,   -60,   -61,   -61,   -61,   -61,    84,   -61,   -61,
     -61,    -8,   -61,   -61,   -61,   -61,   -61,   -61,   -61,   -61,
     -25
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     2,     5,    14,    51,    15,    16,    17,    18,    19,
      20,    36,    37,    38,    82,    39,    21,    74,    67,    22,
      40
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      53,    30,    69,    31,    52,    41,    32,    33,   -43,    32,
      33,    26,    27,   -43,     1,     6,    83,     3,    84,    85,
      72,    73,    34,    80,    81,     8,     9,    59,    10,    11,
       6,    12,    93,     4,    13,    87,    35,    70,     7,    35,
       8,     9,    77,    10,    11,     6,    12,    23,    24,    13,
      25,    42,    28,    29,    43,     8,     9,     6,    10,    11,
      44,    12,    86,    45,    13,    46,    47,     8,     9,     6,
      10,    11,    88,    12,    48,    49,    13,     9,    54,     8,
       9,    55,    10,    11,    56,    12,    57,    94,    13,    61,
      62,    63,    64,    65,    66,    58,    75,    90,    60,    68,
      91,    71,    95,    76,    78,    79,    89,    50,    92
};

static const yytype_int8 yycheck[] =
{
      25,     3,     0,     5,     3,    13,     8,     9,    34,     8,
       9,    15,    16,    39,    10,     3,    76,    35,    78,    79,
      25,    26,    24,     6,     7,    13,    14,    35,    16,    17,
       3,    19,    92,     0,    22,    23,    38,    35,    11,    38,
      13,    14,    67,    16,    17,     3,    19,    33,    12,    22,
       4,    35,     5,    18,    35,    13,    14,     3,    16,    17,
      35,    19,    20,    35,    22,    35,    35,    13,    14,     3,
      16,    17,    18,    19,    35,    35,    22,    14,     4,    13,
      14,     4,    16,    17,     4,    19,     3,    21,    22,    27,
      28,    29,    30,    31,    32,     4,    39,    12,    34,    34,
      12,    34,    12,    35,    35,    35,    34,    23,    35
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    10,    41,    35,     0,    42,     3,    11,    13,    14,
      16,    17,    19,    22,    43,    45,    46,    47,    48,    49,
      50,    56,    59,    33,    12,     4,    15,    16,     5,    18,
       3,     5,     8,     9,    24,    38,    51,    52,    53,    55,
      60,    51,    35,    35,    35,    35,    35,    35,    35,    35,
      47,    44,     3,    60,     4,     4,     4,     3,     4,    51,
      34,    27,    28,    29,    30,    31,    32,    58,    34,     0,
      35,    34,    25,    26,    57,    39,    35,    60,    35,    35,
       6,     7,    54,    42,    42,    42,    20,    23,    18,    34,
      12,    12,    35,    42,    21,    12
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    40,    41,    42,    42,    43,    43,    43,    43,    43,
      43,    43,    43,    44,    44,    45,    46,    47,    47,    48,
      49,    50,    51,    51,    51,    52,    53,    53,    54,    54,
      55,    56,    57,    57,    58,    58,    58,    58,    58,    58,
      59,    60,    60,    60,    60
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     7,     0,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     0,     2,     3,     3,     3,     3,     8,
       1,    11,     1,     1,     1,     3,     1,     1,     1,     1,
       4,     7,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     1,     1,     1,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: ENTER NEWLINE statements PROGRAM_KEYWORD END multiple_newlines_optional $end  */
#line 72 "parser.y"
    { printf("DEBUG PARSER: Programa parseado com sucesso.\n"); YYACCEPT; }
#line 1227 "parser.tab.c"
    break;

  case 3: /* statements: %empty  */
#line 76 "parser.y"
                { (yyval.node) = NULL; }
#line 1233 "parser.tab.c"
    break;

  case 5: /* statement: movement_block NEWLINE  */
#line 81 "parser.y"
                                    { (yyval.node) = (yyvsp[-1].node); }
#line 1239 "parser.tab.c"
    break;

  case 6: /* statement: interact_block NEWLINE  */
#line 82 "parser.y"
                                    { (yyval.node) = (yyvsp[-1].node); }
#line 1245 "parser.tab.c"
    break;

  case 7: /* statement: assignment_block NEWLINE  */
#line 83 "parser.y"
                                    { (yyval.node) = (yyvsp[-1].node); }
#line 1251 "parser.tab.c"
    break;

  case 8: /* statement: sequence_block NEWLINE  */
#line 84 "parser.y"
                                    { (yyval.node) = (yyvsp[-1].node); }
#line 1257 "parser.tab.c"
    break;

  case 9: /* statement: conditional_block NEWLINE  */
#line 85 "parser.y"
                                    { (yyval.node) = (yyvsp[-1].node); }
#line 1263 "parser.tab.c"
    break;

  case 10: /* statement: loop_block NEWLINE  */
#line 86 "parser.y"
                                    { (yyval.node) = (yyvsp[-1].node); }
#line 1269 "parser.tab.c"
    break;

  case 11: /* statement: collect_command NEWLINE  */
#line 87 "parser.y"
                                    { (yyval.node) = (yyvsp[-1].node); }
#line 1275 "parser.tab.c"
    break;

  case 12: /* statement: sequence_call NEWLINE  */
#line 88 "parser.y"
                                    { (yyval.node) = (yyvsp[-1].node); }
#line 1281 "parser.tab.c"
    break;

  case 13: /* multiple_newlines_optional: %empty  */
#line 92 "parser.y"
                { (yyval.node) = NULL; }
#line 1287 "parser.tab.c"
    break;

  case 15: /* assignment_block: IDENTIFIER ASSIGN interact_block  */
#line 98 "parser.y"
    { printf("DEBUG PARSER: Assignment Block: %s = INTERACT_BLOCK\n", (yyvsp[-2].str)); (yyval.node) = create_node_str("ASSIGNMENT_BLOCK", (yyvsp[-2].str)); }
#line 1293 "parser.tab.c"
    break;

  case 16: /* movement_block: MOVE DIRECTION factor  */
#line 103 "parser.y"
    { printf("DEBUG PARSER: Movement Block: move %s by value/iden\n", (yyvsp[-1].str)); (yyval.node) = create_node_str("MOVEMENT_BLOCK", (yyvsp[-1].str)); }
#line 1299 "parser.tab.c"
    break;

  case 17: /* interact_block: INTERACT OPEN DIRECTION  */
#line 108 "parser.y"
    { printf("DEBUG PARSER: Interact Block: interact open %s\n", (yyvsp[0].str)); (yyval.node) = create_node_str("INTERACT_BLOCK_OPEN", (yyvsp[0].str)); }
#line 1305 "parser.tab.c"
    break;

  case 18: /* interact_block: INTERACT COLLECT_KEYWORD DIRECTION  */
#line 110 "parser.y"
    { printf("DEBUG PARSER: Interact Block: interact collect %s\n", (yyvsp[0].str)); (yyval.node) = create_node_str("INTERACT_BLOCK_COLLECT", (yyvsp[0].str)); }
#line 1311 "parser.tab.c"
    break;

  case 19: /* sequence_block: DEFINE SEQUENCE IDENTIFIER COLON NEWLINE statements SEQUENCE END  */
#line 115 "parser.y"
    { printf("DEBUG PARSER: Sequence Block defined: %s\n", (yyvsp[-5].str)); (yyval.node) = create_node_str("SEQUENCE_BLOCK_DEF", (yyvsp[-5].str)); }
#line 1317 "parser.tab.c"
    break;

  case 20: /* sequence_call: IDENTIFIER  */
#line 120 "parser.y"
    { printf("DEBUG PARSER: Sequence Call: %s\n", (yyvsp[0].str)); (yyval.node) = create_node_str("SEQUENCE_CALL", (yyvsp[0].str)); }
#line 1323 "parser.tab.c"
    break;

  case 21: /* conditional_block: IF_KEYWORD condition COLON NEWLINE statements ELSE COLON NEWLINE statements CONDITIONAL END  */
#line 125 "parser.y"
    { printf("DEBUG PARSER: Conditional Block parsed.\n"); (yyval.node) = create_node_keyword("CONDITIONAL_BLOCK"); }
#line 1329 "parser.tab.c"
    break;

  case 22: /* condition: collectable_condition  */
#line 129 "parser.y"
                                { (yyval.node) = (yyvsp[0].node); }
#line 1335 "parser.tab.c"
    break;

  case 23: /* condition: object_condition  */
#line 130 "parser.y"
                                { (yyval.node) = (yyvsp[0].node); }
#line 1341 "parser.tab.c"
    break;

  case 24: /* condition: factor  */
#line 131 "parser.y"
                                { (yyval.node) = (yyvsp[0].node); }
#line 1347 "parser.tab.c"
    break;

  case 25: /* collectable_condition: collectable_or_identifier relational_operator factor  */
#line 136 "parser.y"
    {
        printf("DEBUG PARSER: Collectable Condition: %s (%s) %s (%s) factor\n",
               (yyvsp[-2].node)->type, ((yyvsp[-2].node)->value_str ? (yyvsp[-2].node)->value_str : "NULL"),
               (yyvsp[-1].node)->type, ((yyvsp[-1].node)->value_str ? (yyvsp[-1].node)->value_str : "NULL"));
        (yyval.node) = create_node_keyword("COLLECTABLE_CONDITION");
    }
#line 1358 "parser.tab.c"
    break;

  case 26: /* collectable_or_identifier: COLLECTABLE  */
#line 145 "parser.y"
                { (yyval.node) = create_node_str("COLLECTABLE_TOKEN", (yyvsp[0].str)); }
#line 1364 "parser.tab.c"
    break;

  case 27: /* collectable_or_identifier: IDENTIFIER  */
#line 146 "parser.y"
                 { (yyval.node) = create_node_str("IDENTIFIER_TOKEN", (yyvsp[0].str)); }
#line 1370 "parser.tab.c"
    break;

  case 28: /* object_target: INTERACTABLE  */
#line 151 "parser.y"
    { printf("DEBUG PARSER: Object Target: INTERACTABLE (%s)\n", (yyvsp[0].str)); (yyval.node) = create_node_str("INTERACTABLE_NODE", (yyvsp[0].str)); }
#line 1376 "parser.tab.c"
    break;

  case 29: /* object_target: STATE  */
#line 153 "parser.y"
    { printf("DEBUG PARSER: Object Target: STATE (%s)\n", (yyvsp[0].str)); (yyval.node) = create_node_str("STATE_NODE", (yyvsp[0].str)); }
#line 1382 "parser.tab.c"
    break;

  case 30: /* object_condition: OBJECT DIRECTION relational_bool object_target  */
#line 158 "parser.y"
    {
        printf("DEBUG PARSER: Object Condition: object %s %s (%s) %s (%s)\n",
               (yyvsp[-2].str),
               (yyvsp[-1].node)->type, ((yyvsp[-1].node)->value_str ? (yyvsp[-1].node)->value_str : "NULL"),
               (yyvsp[0].node)->type, ((yyvsp[0].node)->value_str ? (yyvsp[0].node)->value_str : "NULL"));
        (yyval.node) = create_node_keyword("OBJECT_CONDITION");
    }
#line 1394 "parser.tab.c"
    break;

  case 31: /* loop_block: WHILE condition COLON NEWLINE statements LOOP END  */
#line 169 "parser.y"
    { printf("DEBUG PARSER: Loop Block parsed.\n"); (yyval.node) = create_node_keyword("LOOP_BLOCK"); }
#line 1400 "parser.tab.c"
    break;

  case 32: /* relational_bool: IS  */
#line 174 "parser.y"
    { printf("DEBUG PARSER: Relational Bool: IS\n"); (yyval.node) = create_node_keyword("REL_BOOL_IS"); }
#line 1406 "parser.tab.c"
    break;

  case 33: /* relational_bool: IS_NOT  */
#line 176 "parser.y"
    { printf("DEBUG PARSER: Relational Bool: IS_NOT\n"); (yyval.node) = create_node_keyword("REL_BOOL_ISNOT"); }
#line 1412 "parser.tab.c"
    break;

  case 34: /* relational_operator: GT  */
#line 180 "parser.y"
       { printf("DEBUG PARSER: Relational Operator: GT\n"); (yyval.node) = create_node_keyword("REL_OP_GT"); }
#line 1418 "parser.tab.c"
    break;

  case 35: /* relational_operator: LT  */
#line 181 "parser.y"
         { printf("DEBUG PARSER: Relational Operator: LT\n"); (yyval.node) = create_node_keyword("REL_OP_LT"); }
#line 1424 "parser.tab.c"
    break;

  case 36: /* relational_operator: GE  */
#line 182 "parser.y"
         { printf("DEBUG PARSER: Relational Operator: GE\n"); (yyval.node) = create_node_keyword("REL_OP_GE"); }
#line 1430 "parser.tab.c"
    break;

  case 37: /* relational_operator: LE  */
#line 183 "parser.y"
         { printf("DEBUG PARSER: Relational Operator: LE\n"); (yyval.node) = create_node_keyword("REL_OP_LE"); }
#line 1436 "parser.tab.c"
    break;

  case 38: /* relational_operator: EQ  */
#line 184 "parser.y"
         { printf("DEBUG PARSER: Relational Operator: EQ\n"); (yyval.node) = create_node_keyword("REL_OP_EQ"); }
#line 1442 "parser.tab.c"
    break;

  case 39: /* relational_operator: NE  */
#line 185 "parser.y"
         { printf("DEBUG PARSER: Relational Operator: NE\n"); (yyval.node) = create_node_keyword("REL_OP_NE"); }
#line 1448 "parser.tab.c"
    break;

  case 40: /* collect_command: COLLECT_KEYWORD COLLECTABLE DIRECTION  */
#line 190 "parser.y"
    { printf("DEBUG PARSER: Collect Command: collect %s %s\n", (yyvsp[-1].str), (yyvsp[0].str)); (yyval.node) = create_node_str("COLLECT_COMMAND", (yyvsp[-1].str)); }
#line 1454 "parser.tab.c"
    break;

  case 41: /* factor: INT_LITERAL  */
#line 195 "parser.y"
    { printf("DEBUG PARSER: Factor: INT_LITERAL (%d)\n", (yyvsp[0].num)); (yyval.node) = create_node_int("INT_LITERAL_NODE", (yyvsp[0].num)); }
#line 1460 "parser.tab.c"
    break;

  case 42: /* factor: BOOL_LITERAL  */
#line 197 "parser.y"
    { printf("DEBUG PARSER: Factor: BOOL_LITERAL (%d)\n", (yyvsp[0].num_bool)); (yyval.node) = create_node_int("BOOL_LITERAL_NODE", (yyvsp[0].num_bool)); }
#line 1466 "parser.tab.c"
    break;

  case 43: /* factor: IDENTIFIER  */
#line 199 "parser.y"
    { printf("DEBUG PARSER: Factor: IDENTIFIER (%s)\n", (yyvsp[0].str)); (yyval.node) = create_node_str("IDENTIFIER_NODE", (yyvsp[0].str)); }
#line 1472 "parser.tab.c"
    break;

  case 44: /* factor: LPAREN condition RPAREN  */
#line 201 "parser.y"
    { printf("DEBUG PARSER: Factor: Grouped Condition\n"); (yyval.node) = (yyvsp[-1].node); }
#line 1478 "parser.tab.c"
    break;


#line 1482 "parser.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 204 "parser.y"


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
