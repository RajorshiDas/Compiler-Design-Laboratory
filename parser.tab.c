
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
#line 5 "parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ast.h"
#include "symtab.h"

int yylex(void);
void yyerror(const char *message);

extern int yylineno;
extern char *yytext;

typedef struct FunctionSignature {
    char name[64];
    int param_count;
    SymbolType param_types[32];
    SymbolType return_type;
    struct FunctionSignature *next;
} FunctionSignature;

Program *parsed_program = NULL;

static int semantic_errors = 0;
static SymbolType current_decl_type = TYPE_INVALID;
static FunctionSignature *function_signatures = NULL;
static char *function_name_stack[64];
static SymbolType function_return_stack[64];
static SymbolType function_declared_return_stack[64];
static int function_stack_top = 0;

static int is_numeric_type(SymbolType type);
static int is_assignment_compatible(SymbolType target_type, SymbolType value_type);
static ExprNode *make_numeric_expr(const char *op_text, ExprNode *left, ExprNode *right);
static ExprNode *make_relational_expr(const char *op_text, ExprNode *left, ExprNode *right);
static ExprNode *make_logic_expr(const char *op_text, ExprNode *left, ExprNode *right);
static ExprNode *make_unary_minus_expr(ExprNode *operand);
static ExprNode *make_not_expr(ExprNode *operand);
static ExprNode *make_abs_expr(ExprNode *operand);
static int require_declared_identifier(const char *name, SymbolType *out_type);
static int declare_identifier(const char *name, SymbolType type);
static int validate_assignment(const char *name, SymbolType value_type);
static void validate_logic_expression(SymbolType type, const char *context);
static FunctionSignature *find_function_signature(const char *name);
static SymbolType infer_function_call_type(const char *name, ExprList *arguments);
static void begin_function_definition(char *name, ParamNode *parameters, SymbolType declared_return_type);
static SymbolType finish_function_definition(ParamNode *parameters);
static void note_function_return(SymbolType type);
static SymbolType builtin_unary_return_type(const char *name, ExprList *arguments);

int get_semantic_error_count(void) {
    return semantic_errors;
}


/* Line 189 of yacc.c  */
#line 130 "parser.tab.c"

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

/* "%code requires" blocks.  */

/* Line 209 of yacc.c  */
#line 1 "parser.y"

#include "ast.h"



/* Line 209 of yacc.c  */
#line 160 "parser.tab.c"

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INCLUDE_DIRECTIVE = 258,
     ID = 259,
     STRING = 260,
     CHAR_LITERAL = 261,
     INT_LITERAL = 262,
     FLOAT_LITERAL = 263,
     START = 264,
     FX = 265,
     SEND = 266,
     EMPTY = 267,
     NUM_TYPE = 268,
     REAL_TYPE = 269,
     BIGREAL_TYPE = 270,
     CHR_TYPE = 271,
     LOGIC_TYPE = 272,
     TEXT_TYPE = 273,
     READ = 274,
     WRITE = 275,
     CHK = 276,
     ELSE_TRY = 277,
     THEN = 278,
     END = 279,
     REPEAT = 280,
     UNTIL = 281,
     DOING = 282,
     SKIP = 283,
     STOP = 284,
     DECIDE = 285,
     WHEN = 286,
     OTHERWISE = 287,
     TRUE_LITERAL = 288,
     FALSE_LITERAL = 289,
     AND = 290,
     OR = 291,
     NOT = 292,
     XOR = 293,
     PLUS = 294,
     MINUS = 295,
     STAR = 296,
     SLASH = 297,
     MOD = 298,
     ASSIGN = 299,
     EQ = 300,
     NEQ = 301,
     LT = 302,
     GT = 303,
     LE = 304,
     GE = 305,
     ARROW = 306,
     FAT_ARROW = 307,
     PIPE = 308,
     SEMICOLON = 309,
     COMMA = 310,
     LPAREN = 311,
     RPAREN = 312,
     LBRACE = 313,
     RBRACE = 314
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 63 "parser.y"

    int intval;
    float floatval;
    char *strval;
    int type;
    ExprNode *expr;
    StmtNode *stmt;
    ParamNode *param;
    ExprList *arglist;
    CaseNode *caseclause;



