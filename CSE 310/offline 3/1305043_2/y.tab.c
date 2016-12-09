/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 2 "1305043.y" /* yacc.c:339  */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <string>
#include"1305043_symbolTable.cpp"
      /* yyparse() stack type */
using namespace std;


extern FILE* yyin;
SymbolTable *myTable;
SymbolInfo*declaredInfo[1000];
FILE* logFile;
SymbolInfo *spc;

int line_count=1;
int error_count=0;
int var_count=0;
int label_count=0;
int temp_count=0;


stringstream tl;
ofstream codetracker;



string newLabel()
{
	string lbl="L";
	tl.str("");
	tl<<label_count;
	lbl+=tl.str();
	label_count++;
	return lbl;
}

string newTemp()
{
	string tmp="t";
	tl.str("");
	tl<<temp_count;
	tmp+=tl.str();
	temp_count++;
	return tmp;
}





bool err;
int ii;
int marker;


void printError(string s)
{
	
	fprintf(logFile,"Error at line no: %d--%s\n\n\n\n",line_count,s.c_str());

}


void yyerror(const char *s){
	printf("Error at line no: %d--%s\n",line_count,s);
}

int yylex(void);




SymbolInfo* findInDeclaration(string name)
{
	for(int i=0;i<var_count;i++)if(name==declaredInfo[i]->getName()){
		return declaredInfo[i];
	}
	return 0;
}



void printNOW(string line)
{
	fprintf(logFile,"%s",line.c_str());
	fprintf(logFile,"\n\n\n\n");
	codetracker<<line<<"\n";
}


#line 159 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    IF = 258,
    ELSE = 259,
    FOR = 260,
    WHILE = 261,
    DO = 262,
    BREAK = 263,
    INT = 264,
    CHAR = 265,
    FLOAT = 266,
    DOUBLE = 267,
    VOID = 268,
    RETURN = 269,
    SWITCH = 270,
    CASE = 271,
    DEFAULT = 272,
    CONTINUE = 273,
    MAIN = 274,
    PRINTLN = 275,
    CONST_INT = 276,
    CONST_FLOAT = 277,
    CONST_CHAR = 278,
    ADDOP = 279,
    INCOP = 280,
    DECOP = 281,
    MULOP = 282,
    RELOP = 283,
    ASSIGNOP = 284,
    LOGICOP = 285,
    LPAREN = 286,
    RPAREN = 287,
    LCURL = 288,
    RCURL = 289,
    LTHIRD = 290,
    RTHIRD = 291,
    COMMA = 292,
    SEMICOLON = 293,
    STRING = 294,
    NOT = 295,
    ID = 296,
    HELP_ELSE_GET_PRECEDENCE = 297
  };
#endif
/* Tokens.  */
#define IF 258
#define ELSE 259
#define FOR 260
#define WHILE 261
#define DO 262
#define BREAK 263
#define INT 264
#define CHAR 265
#define FLOAT 266
#define DOUBLE 267
#define VOID 268
#define RETURN 269
#define SWITCH 270
#define CASE 271
#define DEFAULT 272
#define CONTINUE 273
#define MAIN 274
#define PRINTLN 275
#define CONST_INT 276
#define CONST_FLOAT 277
#define CONST_CHAR 278
#define ADDOP 279
#define INCOP 280
#define DECOP 281
#define MULOP 282
#define RELOP 283
#define ASSIGNOP 284
#define LOGICOP 285
#define LPAREN 286
#define RPAREN 287
#define LCURL 288
#define RCURL 289
#define LTHIRD 290
#define RTHIRD 291
#define COMMA 292
#define SEMICOLON 293
#define STRING 294
#define NOT 295
#define ID 296
#define HELP_ELSE_GET_PRECEDENCE 297

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 95 "1305043.y" /* yacc.c:355  */

	SymbolInfo* idInfo;
	SymbolInfo* helpInfo;
	const char* helpString;

#line 289 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 306 "y.tab.c" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
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
#define YYLAST   196

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  43
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  17
/* YYNRULES -- Number of rules.  */
#define YYNRULES  48
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  101

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   297

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
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
      35,    36,    37,    38,    39,    40,    41,    42
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   133,   133,   160,   180,   189,   200,   217,   238,   244,
     251,   261,   310,   375,   434,   504,   513,   530,   537,   545,
     556,   575,   597,   606,   644,   662,   672,   685,   722,   772,
     781,   897,   907,   994,  1003,  1100,  1108,  1226,  1235,  1365,
    1406,  1447,  1465,  1537,  1546,  1556,  1566,  1576,  1641
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IF", "ELSE", "FOR", "WHILE", "DO",
  "BREAK", "INT", "CHAR", "FLOAT", "DOUBLE", "VOID", "RETURN", "SWITCH",
  "CASE", "DEFAULT", "CONTINUE", "MAIN", "PRINTLN", "CONST_INT",
  "CONST_FLOAT", "CONST_CHAR", "ADDOP", "INCOP", "DECOP", "MULOP", "RELOP",
  "ASSIGNOP", "LOGICOP", "LPAREN", "RPAREN", "LCURL", "RCURL", "LTHIRD",
  "RTHIRD", "COMMA", "SEMICOLON", "STRING", "NOT", "ID",
  "HELP_ELSE_GET_PRECEDENCE", "$accept", "Program", "compound_statement",
  "var_declaration", "type_specifier", "declaration_list", "statements",
  "statement", "expression_statement", "variable", "expression",
  "logic_expression", "rel_expression", "simple_expression", "term",
  "unary_expression", "factor", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297
};
# endif

#define YYPACT_NINF -39

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-39)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       3,     0,    25,    -2,   -39,     2,     5,    50,   -39,     8,
      10,    15,   -39,   -39,   -39,    56,    17,   -39,   -39,   -39,
      56,    56,   -39,   -39,    56,    -4,   -39,    89,     9,   111,
     -39,   -39,    -5,    11,   -39,    21,   -19,    30,   -39,   -39,
      56,    -8,    56,    20,    22,   -15,   -39,    33,   -39,    56,
       9,   133,    27,   -20,   -39,   -39,   -39,   -39,    56,   -39,
      56,    56,    56,    56,    37,    -8,    43,   -39,    44,   -39,
      46,    -1,   -39,    64,    45,   -39,   -39,   -39,    30,    65,
     -39,   155,    56,   155,    55,   -39,   -39,    66,    69,    97,
      73,   -39,   -39,   -39,    85,   155,   155,    71,   -39,   -39,
     -39
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     1,     0,     0,     0,     2,     0,
       0,     0,     8,    10,     9,     0,     0,    44,    45,    46,
       0,     0,     5,    25,     0,    27,    18,     0,     0,     0,
      15,    17,    42,     0,    29,    31,    33,    35,    37,    41,
       0,     0,     0,     0,     0,    42,    39,     0,    40,     0,
       0,     0,    13,     0,     4,    16,    47,    48,     0,    26,
       0,     0,     0,     0,     0,     0,     0,    24,     0,    43,
       0,     0,     3,     0,     0,     6,    30,    32,    36,    34,
      38,     0,     0,     0,     0,    28,     7,     0,    11,    20,
       0,    22,    23,    14,     0,     0,     0,     0,    21,    19,
      12
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -39,   -39,   102,   -39,    88,    68,    92,   -29,   -38,   -18,
     -14,    63,    77,    61,    67,   -16,   -39
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,    26,    27,    28,    53,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      55,    43,    45,    65,    46,    61,    45,    47,    48,    62,
      56,    57,     1,    17,    18,    19,    20,    74,    75,     3,
      56,    57,    55,    21,    58,     4,    64,    82,    66,     5,
      23,    49,    24,    25,     6,    70,    74,    86,     7,    40,
      45,    41,    45,    45,    45,    45,    42,    80,    44,    59,
      52,    60,    89,     9,    91,    10,    11,    63,    67,    12,
      13,    14,    73,    68,    15,    69,    98,    99,    90,    81,
      16,    17,    18,    19,    20,    83,    84,    17,    18,    19,
      20,    21,    85,     7,    22,    87,    88,    21,    23,    61,
      24,    25,     9,    92,    10,    11,    24,    25,    12,    13,
      14,    95,    93,    15,    94,    96,    97,   100,     8,    16,
      17,    18,    19,    20,     9,    50,    10,    11,    71,    51,
      21,    76,     7,    79,     0,    15,     0,    23,    78,    24,
      25,    16,    17,    18,    19,    20,     9,    77,    10,    11,
       0,     0,    21,     0,     7,    54,     0,    15,     0,    23,
       0,    24,    25,    16,    17,    18,    19,    20,     9,     0,
      10,    11,     0,     0,    21,     0,     7,    72,     0,    15,
       0,    23,     0,    24,    25,    16,    17,    18,    19,    20,
       0,     0,     0,     0,     0,     0,    21,     0,     7,     0,
       0,     0,     0,    23,     0,    24,    25
};

