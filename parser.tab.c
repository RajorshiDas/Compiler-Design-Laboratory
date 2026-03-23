
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
static int function_stack_top = 0;

static int is_numeric_type(SymbolType type);
static int is_assignment_compatible(SymbolType target_type, SymbolType value_type);
static ExprNode *make_numeric_expr(const char *op_text, ExprNode *left, ExprNode *right);
static ExprNode *make_relational_expr(const char *op_text, ExprNode *left, ExprNode *right);
static ExprNode *make_unary_minus_expr(ExprNode *operand);
static int require_declared_identifier(const char *name, SymbolType *out_type);
static int declare_identifier(const char *name, SymbolType type);
static int validate_assignment(const char *name, SymbolType value_type);
static void validate_logic_expression(SymbolType type, const char *context);
static FunctionSignature *find_function_signature(const char *name);
static SymbolType lookup_function_return_type(const char *name);
static void validate_function_call(const char *name, ExprList *arguments);
static void begin_function_definition(char *name, ParamNode *parameters);
static SymbolType finish_function_definition(ParamNode *parameters);
static void note_function_return(SymbolType type);

int get_semantic_error_count(void) {
    return semantic_errors;
}


/* Line 189 of yacc.c  */
#line 125 "parser.tab.c"

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
#line 155 "parser.tab.c"

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
#line 58 "parser.y"

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
#line 232 "parser.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 244 "parser.tab.c"

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
#define YYLAST   198

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  47
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  33
/* YYNRULES -- Number of rules.  */
#define YYNRULES  84
/* YYNRULES -- Number of states.  */
#define YYNSTATES  162

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
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     6,     9,    12,    14,    16,    18,
      20,    22,    24,    26,    28,    30,    33,    36,    40,    42,
      44,    48,    54,    57,    58,    60,    62,    66,    69,    71,
      75,    80,    83,    87,    89,    93,    95,    99,   104,   110,
     114,   119,   125,   131,   137,   143,   151,   152,   155,   164,
     173,   175,   178,   183,   184,   188,   190,   194,   198,   202,
     206,   210,   214,   218,   222,   224,   228,   232,   234,   235,
     237,   239,   243,   245,   250,   252,   254,   256,   260,   263,
     265,   267,   269,   271,   273
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      48,     0,    -1,    49,    -1,    -1,    49,    51,    -1,     1,
      36,    -1,    60,    -1,    63,    -1,    64,    -1,    65,    -1,
      55,    -1,    66,    -1,    68,    -1,    69,    -1,    53,    -1,
      20,    36,    -1,    24,    36,    -1,    24,    74,    36,    -1,
      50,    -1,    40,    -1,    52,    49,    41,    -1,    13,    42,
      38,    56,    39,    -1,    54,    53,    -1,    -1,    57,    -1,
      58,    -1,    57,    37,    58,    -1,    79,    42,    -1,    79,
      -1,    59,    61,    36,    -1,     3,    59,    61,    36,    -1,
      59,    50,    -1,     3,    59,    50,    -1,    62,    -1,    61,
      37,    62,    -1,    42,    -1,    42,    29,    74,    -1,    42,
      29,    74,    36,    -1,     4,    42,    29,    74,    36,    -1,
      42,    29,    50,    -1,     4,    42,    29,    50,    -1,    11,
      38,    42,    39,    36,    -1,    11,    38,     1,    39,    36,
      -1,    12,    38,    74,    39,    36,    -1,    12,    38,     1,
      39,    36,    -1,    14,    38,    73,    39,    16,    53,    67,
      -1,    -1,    15,    53,    -1,    17,    19,    53,    18,    38,
      73,    39,    36,    -1,    21,    38,    74,    39,    40,    70,
      72,    41,    -1,    71,    -1,    70,    71,    -1,    22,    73,
      16,    53,    -1,    -1,    23,    16,    53,    -1,    74,    -1,
      74,    30,    74,    -1,    74,    31,    74,    -1,    74,    32,
      74,    -1,    74,    33,    74,    -1,    74,    34,    74,    -1,
      74,    35,    74,    -1,    74,    25,    75,    -1,    74,    26,
      75,    -1,    75,    -1,    75,    27,    78,    -1,    75,    28,
      78,    -1,    78,    -1,    -1,    77,    -1,    74,    -1,    77,
      37,    74,    -1,    42,    -1,    42,    38,    76,    39,    -1,
      44,    -1,    45,    -1,    43,    -1,    38,    74,    39,    -1,
      26,    78,    -1,     5,    -1,     6,    -1,     7,    -1,     8,
      -1,     9,    -1,    10,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   101,   101,   109,   112,   119,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   140,   144,   154,   162,
     169,   177,   185,   195,   198,   205,   209,   216,   223,   230,
     234,   238,   243,   251,   255,   262,   267,   277,   282,   287,
     293,   302,   307,   316,   320,   329,   338,   341,   348,   356,
     363,   367,   374,   383,   386,   393,   397,   401,   405,   409,
     413,   417,   424,   428,   432,   439,   443,   447,   455,   458,
     465,   469,   476,   483,   488,   492,   496,   502,   506,   513,
     517,   521,   525,   529,   533
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
  "sync_semi", "statement", "block_open", "block", "function_header",
  "function_definition", "parameter_list_opt", "parameter_list",
  "parameter", "declaration_head", "declaration", "id_list", "id_item",
  "assignment_statement", "read_statement", "write_statement",
  "chk_statement", "else_part", "repeat_statement", "decide_statement",
  "when_clause_list", "when_clause", "otherwise_clause_opt", "condition",
  "expression", "term", "argument_list_opt", "argument_list", "factor",
  "type_specifier", 0
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
      51,    51,    51,    51,    51,    51,    51,    51,    51,    52,
      53,    54,    55,    56,    56,    57,    57,    58,    59,    60,
      60,    60,    60,    61,    61,    62,    62,    63,    63,    63,
      63,    64,    64,    65,    65,    66,    67,    67,    68,    69,
      70,    70,    71,    72,    72,    73,    73,    73,    73,    73,
      73,    73,    74,    74,    74,    75,    75,    75,    76,    76,
      77,    77,    78,    78,    78,    78,    78,    78,    78,    79,
      79,    79,    79,    79,    79
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     2,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     2,     3,     1,     1,
       3,     5,     2,     0,     1,     1,     3,     2,     1,     3,
       4,     2,     3,     1,     3,     1,     3,     4,     5,     3,
       4,     5,     5,     5,     5,     7,     0,     2,     8,     8,
       1,     2,     4,     0,     3,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     1,     3,     3,     1,     0,     1,
       1,     3,     1,     4,     1,     1,     1,     3,     2,     1,
       1,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     0,     1,     0,     0,     0,    79,    80,    81,
      82,    83,    84,     0,     0,     0,     0,     0,     0,     0,
       0,    19,     0,    18,     4,     3,    14,     0,    10,     0,
       6,     7,     8,     9,    11,    12,    13,    28,     5,     0,
       0,     0,     0,     0,     0,     0,    15,     0,     0,    16,
       0,    72,    76,    74,    75,     0,    64,    67,     0,     0,
      22,    35,    31,     0,    33,    32,     0,     0,     0,     0,
       0,     0,    23,     0,    55,     0,     0,    78,     0,    68,
       0,     0,    17,     0,     0,    39,     0,    20,     0,    29,
       0,    30,    40,     0,     0,     0,     0,     0,     0,    24,
      25,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    77,    70,     0,    69,    62,    63,    65,    66,    37,
      36,    34,    38,    42,    41,    44,    43,    21,     0,    27,
       0,    56,    57,    58,    59,    60,    61,     0,     0,    73,
       0,    26,    46,     0,     0,    53,    50,    71,     0,    45,
       0,     0,     0,    51,     0,    47,    48,     0,     0,    49,
      52,    54
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    23,    24,    25,    26,    27,    28,    98,
      99,   100,    29,    30,    63,    64,    31,    32,    33,    34,
     149,    35,    36,   145,   146,   154,    73,    74,    56,   113,
     114,    57,    37
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -130
static const yytype_int16 yypact[] =
{
    -130,     5,   132,  -130,   -29,    91,   -21,  -130,  -130,  -130,
    -130,  -130,  -130,   -15,   -10,   -16,    -5,    24,    20,    22,
      36,  -130,    29,  -130,  -130,  -130,  -130,    33,  -130,     2,
    -130,  -130,  -130,  -130,  -130,  -130,  -130,  -130,  -130,     2,
      40,     3,     8,    46,    -7,    33,  -130,    -7,    -7,  -130,
      -7,    72,  -130,  -130,  -130,    57,    27,  -130,    21,   156,
    -130,    42,  -130,    31,  -130,  -130,    39,    21,    38,    65,
      80,   -14,    91,    86,    81,   102,   -12,  -130,    -9,    -7,
      -7,    -7,  -130,    -7,    -7,  -130,    66,  -130,    -7,  -130,
      84,  -130,  -130,    69,    92,    93,    98,   111,    88,   113,
    -130,   106,   135,    -7,    -7,    -7,    -7,    -7,    -7,   116,
     115,  -130,    83,   119,   134,    27,    27,  -130,  -130,  -130,
      83,  -130,  -130,  -130,  -130,  -130,  -130,  -130,    91,  -130,
      33,    83,    83,    83,    83,    83,    83,    -7,   153,  -130,
      -7,  -130,   163,   140,    -7,    95,  -130,    83,    33,  -130,
     145,   166,   167,  -130,   143,  -130,  -130,    33,    33,  -130,
    -130,  -130
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -130,  -130,   160,   -19,  -130,  -130,   -27,  -130,  -130,  -130,
    -130,    58,   182,  -130,   149,    99,  -130,  -130,  -130,  -130,
    -130,  -130,  -130,  -130,    45,  -130,  -129,   -18,    43,  -130,
    -130,   -42,   -71
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -3
static const yytype_int16 yytable[] =
{
      60,   101,    55,     4,    68,     3,    77,    38,   143,    70,
      62,    80,    81,    80,    81,   151,    80,    81,    75,    48,
      65,    40,     4,    41,    71,    97,    43,   110,    42,    76,
     111,    50,    78,    44,    48,    51,    52,    53,    54,    85,
      86,   117,   118,    45,    61,    69,    50,    48,    92,    93,
      51,    52,    53,    54,    83,    84,    46,   101,    58,    50,
      47,   112,    48,    51,    52,    53,    54,    89,    90,    67,
     120,    88,    49,    21,    50,    91,    90,    94,    51,    52,
      53,    54,    80,    81,    72,   131,   132,   133,   134,   135,
     136,    80,    81,    82,    80,    81,     7,     8,     9,    10,
      11,    12,   119,   142,    95,   122,    80,    81,    80,    81,
      79,   103,   104,   105,   106,   107,   108,   144,   152,    96,
     109,   155,   147,   115,   116,   102,    61,   127,   123,   124,
     160,   161,    -2,     4,   125,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,   126,   129,    17,
     128,   130,    18,    19,   137,   138,    20,     4,   139,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,   140,    21,    17,    22,   144,    18,    19,   148,   150,
      20,   156,   157,   158,   159,    59,   141,    39,    66,   121,
     153,     0,     0,     0,     0,     0,    21,    87,    22
};

static const yytype_int16 yycheck[] =
{
      27,    72,    20,     1,     1,     0,    48,    36,   137,     1,
      29,    25,    26,    25,    26,   144,    25,    26,    45,    26,
      39,    42,     1,    38,    42,    39,    42,    39,    38,    47,
      39,    38,    50,    38,    26,    42,    43,    44,    45,    58,
      58,    83,    84,    19,    42,    42,    38,    26,    67,    67,
      42,    43,    44,    45,    27,    28,    36,   128,    29,    38,
      38,    79,    26,    42,    43,    44,    45,    36,    37,    29,
      88,    29,    36,    40,    38,    36,    37,    39,    42,    43,
      44,    45,    25,    26,    38,   103,   104,   105,   106,   107,
     108,    25,    26,    36,    25,    26,     5,     6,     7,     8,
       9,    10,    36,   130,    39,    36,    25,    26,    25,    26,
      38,    30,    31,    32,    33,    34,    35,    22,    23,    39,
      18,   148,   140,    80,    81,    39,    42,    39,    36,    36,
     157,   158,     0,     1,    36,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    36,    42,    17,
      37,    16,    20,    21,    38,    40,    24,     1,    39,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    37,    40,    17,    42,    22,    20,    21,    15,    39,
      24,    36,    16,    16,    41,    25,   128,     5,    39,    90,
     145,    -1,    -1,    -1,    -1,    -1,    40,    41,    42
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    48,    49,     0,     1,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    17,    20,    21,
      24,    40,    42,    50,    51,    52,    53,    54,    55,    59,
      60,    63,    64,    65,    66,    68,    69,    79,    36,    59,
      42,    38,    38,    42,    38,    19,    36,    38,    26,    36,
      38,    42,    43,    44,    45,    74,    75,    78,    29,    49,
      53,    42,    50,    61,    62,    50,    61,    29,     1,    42,
       1,    74,    38,    73,    74,    53,    74,    78,    74,    38,
      25,    26,    36,    27,    28,    50,    74,    41,    29,    36,
      37,    36,    50,    74,    39,    39,    39,    39,    56,    57,
      58,    79,    39,    30,    31,    32,    33,    34,    35,    18,
      39,    39,    74,    76,    77,    75,    75,    78,    78,    36,
      74,    62,    36,    36,    36,    36,    36,    39,    37,    42,
      16,    74,    74,    74,    74,    74,    74,    38,    40,    39,
      37,    58,    53,    73,    22,    70,    71,    74,    15,    67,
      39,    73,    23,    71,    72,    53,    36,    16,    16,    41,
      53,    53
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
      case 42: /* "ID" */

/* Line 1000 of yacc.c  */
#line 84 "parser.y"
	{ free((yyvaluep->strval)); };

/* Line 1000 of yacc.c  */
#line 1298 "parser.tab.c"
	break;
      case 43: /* "STRING" */

/* Line 1000 of yacc.c  */
#line 84 "parser.y"
	{ free((yyvaluep->strval)); };

/* Line 1000 of yacc.c  */
#line 1307 "parser.tab.c"
	break;
      case 49: /* "statement_list" */

/* Line 1000 of yacc.c  */
#line 86 "parser.y"
	{ free_statement_list((yyvaluep->stmt)); };

/* Line 1000 of yacc.c  */
#line 1316 "parser.tab.c"
	break;
      case 50: /* "sync_semi" */

/* Line 1000 of yacc.c  */
#line 86 "parser.y"
	{ free_statement_list((yyvaluep->stmt)); };

/* Line 1000 of yacc.c  */
#line 1325 "parser.tab.c"
	break;
      case 51: /* "statement" */

/* Line 1000 of yacc.c  */
#line 86 "parser.y"
	{ free_statement_list((yyvaluep->stmt)); };

/* Line 1000 of yacc.c  */
#line 1334 "parser.tab.c"
	break;
      case 53: /* "block" */

/* Line 1000 of yacc.c  */
#line 86 "parser.y"
	{ free_statement_list((yyvaluep->stmt)); };

/* Line 1000 of yacc.c  */
#line 1343 "parser.tab.c"
	break;
      case 54: /* "function_header" */

/* Line 1000 of yacc.c  */
#line 87 "parser.y"
	{ free_param_list((yyvaluep->param)); };

/* Line 1000 of yacc.c  */
#line 1352 "parser.tab.c"
	break;
      case 55: /* "function_definition" */

/* Line 1000 of yacc.c  */
#line 86 "parser.y"
	{ free_statement_list((yyvaluep->stmt)); };

/* Line 1000 of yacc.c  */
#line 1361 "parser.tab.c"
	break;
      case 56: /* "parameter_list_opt" */

/* Line 1000 of yacc.c  */
#line 87 "parser.y"
	{ free_param_list((yyvaluep->param)); };

/* Line 1000 of yacc.c  */
#line 1370 "parser.tab.c"
	break;
      case 57: /* "parameter_list" */

/* Line 1000 of yacc.c  */
#line 87 "parser.y"
	{ free_param_list((yyvaluep->param)); };

/* Line 1000 of yacc.c  */
#line 1379 "parser.tab.c"
	break;
      case 58: /* "parameter" */

/* Line 1000 of yacc.c  */
#line 87 "parser.y"
	{ free_param_list((yyvaluep->param)); };

/* Line 1000 of yacc.c  */
#line 1388 "parser.tab.c"
	break;
      case 60: /* "declaration" */

/* Line 1000 of yacc.c  */
#line 86 "parser.y"
	{ free_statement_list((yyvaluep->stmt)); };

/* Line 1000 of yacc.c  */
#line 1397 "parser.tab.c"
	break;
      case 61: /* "id_list" */

/* Line 1000 of yacc.c  */
#line 86 "parser.y"
	{ free_statement_list((yyvaluep->stmt)); };

/* Line 1000 of yacc.c  */
#line 1406 "parser.tab.c"
	break;
      case 62: /* "id_item" */

/* Line 1000 of yacc.c  */
#line 86 "parser.y"
	{ free_statement_list((yyvaluep->stmt)); };

/* Line 1000 of yacc.c  */
#line 1415 "parser.tab.c"
	break;
      case 63: /* "assignment_statement" */

/* Line 1000 of yacc.c  */
#line 86 "parser.y"
	{ free_statement_list((yyvaluep->stmt)); };

/* Line 1000 of yacc.c  */
#line 1424 "parser.tab.c"
	break;
      case 64: /* "read_statement" */

/* Line 1000 of yacc.c  */
#line 86 "parser.y"
	{ free_statement_list((yyvaluep->stmt)); };

/* Line 1000 of yacc.c  */
#line 1433 "parser.tab.c"
	break;
      case 65: /* "write_statement" */

/* Line 1000 of yacc.c  */
#line 86 "parser.y"
	{ free_statement_list((yyvaluep->stmt)); };

/* Line 1000 of yacc.c  */
#line 1442 "parser.tab.c"
	break;
      case 66: /* "chk_statement" */

/* Line 1000 of yacc.c  */
#line 86 "parser.y"
	{ free_statement_list((yyvaluep->stmt)); };

/* Line 1000 of yacc.c  */
#line 1451 "parser.tab.c"
	break;
      case 67: /* "else_part" */

/* Line 1000 of yacc.c  */
#line 86 "parser.y"
	{ free_statement_list((yyvaluep->stmt)); };

/* Line 1000 of yacc.c  */
#line 1460 "parser.tab.c"
	break;
      case 68: /* "repeat_statement" */

/* Line 1000 of yacc.c  */
#line 86 "parser.y"
	{ free_statement_list((yyvaluep->stmt)); };

/* Line 1000 of yacc.c  */
#line 1469 "parser.tab.c"
	break;
      case 69: /* "decide_statement" */

/* Line 1000 of yacc.c  */
#line 86 "parser.y"
	{ free_statement_list((yyvaluep->stmt)); };

/* Line 1000 of yacc.c  */
#line 1478 "parser.tab.c"
	break;
      case 70: /* "when_clause_list" */

/* Line 1000 of yacc.c  */
#line 89 "parser.y"
	{ free_case_list((yyvaluep->caseclause)); };

/* Line 1000 of yacc.c  */
#line 1487 "parser.tab.c"
	break;
      case 71: /* "when_clause" */

/* Line 1000 of yacc.c  */
#line 89 "parser.y"
	{ free_case_list((yyvaluep->caseclause)); };

/* Line 1000 of yacc.c  */
#line 1496 "parser.tab.c"
	break;
      case 72: /* "otherwise_clause_opt" */

/* Line 1000 of yacc.c  */
#line 86 "parser.y"
	{ free_statement_list((yyvaluep->stmt)); };

/* Line 1000 of yacc.c  */
#line 1505 "parser.tab.c"
	break;
      case 73: /* "condition" */

/* Line 1000 of yacc.c  */
#line 85 "parser.y"
	{ free_expr((yyvaluep->expr)); };

/* Line 1000 of yacc.c  */
#line 1514 "parser.tab.c"
	break;
      case 74: /* "expression" */

/* Line 1000 of yacc.c  */
#line 85 "parser.y"
	{ free_expr((yyvaluep->expr)); };

/* Line 1000 of yacc.c  */
#line 1523 "parser.tab.c"
	break;
      case 75: /* "term" */

/* Line 1000 of yacc.c  */
#line 85 "parser.y"
	{ free_expr((yyvaluep->expr)); };

/* Line 1000 of yacc.c  */
#line 1532 "parser.tab.c"
	break;
      case 76: /* "argument_list_opt" */

/* Line 1000 of yacc.c  */
#line 88 "parser.y"
	{ free_expr_list((yyvaluep->arglist)); };

/* Line 1000 of yacc.c  */
#line 1541 "parser.tab.c"
	break;
      case 77: /* "argument_list" */

/* Line 1000 of yacc.c  */
#line 88 "parser.y"
	{ free_expr_list((yyvaluep->arglist)); };

/* Line 1000 of yacc.c  */
#line 1550 "parser.tab.c"
	break;
      case 78: /* "factor" */

/* Line 1000 of yacc.c  */
#line 85 "parser.y"
	{ free_expr((yyvaluep->expr)); };

/* Line 1000 of yacc.c  */
#line 1559 "parser.tab.c"
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
        case 2:

/* Line 1455 of yacc.c  */
#line 102 "parser.y"
    {
          parsed_program = create_program((yyvsp[(1) - (1)].stmt));
      ;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 109 "parser.y"
    {
          (yyval.stmt) = NULL;
      ;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 113 "parser.y"
    {
          (yyval.stmt) = append_statement((yyvsp[(1) - (2)].stmt), (yyvsp[(2) - (2)].stmt));
      ;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 120 "parser.y"
    {
          yyerrok;
          (yyval.stmt) = NULL;
      ;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 137 "parser.y"
    {
          (yyval.stmt) = create_skip_stmt();
      ;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 141 "parser.y"
    {
          (yyval.stmt) = create_stop_stmt();
      ;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 145 "parser.y"
    {
          if (function_stack_top == 0) {
              fprintf(stderr, "Semantic error at line %d: 'stop <expr>;' is only valid inside a function.\n", yylineno);
              semantic_errors++;
          } else {
              note_function_return(((yyvsp[(2) - (3)].expr))->value_type);
          }
          (yyval.stmt) = create_return_stmt((yyvsp[(2) - (3)].expr));
      ;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 155 "parser.y"
    {
          yyerror("invalid statement skipped");
          (yyval.stmt) = NULL;
      ;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 163 "parser.y"
    {
          enter_scope();
      ;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 170 "parser.y"
    {
          leave_scope();
          (yyval.stmt) = create_block_stmt((yyvsp[(2) - (3)].stmt));
      ;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 178 "parser.y"
    {
          begin_function_definition((yyvsp[(2) - (5)].strval), (yyvsp[(4) - (5)].param));
          (yyval.param) = (yyvsp[(4) - (5)].param);
      ;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 186 "parser.y"
    {
          char *function_name = function_name_stack[function_stack_top - 1];
          SymbolType return_type = finish_function_definition((yyvsp[(1) - (2)].param));
          (yyval.stmt) = create_function_def_stmt(function_name, (yyvsp[(1) - (2)].param), (yyvsp[(2) - (2)].stmt), return_type);
      ;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 195 "parser.y"
    {
          (yyval.param) = NULL;
      ;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 199 "parser.y"
    {
          (yyval.param) = (yyvsp[(1) - (1)].param);
      ;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 206 "parser.y"
    {
          (yyval.param) = (yyvsp[(1) - (1)].param);
      ;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 210 "parser.y"
    {
          (yyval.param) = append_param_list((yyvsp[(1) - (3)].param), (yyvsp[(3) - (3)].param));
      ;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 217 "parser.y"
    {
          (yyval.param) = create_param_node((SymbolType)(yyvsp[(1) - (2)].type), (yyvsp[(2) - (2)].strval));
      ;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 224 "parser.y"
    {
          current_decl_type = (SymbolType)(yyvsp[(1) - (1)].type);
      ;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 231 "parser.y"
    {
          (yyval.stmt) = (yyvsp[(2) - (3)].stmt);
      ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 235 "parser.y"
    {
          (yyval.stmt) = (yyvsp[(3) - (4)].stmt);
      ;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 239 "parser.y"
    {
          yyerror("invalid declaration");
          (yyval.stmt) = NULL;
      ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 244 "parser.y"
    {
          yyerror("invalid declaration");
          (yyval.stmt) = NULL;
      ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 252 "parser.y"
    {
          (yyval.stmt) = (yyvsp[(1) - (1)].stmt);
      ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 256 "parser.y"
    {
          (yyval.stmt) = append_statement((yyvsp[(1) - (3)].stmt), (yyvsp[(3) - (3)].stmt));
      ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 263 "parser.y"
    {
          declare_identifier((yyvsp[(1) - (1)].strval), current_decl_type);
          (yyval.stmt) = create_declaration_stmt(current_decl_type, (yyvsp[(1) - (1)].strval), NULL);
      ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 268 "parser.y"
    {
          if (declare_identifier((yyvsp[(1) - (3)].strval), current_decl_type)) {
              validate_assignment((yyvsp[(1) - (3)].strval), ((yyvsp[(3) - (3)].expr))->value_type);
          }
          (yyval.stmt) = create_declaration_stmt(current_decl_type, (yyvsp[(1) - (3)].strval), (yyvsp[(3) - (3)].expr));
      ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 278 "parser.y"
    {
          validate_assignment((yyvsp[(1) - (4)].strval), ((yyvsp[(3) - (4)].expr))->value_type);
          (yyval.stmt) = create_assignment_stmt((yyvsp[(1) - (4)].strval), (yyvsp[(3) - (4)].expr));
      ;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 283 "parser.y"
    {
          validate_assignment((yyvsp[(2) - (5)].strval), ((yyvsp[(4) - (5)].expr))->value_type);
          (yyval.stmt) = create_assignment_stmt((yyvsp[(2) - (5)].strval), (yyvsp[(4) - (5)].expr));
      ;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 288 "parser.y"
    {
          yyerror("invalid assignment expression");
          free((yyvsp[(1) - (3)].strval));
          (yyval.stmt) = NULL;
      ;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 294 "parser.y"
    {
          yyerror("invalid assignment expression");
          free((yyvsp[(2) - (4)].strval));
          (yyval.stmt) = NULL;
      ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 303 "parser.y"
    {
          require_declared_identifier((yyvsp[(3) - (5)].strval), NULL);
          (yyval.stmt) = create_read_stmt((yyvsp[(3) - (5)].strval));
      ;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 308 "parser.y"
    {
          yyerror("invalid read statement");
          yyerrok;
          (yyval.stmt) = NULL;
      ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 317 "parser.y"
    {
          (yyval.stmt) = create_write_stmt((yyvsp[(3) - (5)].expr));
      ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 321 "parser.y"
    {
          yyerror("invalid write statement");
          yyerrok;
          (yyval.stmt) = NULL;
      ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 330 "parser.y"
    {
          validate_logic_expression(((yyvsp[(3) - (7)].expr))->value_type, "chk");
          (yyval.stmt) = create_chk_stmt((yyvsp[(3) - (7)].expr), (yyvsp[(6) - (7)].stmt), (yyvsp[(7) - (7)].stmt));
      ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 338 "parser.y"
    {
          (yyval.stmt) = NULL;
      ;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 342 "parser.y"
    {
          (yyval.stmt) = (yyvsp[(2) - (2)].stmt);
      ;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 349 "parser.y"
    {
          validate_logic_expression(((yyvsp[(6) - (8)].expr))->value_type, "repeat-until");
          (yyval.stmt) = create_repeat_stmt((yyvsp[(3) - (8)].stmt), (yyvsp[(6) - (8)].expr));
      ;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 357 "parser.y"
    {
          (yyval.stmt) = create_decide_stmt((yyvsp[(3) - (8)].expr), (yyvsp[(6) - (8)].caseclause), (yyvsp[(7) - (8)].stmt));
      ;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 364 "parser.y"
    {
          (yyval.caseclause) = (yyvsp[(1) - (1)].caseclause);
      ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 368 "parser.y"
    {
          (yyval.caseclause) = append_case_list((yyvsp[(1) - (2)].caseclause), (yyvsp[(2) - (2)].caseclause));
      ;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 375 "parser.y"
    {
          validate_logic_expression(((yyvsp[(2) - (4)].expr))->value_type, "when");
          (yyval.caseclause) = create_case_node((yyvsp[(2) - (4)].expr), (yyvsp[(4) - (4)].stmt));
      ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 383 "parser.y"
    {
          (yyval.stmt) = NULL;
      ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 387 "parser.y"
    {
          (yyval.stmt) = (yyvsp[(3) - (3)].stmt);
      ;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 394 "parser.y"
    {
          (yyval.expr) = (yyvsp[(1) - (1)].expr);
      ;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 398 "parser.y"
    {
          (yyval.expr) = make_relational_expr("==", (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));
      ;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 402 "parser.y"
    {
          (yyval.expr) = make_relational_expr("!=", (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));
      ;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 406 "parser.y"
    {
          (yyval.expr) = make_relational_expr("<", (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));
      ;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 410 "parser.y"
    {
          (yyval.expr) = make_relational_expr(">", (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));
      ;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 414 "parser.y"
    {
          (yyval.expr) = make_relational_expr("<=", (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));
      ;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 418 "parser.y"
    {
          (yyval.expr) = make_relational_expr(">=", (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));
      ;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 425 "parser.y"
    {
          (yyval.expr) = make_numeric_expr("+", (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));
      ;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 429 "parser.y"
    {
          (yyval.expr) = make_numeric_expr("-", (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));
      ;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 433 "parser.y"
    {
          (yyval.expr) = (yyvsp[(1) - (1)].expr);
      ;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 440 "parser.y"
    {
          (yyval.expr) = make_numeric_expr("*", (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));
      ;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 444 "parser.y"
    {
          (yyval.expr) = make_numeric_expr("/", (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));
      ;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 448 "parser.y"
    {
          (yyval.expr) = (yyvsp[(1) - (1)].expr);
      ;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 455 "parser.y"
    {
          (yyval.arglist) = NULL;
      ;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 459 "parser.y"
    {
          (yyval.arglist) = (yyvsp[(1) - (1)].arglist);
      ;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 466 "parser.y"
    {
          (yyval.arglist) = create_expr_list((yyvsp[(1) - (1)].expr));
      ;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 470 "parser.y"
    {
          (yyval.arglist) = append_expr_list((yyvsp[(1) - (3)].arglist), create_expr_list((yyvsp[(3) - (3)].expr)));
      ;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 477 "parser.y"
    {
          SymbolType type;

          require_declared_identifier((yyvsp[(1) - (1)].strval), &type);
          (yyval.expr) = create_variable_expr((yyvsp[(1) - (1)].strval), type);
      ;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 484 "parser.y"
    {
          validate_function_call((yyvsp[(1) - (4)].strval), (yyvsp[(3) - (4)].arglist));
          (yyval.expr) = create_function_call_expr((yyvsp[(1) - (4)].strval), (yyvsp[(3) - (4)].arglist), lookup_function_return_type((yyvsp[(1) - (4)].strval)));
      ;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 489 "parser.y"
    {
          (yyval.expr) = create_int_literal_expr((yyvsp[(1) - (1)].intval));
      ;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 493 "parser.y"
    {
          (yyval.expr) = create_float_literal_expr((double)(yyvsp[(1) - (1)].floatval));
      ;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 497 "parser.y"
    {
          char *decoded = decode_string_literal((yyvsp[(1) - (1)].strval));
          free((yyvsp[(1) - (1)].strval));
          (yyval.expr) = create_string_literal_expr(decoded);
      ;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 503 "parser.y"
    {
          (yyval.expr) = (yyvsp[(2) - (3)].expr);
      ;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 507 "parser.y"
    {
          (yyval.expr) = make_unary_minus_expr((yyvsp[(2) - (2)].expr));
      ;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 514 "parser.y"
    {
          (yyval.type) = TYPE_NUM;
      ;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 518 "parser.y"
    {
          (yyval.type) = TYPE_REAL;
      ;}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 522 "parser.y"
    {
          (yyval.type) = TYPE_BIGREAL;
      ;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 526 "parser.y"
    {
          (yyval.type) = TYPE_CHR;
      ;}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 530 "parser.y"
    {
          (yyval.type) = TYPE_LOGIC;
      ;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 534 "parser.y"
    {
          (yyval.type) = TYPE_TEXT;
      ;}
    break;



/* Line 1455 of yacc.c  */
#line 2568 "parser.tab.c"
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
#line 539 "parser.y"


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

static SymbolType lookup_function_return_type(const char *name) {
    FunctionSignature *signature = find_function_signature(name);

    if (signature == NULL) {
        return TYPE_UNKNOWN;
    }

    return signature->return_type;
}

static void validate_function_call(const char *name, ExprList *arguments) {
    FunctionSignature *signature = find_function_signature(name);
    ExprList *current_argument = arguments;
    int index = 0;

    if (signature == NULL) {
        return;
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
}

static void begin_function_definition(char *name, ParamNode *parameters) {
    ParamNode *current = parameters;

    if (function_stack_top >= 64) {
        fprintf(stderr, "Semantic error: function nesting limit exceeded.\n");
        semantic_errors++;
        return;
    }

    function_name_stack[function_stack_top] = name;
    function_return_stack[function_stack_top] = TYPE_UNKNOWN;
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
    SymbolType return_type;

    leave_scope();

    if (function_stack_top == 0) {
        return TYPE_UNKNOWN;
    }

    return_type = function_return_stack[function_stack_top - 1];
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
            signature->return_type = return_type;
            signature->next = function_signatures;
            function_signatures = signature;
        }
    }

    --function_stack_top;
    return return_type;
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
            "Semantic error at line %d: inconsistent return types inside function '%s'.\n",
            yylineno,
            function_name_stack[function_stack_top - 1]);
    semantic_errors++;
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

