
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
     RETURN = 280,
     PLUS = 281,
     MINUS = 282,
     STAR = 283,
     SLASH = 284,
     ASSIGN = 285,
     EQ = 286,
     NEQ = 287,
     LT = 288,
     GT = 289,
     LE = 290,
     GE = 291,
     SEMICOLON = 292,
     COMMA = 293,
     LPAREN = 294,
     RPAREN = 295,
     LBRACE = 296,
     RBRACE = 297,
     ID = 298,
     STRING = 299,
     INT_LITERAL = 300,
     FLOAT_LITERAL = 301,
     UMINUS = 302
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
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



/* Line 1676 of yacc.c  */
#line 124 "parser.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


