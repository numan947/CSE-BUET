
%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <string>
#include"1305043_symbolTable.cpp"
#define YYSTYPE double      /* yyparse() stack type */
using namespace std;


void yyerror(char *s){
	printf("%s\n",s);
}

int yylex(void);
extern FILE* yyin;
SymbolTable *myTable;
FILE* logFile;

int line_count=0;
int error_count=0;
int match_count=0;


void printNOW(string line)
{
	stringstream ss;
	ss<<(++match_count);
	line="PARSER RESPONSE "+ss.str()+" . "+line;
	fprintf(logFile,line.c_str());
	fprintf(logFile,"\n\n\n\n");
}

%}

%start Program


%token<helpString> IF ELSE FOR WHILE DO BREAK INT CHAR FLOAT DOUBLE VOID RETURN SWITCH CASE DEFAULT CONTINUE INCOP DECOP ADDOP MULOP RELOP ASSIGNOP LOGICOP LPAREN RPAREN LCURL RCURL LTHIRD RTHIRD COMMA SEMICOLON STRING MAIN PRINTLN NOT


%token<helpInfo>ID CONST_INT CONST_FLOAT CONST_CHAR 


%type <helpString> Program compound_statement statements statement expression_statement var_declaration type_specifier declaration_list

%type <helpInfo> simple_expression rel_expression expression term unary_expression factor variable logic_expression


%nonassoc HELP_ELSE_GET_PRECEDENCE
%nonassoc ELSE

%union {
	SymbolInfo* helpInfo;
	const char* helpString;
}




%%

Program : INT MAIN LPAREN RPAREN compound_statement		{printNOW("Matched Rule>>>Program : INT MAIN LPAREN RPAREN compound_statement"); }
	;


compound_statement : LCURL var_declaration statements RCURL {printNOW("Matched Rule>>>compound_statement : LCURL var_declaration statements RCURL");}
		   | LCURL statements RCURL {printNOW("Matched Rule>>>compound_statement : LCURL statements RCURL");}
		   | LCURL RCURL {printNOW("Matched Rule>>>compound_statement : LCURL RCURL");}
		   ;

			 
var_declaration	: type_specifier declaration_list SEMICOLON {printNOW("Matched Rule>>>var_declaration : type_specifier declaration_list SEMICOLON");}
		|  var_declaration type_specifier declaration_list SEMICOLON {printNOW("Matched Rule>>>var_declaration : var_declaration type_specifier declaration_list SEMICOLON");}
		;

type_specifier	: INT {printNOW("Matched Rule>>>type_specifier : INT");}
		| FLOAT {printNOW("Matched Rule>>>type_specifier : FLOAT");}
		| CHAR 	{printNOW("Matched Rule>>>type_specifier : CHAR");}
		;
			
declaration_list : declaration_list COMMA ID 	{printNOW("Matched Rule>>>declaration_list : declaration_list COMMA ID");}
		 | declaration_list COMMA ID LTHIRD CONST_INT RTHIRD	{printNOW("Matched Rule>>>declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD");}
		 | ID 	{printNOW("Matched Rule>>>declaration_list : ID");}
		 | ID LTHIRD CONST_INT RTHIRD {printNOW("Matched Rule>>>declaration_list : ID LTHIRD CONST_INT RTHIRD");}
		 ;

statements : statement 	{printNOW("Matched Rule>>>statements : statement");}
	   | statements statement 	{printNOW("Matched Rule>>>statements : statements statement");}
	   ;