/* Line 214 of yacc.c  */
#line 250 "parser.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 262 "parser.tab.c"

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
#define YYLAST   264

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  60
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  47
/* YYNRULES -- Number of rules.  */
#define YYNRULES  106
/* YYNRULES -- Number of states.  */
#define YYNSTATES  210

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   314

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
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,     7,    10,    18,    19,    21,    22,
      25,    27,    29,    31,    33,    35,    37,    39,    41,    43,
      45,    47,    49,    52,    55,    57,    61,    69,    72,    73,
      75,    77,    81,    84,    86,    90,    92,    96,    98,   102,
     107,   113,   119,   121,   125,   129,   138,   139,   144,   153,
     163,   169,   177,   184,   186,   189,   196,   197,   201,   203,
     204,   206,   208,   212,   214,   218,   220,   224,   226,   230,
     232,   236,   240,   242,   246,   250,   254,   258,   260,   264,
     268,   270,   274,   278,   282,   284,   287,   290,   293,   297,
     299,   301,   306,   308,   310,   312,   314,   316,   318,   322,
     324,   326,   328,   330,   332,   334,   336
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      61,     0,    -1,    62,    63,    -1,    -1,    62,     3,    -1,
       9,    56,    57,    51,    12,    64,    68,    -1,    -1,    54,
      -1,    -1,    65,    66,    -1,    75,    -1,    78,    -1,    79,
      -1,    80,    -1,    70,    -1,    82,    -1,    83,    -1,    85,
      -1,    86,    -1,    87,    -1,    88,    -1,    68,    -1,    28,
      54,    -1,    29,    54,    -1,    58,    -1,    67,    65,    59,
      -1,    10,     4,    56,    71,    57,    51,   106,    -1,    69,
      68,    -1,    -1,    72,    -1,    73,    -1,    72,    55,    73,
      -1,   105,     4,    -1,   105,    -1,    74,    76,    54,    -1,
      77,    -1,    76,    55,    77,    -1,     4,    -1,     4,    44,
      95,    -1,     4,    44,    95,    54,    -1,    19,    56,     4,
      57,    54,    -1,    20,    56,    81,    57,    54,    -1,    95,
      -1,    81,    55,    95,    -1,    11,    95,    54,    -1,    21,
      56,    95,    57,    65,    24,    21,    84,    -1,    -1,    23,
      65,    24,    23,    -1,    22,    56,    95,    57,    65,    24,
      22,    84,    -1,    25,    56,     4,    55,    95,    55,    95,
      57,    68,    -1,    26,    56,    95,    57,    68,    -1,    27,
      68,    26,    56,    95,    57,    54,    -1,    30,    95,    58,
      89,    91,    59,    -1,    90,    -1,    89,    90,    -1,    31,
      56,    95,    57,    52,    92,    -1,    -1,    32,    52,    92,
      -1,    66,    -1,    -1,    94,    -1,    95,    -1,    94,    55,
      95,    -1,    96,    -1,    96,    36,    97,    -1,    97,    -1,
      97,    38,    98,    -1,    98,    -1,    98,    35,    99,    -1,
      99,    -1,    99,    45,   100,    -1,    99,    46,   100,    -1,
     100,    -1,   100,    47,   101,    -1,   100,    48,   101,    -1,
     100,    49,   101,    -1,   100,    50,   101,    -1,   101,    -1,
     101,    39,   102,    -1,   101,    40,   102,    -1,   102,    -1,
     102,    41,   103,    -1,   102,    42,   103,    -1,   102,    43,
     103,    -1,   103,    -1,    37,   103,    -1,    39,   103,    -1,
      40,   103,    -1,    53,    95,    53,    -1,   104,    -1,     4,
      -1,     4,    56,    93,    57,    -1,     7,    -1,     8,    -1,
       5,    -1,     6,    -1,    33,    -1,    34,    -1,    56,    95,
      57,    -1,    13,    -1,    14,    -1,    15,    -1,    16,    -1,
      17,    -1,    18,    -1,   105,    -1,    12,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   109,   109,   112,   114,   121,   135,   137,   142,   145,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   168,   175,   182,   190,   198,   209,   212,
     219,   223,   230,   237,   244,   251,   255,   262,   267,   277,
     285,   295,   302,   306,   313,   323,   332,   335,   339,   347,
     359,   367,   375,   382,   386,   393,   401,   404,   411,   419,
     422,   429,   433,   440,   447,   451,   458,   462,   469,   473,
     480,   484,   488,   495,   499,   503,   507,   511,   518,   522,
     526,   533,   537,   541,   545,   552,   556,   560,   564,   568,
     575,   582,   588,   592,   596,   602,   608,   612,   616,   623,
     627,   631,   635,   639,   643,   650,   654
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INCLUDE_DIRECTIVE", "ID", "STRING",
  "CHAR_LITERAL", "INT_LITERAL", "FLOAT_LITERAL", "START", "FX", "SEND",
  "EMPTY", "NUM_TYPE", "REAL_TYPE", "BIGREAL_TYPE", "CHR_TYPE",
  "LOGIC_TYPE", "TEXT_TYPE", "READ", "WRITE", "CHK", "ELSE_TRY", "THEN",
  "END", "REPEAT", "UNTIL", "DOING", "SKIP", "STOP", "DECIDE", "WHEN",
  "OTHERWISE", "TRUE_LITERAL", "FALSE_LITERAL", "AND", "OR", "NOT", "XOR",
  "PLUS", "MINUS", "STAR", "SLASH", "MOD", "ASSIGN", "EQ", "NEQ", "LT",
  "GT", "LE", "GE", "ARROW", "FAT_ARROW", "PIPE", "SEMICOLON", "COMMA",
  "LPAREN", "RPAREN", "LBRACE", "RBRACE", "$accept", "program",
  "include_list", "start_definition", "start_semicolon_opt",
  "statement_list", "statement", "block_open", "block", "function_header",
  "function_definition", "parameter_list_opt", "parameter_list",
  "parameter", "declaration_head", "declaration", "id_list", "id_item",
  "assignment_statement", "read_statement", "write_statement",
  "write_argument_list", "send_statement", "chk_statement", "chk_suffix",
  "repeat_statement", "until_statement", "doing_statement",
  "decide_statement", "when_clause_list", "when_clause",
  "otherwise_clause_opt", "case_action", "argument_list_opt",
  "argument_list", "expression", "logic_or", "logic_xor", "logic_and",
  "equality", "relational", "additive", "multiplicative", "unary",
  "primary", "type_specifier", "return_type", 0
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
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    60,    61,    62,    62,    63,    64,    64,    65,    65,
      66,    66,    66,    66,    66,    66,    66,    66,    66,    66,
      66,    66,    66,    66,    67,    68,    69,    70,    71,    71,
      72,    72,    73,    74,    75,    76,    76,    77,    77,    78,
      79,    80,    81,    81,    82,    83,    84,    84,    84,    85,
      86,    87,    88,    89,    89,    90,    91,    91,    92,    93,
      93,    94,    94,    95,    96,    96,    97,    97,    98,    98,
      99,    99,    99,   100,   100,   100,   100,   100,   101,   101,
     101,   102,   102,   102,   102,   103,   103,   103,   103,   103,
     104,   104,   104,   104,   104,   104,   104,   104,   104,   105,
     105,   105,   105,   105,   105,   106,   106
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     0,     2,     7,     0,     1,     0,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     2,     1,     3,     7,     2,     0,     1,
       1,     3,     2,     1,     3,     1,     3,     1,     3,     4,
       5,     5,     1,     3,     3,     8,     0,     4,     8,     9,
       5,     7,     6,     1,     2,     6,     0,     3,     1,     0,
       1,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       3,     3,     1,     3,     3,     3,     3,     1,     3,     3,
       1,     3,     3,     3,     1,     2,     2,     2,     3,     1,
       1,     4,     1,     1,     1,     1,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     0,     1,     4,     0,     2,     0,     0,     0,
       6,     7,     0,    24,     8,     5,     0,     0,     0,     0,
      99,   100,   101,   102,   103,   104,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    25,     9,    21,     0,    14,
       0,    10,    11,    12,    13,    15,    16,    17,    18,    19,
      20,    33,     0,     0,    90,    94,    95,    92,    93,    96,
      97,     0,     0,     0,     0,     0,     0,    63,    65,    67,
      69,    72,    77,    80,    84,    89,     0,     0,     0,     0,
       0,     0,    22,    23,     0,    27,    37,     0,    35,     0,
      28,    59,    85,    86,    87,     0,     0,    44,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    42,     0,     0,     0,     0,     0,
       0,    34,     0,    39,     0,    29,    30,     0,     0,    60,
      61,    88,    98,    64,    66,    68,    70,    71,    73,    74,
      75,    76,    78,    79,    81,    82,    83,     0,     0,     0,
       8,     0,     0,     0,     0,    56,    53,    38,    36,     0,
       0,    32,    91,     0,    40,    43,    41,     0,     0,    50,
       0,     0,     0,    54,     0,     0,    31,    62,     0,     0,
       0,     0,     0,    52,   106,   105,    26,    46,     0,    51,
       0,    58,    57,     0,     8,    45,     0,     0,     0,     0,
      49,    55,     0,     0,     8,    47,     0,     0,    46,    48
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     6,    12,    16,    36,    14,    37,    38,
      39,   124,   125,   126,    40,    41,    87,    88,    42,    43,
      44,   113,    45,    46,   195,    47,    48,    49,    50,   155,
     156,   174,   192,   128,   129,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    51,   186
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -180
static const yytype_int16 yypact[] =
{
    -180,    17,    12,  -180,  -180,   -25,  -180,   -13,    -4,    58,
      24,  -180,    31,  -180,  -180,  -180,    47,    48,    91,   207,
    -180,  -180,  -180,  -180,  -180,  -180,    61,    64,    66,    67,
      68,    31,    71,    72,   207,  -180,  -180,  -180,    31,  -180,
     114,  -180,  -180,  -180,  -180,  -180,  -180,  -180,  -180,  -180,
    -180,  -180,   207,    73,    74,  -180,  -180,  -180,  -180,  -180,
    -180,   207,   207,   207,   207,   207,    78,    92,    89,    98,
       4,   -20,    16,   -19,  -180,  -180,   130,   207,   207,   131,
     207,   110,  -180,  -180,    79,  -180,    94,    26,  -180,    88,
      21,   207,  -180,  -180,  -180,    90,    87,  -180,   207,   207,
     207,   207,   207,   207,   207,   207,   207,   207,   207,   207,
     207,   207,    93,   -41,  -180,    95,    96,    99,    97,   115,
     207,  -180,   114,  -180,   118,   112,  -180,   141,   119,   122,
    -180,  -180,  -180,    89,    98,     4,   -20,   -20,    16,    16,
      16,    16,   -19,   -19,  -180,  -180,  -180,   124,   207,   125,
    -180,   207,    31,   207,   126,    51,  -180,  -180,  -180,   129,
      21,  -180,  -180,   207,  -180,  -180,  -180,    83,   132,  -180,
     128,   207,   134,  -180,   142,    -5,  -180,  -180,   160,   207,
     137,   161,   206,  -180,  -180,  -180,  -180,    62,   171,  -180,
     136,  -180,  -180,   173,  -180,  -180,    31,   206,   207,   144,
    -180,  -180,   181,   216,  -180,  -180,   179,   127,    62,  -180
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -180,  -180,  -180,  -180,  -180,  -125,  -179,  -180,   -12,  -180,
    -180,  -180,  -180,    70,  -180,  -180,  -180,   120,  -180,  -180,
    -180,  -180,  -180,  -180,    35,  -180,  -180,  -180,  -180,  -180,
     100,  -180,    52,  -180,  -180,   -32,  -180,   147,   149,   150,
     -11,   -63,     7,   -57,  -180,   -89,  -180
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      15,   127,    84,   191,    92,    93,    94,   184,    20,    21,
      22,    23,    24,    25,   148,     4,   149,     3,   191,    81,
      89,     5,   109,   110,   111,   167,    85,   103,   104,   105,
     106,     7,    95,    96,    20,    21,    22,    23,    24,    25,
     138,   139,   140,   141,     8,   114,   115,     9,   117,   101,
     102,    17,   144,   145,   146,   107,   108,    18,    19,   130,
      20,    21,    22,    23,    24,    25,    26,    27,    28,   199,
      10,   127,    29,    30,    31,    32,    33,    34,    11,   206,
     121,   122,   154,   172,   193,   194,   185,    17,   157,    13,
     136,   137,    52,    18,    19,    53,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    13,    35,   178,    29,    30,
      31,    32,    33,    34,   142,   143,   165,    76,    86,   168,
      77,   170,    78,    79,    80,    82,    83,    99,    98,    90,
      91,   177,    97,   100,   112,   116,   118,   119,   120,   181,
     169,    13,   123,   131,   132,   161,   154,   188,    17,   208,
     147,   151,   150,   153,    18,    19,   152,    20,    21,    22,
      23,    24,    25,    26,    27,    28,   202,   160,   203,    29,
      30,    31,    32,    33,    34,   159,   162,   163,   164,   166,
     175,   187,   171,    17,   200,   180,   182,   179,   197,    18,
      19,   189,    20,    21,    22,    23,    24,    25,    26,    27,
      28,   183,    13,   207,    29,    30,    31,    32,    33,    34,
      17,    54,    55,    56,    57,    58,    18,    19,   190,    20,
      21,    22,    23,    24,    25,    26,    27,    28,   196,   198,
     176,    29,    30,    31,    32,    33,    34,    13,   204,   205,
      59,    60,   158,   209,    61,   133,    62,    63,   134,   201,
     135,     0,     0,     0,     0,   173,     0,     0,     0,     0,
      64,     0,     0,    65,    13
};

