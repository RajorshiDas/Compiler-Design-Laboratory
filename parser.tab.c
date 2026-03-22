
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "parser.y"

/* C declarations */
#include <stdio.h>
#include <stdlib.h>
#include "symtab.h"

int yylex(void);
void yyerror(const char *message);

extern int yylineno;
extern char *yytext;

static int semantic_errors = 0;
static SymbolType current_decl_type = TYPE_INVALID;

static int is_numeric_type(SymbolType type);
static SymbolType make_numeric_result(SymbolType left, SymbolType right, const char *op_text);
static SymbolType make_relational_result(SymbolType left, SymbolType right, const char *op_text);
static SymbolType require_declared_identifier(const char *name);
static int declare_identifier(const char *name, SymbolType type);
static void validate_assignment(const char *name, SymbolType value_type);
static void validate_logic_expression(SymbolType type, const char *context);


/* Line 189 of yacc.c  */
#line 98 "parser.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     LOAD = 258,
     SET = 259,
     NUM_TYPE = 260,
     REAL_TYPE = 261,
     BIGREAL_TYPE = 262,
     CHR_TYPE = 263,
     LOGIC_TYPE = 264,
     TEXT_TYPE = 265,
     READ = 266,
     WRITE = 267,
     FX = 268,
     CHK = 269,
     ELSE_TRY = 270,
     THEN = 271,
     REPEAT = 272,
     UNTIL = 273,
     DOING = 274,
     SKIP = 275,
     DECIDE = 276,
     WHEN = 277,
     OTHERWISE = 278,
     STOP = 279,
     PLUS = 280,
     MINUS = 281,
     STAR = 282,
     SLASH = 283,
     ASSIGN = 284,
     EQ = 285,
     NEQ = 286,
     LT = 287,
     GT = 288,
     LE = 289,
     GE = 290,
     SEMICOLON = 291,
     COMMA = 292,
     LPAREN = 293,
     RPAREN = 294,
     LBRACE = 295,
     RBRACE = 296,
     ID = 297,
     STRING = 298,
     INT_LITERAL = 299,
     FLOAT_LITERAL = 300,
     UMINUS = 301
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 28 "parser.y"

    int intval;
    float floatval;
    char *strval;
    int type;
    int expr_type;