static const yytype_int8 yycheck[] =
{
      29,    15,    20,    41,    20,    24,    24,    21,    24,    28,
      25,    26,     9,    21,    22,    23,    24,    37,    38,    19,
      25,    26,    51,    31,    29,     0,    40,    65,    42,    31,
      38,    35,    40,    41,    32,    49,    37,    38,    33,    31,
      58,    31,    60,    61,    62,    63,    31,    63,    31,    38,
      41,    30,    81,     3,    83,     5,     6,    27,    38,     9,
      10,    11,    35,    41,    14,    32,    95,    96,    82,    32,
      20,    21,    22,    23,    24,    32,    32,    21,    22,    23,
      24,    31,    36,    33,    34,    21,    41,    31,    38,    24,
      40,    41,     3,    38,     5,     6,    40,    41,     9,    10,
      11,     4,    36,    14,    35,    32,    21,    36,     6,    20,
      21,    22,    23,    24,     3,    27,     5,     6,    50,    27,
      31,    58,    33,    62,    -1,    14,    -1,    38,    61,    40,
      41,    20,    21,    22,    23,    24,     3,    60,     5,     6,
      -1,    -1,    31,    -1,    33,    34,    -1,    14,    -1,    38,
      -1,    40,    41,    20,    21,    22,    23,    24,     3,    -1,
       5,     6,    -1,    -1,    31,    -1,    33,    34,    -1,    14,
      -1,    38,    -1,    40,    41,    20,    21,    22,    23,    24,
      -1,    -1,    -1,    -1,    -1,    -1,    31,    -1,    33,    -1,
      -1,    -1,    -1,    38,    -1,    40,    41
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     9,    44,    19,     0,    31,    32,    33,    45,     3,
       5,     6,     9,    10,    11,    14,    20,    21,    22,    23,
      24,    31,    34,    38,    40,    41,    45,    46,    47,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      31,    31,    31,    53,    31,    52,    58,    53,    58,    35,
      47,    49,    41,    48,    34,    50,    25,    26,    29,    38,
      30,    24,    28,    27,    53,    51,    53,    38,    41,    32,
      53,    48,    34,    35,    37,    38,    54,    55,    57,    56,
      58,    32,    51,    32,    32,    36,    38,    21,    41,    50,
      53,    50,    38,    36,    35,     4,    32,    21,    50,    50,
      36
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    43,    44,    45,    45,    45,    46,    46,    47,    47,
      47,    48,    48,    48,    48,    49,    49,    50,    50,    50,
      50,    50,    50,    50,    50,    51,    51,    52,    52,    53,
      53,    54,    54,    55,    55,    56,    56,    57,    57,    58,
      58,    58,    59,    59,    59,    59,    59,    59,    59
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     5,     4,     3,     2,     3,     4,     1,     1,
       1,     3,     6,     1,     4,     1,     2,     1,     1,     7,
       5,     7,     5,     5,     3,     1,     2,     1,     4,     1,
       3,     1,     3,     1,     3,     1,     3,     1,     3,     2,
       2,     1,     1,     3,     1,     1,     1,     2,     2
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
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
  int yytoken = 0;
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

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
        case 2:
#line 133 "1305043.y" /* yacc.c:1646  */
    {
														printNOW("Program : INT MAIN LPAREN RPAREN compound_statement"); 

														//todo insert appropriate data segment register initialization code and others like main proc


														(yyval.helpInfo)=(yyvsp[0].helpInfo);

														ofstream fout;
														fout.open("1305043_code.asm");

														fout<<"TITLE PROGRAM:numan947\n";
														fout<<".model small\n.stack 100h\n";


														fout<<(yyval.helpInfo)->code;

														fout<<"\nmain endp\nend main\n";
														fout.close();


														codetracker<<(yyval.helpInfo)->code;

														}
#line 1493 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 160 "1305043.y" /* yacc.c:1646  */
    {
																printNOW("compound_statement : LCURL var_declaration statements RCURL");

																(yyval.helpInfo)=new SymbolInfo("COPY","COPY");
																(yyval.helpInfo)->code="\n.data\n\n";

																(yyval.helpInfo)->code+=(yyvsp[-2].helpInfo)->code;
																for(int i=0;i<temp_count;i++){
																	tl.str("");
																	tl<<i;
																	(yyval.helpInfo)->code+="t"+tl.str()+" dw ?\n";
																}

																(yyval.helpInfo)->code+="\n.code\n\nmain proc\n\nmov ax ,@data\nmov ds ,ax\n";
																(yyval.helpInfo)->code+=(yyvsp[-1].helpInfo)->code;

																codetracker<<(yyval.helpInfo)->code;
															}
#line 1516 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 180 "1305043.y" /* yacc.c:1646  */
    {
		   							printNOW("compound_statement : LCURL statements RCURL");
		   							(yyval.helpInfo)=(yyvsp[-1].helpInfo);


		   							codetracker<<(yyval.helpInfo)->code;
		   						}
#line 1528 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 189 "1305043.y" /* yacc.c:1646  */
    {
		   					printNOW("compound_statement : LCURL RCURL");
		   					(yyval.helpInfo)=new SymbolInfo("compound_statement","DUMMY");
		   					

		   					codetracker<<(yyval.helpInfo)->code;		

		   				}
#line 1541 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 200 "1305043.y" /* yacc.c:1646  */
    {
																printNOW("var_declaration : type_specifier declaration_list SEMICOLON");


																for(int i=marker;i<var_count;i++){
																	declaredInfo[i]->varType=(yyvsp[-2].helpString);
																}
																marker=var_count;

																(yyval.helpInfo)=(yyvsp[-1].helpInfo);
																

																codetracker<<(yyval.helpInfo)->code;
															}
#line 1560 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 217 "1305043.y" /* yacc.c:1646  */
    {
																		printNOW("var_declaration : var_declaration type_specifier declaration_list SEMICOLON");

																		
																		//cout<<$2<<endl;

																		for(int i=marker;i<var_count;i++){
																			declaredInfo[i]->varType=(yyvsp[-2].helpString);
																		}
																		marker=var_count;



																		(yyval.helpInfo)=(yyvsp[-3].helpInfo);
																		(yyval.helpInfo)->code+=(yyvsp[-1].helpInfo)->code;

																		codetracker<<(yyval.helpInfo)->code;

																	}
#line 1584 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 238 "1305043.y" /* yacc.c:1646  */
    {
							printNOW("type_specifier : INT");
							(yyval.helpString)="INT";
					}
#line 1593 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 244 "1305043.y" /* yacc.c:1646  */
    {
					printNOW("type_specifier : FLOAT");
					(yyval.helpString)="FLOAT";
				}
#line 1602 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 251 "1305043.y" /* yacc.c:1646  */
    {
					printNOW("type_specifier : CHAR");

					(yyval.helpString)="CHAR";
				}
#line 1612 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 261 "1305043.y" /* yacc.c:1646  */
    {
													printNOW("declaration_list : declaration_list COMMA ID");

													//todo code;

													(yyval.helpInfo)=(yyvsp[-2].helpInfo);

													string s=""+(yyvsp[0].idInfo)->getName();

													(yyvsp[0].idInfo)->array=false;


													err=false;
													for(ii=0;ii<var_count;ii++){
														string s1=""+declaredInfo[ii]->getName();

														if(s1==s){
															err=true;
															break;
														}			
													}
													

													if(!err){
														myTable->Insert(*(yyvsp[0].idInfo));
														declaredInfo[var_count++]=myTable->getSymbolInfo(s);
														
														printNOW(s);
														myTable->Print(logFile);
														fprintf(logFile,"\n\n\n\n");

														string retCode=s+" dw "+"?\n";

														//concat the code to print
														(yyval.helpInfo)->code+=retCode;

													}
													else{
														printError("multiple declarations for "+s);
														error_count++;
													}


													codetracker<<(yyval.helpInfo)->code;


												}
#line 1664 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 310 "1305043.y" /* yacc.c:1646  */
    {
		 											printNOW("declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD");
		 											
		 											//todo code

		 											(yyvsp[-3].idInfo)->arrayLength=(yyvsp[-1].helpInfo)->iVal;

													(yyvsp[-3].idInfo)->array=true;

													for(int i=0;i<(yyvsp[-3].idInfo)->arrayLength;i++)(yyvsp[-3].idInfo)->arrayStorage[i]=-1;


													string s=""+(yyvsp[-3].idInfo)->getName();


													err=false;
													for(ii=0;ii<var_count;ii++){
														string s1=""+declaredInfo[ii]->getName();

														if(s1==s){
															err=true;
															break;
														}			
													}
													

													if(!err){
														myTable->Insert(*(yyvsp[-3].idInfo));
														declaredInfo[var_count++]=myTable->getSymbolInfo(s);
														
														printNOW(s);
														myTable->Print(logFile);
														fprintf(logFile,"\n\n\n\n");


														//code
														string retCode=s+" dw "+"?";

														for(int a=0;a<declaredInfo[var_count-1]->arrayLength-1;a++){
															retCode+=" ,?";												
														}
														retCode+="\n";

														//concat the code to print
														(yyval.helpInfo)->code+=retCode;




													}
													else{
														stringstream ss;
														ss<<(yyvsp[-3].idInfo)->line;

														printError("multiple declarations for "+s);
														error_count++;
													}

													codetracker<<(yyval.helpInfo)->code;
													

		 										}
#line 1731 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 375 "1305043.y" /* yacc.c:1646  */
    {	
		 			printNOW("declaration_list : ID");
					
					string s=""+(yyvsp[0].idInfo)->getName();

					(yyvsp[0].idInfo)->array=false;



					err=false;
					for(ii=0;ii<var_count;ii++){
						string s1=""+declaredInfo[ii]->getName();

						if(s1==s){
							err=true;
							break;
						}			
					}
					

					if(!err){

						myTable->Insert(*(yyvsp[0].idInfo));
						declaredInfo[var_count++]=myTable->getSymbolInfo(s);
						printNOW(s);
						myTable->Print(logFile);
						fprintf(logFile,"\n\n\n\n");


						//code
						string retCode=s+" dw "+"?\n";

						//copy the code from SymbolInfo
						(yyval.helpInfo)=new SymbolInfo("COPY","COPY");
						(yyval.helpInfo)->code= retCode;
						


					}
					else{	
							printError("multiple declarations for "+s);
							error_count++;

							//code
							SymbolInfo *copy=new SymbolInfo("ERROR","ERROR");

							tl.str("");
							tl<<line_count;

							copy->code="Error at "+tl.str()+"\n";
							(yyval.helpInfo)=copy;
						}

						codetracker<<(yyval.helpInfo)->code;

		 		}
#line 1792 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 434 "1305043.y" /* yacc.c:1646  */
    {
		 								
		 								printNOW("declaration_list : ID LTHIRD CONST_INT RTHIRD");

										(yyvsp[-3].idInfo)->arrayLength=(yyvsp[-1].helpInfo)->iVal;
										(yyvsp[-3].idInfo)->array=true;

										for(int i=0;i<(yyvsp[-3].idInfo)->arrayLength;i++)(yyvsp[-3].idInfo)->arrayStorage[i]=-1;
										

										string s=""+(yyvsp[-3].idInfo)->getName();


										err=false;
										for(ii=0;ii<var_count;ii++){
											string s1=""+declaredInfo[ii]->getName();

											if(s1==s){
												err=true;
												break;
											}			
										}
										

										if(!err){
											myTable->Insert(*(yyvsp[-3].idInfo));
											declaredInfo[var_count++]=myTable->getSymbolInfo(s);
											
											printNOW(s);
											myTable->Print(logFile);
											fprintf(logFile,"\n\n\n\n");



											//code
											string retCode=s+" dw "+"?";

											for(int a=0;a<declaredInfo[var_count-1]->arrayLength-1;a++){
												retCode+=" ,?";												
											}
											retCode+="\n";
											
											//copy the code for printing :)
											(yyval.helpInfo)=new SymbolInfo("COPY","COPY");
											(yyval.helpInfo)->code=retCode;


										}
										else{
											printError("multiple declarations for "+s);
											error_count++;
											SymbolInfo *copy=new SymbolInfo("ERROR","ERROR");
											
											tl.str("");
											tl<<line_count;

											copy->code="Error at "+tl.str()+"\n";
											(yyval.helpInfo)=copy;
										}
									codetracker<<(yyval.helpInfo)->code;
		 									
		 				}
#line 1859 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 504 "1305043.y" /* yacc.c:1646  */
    {
							printNOW("statements : statement");
							(yyval.helpInfo)=(yyvsp[0].helpInfo);
							codetracker<<(yyval.helpInfo)->code;

						}
#line 1870 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 513 "1305043.y" /* yacc.c:1646  */
    {
	   								printNOW("statements : statements statement");
	   								(yyval.helpInfo)=(yyvsp[-1].helpInfo);
	   								(yyval.helpInfo)->code+=(yyvsp[0].helpInfo)->code;

	   								codetracker<<"SPC11: \n"<<(yyvsp[-1].helpInfo)->code<<"\n";
	   								codetracker<<"SPC22: \n"<<(yyvsp[0].helpInfo)->code<<"\n";

	   								codetracker<<(yyval.helpInfo)->code;
	   							}
#line 1885 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 530 "1305043.y" /* yacc.c:1646  */
    {
										printNOW("statement  : expression_statement");
										(yyval.helpInfo)=(yyvsp[0].helpInfo);
										codetracker<<(yyval.helpInfo)->code;
									}
#line 1895 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 537 "1305043.y" /* yacc.c:1646  */
    {
	   								printNOW("statement  : compound_statement");
	   								(yyval.helpInfo)=(yyvsp[0].helpInfo);
	   								codetracker<<(yyval.helpInfo)->code;
	   							}
#line 1905 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 545 "1305043.y" /* yacc.c:1646  */
    {
	   																			
	   																			printNOW("statement  : FOR LPAREN expression_statement expression_statement expression RPAREN statement");


	   																			//todo code

	   																		}
#line 1918 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 556 "1305043.y" /* yacc.c:1646  */
    {
	   																				printNOW("statement  : IF LPAREN expression RPAREN statement");
	   																				
	   																				(yyval.helpInfo)=(yyvsp[-2].helpInfo);

	   																				string label=newLabel();
	   																				(yyval.helpInfo)->code+="mov ax, "+(yyvsp[-2].helpInfo)->getName()+"\n";
	   																				(yyval.helpInfo)->code+="cmp ax, 1\n";
	   																				(yyval.helpInfo)->code+="jne "+label+"\n";
	   																				(yyval.helpInfo)->code+=(yyvsp[0].helpInfo)->code;
	   																				(yyval.helpInfo)->code+=label+":\n";


	   																				codetracker<<(yyval.helpInfo)->code;

	   																			}
#line 1939 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 575 "1305043.y" /* yacc.c:1646  */
    {
	   																printNOW("statement  : IF LPAREN expression RPAREN statement ELSE statement");

	   																//todo code

	   																string l1=newLabel();
	   																string l2=newLabel();

	   																(yyval.helpInfo)=(yyvsp[-4].helpInfo);
	   																(yyval.helpInfo)->code+="mov ax, "+(yyvsp[-4].helpInfo)->getName()+"\n";
	   																(yyval.helpInfo)->code+="cmp ax, 1\n";
	   																(yyval.helpInfo)->code+="jl "+l1+"\n";
	   																(yyval.helpInfo)->code+=(yyvsp[-2].helpInfo)->code;
	   																(yyval.helpInfo)->code+="jump "+l2+"\n";
	   																(yyval.helpInfo)->code+=l1+":\n"+(yyvsp[0].helpInfo)->code;
	   																(yyval.helpInfo)->code+=l2+":\n";

	   																codetracker<<(yyval.helpInfo)->code;
	   															}
#line 1963 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 597 "1305043.y" /* yacc.c:1646  */
    {
	   													printNOW("statement  : WHILE LPAREN expression RPAREN statement");

	   													//todo code

	   												}
#line 1974 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 606 "1305043.y" /* yacc.c:1646  */
    {
	   												printNOW("statement  : PRINTLN LPAREN ID RPAREN SEMICOLON ");

	   												//todo code

	   												if((yyvsp[-2].idInfo)->varType=="")(yyvsp[-2].idInfo)=findInDeclaration((yyvsp[-2].idInfo)->getName());

	   												ostringstream o;

	   												if((yyvsp[-2].idInfo)->array==false){
		   												if((yyvsp[-2].idInfo)->getType()=="INT"){
		   													o<<(yyvsp[-2].idInfo)->iVal;
		   													printNOW(o.str());
		   												}
		   												else if((yyvsp[-2].idInfo)->getType()=="FLOAT"){
		   													o<<(yyvsp[-2].idInfo)->dVal;
		   													printNOW(o.str());
		   												}
		   												else if((yyvsp[-2].idInfo)->getType()=="CHAR"){
		   													o<<(yyvsp[-2].idInfo)->chVal;
		   													printNOW(o.str());
		   												}
	   												}
	   												else{
		   												if((yyvsp[-2].idInfo)->getType()=="INT"){
		   													for(int i=0;i<(yyvsp[-2].idInfo)->arrayLength;i++)printf("%d ",(int)(yyvsp[-2].idInfo)->arrayStorage[i]);
		   												}
		   												else if((yyvsp[-2].idInfo)->getType()=="FLOAT"){
		   													for(int i=0;i<(yyvsp[-2].idInfo)->arrayLength;i++)printf("%lf ",(double)(yyvsp[-2].idInfo)->arrayStorage[i]);
		   												}
		   												else if((yyvsp[-2].idInfo)->getType()=="CHAR"){
		   													for(int i=0;i<(yyvsp[-2].idInfo)->arrayLength;i++)printf("%c ",(char)(yyvsp[-2].idInfo)->arrayStorage[i]);
		   												}
	   												}
	   											}
#line 2014 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 644 "1305043.y" /* yacc.c:1646  */
    {
	   										printNOW("statement  : RETURN expression SEMICOLON");
	   										
	   										//asm-code

	   										(yyval.helpInfo)=(yyvsp[-1].helpInfo);
	   										(yyval.helpInfo)->code+="mov ah, 4ch\nint 21h\n";

	   										codetracker<<(yyval.helpInfo)->code;

	   									}
#line 2030 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 662 "1305043.y" /* yacc.c:1646  */
    {
							printNOW("expression_statement : SEMICOLON");
							(yyval.helpInfo)=new SymbolInfo(";","SEMICOLON");
							(yyval.helpInfo)->code="";

							codetracker<<(yyval.helpInfo)->code;
						}
#line 2042 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 672 "1305043.y" /* yacc.c:1646  */
    {
										printNOW("expression_statement : expression SEMICOLON");

										(yyval.helpInfo)=(yyvsp[-1].helpInfo);

										codetracker<<(yyval.helpInfo)->code;
									
									}
#line 2055 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 685 "1305043.y" /* yacc.c:1646  */
    {
						printNOW("variable : ID ");
						//FLAG
						

						SymbolInfo* target=findInDeclaration((yyvsp[0].idInfo)->getName());
						

						if(target==0){
							printError("undeclared variable "+(yyvsp[0].idInfo)->getName());
							error_count++;
							(yyval.helpInfo)=new SymbolInfo();
							(yyval.helpInfo)->varType="DUMMY";

						}
						else if(target->array==true){
							SymbolInfo* fun=new SymbolInfo();
							*fun=*target;
							fun->setType("COPY");
							(yyval.helpInfo)=fun;
							(yyval.helpInfo)->pIndex=-1;
						}

						else {
							SymbolInfo* fun=new SymbolInfo();
							*fun=*target;
							fun->setType("COPY");
							(yyval.helpInfo)=fun;

						}


						codetracker<<(yyval.helpInfo)->code;
				}
#line 2094 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 722 "1305043.y" /* yacc.c:1646  */
    {
	 									
	 									printNOW("variable : ID LTHIRD expression RTHIRD ");
										
										SymbolInfo* target=findInDeclaration((yyvsp[-3].idInfo)->getName());

										if((yyvsp[-1].helpInfo)->varType=="")(yyvsp[-1].helpInfo)=findInDeclaration((yyvsp[-1].helpInfo)->getName());

										
										if(target==0){
											printError("undeclared variable "+(yyvsp[-3].idInfo)->getName());
											error_count++;
											(yyval.helpInfo)=new SymbolInfo();
											(yyval.helpInfo)->varType="DUMMY";
										}

										else if((yyvsp[-1].helpInfo)->varType!="INT"){
											printError("Index for array "+(yyvsp[-3].idInfo)->getName()+" is not INT");
											error_count++;
											(yyval.helpInfo)=new SymbolInfo("DUMMY","DUMMY");
											(yyval.helpInfo)->varType="DUMMY";								
										}
										
										else{

											printf("<%d>\n",(yyvsp[-1].helpInfo)->iVal);
											printf("<%s>\n",(yyvsp[-1].helpInfo)->getName().c_str());

											SymbolInfo* fun=new SymbolInfo();

											*fun=*target;
											fun->setType("COPY");

											(yyval.helpInfo)=fun;

											(yyval.helpInfo)->pIndex=(yyvsp[-1].helpInfo)->iVal;
											(yyval.helpInfo)->code=(yyvsp[-1].helpInfo)->code;
											(yyval.helpInfo)->expIndex=(yyvsp[-1].helpInfo)->getName();
										}


										codetracker<<(yyval.helpInfo)->code;

	 								}
#line 2143 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 772 "1305043.y" /* yacc.c:1646  */
    {
									printNOW("expression : logic_expression");
									(yyval.helpInfo)=(yyvsp[0].helpInfo);

									codetracker<<(yyval.helpInfo)->code;
								}
#line 2154 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 781 "1305043.y" /* yacc.c:1646  */
    {
	   												printNOW("expression : variable ASSIGNOP logic_expression");

	   												

	   												//todo code

	   												if((yyvsp[-2].helpInfo)->varType=="DUMMY")(yyval.helpInfo)=(yyvsp[-2].helpInfo);
	   												
	   												else if((yyvsp[0].helpInfo)->varType=="DUMMY")(yyval.helpInfo)=(yyvsp[0].helpInfo);

	   												

	   												else{

		   												SymbolInfo* target=findInDeclaration((yyvsp[-2].helpInfo)->getName());

		   												if((yyvsp[0].helpInfo)->varType=="")(yyvsp[0].helpInfo)=findInDeclaration((yyvsp[0].helpInfo)->getName());

		   												if((yyvsp[-2].helpInfo)->getType()=="COPY"){
		   													target->expIndex=(yyvsp[-2].helpInfo)->expIndex;
		   													target->pIndex=(yyvsp[-2].helpInfo)->pIndex;
		   												}

		   												//code-asm
		   												(yyval.helpInfo)=new SymbolInfo("COPY","COPY");
		   												(yyval.helpInfo)->code=(yyvsp[0].helpInfo)->code+target->code;
		   												(yyval.helpInfo)->code+="mov ax, "+(yyvsp[0].helpInfo)->getName()+"\n";


		   												if(target==0){
		   													//check for error later :/ 
		   												}


		   												else{

			   													if(target->array==false){

			   														if(target->varType=="INT"&&(yyvsp[0].helpInfo)->varType=="INT")target->iVal=(yyvsp[0].helpInfo)->iVal;
			   														else if(target->varType=="FLOAT"&&(yyvsp[0].helpInfo)->varType=="FLOAT")target->dVal=(yyvsp[0].helpInfo)->dVal;
			   														else if(target->varType=="CHAR"&&(yyvsp[0].helpInfo)->varType=="CHAR")target->chVal=(yyvsp[0].helpInfo)->chVal;
			   														else if(target->varType=="FLOAT"){
			   															if((yyvsp[0].helpInfo)->varType=="INT")target->dVal=(yyvsp[0].helpInfo)->iVal;
			   															else if((yyvsp[0].helpInfo)->varType=="CHAR")target->dVal=(yyvsp[0].helpInfo)->chVal;
			   														}
			   														else {
			   															printError("Type Mismatch");
				   														error_count++;
			   														}
			   														(yyval.helpInfo)->code+="mov "+target->getName()+", ax\n";
			   													}


			   													else if(target->pIndex>-1 && target->pIndex<target->arrayLength){

																	
			   														if(target->varType=="INT"){
				   														if((yyvsp[0].helpInfo)->varType=="INT")target->arrayStorage[target->pIndex]=(int)(yyvsp[0].helpInfo)->iVal;
				   														else{
				   															printError("Type Mismatch");
				   															error_count++;
				   														}
				   													}
				   													else if(target->varType=="FLOAT"){
				   														if((yyvsp[0].helpInfo)->varType=="INT")target->arrayStorage[target->pIndex]=(double)(yyvsp[0].helpInfo)->iVal;
				   														else if((yyvsp[0].helpInfo)->varType=="FLOAT")target->arrayStorage[target->pIndex]=(double)(yyvsp[0].helpInfo)->dVal;
				   														else if((yyvsp[0].helpInfo)->varType=="CHAR")target->arrayStorage[target->pIndex]=(double)(yyvsp[0].helpInfo)->chVal;
				   													}
				   													else if(target->varType=="CHAR"){
				   														if((yyvsp[0].helpInfo)->varType=="CHAR")target->arrayStorage[target->pIndex]=(char)(yyvsp[0].helpInfo)->chVal;
				   														else {
				   															printError("Type Mismatch");
				   															error_count++;
				   														}
				   													}


				   													(yyval.helpInfo)->code+="lea di, "+target->getName()+"\n";

				   													tl.str("");
				   													
				   													tl<<target->expIndex;

				   													for(int i=0;i<2;i++){
				   														(yyval.helpInfo)->code+="add di, "+tl.str()+"\n";
				   													}
				   													(yyval.helpInfo)->code+="mov [di], ax\n";

				   													(yyval.helpInfo)->pIndex=-1;


			   													}
			   													else{
			   														if(target->pIndex<0){
			   															printError("Type Mismatch");
				   														error_count++;
			   														}
			   														else if(target->pIndex>=target->arrayLength){
			   															printError("Array index out of bound for "+target->getName());
			   															error_count++;
			   														}
			   													}

			   													
			   													myTable->Print(logFile);
			   													fprintf(logFile,"\n\n\n\n");
			   												}
		   												}

		   												codetracker<<(yyval.helpInfo)->code;

	   											}
#line 2272 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 897 "1305043.y" /* yacc.c:1646  */
    {
										printNOW("logic_expression : rel_expression");
										(yyval.helpInfo)=(yyvsp[0].helpInfo);

										codetracker<<(yyval.helpInfo)->code;

									}
#line 2284 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 907 "1305043.y" /* yacc.c:1646  */
    {
		 												printNOW("logic_expression : rel_expression LOGICOP rel_expression");

		 												//todo code

		 												if((yyvsp[-2].helpInfo)->varType=="DUMMY")(yyval.helpInfo)=(yyvsp[-2].helpInfo);
														
														else if((yyvsp[0].helpInfo)->varType=="DUMMY")(yyval.helpInfo)=(yyvsp[0].helpInfo);
														
														else{

			 												SymbolInfo* res=new SymbolInfo("COPY","COPY");
			 												res->varType="INT";
			 												
			 												if((yyvsp[-2].helpInfo)->varType=="")(yyvsp[-2].helpInfo)=findInDeclaration((yyvsp[-2].helpInfo)->getName());
			 												if((yyvsp[0].helpInfo)->varType=="")(yyvsp[0].helpInfo)=findInDeclaration((yyvsp[0].helpInfo)->getName());

			 												//code-asm
			 												bool ok=true;
															(yyval.helpInfo)=res;
															(yyval.helpInfo)->code=(yyvsp[-2].helpInfo)->code+(yyvsp[0].helpInfo)->code;
															

															string tmp=newTemp();
															string l1=newLabel();
															string l2=newLabel();




			 												if((yyvsp[-2].helpInfo)->array||(yyvsp[0].helpInfo)->array){
																printError("Logic operations on arrays");
																error_count++;
																ok=false;
															}
															else{
																float a,b;
																if((yyvsp[-2].helpInfo)->varType=="INT")a=(double)(yyvsp[-2].helpInfo)->iVal;
																if((yyvsp[-2].helpInfo)->varType=="FLOAT")a=(yyvsp[-2].helpInfo)->dVal;
																if((yyvsp[-2].helpInfo)->varType=="CHAR")a=(double)(yyvsp[-2].helpInfo)->chVal;
																if((yyvsp[0].helpInfo)->varType=="INT")b=(double)(yyvsp[0].helpInfo)->iVal;
																if((yyvsp[0].helpInfo)->varType=="FLOAT")b=(yyvsp[0].helpInfo)->dVal;
																if((yyvsp[0].helpInfo)->varType=="CHAR")b=(double)(yyvsp[0].helpInfo)->iVal;

																if((yyvsp[-1].helpInfo)->getName()=="&&"){
																	res->iVal=(a&&b);


																	(yyval.helpInfo)->code+="cmp "+(yyvsp[-2].helpInfo)->getName()+",1\n";
																	(yyval.helpInfo)->code+="jne "+l1+"\n";
																	(yyval.helpInfo)->code+="cmp "+(yyvsp[0].helpInfo)->getName()+",1\n";
																	(yyval.helpInfo)->code+="jne "+l1+"\n";

																	(yyval.helpInfo)->code+="mov "+tmp+", 1\n";
																	(yyval.helpInfo)->code+="jmp "+l2+"\n";
																	
																	(yyval.helpInfo)->code+=l1+":\nmov "+tmp+", 0\n";
																	(yyval.helpInfo)->code+=l2+":\n";
																}
																else if((yyvsp[-1].helpInfo)->getName()=="||"){
																	res->iVal=(a||b);


																	(yyval.helpInfo)->code+="cmp "+(yyvsp[-2].helpInfo)->getName()+",1\n";
																	(yyval.helpInfo)->code+="je "+l1+"\n";
																	(yyval.helpInfo)->code+="cmp "+(yyvsp[0].helpInfo)->getName()+",1\n";
																	(yyval.helpInfo)->code+="je "+l1+"\n";

																	(yyval.helpInfo)->code+="mov "+tmp+", 0\n";
																	(yyval.helpInfo)->code+="jmp "+l2+"\n";
																	(yyval.helpInfo)->code+=l1+":\nmov "+tmp+", 1\n";
																	(yyval.helpInfo)->code+=l2+":\n";
																} 

																(yyval.helpInfo)->setName(tmp);
																
															}		 	
														}		


														codetracker<<(yyval.helpInfo)->code;								
													}
#line 2371 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 994 "1305043.y" /* yacc.c:1646  */
    {
										printNOW("rel_expression : simple_expression");
										(yyval.helpInfo)=(yyvsp[0].helpInfo);

										codetracker<<(yyval.helpInfo)->code;
									}
#line 2382 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 1003 "1305043.y" /* yacc.c:1646  */
    {
														//FLAG

														printNOW("rel_expression : simple_expression RELOP simple_expression");

														//todo code

														if((yyvsp[-2].helpInfo)->varType=="DUMMY")(yyval.helpInfo)=(yyvsp[-2].helpInfo);
														else if((yyvsp[0].helpInfo)->varType=="DUMMY")(yyval.helpInfo)=(yyvsp[0].helpInfo);
														else{

															SymbolInfo* res=new SymbolInfo("COPY","COPY");
															res->varType="INT";


															if((yyvsp[-2].helpInfo)->varType==""){
																(yyvsp[-2].helpInfo)=findInDeclaration((yyvsp[-2].helpInfo)->getName());
															}
															
															if((yyvsp[0].helpInfo)->varType==""){
																(yyvsp[0].helpInfo)=findInDeclaration((yyvsp[0].helpInfo)->getName());
															}

															//code-asm

															bool ok=true;
															(yyval.helpInfo)=res;
															(yyval.helpInfo)->code=(yyvsp[-2].helpInfo)->code+(yyvsp[0].helpInfo)->code;
															(yyval.helpInfo)->code+="mov ax, "+(yyvsp[-2].helpInfo)->getName()+"\n";
															(yyval.helpInfo)->code+="cmp ax, "+(yyvsp[0].helpInfo)->getName()+"\n";

															string tmp=newTemp();
															string l1=newLabel();
															string l2=newLabel();






															if((yyvsp[-2].helpInfo)->array||(yyvsp[0].helpInfo)->array){
																printNOW("RELOP operations on arrays");
																ok=false;

															}
															else{
																float a,b;
																if((yyvsp[-2].helpInfo)->varType=="INT")a=(double)(yyvsp[-2].helpInfo)->iVal;
																if((yyvsp[-2].helpInfo)->varType=="FLOAT")a=(yyvsp[-2].helpInfo)->dVal;
																if((yyvsp[-2].helpInfo)->varType=="CHAR")a=(double)(yyvsp[-2].helpInfo)->chVal;
																if((yyvsp[0].helpInfo)->varType=="INT")b=(double)(yyvsp[0].helpInfo)->iVal;
																if((yyvsp[0].helpInfo)->varType=="FLOAT")b=(yyvsp[0].helpInfo)->dVal;
																if((yyvsp[0].helpInfo)->varType=="CHAR")b=(double)(yyvsp[0].helpInfo)->iVal;

																if((yyvsp[-1].helpInfo)->getName()=="=="){
																	res->iVal=(a==b);
																	(yyval.helpInfo)->code+="je "+l1+"\n";

																}
																else if((yyvsp[-1].helpInfo)->getName()=="!="){
																	res->iVal=(a!=b);
																	(yyval.helpInfo)->code+="jne "+l1+"\n";
																}
																else if((yyvsp[-1].helpInfo)->getName()=="<"){
																	res->iVal=(a<b);
																	(yyval.helpInfo)->code+="jl "+l1+"\n";
																}
																else if((yyvsp[-1].helpInfo)->getName()=="<="){
																	res->iVal=(a<=b);
																	(yyval.helpInfo)->code+="jle "+l1+"\n";
																}
																else if((yyvsp[-1].helpInfo)->getName()==">"){
																	res->iVal=(a>b);
																	(yyval.helpInfo)->code+="jg "+l1+"\n";
																}
																else if((yyvsp[-1].helpInfo)->getName()==">="){
																	res->iVal=(a>=b);
																	(yyval.helpInfo)->code+="jge "+l1+"\n";
																}

																(yyval.helpInfo)->code+="mov "+tmp+", 0\n";
																(yyval.helpInfo)->code+="jmp "+l2+"\n";
																(yyval.helpInfo)->code+=l1+":\nmov "+tmp+", 1\n";
																(yyval.helpInfo)->code+=l2+":\n";
																(yyval.helpInfo)->setName(tmp);
																
															}
														}

														codetracker<<(yyval.helpInfo)->code;
													}
#line 2478 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 1100 "1305043.y" /* yacc.c:1646  */
    {
							printNOW("simple_expression : term ");
							(yyval.helpInfo)=(yyvsp[0].helpInfo);
							codetracker<<(yyval.helpInfo)->code;
						}
#line 2488 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 1108 "1305043.y" /* yacc.c:1646  */
    {

		  									printNOW("simple_expression : simple_expression ADDOP term");

		  									//todo code

		  									if((yyvsp[0].helpInfo)->varType=="DUMMY")(yyval.helpInfo)=(yyvsp[0].helpInfo);

		  									else{
			  									
			  									SymbolInfo* res=new SymbolInfo("COPY","COPY");
			  									

			  									if((yyvsp[-2].helpInfo)->varType==""){
			  											//cout<<"GO FIND NEMO "<<$1->getName()<<endl;
			  											(yyvsp[-2].helpInfo)=findInDeclaration((yyvsp[-2].helpInfo)->getName());

			  											//cout<<$1->iVal<<endl;
			  										}
			  									if((yyvsp[0].helpInfo)->varType==""){
			  											//cout<<"GO FIND NEMO "<<$3->getName()<<endl;
			  											(yyvsp[0].helpInfo)=findInDeclaration((yyvsp[0].helpInfo)->getName());

			  										}

			  									//code-asm
			  									(yyval.helpInfo)=(yyvsp[-2].helpInfo);
			  									(yyval.helpInfo)->code+=(yyvsp[0].helpInfo)->code;

			  									bool ok=true;
			  									string tmp=newTemp();
			  									


	 											if((yyvsp[-2].helpInfo)->varType=="CHAR"||(yyvsp[0].helpInfo)->varType=="CHAR"){
	 													printError("Add operation on CHAR");
	 													error_count++;
	 													ok=false;
	 											}

	 											if((yyvsp[-2].helpInfo)->array||(yyvsp[0].helpInfo)->array){
	 												printError("Add operation on arrays");
	 												error_count++;
	 												ok=false;
	 											}
	 											


	 											if((yyvsp[-1].helpInfo)->getName()=="+"){

		 											if((yyvsp[-2].helpInfo)->varType=="FLOAT"||(yyvsp[0].helpInfo)->varType=="FLOAT"){
		 												
		 												if((yyvsp[-2].helpInfo)->varType=="FLOAT"&&(yyvsp[0].helpInfo)->varType=="FLOAT"){
		 														(yyvsp[-2].helpInfo)->dVal+=(yyvsp[0].helpInfo)->dVal;
		 														
		 													}
		 												
		 												else if((yyvsp[-2].helpInfo)->varType=="FLOAT"){
		 													
		 														(yyvsp[-2].helpInfo)->dVal+=(yyvsp[0].helpInfo)->iVal;
		 													}
		 												
		 												else {
		 														(yyvsp[-2].helpInfo)->dVal=((yyvsp[-2].helpInfo)->iVal+(yyvsp[0].helpInfo)->dVal);
		 														(yyvsp[-2].helpInfo)->varType="FLOAT";
		 													}
		 												}
		 											else{
		 													(yyvsp[-2].helpInfo)->iVal+=(yyvsp[0].helpInfo)->iVal;
		 												}

		 											if(ok){
		 												//code-asm
		 												(yyval.helpInfo)->code+="mov ax, "+(yyvsp[-2].helpInfo)->getName()+"\n";
		 												(yyval.helpInfo)->code+="add ax, "+(yyvsp[0].helpInfo)->getName()+"\n";
		 												(yyval.helpInfo)->code+="mov "+tmp+", ax\n";

		 												(yyval.helpInfo)->setName(tmp);


		 											}

	 											}
	 											else if((yyvsp[-1].helpInfo)->getName()=="-"){

		 											if((yyvsp[-2].helpInfo)->varType=="FLOAT"||(yyvsp[0].helpInfo)->varType=="FLOAT"){
		 												if((yyvsp[-2].helpInfo)->varType=="FLOAT"&&(yyvsp[0].helpInfo)->varType=="FLOAT")(yyvsp[-2].helpInfo)->dVal-=(yyvsp[0].helpInfo)->dVal;
		 												else if((yyvsp[-2].helpInfo)->varType=="FLOAT")(yyvsp[-2].helpInfo)->dVal-=(yyvsp[0].helpInfo)->iVal;
		 												else {
		 														(yyvsp[-2].helpInfo)->dVal=((yyvsp[-2].helpInfo)->iVal-(yyvsp[0].helpInfo)->dVal);
		 														(yyvsp[-2].helpInfo)->varType="FLOAT";
		 													}
		 												}
		 											else (yyvsp[-2].helpInfo)->iVal-=(yyvsp[0].helpInfo)->iVal;


		 											if(ok){
		 												//code-asm
		 												(yyval.helpInfo)->code+="mov ax, "+(yyvsp[-2].helpInfo)->getName()+"\n";
		 												(yyval.helpInfo)->code+="sub ax, "+(yyvsp[0].helpInfo)->getName();+"\n";
		 												(yyval.helpInfo)->code+="mov "+tmp+", ax\n";

		 												(yyval.helpInfo)->setName(tmp);


		 											}
	 											}

			  									
		  									}

		  								codetracker<<(yyval.helpInfo)->code;
		  								}
#line 2606 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 1226 "1305043.y" /* yacc.c:1646  */
    {
								printNOW("term :unary_expression");
								(yyval.helpInfo)=(yyvsp[0].helpInfo);
								codetracker<<(yyval.helpInfo)->code;

							}
#line 2617 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 1235 "1305043.y" /* yacc.c:1646  */
    {
     										printNOW("term : term MULOP unary_expression");

     										if((yyvsp[0].helpInfo)->varType=="DUMMY")(yyval.helpInfo)=(yyvsp[0].helpInfo);

     										//todo code


     										else{

	     										if((yyvsp[-2].helpInfo)->varType=="")(yyvsp[-2].helpInfo)=findInDeclaration((yyvsp[-2].helpInfo)->getName());
	     										if((yyvsp[0].helpInfo)->varType=="")(yyvsp[0].helpInfo)=findInDeclaration((yyvsp[0].helpInfo)->getName());


	     										(yyval.helpInfo)=(yyvsp[-2].helpInfo);
	     										
	     										//asm-code
	     										(yyval.helpInfo)->code+=(yyvsp[0].helpInfo)->code;
	     										(yyval.helpInfo)->code+="mov ax, "+(yyvsp[-2].helpInfo)->getName()+"\n";
	     										(yyval.helpInfo)->code+="mov bx, "+(yyvsp[0].helpInfo)->getName()+"\n";

	     										string tmp=newTemp();
	     										bool ok=true;


	     										if((yyvsp[-1].helpInfo)->getName()=="*"){
	     											if((yyvsp[-2].helpInfo)->varType=="CHAR"||(yyvsp[0].helpInfo)->varType=="CHAR"){
	     												printError("Multiplication operation on CHARs");
	     												error_count++;
	     												ok=false;
	     											}

	     											else if((yyvsp[-2].helpInfo)->varType=="FLOAT"||(yyvsp[0].helpInfo)->varType=="FLOAT"){
	     												
	     												if((yyvsp[-2].helpInfo)->varType=="FLOAT"&&(yyvsp[0].helpInfo)->varType=="FLOAT")(yyvsp[-2].helpInfo)->dVal*=(yyvsp[0].helpInfo)->dVal;
	     												
	     												else if((yyvsp[-2].helpInfo)->varType=="FLOAT")(yyvsp[-2].helpInfo)->dVal*=(yyvsp[0].helpInfo)->iVal;
	     												
	     												else {
	     														(yyvsp[-2].helpInfo)->dVal=((yyvsp[-2].helpInfo)->iVal*(yyvsp[0].helpInfo)->dVal);
	     														(yyvsp[-2].helpInfo)->varType="FLOAT";
	     													}
	     											
	     											}
	     											else (yyvsp[-2].helpInfo)->iVal*=(yyvsp[0].helpInfo)->iVal;

	     											if(ok){
		     											//code-asm

		     											(yyval.helpInfo)->code+="mul bx\n";
		     											(yyval.helpInfo)->code+="mov "+tmp+", ax\n";


		     											(yyval.helpInfo)->setName(tmp);
	     											}
	     										}


												else if((yyvsp[-1].helpInfo)->getName()=="/"){
	     											if((yyvsp[-2].helpInfo)->varType=="CHAR"||(yyvsp[0].helpInfo)->varType=="CHAR"){
	     												printError("Division operations of CHARs");
	     												error_count++;
	     												ok=false;
	     												}
	     											
	     											else if((yyvsp[-2].helpInfo)->varType=="FLOAT"||(yyvsp[0].helpInfo)->varType=="FLOAT"){
	     												
	     												if((yyvsp[-2].helpInfo)->varType=="FLOAT"&&(yyvsp[0].helpInfo)->varType=="FLOAT")(yyvsp[-2].helpInfo)->dVal/=(yyvsp[0].helpInfo)->dVal;
	     												
	     												else if((yyvsp[-2].helpInfo)->varType=="FLOAT")(yyvsp[-2].helpInfo)->dVal/=(double)(yyvsp[0].helpInfo)->iVal;
	     												
	     												else {
	     														(yyvsp[-2].helpInfo)->dVal=((double)(yyvsp[-2].helpInfo)->iVal/(yyvsp[0].helpInfo)->dVal);
	     														(yyvsp[-2].helpInfo)->varType="FLOAT";
	     													}
	     											}

	     											else (yyvsp[-2].helpInfo)->iVal/=(yyvsp[0].helpInfo)->iVal;

	     											if(ok){
		     											//code-asm
		     											(yyval.helpInfo)->code+="xor dx, dx\n";

		     											(yyval.helpInfo)->code+="div bx\n";
		     											(yyval.helpInfo)->code+="mov "+tmp+", ax\n";


		     											(yyval.helpInfo)->setName(tmp);
	     											}

	     										}  



	     										else if((yyvsp[-1].helpInfo)->getName()=="%"){
	     											if((yyvsp[-2].helpInfo)->varType=="CHAR"||(yyvsp[0].helpInfo)->varType=="CHAR"||(yyvsp[-2].helpInfo)->varType=="FLOAT"||(yyvsp[0].helpInfo)->varType=="FLOAT"){
	     												printError("Non integer operands on MODULUS");
	     												error_count++;
	     												(yyvsp[-2].helpInfo)->iVal=-99999;
	     												ok=false;
	     											}
	     											
	     											else (yyvsp[-2].helpInfo)->iVal%=(yyvsp[0].helpInfo)->iVal;

	     											if(ok){
		     											//code-asm
		     											(yyval.helpInfo)->code+="xor dx, dx\n";

		     											(yyval.helpInfo)->code+="div bx\n";
		     											(yyval.helpInfo)->code+="mov "+tmp+", dx\n";

		     											(yyval.helpInfo)->setName(tmp);
	     											}

	     											
	     										} 
     										}
     										codetracker<<(yyval.helpInfo)->code;
  
     									}
#line 2742 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 1365 "1305043.y" /* yacc.c:1646  */
    {
												printNOW("unary_expression : ADDOP unary_expression");

												//todo code

												if((yyvsp[0].helpInfo)->varType=="DUMMY")(yyval.helpInfo)=(yyvsp[0].helpInfo);

												else{
													if((yyvsp[0].helpInfo)->varType=="")(yyvsp[0].helpInfo)=findInDeclaration((yyvsp[0].helpInfo)->getName());


													if((yyvsp[-1].helpInfo)->getName()=="-"){
														string s=(yyvsp[0].helpInfo)->varType;

														if(s=="INT")(yyvsp[0].helpInfo)->iVal=-((yyvsp[0].helpInfo)->iVal);
														else if(s=="FLOAT")(yyvsp[0].helpInfo)->dVal=-((yyvsp[0].helpInfo)->dVal);
														else if(s=="CHAR"){
															printError("Can't use UNARYOP on CHARs");
															error_count++;
														}
													}

													(yyval.helpInfo)=(yyvsp[0].helpInfo);

													//code-asm
													string tmp=newTemp();
					 								(yyval.helpInfo)->code="mov ax, "+(yyvsp[0].helpInfo)->getName()+"\n";
					 								(yyval.helpInfo)->code+="neg ax\n";
					 								(yyval.helpInfo)->code+="mov "+tmp+", ax\n";

					 								(yyval.helpInfo)->setName(tmp);



												}

												codetracker<<(yyval.helpInfo)->code;
											}
#line 2785 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 1406 "1305043.y" /* yacc.c:1646  */
    {
		 								printNOW("unary_expression : NOT unary_expression ");
		 								
		 								//todo code

		 								if((yyvsp[0].helpInfo)->varType=="DUMMY")(yyval.helpInfo)=(yyvsp[0].helpInfo);

		 								else{
			 								
			 								
			 								string s=(yyvsp[0].helpInfo)->varType;
			 								
			 								if(s==""){
			 									(yyvsp[0].helpInfo)=findInDeclaration((yyvsp[0].helpInfo)->getName());
			 									s=(yyvsp[0].helpInfo)->varType;
			 								}

			 								if(s=="INT")(yyvsp[0].helpInfo)->iVal=!((yyvsp[0].helpInfo)->iVal);
			 								else if(s=="FLOAT")(yyvsp[0].helpInfo)->dVal=!((yyvsp[0].helpInfo)->dVal);
			 								else if(s=="CHAR")
			 								{
												printError("Can't use UNARYOP on CHARs");
												error_count++;
											}
			 								(yyval.helpInfo)=(yyvsp[0].helpInfo);

			 								//code-asm
			 								string tmp=newTemp();
			 								(yyval.helpInfo)->code="mov ax, "+(yyvsp[0].helpInfo)->getName()+"\n";
			 								(yyval.helpInfo)->code+="not ax\n";
			 								(yyval.helpInfo)->code+="mov "+tmp+", ax\n";

			 								(yyval.helpInfo)->setName(tmp);

		 								}

		 								codetracker<<(yyval.helpInfo)->code;
		 							}
#line 2828 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 1447 "1305043.y" /* yacc.c:1646  */
    {
		 			printNOW("unary_expression : factor");
		 			(yyval.helpInfo)=(yyvsp[0].helpInfo);

		 			codetracker<<(yyval.helpInfo)->code;
		 		}
#line 2839 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 1465 "1305043.y" /* yacc.c:1646  */
    {

						printNOW("factor : variable ");
						


						if((yyvsp[0].helpInfo)->varType=="DUMMY")(yyval.helpInfo)=(yyvsp[0].helpInfo);

						else{


							SymbolInfo* real=findInDeclaration((yyvsp[0].helpInfo)->getName());
							SymbolInfo* ret=new SymbolInfo(real->getName(),real->getType());
							ret->varType=real->varType;

							
							real->pIndex=(yyvsp[0].helpInfo)->pIndex;
							real->expIndex=(yyvsp[0].helpInfo)->expIndex;
							

							if((yyvsp[0].helpInfo)->array){	
								if(real->varType=="INT")ret->iVal=(int)real->arrayStorage[real->pIndex];
								else if(real->varType=="FLOAT")ret->dVal=(double)real->arrayStorage[real->pIndex];
								else if(real->varType=="CHAR")ret->chVal=(char)real->arrayStorage[real->pIndex];
								
								//printf("<<%s>>\n",$$->getName().c_str());

								
								//asm-code
								
								(yyval.helpInfo)=ret;
								(yyval.helpInfo)->code=(yyvsp[0].helpInfo)->code;

								

								//printf("HELLOW WORLD %s\n ",$1->getName().c_str());
								(yyval.helpInfo)->code+="lea di, "+(yyvsp[0].helpInfo)->getName()+"\n";

								tl.str("");
								tl<<(yyvsp[0].helpInfo)->expIndex;


								for(int i=0;i<2;i++){
									(yyval.helpInfo)->code+="add di, "+tl.str()+"\n";
								}

								string tmp=newTemp();

								(yyval.helpInfo)->code+="mov "+tmp+", [di]\n";
								(yyval.helpInfo)->setName(tmp);
								(yyval.helpInfo)->pIndex=0;


							}
							else{
								if(real->varType=="INT")ret->iVal=real->iVal;
								else if(real->varType=="FLOAT")ret->dVal=real->dVal;
								else if(real->varType=="CHAR")ret->chVal=real->chVal;
								(yyval.helpInfo)=ret;


								//asm-code??
								

							}
						}

						codetracker<<(yyval.helpInfo)->code;
					}
#line 2913 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 1537 "1305043.y" /* yacc.c:1646  */
    {
									printNOW("factor : LPAREN expression RPAREN");
									(yyval.helpInfo)=(yyvsp[-1].helpInfo);

									codetracker<<(yyval.helpInfo)->code;
								}
#line 2924 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 1546 "1305043.y" /* yacc.c:1646  */
    {
						printNOW("factor : CONST_INT ");
						(yyval.helpInfo)=(yyvsp[0].helpInfo);
						printNOW((yyvsp[0].helpInfo)->getName());

						codetracker<<(yyval.helpInfo)->code;
					}
#line 2936 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 1556 "1305043.y" /* yacc.c:1646  */
    {
						printNOW("factor : CONST_FLOAT ");
						(yyval.helpInfo)=(yyvsp[0].helpInfo);
						printNOW((yyvsp[0].helpInfo)->getName());

						codetracker<<(yyval.helpInfo)->code;
					}
#line 2948 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 1566 "1305043.y" /* yacc.c:1646  */
    {
						printNOW("factor : CONST_CHAR ");
						(yyval.helpInfo)=(yyvsp[0].helpInfo);
						printNOW((yyvsp[0].helpInfo)->getName());

						codetracker<<(yyval.helpInfo)->code;
					}
#line 2960 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 1576 "1305043.y" /* yacc.c:1646  */
    {
						printNOW("factor : INCOP variable ");
						//todo code
						if((yyval.helpInfo)->varType=="DUMMY")(yyval.helpInfo)=(yyvsp[-1].helpInfo);

						else{
							bool print=true;

							SymbolInfo* original=findInDeclaration((yyvsp[-1].helpInfo)->getName());
							if(original==0){
								original=new SymbolInfo("DUMMY","DUMMY");
								original->varType="DUMMY";
								print=false;
							}

							else if((yyvsp[-1].helpInfo)->array){
								original->expIndex=(yyvsp[-1].helpInfo)->expIndex;
								original->pIndex=(yyvsp[-1].helpInfo)->pIndex;

								string s=original->varType;
								if(s=="INT")original->arrayStorage[original->pIndex]++;
								else if(s=="FLOAT")original->arrayStorage[original->pIndex]++;
								else if(s=="CHAR")original->arrayStorage[original->pIndex]++;
								

								
								(yyval.helpInfo)=new SymbolInfo();
								*((yyval.helpInfo))=*original;
								(yyval.helpInfo)->setType("COPY");


								//asm-code
								(yyval.helpInfo)->code="lea di, "+original->getName()+"\n";
								for(int i=0;i<2;i++)(yyval.helpInfo)->code+="add di, "+original->expIndex+"\n";
								(yyval.helpInfo)->code+="inc [di]\n";
							}
							else{


								string s=original->varType;
								if(s=="INT")original->iVal++;
								else if(s=="FLOAT")original->dVal++;
								else if(s=="CHAR")original->chVal++;

								(yyval.helpInfo)=new SymbolInfo();
								(*(yyval.helpInfo))=*original;
								(yyval.helpInfo)->setType("COPY");


								//asm-code
								(yyval.helpInfo)->code="inc "+original->getName()+"\n";
							}

							if(print){
								myTable->Print(logFile);
								fprintf(logFile,"\n\n\n\n");
							}
						}

						codetracker<<(yyval.helpInfo)->code;
					
					}
#line 3027 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 1641 "1305043.y" /* yacc.c:1646  */
    {
						printNOW("factor : DECOP variable ");
						

						//todo code
						if((yyval.helpInfo)->varType=="DUMMY")(yyval.helpInfo)=(yyvsp[-1].helpInfo);

						else{
							bool print=true;

							SymbolInfo* original=findInDeclaration((yyvsp[-1].helpInfo)->getName());
							if(original==0){
								original=new SymbolInfo("DUMMY","DUMMY");
								original->varType="DUMMY";
								print=false;
							}

							else if((yyvsp[-1].helpInfo)->array){
								original->expIndex=(yyvsp[-1].helpInfo)->expIndex;
								original->pIndex=(yyvsp[-1].helpInfo)->pIndex;

								string s=original->varType;
								if(s=="INT")original->arrayStorage[original->pIndex]--;
								else if(s=="FLOAT")original->arrayStorage[original->pIndex]--;
								else if(s=="CHAR")original->arrayStorage[original->pIndex]--;
								

								
								(yyval.helpInfo)=new SymbolInfo();
								*((yyval.helpInfo))=*original;
								(yyval.helpInfo)->setType("COPY");


								//asm-code
								(yyval.helpInfo)->code="lea di, "+original->getName()+"\n";
								for(int i=0;i<2;i++)(yyval.helpInfo)->code+="add di, "+original->expIndex+"\n";
								(yyval.helpInfo)->code+="dec [di]\n";
							}
							else{


								string s=original->varType;
								if(s=="INT")original->iVal--;
								else if(s=="FLOAT")original->dVal--;
								else if(s=="CHAR")original->chVal--;

								(yyval.helpInfo)=new SymbolInfo();
								(*(yyval.helpInfo))=*original;
								(yyval.helpInfo)->setType("COPY");


								//asm-code
								(yyval.helpInfo)->code="dec "+original->getName()+"\n";
							}

							if(print){
								myTable->Print(logFile);
								fprintf(logFile,"\n\n\n\n");
							}
						}

						codetracker<<(yyval.helpInfo)->code;
					
					}
#line 3096 "y.tab.c" /* yacc.c:1646  */
    break;


#line 3100 "y.tab.c" /* yacc.c:1646  */
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
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

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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

#if !defined yyoverflow || YYERROR_VERBOSE
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
  return yyresult;
}
#line 1706 "1305043.y" /* yacc.c:1906  */