static const yytype_int16 yycheck[] =
{
      12,    90,    34,   182,    61,    62,    63,    12,    13,    14,
      15,    16,    17,    18,    55,     3,    57,     0,   197,    31,
      52,     9,    41,    42,    43,   150,    38,    47,    48,    49,
      50,    56,    64,    65,    13,    14,    15,    16,    17,    18,
     103,   104,   105,   106,    57,    77,    78,    51,    80,    45,
      46,     4,   109,   110,   111,    39,    40,    10,    11,    91,
      13,    14,    15,    16,    17,    18,    19,    20,    21,   194,
      12,   160,    25,    26,    27,    28,    29,    30,    54,   204,
      54,    55,    31,    32,    22,    23,   175,     4,   120,    58,
     101,   102,    44,    10,    11,     4,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    58,    59,    24,    25,    26,
      27,    28,    29,    30,   107,   108,   148,    56,     4,   151,
      56,   153,    56,    56,    56,    54,    54,    38,    36,    56,
      56,   163,    54,    35,     4,     4,    26,    58,    44,   171,
     152,    58,    54,    53,    57,     4,    31,   179,     4,    22,
      57,    55,    57,    56,    10,    11,    57,    13,    14,    15,
      16,    17,    18,    19,    20,    21,   198,    55,    24,    25,
      26,    27,    28,    29,    30,    57,    57,    55,    54,    54,
      51,    21,    56,     4,   196,    57,    52,    55,    52,    10,
      11,    54,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    59,    58,    24,    25,    26,    27,    28,    29,    30,
       4,     4,     5,     6,     7,     8,    10,    11,    57,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    57,    56,
     160,    25,    26,    27,    28,    29,    30,    58,    57,    23,
      33,    34,   122,   208,    37,    98,    39,    40,    99,   197,
     100,    -1,    -1,    -1,    -1,   155,    -1,    -1,    -1,    -1,
      53,    -1,    -1,    56,    58
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    61,    62,     0,     3,     9,    63,    56,    57,    51,
      12,    54,    64,    58,    67,    68,    65,     4,    10,    11,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    25,
      26,    27,    28,    29,    30,    59,    66,    68,    69,    70,
      74,    75,    78,    79,    80,    82,    83,    85,    86,    87,
      88,   105,    44,     4,     4,     5,     6,     7,     8,    33,
      34,    37,    39,    40,    53,    56,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,    56,    56,    56,    56,
      56,    68,    54,    54,    95,    68,     4,    76,    77,    95,
      56,    56,   103,   103,   103,    95,    95,    54,    36,    38,
      35,    45,    46,    47,    48,    49,    50,    39,    40,    41,
      42,    43,     4,    81,    95,    95,     4,    95,    26,    58,
      44,    54,    55,    54,    71,    72,    73,   105,    93,    94,
      95,    53,    57,    97,    98,    99,   100,   100,   101,   101,
     101,   101,   102,   102,   103,   103,   103,    57,    55,    57,
      57,    55,    57,    56,    31,    89,    90,    95,    77,    57,
      55,     4,    57,    55,    54,    95,    54,    65,    95,    68,
      95,    56,    32,    90,    91,    51,    73,    95,    24,    55,
      57,    95,    52,    59,    12,   105,   106,    21,    95,    54,
      57,    66,    92,    22,    23,    84,    57,    52,    56,    65,
      68,    92,    95,    24,    57,    23,    65,    24,    22,    84
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
      case 3: /* "INCLUDE_DIRECTIVE" */

/* Line 1000 of yacc.c  */
#line 97 "parser.y"
	{ free((yyvaluep->strval)); };

/* Line 1000 of yacc.c  */
#line 1366 "parser.tab.c"
	break;
      case 4: /* "ID" */

/* Line 1000 of yacc.c  */
#line 97 "parser.y"
	{ free((yyvaluep->strval)); };

/* Line 1000 of yacc.c  */
#line 1375 "parser.tab.c"
	break;
      case 5: /* "STRING" */

/* Line 1000 of yacc.c  */
#line 97 "parser.y"
	{ free((yyvaluep->strval)); };

/* Line 1000 of yacc.c  */
#line 1384 "parser.tab.c"
	break;
      case 6: /* "CHAR_LITERAL" */

/* Line 1000 of yacc.c  */
#line 97 "parser.y"
	{ free((yyvaluep->strval)); };

/* Line 1000 of yacc.c  */
#line 1393 "parser.tab.c"
	break;
      case 65: /* "statement_list" */

/* Line 1000 of yacc.c  */
#line 99 "parser.y"
	{ free_statement_list((yyvaluep->stmt)); };

/* Line 1000 of yacc.c  */
#line 1402 "parser.tab.c"
	break;
      case 66: /* "statement" */

/* Line 1000 of yacc.c  */
#line 99 "parser.y"
	{ free_statement_list((yyvaluep->stmt)); };

/* Line 1000 of yacc.c  */
#line 1411 "parser.tab.c"
	break;
      case 68: /* "block" */

/* Line 1000 of yacc.c  */
#line 99 "parser.y"
	{ free_statement_list((yyvaluep->stmt)); };

/* Line 1000 of yacc.c  */
#line 1420 "parser.tab.c"
	break;
      case 69: /* "function_header" */

/* Line 1000 of yacc.c  */
#line 100 "parser.y"
	{ free_param_list((yyvaluep->param)); };

/* Line 1000 of yacc.c  */
#line 1429 "parser.tab.c"
	break;
      case 70: /* "function_definition" */

/* Line 1000 of yacc.c  */
#line 99 "parser.y"
	{ free_statement_list((yyvaluep->stmt)); };

/* Line 1000 of yacc.c  */
#line 1438 "parser.tab.c"
	break;
      case 71: /* "parameter_list_opt" */

/* Line 1000 of yacc.c  */
#line 100 "parser.y"
	{ free_param_list((yyvaluep->param)); };

/* Line 1000 of yacc.c  */
#line 1447 "parser.tab.c"
	break;
      case 72: /* "parameter_list" */

/* Line 1000 of yacc.c  */
#line 100 "parser.y"
	{ free_param_list((yyvaluep->param)); };

/* Line 1000 of yacc.c  */
#line 1456 "parser.tab.c"
	break;
      case 73: /* "parameter" */

/* Line 1000 of yacc.c  */
#line 100 "parser.y"
	{ free_param_list((yyvaluep->param)); };

/* Line 1000 of yacc.c  */
#line 1465 "parser.tab.c"
	break;
      case 75: /* "declaration" */

/* Line 1000 of yacc.c  */
#line 99 "parser.y"
	{ free_statement_list((yyvaluep->stmt)); };

/* Line 1000 of yacc.c  */
#line 1474 "parser.tab.c"
	break;
      case 76: /* "id_list" */

/* Line 1000 of yacc.c  */
#line 99 "parser.y"
	{ free_statement_list((yyvaluep->stmt)); };

/* Line 1000 of yacc.c  */
#line 1483 "parser.tab.c"
	break;
      case 77: /* "id_item" */

/* Line 1000 of yacc.c  */
#line 99 "parser.y"
	{ free_statement_list((yyvaluep->stmt)); };

/* Line 1000 of yacc.c  */
#line 1492 "parser.tab.c"
	break;
      case 78: /* "assignment_statement" */

/* Line 1000 of yacc.c  */
#line 99 "parser.y"
	{ free_statement_list((yyvaluep->stmt)); };

/* Line 1000 of yacc.c  */
#line 1501 "parser.tab.c"
	break;
      case 79: /* "read_statement" */

/* Line 1000 of yacc.c  */
#line 99 "parser.y"
	{ free_statement_list((yyvaluep->stmt)); };

/* Line 1000 of yacc.c  */
#line 1510 "parser.tab.c"
	break;
      case 80: /* "write_statement" */

/* Line 1000 of yacc.c  */
#line 99 "parser.y"
	{ free_statement_list((yyvaluep->stmt)); };

/* Line 1000 of yacc.c  */
#line 1519 "parser.tab.c"
	break;
      case 81: /* "write_argument_list" */

/* Line 1000 of yacc.c  */
#line 101 "parser.y"
	{ free_expr_list((yyvaluep->arglist)); };

/* Line 1000 of yacc.c  */
#line 1528 "parser.tab.c"
	break;
      case 82: /* "send_statement" */

/* Line 1000 of yacc.c  */
#line 99 "parser.y"
	{ free_statement_list((yyvaluep->stmt)); };

/* Line 1000 of yacc.c  */
#line 1537 "parser.tab.c"
	break;
      case 83: /* "chk_statement" */

/* Line 1000 of yacc.c  */
#line 99 "parser.y"
	{ free_statement_list((yyvaluep->stmt)); };

/* Line 1000 of yacc.c  */
#line 1546 "parser.tab.c"
	break;
      case 84: /* "chk_suffix" */

/* Line 1000 of yacc.c  */
#line 99 "parser.y"
	{ free_statement_list((yyvaluep->stmt)); };

/* Line 1000 of yacc.c  */
#line 1555 "parser.tab.c"
	break;
      case 85: /* "repeat_statement" */

/* Line 1000 of yacc.c  */
#line 99 "parser.y"
	{ free_statement_list((yyvaluep->stmt)); };

/* Line 1000 of yacc.c  */
#line 1564 "parser.tab.c"
	break;
      case 86: /* "until_statement" */

/* Line 1000 of yacc.c  */
#line 99 "parser.y"
	{ free_statement_list((yyvaluep->stmt)); };

/* Line 1000 of yacc.c  */
#line 1573 "parser.tab.c"
	break;
      case 87: /* "doing_statement" */

/* Line 1000 of yacc.c  */
#line 99 "parser.y"
	{ free_statement_list((yyvaluep->stmt)); };

/* Line 1000 of yacc.c  */
#line 1582 "parser.tab.c"
	break;
      case 88: /* "decide_statement" */

/* Line 1000 of yacc.c  */
#line 99 "parser.y"
	{ free_statement_list((yyvaluep->stmt)); };

/* Line 1000 of yacc.c  */
#line 1591 "parser.tab.c"
	break;
      case 89: /* "when_clause_list" */

/* Line 1000 of yacc.c  */
#line 102 "parser.y"
	{ free_case_list((yyvaluep->caseclause)); };

/* Line 1000 of yacc.c  */
#line 1600 "parser.tab.c"
	break;
      case 90: /* "when_clause" */

/* Line 1000 of yacc.c  */
#line 102 "parser.y"
	{ free_case_list((yyvaluep->caseclause)); };

/* Line 1000 of yacc.c  */
#line 1609 "parser.tab.c"
	break;
      case 91: /* "otherwise_clause_opt" */

/* Line 1000 of yacc.c  */
#line 99 "parser.y"
	{ free_statement_list((yyvaluep->stmt)); };

/* Line 1000 of yacc.c  */
#line 1618 "parser.tab.c"
	break;
      case 92: /* "case_action" */

/* Line 1000 of yacc.c  */
#line 99 "parser.y"
	{ free_statement_list((yyvaluep->stmt)); };

/* Line 1000 of yacc.c  */
#line 1627 "parser.tab.c"
	break;
      case 93: /* "argument_list_opt" */

/* Line 1000 of yacc.c  */
#line 101 "parser.y"
	{ free_expr_list((yyvaluep->arglist)); };

/* Line 1000 of yacc.c  */
#line 1636 "parser.tab.c"
	break;
      case 94: /* "argument_list" */

/* Line 1000 of yacc.c  */
#line 101 "parser.y"
	{ free_expr_list((yyvaluep->arglist)); };

/* Line 1000 of yacc.c  */
#line 1645 "parser.tab.c"
	break;
      case 95: /* "expression" */

/* Line 1000 of yacc.c  */
#line 98 "parser.y"
	{ free_expr((yyvaluep->expr)); };

/* Line 1000 of yacc.c  */
#line 1654 "parser.tab.c"
	break;
      case 96: /* "logic_or" */

/* Line 1000 of yacc.c  */
#line 98 "parser.y"
	{ free_expr((yyvaluep->expr)); };

/* Line 1000 of yacc.c  */
#line 1663 "parser.tab.c"
	break;
      case 97: /* "logic_xor" */

/* Line 1000 of yacc.c  */
#line 98 "parser.y"
	{ free_expr((yyvaluep->expr)); };

/* Line 1000 of yacc.c  */
#line 1672 "parser.tab.c"
	break;
      case 98: /* "logic_and" */

/* Line 1000 of yacc.c  */
#line 98 "parser.y"
	{ free_expr((yyvaluep->expr)); };

/* Line 1000 of yacc.c  */
#line 1681 "parser.tab.c"
	break;
      case 99: /* "equality" */

/* Line 1000 of yacc.c  */
#line 98 "parser.y"
	{ free_expr((yyvaluep->expr)); };

/* Line 1000 of yacc.c  */
#line 1690 "parser.tab.c"
	break;
      case 100: /* "relational" */

/* Line 1000 of yacc.c  */
#line 98 "parser.y"
	{ free_expr((yyvaluep->expr)); };

/* Line 1000 of yacc.c  */
#line 1699 "parser.tab.c"
	break;
      case 101: /* "additive" */

/* Line 1000 of yacc.c  */
#line 98 "parser.y"
	{ free_expr((yyvaluep->expr)); };

/* Line 1000 of yacc.c  */
#line 1708 "parser.tab.c"
	break;
      case 102: /* "multiplicative" */

/* Line 1000 of yacc.c  */
#line 98 "parser.y"
	{ free_expr((yyvaluep->expr)); };

/* Line 1000 of yacc.c  */
#line 1717 "parser.tab.c"
	break;
      case 103: /* "unary" */

/* Line 1000 of yacc.c  */
#line 98 "parser.y"
	{ free_expr((yyvaluep->expr)); };

/* Line 1000 of yacc.c  */
#line 1726 "parser.tab.c"
	break;
      case 104: /* "primary" */

/* Line 1000 of yacc.c  */
#line 98 "parser.y"
	{ free_expr((yyvaluep->expr)); };

/* Line 1000 of yacc.c  */
#line 1735 "parser.tab.c"
	break;

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
        case 4:

/* Line 1455 of yacc.c  */
#line 115 "parser.y"
    {
          free((yyvsp[(2) - (2)].strval));
      ;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 122 "parser.y"
    {
          StmtNode *body = NULL;

          if ((yyvsp[(7) - (7)].stmt) != NULL && (yyvsp[(7) - (7)].stmt)->kind == STMT_BLOCK) {
              body = (yyvsp[(7) - (7)].stmt)->data.block.statements;
              (yyvsp[(7) - (7)].stmt)->data.block.statements = NULL;
              free_statement_list((yyvsp[(7) - (7)].stmt));
          }

          parsed_program = create_program(body);
      ;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 142 "parser.y"
    {
          (yyval.stmt) = NULL;
      ;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 146 "parser.y"
    {
          (yyval.stmt) = append_statement((yyvsp[(1) - (2)].stmt), (yyvsp[(2) - (2)].stmt));
      ;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 165 "parser.y"
    {
          (yyval.stmt) = create_skip_stmt();
      ;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 169 "parser.y"
    {
          (yyval.stmt) = create_stop_stmt();
      ;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 176 "parser.y"
    {
          enter_scope();
      ;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 183 "parser.y"
    {
          leave_scope();
          (yyval.stmt) = create_block_stmt((yyvsp[(2) - (3)].stmt));
      ;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 191 "parser.y"
    {
          begin_function_definition((yyvsp[(2) - (7)].strval), (yyvsp[(4) - (7)].param), (SymbolType)(yyvsp[(7) - (7)].type));
          (yyval.param) = (yyvsp[(4) - (7)].param);
      ;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 199 "parser.y"
    {
          char *function_name = function_name_stack[function_stack_top - 1];
          SymbolType return_type_value = finish_function_definition((yyvsp[(1) - (2)].param));

          (yyval.stmt) = create_function_def_stmt(function_name, (yyvsp[(1) - (2)].param), (yyvsp[(2) - (2)].stmt), return_type_value);
      ;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 209 "parser.y"
    {
          (yyval.param) = NULL;
      ;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 213 "parser.y"
    {
          (yyval.param) = (yyvsp[(1) - (1)].param);
      ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 220 "parser.y"
    {
          (yyval.param) = (yyvsp[(1) - (1)].param);
      ;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 224 "parser.y"
    {
          (yyval.param) = append_parameter_list((yyvsp[(1) - (3)].param), (yyvsp[(3) - (3)].param));
      ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 231 "parser.y"
    {
          (yyval.param) = create_parameter_node((SymbolType)(yyvsp[(1) - (2)].type), (yyvsp[(2) - (2)].strval));
      ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 238 "parser.y"
    {
          current_decl_type = (SymbolType)(yyvsp[(1) - (1)].type);
      ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 245 "parser.y"
    {
          (yyval.stmt) = (yyvsp[(2) - (3)].stmt);
      ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 252 "parser.y"
    {
          (yyval.stmt) = (yyvsp[(1) - (1)].stmt);
      ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 256 "parser.y"
    {
          (yyval.stmt) = append_statement((yyvsp[(1) - (3)].stmt), (yyvsp[(3) - (3)].stmt));
      ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 263 "parser.y"
    {
          declare_identifier((yyvsp[(1) - (1)].strval), current_decl_type);
          (yyval.stmt) = create_declaration_stmt(current_decl_type, (yyvsp[(1) - (1)].strval), NULL);
      ;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 268 "parser.y"
    {
          if (declare_identifier((yyvsp[(1) - (3)].strval), current_decl_type)) {
              validate_assignment((yyvsp[(1) - (3)].strval), ((yyvsp[(3) - (3)].expr))->value_type);
          }
          (yyval.stmt) = create_declaration_stmt(current_decl_type, (yyvsp[(1) - (3)].strval), (yyvsp[(3) - (3)].expr));
      ;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 278 "parser.y"
    {
          validate_assignment((yyvsp[(1) - (4)].strval), ((yyvsp[(3) - (4)].expr))->value_type);
          (yyval.stmt) = create_assignment_stmt((yyvsp[(1) - (4)].strval), (yyvsp[(3) - (4)].expr));
      ;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 286 "parser.y"
    {
          SymbolType type;

          require_declared_identifier((yyvsp[(3) - (5)].strval), &type);
          (yyval.stmt) = create_read_stmt((yyvsp[(3) - (5)].strval), type);
      ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 296 "parser.y"
    {
          (yyval.stmt) = create_write_stmt((yyvsp[(3) - (5)].arglist));
      ;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 303 "parser.y"
    {
          (yyval.arglist) = create_expr_list((yyvsp[(1) - (1)].expr));
      ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 307 "parser.y"
    {
          (yyval.arglist) = append_expr_list((yyvsp[(1) - (3)].arglist), create_expr_list((yyvsp[(3) - (3)].expr)));
      ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 314 "parser.y"
    {
          if (function_stack_top > 0) {
              note_function_return(((yyvsp[(2) - (3)].expr))->value_type);
          }
          (yyval.stmt) = create_return_stmt((yyvsp[(2) - (3)].expr));
      ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 324 "parser.y"
    {
          validate_logic_expression(((yyvsp[(3) - (8)].expr))->value_type, "chk");
          (yyval.stmt) = create_chk_stmt((yyvsp[(3) - (8)].expr), (yyvsp[(5) - (8)].stmt), (yyvsp[(8) - (8)].stmt));
      ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 332 "parser.y"
    {
          (yyval.stmt) = NULL;
      ;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 336 "parser.y"
    {
          (yyval.stmt) = (yyvsp[(2) - (4)].stmt);
      ;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 340 "parser.y"
    {
          validate_logic_expression(((yyvsp[(3) - (8)].expr))->value_type, "else_try");
          (yyval.stmt) = create_chk_stmt((yyvsp[(3) - (8)].expr), (yyvsp[(5) - (8)].stmt), (yyvsp[(8) - (8)].stmt));
      ;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 348 "parser.y"
    {
          SymbolType type;

          require_declared_identifier((yyvsp[(3) - (9)].strval), &type);
          validate_logic_expression(((yyvsp[(5) - (9)].expr))->value_type, "repeat");
          validate_assignment((yyvsp[(3) - (9)].strval), ((yyvsp[(7) - (9)].expr))->value_type);
          (yyval.stmt) = create_repeat_stmt((yyvsp[(3) - (9)].strval), (yyvsp[(5) - (9)].expr), (yyvsp[(7) - (9)].expr), (yyvsp[(9) - (9)].stmt));
      ;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 360 "parser.y"
    {
          validate_logic_expression(((yyvsp[(3) - (5)].expr))->value_type, "until");
          (yyval.stmt) = create_until_stmt((yyvsp[(3) - (5)].expr), (yyvsp[(5) - (5)].stmt));
      ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 368 "parser.y"
    {
          validate_logic_expression(((yyvsp[(5) - (7)].expr))->value_type, "doing-until");
          (yyval.stmt) = create_doing_stmt((yyvsp[(2) - (7)].stmt), (yyvsp[(5) - (7)].expr));
      ;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 376 "parser.y"
    {
          (yyval.stmt) = create_decide_stmt((yyvsp[(2) - (6)].expr), (yyvsp[(4) - (6)].caseclause), (yyvsp[(5) - (6)].stmt));
      ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 383 "parser.y"
    {
          (yyval.caseclause) = (yyvsp[(1) - (1)].caseclause);
      ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 387 "parser.y"
    {
          (yyval.caseclause) = append_case_list((yyvsp[(1) - (2)].caseclause), (yyvsp[(2) - (2)].caseclause));
      ;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 394 "parser.y"
    {
          (yyval.caseclause) = create_case_node((yyvsp[(3) - (6)].expr), (yyvsp[(6) - (6)].stmt));
      ;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 401 "parser.y"
    {
          (yyval.stmt) = NULL;
      ;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 405 "parser.y"
    {
          (yyval.stmt) = (yyvsp[(3) - (3)].stmt);
      ;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 412 "parser.y"
    {
          (yyval.stmt) = (yyvsp[(1) - (1)].stmt);
      ;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 419 "parser.y"
    {
          (yyval.arglist) = NULL;
      ;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 423 "parser.y"
    {
          (yyval.arglist) = (yyvsp[(1) - (1)].arglist);
      ;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 430 "parser.y"
    {
          (yyval.arglist) = create_argument_list((yyvsp[(1) - (1)].expr));
      ;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 434 "parser.y"
    {
          (yyval.arglist) = append_argument_list((yyvsp[(1) - (3)].arglist), create_argument_list((yyvsp[(3) - (3)].expr)));
      ;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 441 "parser.y"
    {
          (yyval.expr) = (yyvsp[(1) - (1)].expr);
      ;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 448 "parser.y"
    {
          (yyval.expr) = make_logic_expr("OR", (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));
      ;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 452 "parser.y"
    {
          (yyval.expr) = (yyvsp[(1) - (1)].expr);
      ;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 459 "parser.y"
    {
          (yyval.expr) = make_logic_expr("XOR", (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));
      ;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 463 "parser.y"
    {
          (yyval.expr) = (yyvsp[(1) - (1)].expr);
      ;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 470 "parser.y"
    {
          (yyval.expr) = make_logic_expr("AND", (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));
      ;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 474 "parser.y"
    {
          (yyval.expr) = (yyvsp[(1) - (1)].expr);
      ;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 481 "parser.y"
    {
          (yyval.expr) = make_relational_expr("==", (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));
      ;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 485 "parser.y"
    {
          (yyval.expr) = make_relational_expr("!=", (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));
      ;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 489 "parser.y"
    {
          (yyval.expr) = (yyvsp[(1) - (1)].expr);
      ;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 496 "parser.y"
    {
          (yyval.expr) = make_relational_expr("<", (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));
      ;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 500 "parser.y"
    {
          (yyval.expr) = make_relational_expr(">", (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));
      ;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 504 "parser.y"
    {
          (yyval.expr) = make_relational_expr("<=", (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));
      ;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 508 "parser.y"
    {
          (yyval.expr) = make_relational_expr(">=", (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));
      ;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 512 "parser.y"
    {
          (yyval.expr) = (yyvsp[(1) - (1)].expr);
      ;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 519 "parser.y"
    {
          (yyval.expr) = make_numeric_expr("+", (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));
      ;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 523 "parser.y"
    {
          (yyval.expr) = make_numeric_expr("-", (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));
      ;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 527 "parser.y"
    {
          (yyval.expr) = (yyvsp[(1) - (1)].expr);
      ;}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 534 "parser.y"
    {
          (yyval.expr) = make_numeric_expr("*", (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));
      ;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 538 "parser.y"
    {
          (yyval.expr) = make_numeric_expr("/", (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));
      ;}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 542 "parser.y"
    {
          (yyval.expr) = make_numeric_expr("%", (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));
      ;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 546 "parser.y"
    {
          (yyval.expr) = (yyvsp[(1) - (1)].expr);
      ;}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 553 "parser.y"
    {
          (yyval.expr) = make_not_expr((yyvsp[(2) - (2)].expr));
      ;}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 557 "parser.y"
    {
          (yyval.expr) = (yyvsp[(2) - (2)].expr);
      ;}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 561 "parser.y"
    {
          (yyval.expr) = make_unary_minus_expr((yyvsp[(2) - (2)].expr));
      ;}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 565 "parser.y"
    {
          (yyval.expr) = make_abs_expr((yyvsp[(2) - (3)].expr));
      ;}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 569 "parser.y"
    {
          (yyval.expr) = (yyvsp[(1) - (1)].expr);
      ;}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 576 "parser.y"
    {
          SymbolType type;

          require_declared_identifier((yyvsp[(1) - (1)].strval), &type);
          (yyval.expr) = create_variable_expr((yyvsp[(1) - (1)].strval), type);
      ;}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 583 "parser.y"
    {
          SymbolType return_type_value = infer_function_call_type((yyvsp[(1) - (4)].strval), (yyvsp[(3) - (4)].arglist));

          (yyval.expr) = create_function_call_expr((yyvsp[(1) - (4)].strval), (yyvsp[(3) - (4)].arglist), return_type_value);
      ;}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 589 "parser.y"
    {
          (yyval.expr) = create_int_literal_expr((yyvsp[(1) - (1)].intval));
      ;}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 593 "parser.y"
    {
          (yyval.expr) = create_float_literal_expr((double)(yyvsp[(1) - (1)].floatval));
      ;}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 597 "parser.y"
    {
          char *decoded = decode_string_literal((yyvsp[(1) - (1)].strval));
          free((yyvsp[(1) - (1)].strval));
          (yyval.expr) = create_string_literal_expr(decoded);
      ;}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 603 "parser.y"
    {
          char value = decode_char_literal((yyvsp[(1) - (1)].strval));
          free((yyvsp[(1) - (1)].strval));
          (yyval.expr) = create_char_literal_expr(value);
      ;}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 609 "parser.y"
    {
          (yyval.expr) = create_bool_literal_expr(1);
      ;}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 613 "parser.y"
    {
          (yyval.expr) = create_bool_literal_expr(0);
      ;}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 617 "parser.y"
    {
          (yyval.expr) = (yyvsp[(2) - (3)].expr);
      ;}
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 624 "parser.y"
    {
          (yyval.type) = TYPE_NUM;
      ;}
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 628 "parser.y"
    {
          (yyval.type) = TYPE_REAL;
      ;}
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 632 "parser.y"
    {
          (yyval.type) = TYPE_BIGREAL;
      ;}
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 636 "parser.y"
    {
          (yyval.type) = TYPE_CHR;
      ;}
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 640 "parser.y"
    {
          (yyval.type) = TYPE_LOGIC;
      ;}
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 644 "parser.y"
    {
          (yyval.type) = TYPE_TEXT;
      ;}
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 651 "parser.y"
    {
          (yyval.type) = (yyvsp[(1) - (1)].type);
      ;}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 655 "parser.y"
    {
          (yyval.type) = TYPE_EMPTY;
      ;}
    break;



/* Line 1455 of yacc.c  */
#line 2883 "parser.tab.c"
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
#line 660 "parser.y"


static int is_numeric_type(SymbolType type) {
    return type == TYPE_NUM || type == TYPE_REAL || type == TYPE_BIGREAL;
}

static int is_assignment_compatible(SymbolType target_type, SymbolType value_type) {
    if (value_type == TYPE_UNKNOWN) {
        return 1;
    }

    if (target_type == value_type) {
        return 1;
    }

    return (value_type == TYPE_NUM && target_type == TYPE_REAL) ||
           (value_type == TYPE_NUM && target_type == TYPE_BIGREAL) ||
           (value_type == TYPE_REAL && target_type == TYPE_BIGREAL);
}

static ExprNode *make_numeric_expr(const char *op_text, ExprNode *left, ExprNode *right) {
    SymbolType result_type_value;

    if (left->value_type == TYPE_INVALID || right->value_type == TYPE_INVALID) {
        return create_binary_expr(op_text, left, right, TYPE_INVALID);
    }

    if (strcmp(op_text, "%") == 0) {
        if (left->value_type != TYPE_NUM || right->value_type != TYPE_NUM) {
            fprintf(stderr, "Semantic error at line %d: modulus requires num operands.\n", yylineno);
            semantic_errors++;
            return create_binary_expr(op_text, left, right, TYPE_INVALID);
        }

        return create_binary_expr(op_text, left, right, TYPE_NUM);
    }

    result_type_value = result_type(left->value_type, right->value_type);
    if (result_type_value == TYPE_INVALID) {
        semantic_errors++;
    }

    return create_binary_expr(op_text, left, right, result_type_value);
}

static ExprNode *make_relational_expr(const char *op_text, ExprNode *left, ExprNode *right) {
    SymbolType left_type = left->value_type;
    SymbolType right_type = right->value_type;

    if (left_type == TYPE_INVALID || right_type == TYPE_INVALID) {
        return create_binary_expr(op_text, left, right, TYPE_INVALID);
    }

    if (left_type != TYPE_UNKNOWN && right_type != TYPE_UNKNOWN &&
        !((is_numeric_type(left_type) && is_numeric_type(right_type)) || left_type == right_type)) {
        fprintf(stderr,
                "Semantic error at line %d: operator '%s' cannot compare %s with %s.\n",
                yylineno,
                op_text,
                symbol_type_name(left_type),
                symbol_type_name(right_type));
        semantic_errors++;
        return create_binary_expr(op_text, left, right, TYPE_INVALID);
    }

    return create_binary_expr(op_text, left, right, TYPE_LOGIC);
}

static ExprNode *make_logic_expr(const char *op_text, ExprNode *left, ExprNode *right) {
    SymbolType result_type_value = TYPE_LOGIC;

    if (left->value_type == TYPE_INVALID || right->value_type == TYPE_INVALID) {
        return create_binary_expr(op_text, left, right, TYPE_INVALID);
    }

    if (strcmp(op_text, "XOR") == 0) {
        if (left->value_type == TYPE_LOGIC && right->value_type == TYPE_LOGIC) {
            result_type_value = TYPE_LOGIC;
        } else if (left->value_type == TYPE_NUM && right->value_type == TYPE_NUM) {
            result_type_value = TYPE_NUM;
        } else {
            fprintf(stderr,
                    "Semantic error at line %d: XOR requires either two logic operands or two num operands.\n",
                    yylineno);
            semantic_errors++;
            result_type_value = TYPE_INVALID;
        }
    } else if (left->value_type != TYPE_LOGIC || right->value_type != TYPE_LOGIC) {
        fprintf(stderr,
                "Semantic error at line %d: operator '%s' requires logic operands.\n",
                yylineno,
                op_text);
        semantic_errors++;
        result_type_value = TYPE_INVALID;
    }

    return create_binary_expr(op_text, left, right, result_type_value);
}

static ExprNode *make_unary_minus_expr(ExprNode *operand) {
    if (operand->value_type != TYPE_UNKNOWN &&
        operand->value_type != TYPE_INVALID &&
        !is_numeric_type(operand->value_type)) {
        fprintf(stderr, "Semantic error at line %d: unary '-' requires a numeric operand.\n", yylineno);
        semantic_errors++;
        return create_unary_expr("-", operand, TYPE_INVALID);
    }

    return create_unary_expr("-", operand, operand->value_type);
}

static ExprNode *make_not_expr(ExprNode *operand) {
    if (operand->value_type != TYPE_UNKNOWN &&
        operand->value_type != TYPE_INVALID &&
        operand->value_type != TYPE_LOGIC) {
        fprintf(stderr, "Semantic error at line %d: NOT requires a logic operand.\n", yylineno);
        semantic_errors++;
        return create_unary_expr("!", operand, TYPE_INVALID);
    }

    return create_unary_expr("!", operand, TYPE_LOGIC);
}

static ExprNode *make_abs_expr(ExprNode *operand) {
    if (operand->value_type != TYPE_UNKNOWN &&
        operand->value_type != TYPE_INVALID &&
        !is_numeric_type(operand->value_type)) {
        fprintf(stderr, "Semantic error at line %d: absolute value requires a numeric operand.\n", yylineno);
        semantic_errors++;
        return create_unary_expr("ABS", operand, TYPE_INVALID);
    }

    return create_unary_expr("ABS", operand, operand->value_type);
}

static int require_declared_identifier(const char *name, SymbolType *out_type) {
    SymbolType type = get_type(name);

    if (type == TYPE_INVALID) {
        semantic_errors++;
        if (out_type != NULL) {
            *out_type = TYPE_INVALID;
        }
        return 0;
    }

    if (out_type != NULL) {
        *out_type = type;
    }

    return 1;
}

static int declare_identifier(const char *name, SymbolType type) {
    if (!insert_symbol(name, type)) {
        semantic_errors++;
        return 0;
    }

    return 1;
}

static int validate_assignment(const char *name, SymbolType value_type) {
    if (value_type == TYPE_INVALID) {
        return 0;
    }

    if (!check_assignment(name, value_type)) {
        semantic_errors++;
        return 0;
    }

    return 1;
}

static void validate_logic_expression(SymbolType type, const char *context) {
    if (type == TYPE_INVALID || type == TYPE_UNKNOWN) {
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

static FunctionSignature *find_function_signature(const char *name) {
    FunctionSignature *current = function_signatures;

    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return current;
        }
        current = current->next;
    }

    return NULL;
}

static SymbolType builtin_unary_return_type(const char *name, ExprList *arguments) {
    if (arguments == NULL || arguments->next != NULL) {
        fprintf(stderr,
                "Semantic error at line %d: builtin '%s' expects one argument.\n",
                yylineno,
                name);
        semantic_errors++;
        return TYPE_INVALID;
    }

    if (!is_numeric_type(arguments->expr->value_type)) {
        fprintf(stderr,
                "Semantic error at line %d: builtin '%s' requires a numeric argument.\n",
                yylineno,
                name);
        semantic_errors++;
        return TYPE_INVALID;
    }

    return arguments->expr->value_type;
}

static SymbolType infer_function_call_type(const char *name, ExprList *arguments) {
    FunctionSignature *signature = find_function_signature(name);
    ExprList *current_argument = arguments;
    int index = 0;

    if (strcmp(name, "power") == 0) {
        if (arguments == NULL || arguments->next == NULL || arguments->next->next != NULL) {
            fprintf(stderr,
                    "Semantic error at line %d: builtin 'power' expects two arguments.\n",
                    yylineno);
            semantic_errors++;
            return TYPE_INVALID;
        }

        if (!is_numeric_type(arguments->expr->value_type) ||
            !is_numeric_type(arguments->next->expr->value_type)) {
            fprintf(stderr,
                    "Semantic error at line %d: builtin 'power' requires numeric arguments.\n",
                    yylineno);
            semantic_errors++;
            return TYPE_INVALID;
        }

        return result_type(arguments->expr->value_type, arguments->next->expr->value_type);
    }

    if (strcmp(name, "squart") == 0 || strcmp(name, "upper") == 0 ||
        strcmp(name, "lower") == 0 || strcmp(name, "log") == 0 ||
        strcmp(name, "sin") == 0 || strcmp(name, "cos") == 0 ||
        strcmp(name, "tan") == 0 || strcmp(name, "asin") == 0 ||
        strcmp(name, "acos") == 0 || strcmp(name, "atan") == 0) {
        return builtin_unary_return_type(name, arguments);
    }

    if (signature == NULL) {
        fprintf(stderr,
                "Semantic error at line %d: function '%s' is not defined.\n",
                yylineno,
                name);
        semantic_errors++;
        return TYPE_INVALID;
    }

    while (current_argument != NULL && index < signature->param_count) {
        if (!is_assignment_compatible(signature->param_types[index], current_argument->expr->value_type)) {
            fprintf(stderr,
                    "Semantic error at line %d: argument %d of function '%s' expects %s but found %s.\n",
                    yylineno,
                    index + 1,
                    name,
                    symbol_type_name(signature->param_types[index]),
                    symbol_type_name(current_argument->expr->value_type));
            semantic_errors++;
        }
        current_argument = current_argument->next;
        ++index;
    }

    if (current_argument != NULL || index != signature->param_count) {
        fprintf(stderr,
                "Semantic error at line %d: function '%s' called with the wrong number of arguments.\n",
                yylineno,
                name);
        semantic_errors++;
    }

    return signature->return_type;
}

static void begin_function_definition(char *name, ParamNode *parameters, SymbolType declared_return_type) {
    ParamNode *current = parameters;

    if (function_stack_top >= 64) {
        fprintf(stderr, "Semantic error: function nesting limit exceeded.\n");
        semantic_errors++;
        return;
    }

    function_name_stack[function_stack_top] = name;
    function_return_stack[function_stack_top] = TYPE_UNKNOWN;
    function_declared_return_stack[function_stack_top] = declared_return_type;
    ++function_stack_top;

    enter_scope();
    while (current != NULL) {
        declare_identifier(current->name, current->type);
        current = current->next;
    }
}

static SymbolType finish_function_definition(ParamNode *parameters) {
    FunctionSignature *signature;
    ParamNode *current;
    int index = 0;
    SymbolType observed_return_type;
    SymbolType declared_return_type;

    leave_scope();

    if (function_stack_top == 0) {
        return TYPE_UNKNOWN;
    }

    observed_return_type = function_return_stack[function_stack_top - 1];
    declared_return_type = function_declared_return_stack[function_stack_top - 1];

    if (declared_return_type == TYPE_EMPTY) {
        if (observed_return_type != TYPE_UNKNOWN) {
            fprintf(stderr,
                    "Semantic error at line %d: function '%s' is declared empty but sends a value.\n",
                    yylineno,
                    function_name_stack[function_stack_top - 1]);
            semantic_errors++;
        }
    } else if (observed_return_type == TYPE_UNKNOWN) {
        fprintf(stderr,
                "Semantic error at line %d: function '%s' must send a %s value.\n",
                yylineno,
                function_name_stack[function_stack_top - 1],
                symbol_type_name(declared_return_type));
        semantic_errors++;
    } else if (!is_assignment_compatible(declared_return_type, observed_return_type)) {
        fprintf(stderr,
                "Semantic error at line %d: function '%s' sends %s but is declared as %s.\n",
                yylineno,
                function_name_stack[function_stack_top - 1],
                symbol_type_name(observed_return_type),
                symbol_type_name(declared_return_type));
        semantic_errors++;
    }

    signature = find_function_signature(function_name_stack[function_stack_top - 1]);
    if (signature != NULL) {
        fprintf(stderr,
                "Semantic error at line %d: function '%s' is already defined.\n",
                yylineno,
                function_name_stack[function_stack_top - 1]);
        semantic_errors++;
    } else {
        signature = (FunctionSignature *)malloc(sizeof(FunctionSignature));
        if (signature != NULL) {
            strncpy(signature->name, function_name_stack[function_stack_top - 1], sizeof(signature->name) - 1);
            signature->name[sizeof(signature->name) - 1] = '\0';
            signature->param_count = 0;
            current = parameters;
            while (current != NULL && index < 32) {
                signature->param_types[index++] = current->type;
                current = current->next;
            }
            signature->param_count = index;
            signature->return_type = declared_return_type;
            signature->next = function_signatures;
            function_signatures = signature;
        }
    }

    --function_stack_top;
    return declared_return_type;
}

static void note_function_return(SymbolType type) {
    SymbolType *current_type;

    if (function_stack_top == 0) {
        return;
    }

    current_type = &function_return_stack[function_stack_top - 1];
    if (*current_type == TYPE_UNKNOWN) {
        *current_type = type;
        return;
    }

    if (*current_type == type) {
        return;
    }

    if (is_numeric_type(*current_type) && is_numeric_type(type)) {
        *current_type = result_type(*current_type, type);
        return;
    }

    fprintf(stderr,
            "Semantic error at line %d: inconsistent send types inside function '%s'.\n",
            yylineno,
            function_name_stack[function_stack_top - 1]);
    semantic_errors++;
}

void yyerror(const char *message) {
    const char *near_text = yytext;

    if (near_text == NULL || near_text[0] == '\0') {
        near_text = "end of input";
    }

    fprintf(stderr,
            "Syntax error at line %d near '%s': %s\n",
            yylineno,
            near_text,
            message);
}

