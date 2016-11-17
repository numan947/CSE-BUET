
%{
#include <stdio.h>
#include <stdlib.h>
#define YYSTYPE double      /* yyparse() stack type */

void yyerror(char *s){
	printf("%s\n",s);
}

int yylex(void);

%}

%token IF ELSE FOR WHILE DO BREAK INT CHAR FLOAT DOUBLE VOID RETURN SWITCH CASE DEFAULT CONTINUE INCOP ADDOP MULOP RELOP ASSIGNOP LOGICOP LPAREN RPAREN LCURL RCURL LTHIRD RTHIRD COMMA SEMICOLON ID CONST_LIT FLOAT_LIT CHAR_LIT STRING

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

main(void)
{
	//yydebug=1;
	yyparse();
	return 0;
}