/* Line 214 of yacc.c  */
#line 190 "parser.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 202 "parser.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   178

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  47
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  29
/* YYNRULES -- Number of rules.  */
#define YYNRULES  76
/* YYNRULES -- Number of states.  */
#define YYNSTATES  151

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   301

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     6,     9,    12,    14,    16,    18,
      20,    22,    24,    26,    28,    30,    33,    36,    38,    42,
      49,    50,    52,    54,    58,    61,    63,    67,    72,    75,
      79,    81,    85,    87,    91,    96,   102,   106,   111,   117,
     123,   129,   135,   143,   144,   147,   156,   165,   167,   170,
     175,   176,   180,   182,   186,   190,   194,   198,   202,   206,
     210,   214,   216,   220,   224,   226,   228,   230,   232,   234,
     238,   241,   243,   245,   247,   249,   251
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      48,     0,    -1,    49,    -1,    -1,    49,    51,    -1,     1,
      36,    -1,    58,    -1,    61,    -1,    62,    -1,    63,    -1,
      53,    -1,    64,    -1,    66,    -1,    67,    -1,    52,    -1,
      20,    36,    -1,    24,    36,    -1,    50,    -1,    40,    49,
      41,    -1,    13,    42,    38,    54,    39,    52,    -1,    -1,
      55,    -1,    56,    -1,    55,    37,    56,    -1,    75,    42,
      -1,    75,    -1,    57,    59,    36,    -1,     3,    57,    59,
      36,    -1,    57,    50,    -1,     3,    57,    50,    -1,    60,
      -1,    59,    37,    60,    -1,    42,    -1,    42,    29,    72,
      -1,    42,    29,    72,    36,    -1,     4,    42,    29,    72,
      36,    -1,    42,    29,    50,    -1,     4,    42,    29,    50,
      -1,    11,    38,    42,    39,    36,    -1,    11,    38,     1,
      39,    36,    -1,    12,    38,    72,    39,    36,    -1,    12,
      38,     1,    39,    36,    -1,    14,    38,    71,    39,    16,
      52,    65,    -1,    -1,    15,    52,    -1,    17,    19,    52,
      18,    38,    71,    39,    36,    -1,    21,    38,    72,    39,
      40,    68,    70,    41,    -1,    69,    -1,    68,    69,    -1,
      22,    71,    16,    52,    -1,    -1,    23,    16,    52,    -1,
      72,    -1,    72,    30,    72,    -1,    72,    31,    72,    -1,
      72,    32,    72,    -1,    72,    33,    72,    -1,    72,    34,
      72,    -1,    72,    35,    72,    -1,    72,    25,    73,    -1,
      72,    26,    73,    -1,    73,    -1,    73,    27,    74,    -1,
      73,    28,    74,    -1,    74,    -1,    42,    -1,    44,    -1,
      45,    -1,    43,    -1,    38,    72,    39,    -1,    26,    74,
      -1,     5,    -1,     6,    -1,     7,    -1,     8,    -1,     9,
      -1,    10,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    59,    59,    69,    71,    76,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,   103,   107,
     114,   116,   120,   121,   125,   134,   141,   142,   143,   147,
     154,   155,   159,   164,   175,   180,   185,   190,   198,   203,
     211,   215,   224,   230,   232,   236,   243,   247,   248,   252,
     258,   260,   265,   269,   273,   277,   281,   285,   289,   296,
     300,   304,   311,   315,   319,   326,   331,   335,   339,   344,
     348,   362,   366,   370,   374,   378,   382
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "LOAD", "SET", "NUM_TYPE", "REAL_TYPE",
  "BIGREAL_TYPE", "CHR_TYPE", "LOGIC_TYPE", "TEXT_TYPE", "READ", "WRITE",
  "FX", "CHK", "ELSE_TRY", "THEN", "REPEAT", "UNTIL", "DOING", "SKIP",
  "DECIDE", "WHEN", "OTHERWISE", "STOP", "PLUS", "MINUS", "STAR", "SLASH",
  "ASSIGN", "EQ", "NEQ", "LT", "GT", "LE", "GE", "SEMICOLON", "COMMA",
  "LPAREN", "RPAREN", "LBRACE", "RBRACE", "ID", "STRING", "INT_LITERAL",
  "FLOAT_LITERAL", "UMINUS", "$accept", "program", "statement_list",
  "sync_semi", "statement", "block", "function_definition",
  "parameter_list_opt", "parameter_list", "parameter", "declaration_head",
  "declaration", "id_list", "id_item", "assignment_statement",
  "read_statement", "write_statement", "chk_statement", "else_part",
  "repeat_statement", "decide_statement", "when_clause_list",
  "when_clause", "otherwise_clause_opt", "condition", "expression", "term",
  "factor", "type_specifier", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    47,    48,    49,    49,    50,    51,    51,    51,    51,
      51,    51,    51,    51,    51,    51,    51,    51,    52,    53,
      54,    54,    55,    55,    56,    57,    58,    58,    58,    58,
      59,    59,    60,    60,    61,    61,    61,    61,    62,    62,
      63,    63,    64,    65,    65,    66,    67,    68,    68,    69,
      70,    70,    71,    71,    71,    71,    71,    71,    71,    72,
      72,    72,    73,    73,    73,    74,    74,    74,    74,    74,
      74,    75,    75,    75,    75,    75,    75
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     2,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     2,     1,     3,     6,
       0,     1,     1,     3,     2,     1,     3,     4,     2,     3,
       1,     3,     1,     3,     4,     5,     3,     4,     5,     5,
       5,     5,     7,     0,     2,     8,     8,     1,     2,     4,
       0,     3,     1,     3,     3,     3,     3,     3,     3,     3,
       3,     1,     3,     3,     1,     1,     1,     1,     1,     3,
       2,     1,     1,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     0,     1,     0,     0,     0,    71,    72,    73,
      74,    75,    76,     0,     0,     0,     0,     0,     0,     0,
       0,     3,     0,    17,     4,    14,    10,     0,     6,     7,
       8,     9,    11,    12,    13,    25,     5,     0,     0,     0,
       0,     0,     0,     0,    15,     0,    16,     0,     0,    32,
      28,     0,    30,    29,     0,     0,     0,     0,     0,     0,
       0,    65,    68,    66,    67,     0,    61,    64,    20,     0,
      52,     0,     0,    18,    36,     0,     0,    26,     0,    27,
      37,     0,     0,     0,     0,    70,     0,     0,     0,     0,
       0,     0,     0,    21,    22,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    34,    33,    31,    35,    39,
      38,    41,    69,    59,    60,    40,    62,    63,     0,     0,
      24,     0,    53,    54,    55,    56,    57,    58,     0,     0,
      19,    23,    43,     0,     0,    50,    47,     0,    42,     0,
       0,     0,    48,     0,    44,    45,     0,     0,    46,    49,
      51
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    23,    24,    25,    26,    92,    93,    94,
      27,    28,    51,    52,    29,    30,    31,    32,   138,    33,
      34,   135,   136,   143,    69,    70,    66,    67,    35
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -115
static const yytype_int16 yypact[] =
{
    -115,    19,    76,  -115,   -24,   136,   -17,  -115,  -115,  -115,
    -115,  -115,  -115,   -11,    -6,    -3,    -4,    32,    31,    36,
      59,  -115,    72,  -115,  -115,  -115,  -115,     6,  -115,  -115,
    -115,  -115,  -115,  -115,  -115,  -115,  -115,     6,   105,     7,
       2,    97,    26,    98,  -115,    26,  -115,   116,    12,   110,
    -115,   -14,  -115,  -115,     5,    12,   108,   109,   111,    26,
      26,  -115,  -115,  -115,  -115,   -15,    38,  -115,   136,   112,
      80,   131,    -8,  -115,  -115,    66,    26,  -115,   113,  -115,
    -115,    73,   117,   118,   123,  -115,     4,    26,    26,   124,
      26,    26,   122,   115,  -115,   120,   147,    26,    26,    26,
      26,    26,    26,   126,   125,  -115,    47,  -115,  -115,  -115,
    -115,  -115,  -115,    38,    38,  -115,  -115,  -115,    98,   136,
    -115,    98,    47,    47,    47,    47,    47,    47,    26,   144,
    -115,  -115,   152,   129,    26,    85,  -115,    98,  -115,   133,
     154,   155,  -115,   132,  -115,  -115,    98,    98,  -115,  -115,
    -115
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -115,  -115,   151,   -22,  -115,   -43,  -115,  -115,  -115,    55,
     170,  -115,   139,    99,  -115,  -115,  -115,  -115,  -115,  -115,
    -115,  -115,    43,  -115,  -114,   -39,    44,   -55,   -66
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -3
static const yytype_int16 yytable[] =
{
      71,    65,    95,    58,    85,    50,    72,     4,    56,    75,
      87,    88,    36,     4,   133,    53,    81,    87,    88,     3,
     140,    86,    77,    78,    89,    38,    74,    39,    59,    87,
      88,   104,    40,    80,    42,   116,   117,   106,    59,    41,
      60,    79,    78,   112,    61,    62,    63,    64,    49,    57,
      60,    43,    59,    95,    61,    62,    63,    64,   122,   123,
     124,   125,   126,   127,    60,    90,    91,    44,    61,    62,
      63,    64,    87,    88,    45,   130,    -2,     4,   132,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    87,    88,    17,   144,    46,    18,    19,    87,    88,
      20,    48,   105,   149,   150,    87,    88,   134,   141,   108,
      97,    98,    99,   100,   101,   102,    21,     4,    22,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,   113,   114,    17,    55,    68,    18,    19,    21,    76,
      20,     7,     8,     9,    10,    11,    12,    82,    83,   103,
      84,    96,   119,   109,   110,    49,    21,    73,    22,   111,
     115,   118,   120,   121,   128,   129,   134,   137,   139,   145,
     146,   147,    47,   148,   131,    37,    54,   107,   142
};

static const yytype_uint8 yycheck[] =
{
      43,    40,    68,     1,    59,    27,    45,     1,     1,    48,
      25,    26,    36,     1,   128,    37,    55,    25,    26,     0,
     134,    60,    36,    37,    39,    42,    48,    38,    26,    25,
      26,    39,    38,    55,    38,    90,    91,    76,    26,    42,
      38,    36,    37,    39,    42,    43,    44,    45,    42,    42,
      38,    19,    26,   119,    42,    43,    44,    45,    97,    98,
      99,   100,   101,   102,    38,    27,    28,    36,    42,    43,
      44,    45,    25,    26,    38,   118,     0,     1,   121,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    25,    26,    17,   137,    36,    20,    21,    25,    26,
      24,    29,    36,   146,   147,    25,    26,    22,    23,    36,
      30,    31,    32,    33,    34,    35,    40,     1,    42,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    87,    88,    17,    29,    38,    20,    21,    40,    29,
      24,     5,     6,     7,     8,     9,    10,    39,    39,    18,
      39,    39,    37,    36,    36,    42,    40,    41,    42,    36,
      36,    39,    42,    16,    38,    40,    22,    15,    39,    36,
      16,    16,    21,    41,   119,     5,    37,    78,   135
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    48,    49,     0,     1,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    17,    20,    21,
      24,    40,    42,    50,    51,    52,    53,    57,    58,    61,
      62,    63,    64,    66,    67,    75,    36,    57,    42,    38,
      38,    42,    38,    19,    36,    38,    36,    49,    29,    42,
      50,    59,    60,    50,    59,    29,     1,    42,     1,    26,
      38,    42,    43,    44,    45,    72,    73,    74,    38,    71,
      72,    52,    72,    41,    50,    72,    29,    36,    37,    36,
      50,    72,    39,    39,    39,    74,    72,    25,    26,    39,
      27,    28,    54,    55,    56,    75,    39,    30,    31,    32,
      33,    34,    35,    18,    39,    36,    72,    60,    36,    36,
      36,    36,    39,    73,    73,    36,    74,    74,    39,    37,
      42,    16,    72,    72,    72,    72,    72,    72,    38,    40,
      52,    56,    52,    71,    22,    68,    69,    15,    65,    39,
      71,    23,    69,    70,    52,    36,    16,    16,    41,    52,
      52
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
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



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 60 "parser.y"
    {
          if (semantic_errors == 0) {
              printf("Parsing completed successfully.\n");
          } else {
              printf("Parsing completed with %d semantic error(s).\n", semantic_errors);
          }
      ;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 77 "parser.y"
    {
          yyerrok;
      ;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 96 "parser.y"
    {
          yyerror("invalid statement skipped");
      ;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 108 "parser.y"
    {
          free((yyvsp[(2) - (6)].strval));
      ;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 126 "parser.y"
    {
          declare_identifier((yyvsp[(2) - (2)].strval), (SymbolType)(yyvsp[(1) - (2)].type));
          free((yyvsp[(2) - (2)].strval));
      ;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 135 "parser.y"
    {
          current_decl_type = (SymbolType)(yyvsp[(1) - (1)].type);
      ;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 144 "parser.y"
    {
          yyerror("invalid declaration");
      ;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 148 "parser.y"
    {
          yyerror("invalid declaration");
      ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 160 "parser.y"
    {
          declare_identifier((yyvsp[(1) - (1)].strval), current_decl_type);
          free((yyvsp[(1) - (1)].strval));
      ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 165 "parser.y"
    {
          if (declare_identifier((yyvsp[(1) - (3)].strval), current_decl_type)) {
              validate_assignment((yyvsp[(1) - (3)].strval), (SymbolType)(yyvsp[(3) - (3)].expr_type));
          }
          free((yyvsp[(1) - (3)].strval));
      ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 176 "parser.y"
    {
          validate_assignment((yyvsp[(1) - (4)].strval), (SymbolType)(yyvsp[(3) - (4)].expr_type));
          free((yyvsp[(1) - (4)].strval));
      ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 181 "parser.y"
    {
          validate_assignment((yyvsp[(2) - (5)].strval), (SymbolType)(yyvsp[(4) - (5)].expr_type));
          free((yyvsp[(2) - (5)].strval));
      ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 186 "parser.y"
    {
          yyerror("invalid assignment expression");
          free((yyvsp[(1) - (3)].strval));
      ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 191 "parser.y"
    {
          yyerror("invalid assignment expression");
          free((yyvsp[(2) - (4)].strval));
      ;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 199 "parser.y"
    {
          require_declared_identifier((yyvsp[(3) - (5)].strval));
          free((yyvsp[(3) - (5)].strval));
      ;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 204 "parser.y"
    {
          yyerror("invalid read statement");
          yyerrok;
      ;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 212 "parser.y"
    {
          (void)(yyvsp[(3) - (5)].expr_type);
      ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 216 "parser.y"
    {
          yyerror("invalid write statement");
          yyerrok;
      ;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 225 "parser.y"
    {
          validate_logic_expression((SymbolType)(yyvsp[(3) - (7)].expr_type), "chk");
      ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 237 "parser.y"
    {
          validate_logic_expression((SymbolType)(yyvsp[(6) - (8)].expr_type), "repeat-until");
      ;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 253 "parser.y"
    {
          validate_logic_expression((SymbolType)(yyvsp[(2) - (4)].expr_type), "when");
      ;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 266 "parser.y"
    {
          (yyval.expr_type) = (yyvsp[(1) - (1)].expr_type);
      ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 270 "parser.y"
    {
          (yyval.expr_type) = make_relational_result((SymbolType)(yyvsp[(1) - (3)].expr_type), (SymbolType)(yyvsp[(3) - (3)].expr_type), "==");
      ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 274 "parser.y"
    {
          (yyval.expr_type) = make_relational_result((SymbolType)(yyvsp[(1) - (3)].expr_type), (SymbolType)(yyvsp[(3) - (3)].expr_type), "!=");
      ;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 278 "parser.y"
    {
          (yyval.expr_type) = make_relational_result((SymbolType)(yyvsp[(1) - (3)].expr_type), (SymbolType)(yyvsp[(3) - (3)].expr_type), "<");
      ;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 282 "parser.y"
    {
          (yyval.expr_type) = make_relational_result((SymbolType)(yyvsp[(1) - (3)].expr_type), (SymbolType)(yyvsp[(3) - (3)].expr_type), ">");
      ;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 286 "parser.y"
    {
          (yyval.expr_type) = make_relational_result((SymbolType)(yyvsp[(1) - (3)].expr_type), (SymbolType)(yyvsp[(3) - (3)].expr_type), "<=");
      ;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 290 "parser.y"
    {
          (yyval.expr_type) = make_relational_result((SymbolType)(yyvsp[(1) - (3)].expr_type), (SymbolType)(yyvsp[(3) - (3)].expr_type), ">=");
      ;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 297 "parser.y"
    {
          (yyval.expr_type) = make_numeric_result((SymbolType)(yyvsp[(1) - (3)].expr_type), (SymbolType)(yyvsp[(3) - (3)].expr_type), "+");
      ;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 301 "parser.y"
    {
          (yyval.expr_type) = make_numeric_result((SymbolType)(yyvsp[(1) - (3)].expr_type), (SymbolType)(yyvsp[(3) - (3)].expr_type), "-");
      ;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 305 "parser.y"
    {
          (yyval.expr_type) = (yyvsp[(1) - (1)].expr_type);
      ;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 312 "parser.y"
    {
          (yyval.expr_type) = make_numeric_result((SymbolType)(yyvsp[(1) - (3)].expr_type), (SymbolType)(yyvsp[(3) - (3)].expr_type), "*");
      ;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 316 "parser.y"
    {
          (yyval.expr_type) = make_numeric_result((SymbolType)(yyvsp[(1) - (3)].expr_type), (SymbolType)(yyvsp[(3) - (3)].expr_type), "/");
      ;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 320 "parser.y"
    {
          (yyval.expr_type) = (yyvsp[(1) - (1)].expr_type);
      ;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 327 "parser.y"
    {
          (yyval.expr_type) = require_declared_identifier((yyvsp[(1) - (1)].strval));
          free((yyvsp[(1) - (1)].strval));
      ;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 332 "parser.y"
    {
          (yyval.expr_type) = TYPE_NUM;
      ;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 336 "parser.y"
    {
          (yyval.expr_type) = TYPE_REAL;
      ;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 340 "parser.y"
    {
          (yyval.expr_type) = TYPE_TEXT;
          free((yyvsp[(1) - (1)].strval));
      ;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 345 "parser.y"
    {
          (yyval.expr_type) = (yyvsp[(2) - (3)].expr_type);
      ;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 349 "parser.y"
    {
          if (!is_numeric_type((SymbolType)(yyvsp[(2) - (2)].expr_type))) {
              fprintf(stderr, "Semantic error at line %d: unary '-' requires a numeric operand.\n", yylineno);
              semantic_errors++;
              (yyval.expr_type) = TYPE_INVALID;
          } else {
              (yyval.expr_type) = (yyvsp[(2) - (2)].expr_type);
          }
      ;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 363 "parser.y"
    {
          (yyval.type) = TYPE_NUM;
      ;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 367 "parser.y"
    {
          (yyval.type) = TYPE_REAL;
      ;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 371 "parser.y"
    {
          (yyval.type) = TYPE_BIGREAL;
      ;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 375 "parser.y"
    {
          (yyval.type) = TYPE_CHR;
      ;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 379 "parser.y"
    {
          (yyval.type) = TYPE_LOGIC;
      ;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 383 "parser.y"
    {
          (yyval.type) = TYPE_TEXT;
      ;}
    break;



/* Line 1455 of yacc.c  */
#line 1974 "parser.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 388 "parser.y"


/* Helper functions */
static int is_numeric_type(SymbolType type) {
    return type == TYPE_NUM || type == TYPE_REAL || type == TYPE_BIGREAL;
}

static SymbolType make_numeric_result(SymbolType left, SymbolType right, const char *op_text) {
    SymbolType combined_type;

    (void)op_text;

    if (left == TYPE_INVALID || right == TYPE_INVALID) {
        return TYPE_INVALID;
    }

    combined_type = result_type(left, right);
    if (combined_type == TYPE_INVALID) {
        semantic_errors++;
    }

    return combined_type;
}

static SymbolType make_relational_result(SymbolType left, SymbolType right, const char *op_text) {
    if (left == TYPE_INVALID || right == TYPE_INVALID) {
        return TYPE_INVALID;
    }

    if ((is_numeric_type(left) && is_numeric_type(right)) || left == right) {
        return TYPE_LOGIC;
    }

    fprintf(stderr,
            "Semantic error at line %d: operator '%s' cannot compare %s with %s.\n",
            yylineno,
            op_text,
            symbol_type_name(left),
            symbol_type_name(right));
    semantic_errors++;
    return TYPE_INVALID;
}

static SymbolType require_declared_identifier(const char *name) {
    SymbolType type = get_type(name);

    if (type == TYPE_INVALID) {
        semantic_errors++;
    }

    return type;
}

static int declare_identifier(const char *name, SymbolType type) {
    if (!insert_symbol(name, type)) {
        semantic_errors++;
        return 0;
    }

    return 1;
}

static void validate_assignment(const char *name, SymbolType value_type) {
    if (value_type == TYPE_INVALID) {
        return;
    }

    if (!check_assignment(name, value_type)) {
        semantic_errors++;
    }
}

static void validate_logic_expression(SymbolType type, const char *context) {
    if (type == TYPE_INVALID) {
        return;
    }

    if (type != TYPE_LOGIC) {
        fprintf(stderr,
                "Semantic error at line %d: %s requires a logic expression, but found %s.\n",
                yylineno,
                context,
                symbol_type_name(type));
        semantic_errors++;
    }
}

void yyerror(const char *message) {
    if (yytext != NULL && yytext[0] != '\0') {
        fprintf(stderr,
                "Syntax error at line %d near '%s': %s\n",
                yylineno,
                yytext,
                message);
    } else {
        fprintf(stderr,
                "Syntax error at line %d: %s\n",
                yylineno,
                message);
    }
}