main(int argc,char *argv[])
{

	
	marker=0;
	if(argc!=2){
		printf("No input file provided\n");
		return 0;
	}
	
	FILE *fin=fopen(argv[1],"r");
	if(fin==NULL){
		printf("File can't be opened\n");
		return 0;
	}
	codetracker.open("code_tracker.txt");
	
	logFile= fopen("1305043_log.txt","w");
	myTable=new SymbolTable(15);
	yyin=fin;
	yyparse();

	fprintf(logFile,"PRINTING SYMBOL TABLE\n");
	myTable->Print(logFile);
	fprintf(logFile,"\n\n\n\n");

	
	fprintf(logFile,"\n\nPRINTING VARIABLE LIST\n");
	for(int i=0;i<var_count;i++){
		fprintf(logFile,"%s %s %s\n",declaredInfo[i]->getName().c_str(),declaredInfo[i]->getType().c_str(),declaredInfo[i]->varType.c_str());
	}

	for(int i=0;i<var_count;i++){
		codetracker<<declaredInfo[i]->getName()<<"\n"<<declaredInfo[i]->code<<endl;
	}


	fclose(yyin);
	fprintf(logFile,"\n\nTOTAL LINES: %03d\n",line_count);
	fprintf(logFile,"\n\nTOTAL ERRORS: %3d\n",error_count);
	fclose(logFile);

	return 0;
}
