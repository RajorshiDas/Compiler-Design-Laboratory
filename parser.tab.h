
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
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

/* "%code requires" blocks.  */

/* Line 1676 of yacc.c  */
#line 1 "parser.y"

#include "ast.h"



/* Line 1676 of yacc.c  */
#line 46 "parser.tab.h"

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

/* Line 1676 of yacc.c  */
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



/* Line 1676 of yacc.c  */
#line 136 "parser.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


