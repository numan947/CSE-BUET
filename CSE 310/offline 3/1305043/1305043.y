
%{
#include <stdio.h>
#include <stdlib.h>
#include"1305043_symbolTable.cpp"
#define YYSTYPE double      /* yyparse() stack type */

void yyerror(char *s){
	printf("%s\n",s);
}

int yylex(void);
extern FILE* yyin;
SymbolTable *myTable;
FILE* logFile;

extern int line_count;
extern int error_count;

%}

%token IF ELSE FOR WHILE DO BREAK INT CHAR FLOAT DOUBLE VOID RETURN SWITCH CASE DEFAULT CONTINUE INCOP DECOP ADDOP MULOP RELOP ASSIGNOP LOGICOP LPAREN RPAREN LCURL RCURL LTHIRD RTHIRD COMMA SEMICOLON ID CONST_INT CONST_FLOAT CONST_CHAR STRING MAIN PRINTLN NOT

%%


Program : INT MAIN LPAREN RPAREN compound_statement
	;


compound_statement : LCURL var_declaration statements RCURL
		   | LCURL statements RCURL
		   | LCURL RCURL
		   ;

			 
var_declaration	: type_specifier declaration_list SEMICOLON
		|  var_declaration type_specifier declaration_list SEMICOLON
		;

type_specifier	: INT 
		| FLOAT
		| CHAR
		;
			
declaration_list : declaration_list COMMA ID 
		 | declaration_list COMMA ID LTHIRD CONST_INT RTHIRD
		 | ID 
		 | ID LTHIRD CONST_INT RTHIRD 
		 ;

statements : statement 
	   | statements statement 
	   ;


statement  : expression_statement 
	   | compound_statement 
	   | FOR LPAREN expression_statement expression_statement expression RPAREN statement 
	   | IF LPAREN expression RPAREN statement
	   | IF LPAREN expression RPAREN statement ELSE statement
	   | WHILE LPAREN expression RPAREN statement 
	   | PRINTLN LPAREN ID RPAREN SEMICOLON 
	   | RETURN expression SEMICOLON 
	   ;
		
expression_statement	: SEMICOLON			
			| expression SEMICOLON 
			;
						
variable : ID 		
	 | ID LTHIRD expression RTHIRD 
	 ;
			
expression : logic_expression	
	   | variable ASSIGNOP logic_expression 	
	   ;
			
logic_expression : rel_expression 	
		 | rel_expression LOGICOP rel_expression 	
		 ;
			
rel_expression	: simple_expression 
		| simple_expression RELOP simple_expression	
		;
				
simple_expression : term 
		  | simple_expression ADDOP term 
		  ;
					
term :	unary_expression
     |  term MULOP unary_expression
     ;

unary_expression : ADDOP unary_expression  
		 | NOT unary_expression 
		 | factor 
		 ;
	
factor	: variable 
	| LPAREN expression RPAREN 
	| CONST_INT 
	| CONST_FLOAT
	| CONST_CHAR
	| factor INCOP 
	| factor DECOP
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

	fprintf(logFile,"\n\nTOTAL LINES: %03d\n",line_count);

	fclose(yyin);
	fclose(logFile);
	return 0;
}