statement  : expression_statement 	{printNOW("Matched Rule>>>statement  : expression_statement");}
	   | compound_statement 	{printNOW("Matched Rule>>>statement  : compound_statement");}
	   | FOR LPAREN expression_statement expression_statement expression RPAREN statement 	{printNOW("Matched Rule>>>statement  : FOR LPAREN expression_statement expression_statement expression RPAREN statement");}
	   | IF LPAREN expression RPAREN statement %prec HELP_ELSE_GET_PRECEDENCE	{printNOW("Matched Rule>>>statement  : IF LPAREN expression RPAREN statement %prec HELP_ELSE_GET_PRECEDENCE");}
	   | IF LPAREN expression RPAREN statement ELSE statement 	{printNOW("Matched Rule>>>statement  : IF LPAREN expression RPAREN statement ELSE statement");}
	   | WHILE LPAREN expression RPAREN statement 	{printNOW("Matched Rule>>>statement  : WHILE LPAREN expression RPAREN statement");}
	   | PRINTLN LPAREN ID RPAREN SEMICOLON 	{printNOW("Matched Rule>>>statement  : PRINTLN LPAREN ID RPAREN SEMICOLON ");}
	   | RETURN expression SEMICOLON 	{printNOW("Matched Rule>>>statement  : RETURN expression SEMICOLON");}
	   ;



expression_statement	: SEMICOLON		{printNOW("Matched Rule>>>expression_statement : SEMICOLON");}			
			| expression SEMICOLON 	{printNOW("Matched Rule>>>expression_statement : expression SEMICOLON");}
			;
						
variable : ID 	{printNOW("Matched Rule>>>variable : ID ");}				
	 | ID LTHIRD expression RTHIRD  {printNOW("Matched Rule>>>variable : ID LTHIRD expression RTHIRD ");}
	 ;
			
expression : logic_expression	{printNOW("Matched Rule>>>expression : logic_expression");}
	   | variable ASSIGNOP logic_expression 	{printNOW("Matched Rule>>>expression : variable ASSIGNOP logic_expression");}
	   ;
			
logic_expression : rel_expression 	{printNOW("Matched Rule>>>logic_expression : rel_expression");}
		 | rel_expression LOGICOP rel_expression 	{printNOW("Matched Rule>>>logic_expression : rel_expression LOGICOP rel_expression");}	
		 ;
			
rel_expression	: simple_expression  {printNOW("Matched Rule>>>rel_expression : simple_expression");}
		| simple_expression RELOP simple_expression	 {printNOW("Matched Rule>>>rel_expression : simple_expression RELOP simple_expression");}
		;
				
simple_expression : term  {printNOW("Matched Rule>>>simple_expression : term ");}
		  | simple_expression ADDOP term  {printNOW("Matched Rule>>>simple_expression : simple_expression ADDOP term");}
		  ;
					
term :	unary_expression	{printNOW("Matched Rule>>>term :unary_expression");}
     |  term MULOP unary_expression		{printNOW("Matched Rule>>>term : term MULOP unary_expression");}
     ;

unary_expression : ADDOP unary_expression   {printNOW("Matched Rule>>>unary_expression : ADDOP unary_expression");}
		 | NOT unary_expression 	{printNOW("Matched Rule>>>unary_expression : NOT unary_expression ");}
		 | factor {printNOW("Matched Rule>>>unary_expression : factor");}
		 ;
	
factor	: variable 	{printNOW("Matched Rule>>>factor : variable ");}
	| LPAREN expression RPAREN  {printNOW("Matched Rule>>>factor : LPAREN expression RPAREN");}
	| CONST_INT 	{printNOW("Matched Rule>>>factor : CONST_INT ");}
	| CONST_FLOAT	{printNOW("Matched Rule>>>factor : CONST_FLOAT ");}
	| CONST_CHAR	{printNOW("Matched Rule>>>factor : CONST_CHAR ");}
	| factor INCOP 	{printNOW("Matched Rule>>>factor : INCOP ");}
	| factor DECOP	{printNOW("Matched Rule>>>factor : DECOP ");}
	;
%%

main(int argc,char *argv[])
{
/*	//yydebug=1;
	yyparse();
	return 0;
*/


	if(argc!=2){
		printf("No input file provided\n");
		return 0;
	}
	
	FILE *fin=fopen(argv[1],"r");
	if(fin==NULL){
		printf("File can't be opened\n");
		return 0;
	}
	
	logFile= fopen("1305043_log.txt","w");
	myTable=new SymbolTable(15);

	yyin=fin;
	yyparse();



	fclose(yyin);
	fprintf(logFile,"\n\nTOTAL LINES: %03d\n",line_count);
	fclose(logFile);

	return 0;
}
