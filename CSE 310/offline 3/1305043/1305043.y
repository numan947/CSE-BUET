
%{
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

int line_count=0;
int error_count=0;
int match_count=0;
int var_count=0;

bool err;
int ii;
int marker;



void yyerror(char *s){
	printf("%s\n",s);
}

int yylex(void);



void printNOW(string line)
{
	fprintf(logFile,line.c_str());
	fprintf(logFile,"\n\n\n\n");
}

%}

%union {
	SymbolInfo* idInfo;
	SymbolInfo* helpInfo;
	const char* helpString;
}




%start Program


%token<helpString> IF ELSE FOR WHILE DO BREAK INT CHAR FLOAT DOUBLE VOID RETURN SWITCH CASE DEFAULT CONTINUE INCOP DECOP ADDOP MULOP RELOP ASSIGNOP LOGICOP LPAREN RPAREN LCURL RCURL LTHIRD RTHIRD COMMA SEMICOLON STRING MAIN PRINTLN NOT


%token<helpInfo>CONST_INT CONST_FLOAT CONST_CHAR 
%token<idInfo>ID

%type <helpString> Program compound_statement statements statement expression_statement var_declaration declaration_list

%type <helpInfo> simple_expression rel_expression expression term unary_expression factor variable logic_expression type_specifier


%nonassoc HELP_ELSE_GET_PRECEDENCE
%nonassoc ELSE




%%

Program : INT MAIN LPAREN RPAREN compound_statement		{
														printNOW("Matched Rule>>>Program : INT MAIN LPAREN RPAREN compound_statement"); 
														}
	;


compound_statement : LCURL var_declaration statements RCURL {
									printNOW("Matched Rule>>>compound_statement : LCURL var_declaration statements RCURL");}
		   

		   | LCURL statements RCURL {
		   							printNOW("Matched Rule>>>compound_statement : LCURL statements RCURL");}
		   

		   | LCURL RCURL {
		   								printNOW("Matched Rule>>>compound_statement : LCURL RCURL");}
		   ;

			 
var_declaration	: type_specifier declaration_list SEMICOLON {
																printNOW("Matched Rule>>>var_declaration : type_specifier declaration_list SEMICOLON");
																cout<<$1->getType()<<endl;

																for(int i=marker;i<var_count;i++){
																	declaredInfo[i]->varType=$1->getType();
																}
																marker=var_count;
															}
		


		|  var_declaration type_specifier declaration_list SEMICOLON {
																		printNOW("Matched Rule>>>var_declaration : var_declaration type_specifier declaration_list SEMICOLON");

																		
																		cout<<$2->getType()<<endl;

																		for(int i=marker;i<var_count;i++){
																			declaredInfo[i]->varType=$2->getType();
																		}
																		marker=var_count;
																		

																	}
		;

type_specifier	: INT {
							printNOW("Matched Rule>>>type_specifier : INT");
							SymbolInfo* s=new SymbolInfo("DUMMY","INT");
							$$=s; 
							
					}
		

		| FLOAT {
					printNOW("Matched Rule>>>type_specifier : FLOAT");
					
					SymbolInfo* s=new SymbolInfo("DUMMY","FLOAT");
					$$=s; 
					
				}
		


		| CHAR 	{
					printNOW("Matched Rule>>>type_specifier : CHAR");

					SymbolInfo* s=new SymbolInfo("DUMMY","CHAR");
					$$=s; 

				}
		;
			
declaration_list : declaration_list COMMA ID 	{
													printNOW("Matched Rule>>>declaration_list : declaration_list COMMA ID");

													string s=""+$3->getName();

													$3->array=false;


													err=false;
													for(ii=0;ii<var_count;ii++){
														string s1=""+declaredInfo[ii]->getName();

														if(s1==s){
															err=true;
															break;
														}			
													}
													

													if(!err){
														myTable->Insert(*$3);
														declaredInfo[var_count++]=myTable->getSymbolInfo(s);

													}
													else{
														printNOW("ERROR!! "+s+" re-declared!!");
													}



												}
		 

		 | declaration_list COMMA ID LTHIRD CONST_INT RTHIRD	{
		 											printNOW("Matched Rule>>>declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD");
		 										
		 											$3->arrayLength=$5->iVal;
													$3->array=true;

													string s=""+$3->getName();


													err=false;
													for(ii=0;ii<var_count;ii++){
														string s1=""+declaredInfo[ii]->getName();

														if(s1==s){
															err=true;
															break;
														}			
													}
													

													if(!err){
														myTable->Insert(*$3);
														declaredInfo[var_count++]=myTable->getSymbolInfo(s);

													}
													else{
														printNOW("ERROR!! "+s+" re-declared!!");
													}

		 										}
		 


		 | ID 	{	
		 			printNOW("Matched Rule>>>declaration_list : ID");
					
					string s=""+$1->getName();

					$1->array=false;


					err=false;
					for(ii=0;ii<var_count;ii++){
						string s1=""+declaredInfo[ii]->getName();

						if(s1==s){
							err=true;
							break;
						}			
					}
					

					if(!err){
						myTable->Insert(*$1);
						declaredInfo[var_count++]=myTable->getSymbolInfo(s);

					}
					else{
						printNOW("ERROR!! "+s+" re-declared!!");
					}

		 		}
		 


		 |  ID LTHIRD CONST_INT RTHIRD  {
		 								
		 								printNOW("Matched Rule>>>declaration_list : ID LTHIRD CONST_INT RTHIRD");

										$1->arrayLength=$3->iVal;
										$1->array=true;

										string s=""+$1->getName();


										err=false;
										for(ii=0;ii<var_count;ii++){
											string s1=""+declaredInfo[ii]->getName();

											if(s1==s){
												err=true;
												break;
											}			
										}
										

										if(!err){
											myTable->Insert(*$1);
											declaredInfo[var_count++]=myTable->getSymbolInfo(s);

										}
										else{
											printNOW("ERROR!! "+s+" re-declared!!");
										}
		 									
		 							}
		 ;




statements : statement 	{
							printNOW("Matched Rule>>>statements : statement");
							//??

						}
	   


	   | statements statement 	{
	   								printNOW("Matched Rule>>>statements : statements statement");
	   								//??

	   							}
	   ;






statement  : expression_statement 	{
										printNOW("Matched Rule>>>statement  : expression_statement");
										//??
									}
	   

	   | compound_statement 	{
	   								printNOW("Matched Rule>>>statement  : compound_statement");
	   								//??
	   							}
	   


	   | FOR LPAREN expression_statement expression_statement expression RPAREN statement 	{
	   																			
	   																			printNOW("Matched Rule>>>statement  : FOR LPAREN expression_statement expression_statement expression RPAREN statement");


	   																			//LATER??

	   																		}
	   


	   | IF LPAREN expression RPAREN statement %prec HELP_ELSE_GET_PRECEDENCE	{
	   																				printNOW("Matched Rule>>>statement  : IF LPAREN expression RPAREN statement");
	   																				
	   																				//LATER??
	   																			}
	   


	   | IF LPAREN expression RPAREN statement ELSE statement 	{
	   																printNOW("Matched Rule>>>statement  : IF LPAREN expression RPAREN statement ELSE statement");

	   																//LATER??
	   															}
	   


	   | WHILE LPAREN expression RPAREN statement 	{
	   													printNOW("Matched Rule>>>statement  : WHILE LPAREN expression RPAREN statement");

	   													//LATER??

	   												}
	   


	   | PRINTLN LPAREN ID RPAREN SEMICOLON 	{
	   												printNOW("Matched Rule>>>statement  : PRINTLN LPAREN ID RPAREN SEMICOLON ");

	   												ostringstream o;

	   												if($3->array==false){
		   												if($3->getType()=="INT"){
		   													o<<$3->iVal;
		   													printNOW(o.str());
		   												}
		   												else if($3->getType()=="FLOAT"){
		   													o<<$3->dVal;
		   													printNOW(o.str());
		   												}
		   												else if($3->getType()=="CHAR"){
		   													o<<$3->chVal;
		   													printNOW(o.str());
		   												}
	   												}
	   												else{
		   												if($3->getType()=="INT"){
		   													for(int i=0;i<$3->arrayLength;i++)printf("%d ",(int)$3->arrayStorage[i]);
		   												}
		   												else if($3->getType()=="FLOAT"){
		   													for(int i=0;i<$3->arrayLength;i++)printf("%lf ",(double)$3->arrayStorage[i]);
		   												}
		   												else if($3->getType()=="CHAR"){
		   													for(int i=0;i<$3->arrayLength;i++)printf("%c ",(char)$3->arrayStorage[i]);
		   												}
	   												}

	   												//later???????what The fuck??

	   											}
	   


	   | RETURN expression SEMICOLON 	{
	   										printNOW("Matched Rule>>>statement  : RETURN expression SEMICOLON");
	   										

	   										//Later??
	   									}
	   ;



expression_statement	: SEMICOLON		{
							printNOW("Matched Rule>>>expression_statement : SEMICOLON");

						}			
			


			| expression SEMICOLON 	{
										printNOW("Matched Rule>>>expression_statement : expression SEMICOLON");
										//LATER??

									}
			;
						
variable : ID 	{
						printNOW("Matched Rule>>>variable : ID ");
						//LATER
						$$=$1;

				}				
	 


	 | ID LTHIRD expression RTHIRD  {
	 									printNOW("Matched Rule>>>variable : ID LTHIRD expression RTHIRD ");
	 									$$=$1;

	 									//later
	 								}
	 ;
			
expression : logic_expression	{
									printNOW("Matched Rule>>>expression : logic_expression");
									$$=$1;
								}
	   


	   | variable ASSIGNOP logic_expression 	{
	   												printNOW("Matched Rule>>>expression : variable ASSIGNOP logic_expression");
	   												$$=$1;
	   												//LATER

	   											}
	   ;



			
logic_expression : rel_expression 	{
										printNOW("Matched Rule>>>logic_expression : rel_expression");
										$$=$1;

									}
		 


		 | rel_expression LOGICOP rel_expression 	{
		 												printNOW("Matched Rule>>>logic_expression : rel_expression LOGICOP rel_expression");
		 												$$=$1;

		 												//LATER
		 											}	
		 ;



			
rel_expression	: simple_expression  {
										printNOW("Matched Rule>>>rel_expression : simple_expression");
										$$=$1;


									}
		


		| simple_expression RELOP simple_expression	 {

														printNOW("Matched Rule>>>rel_expression : simple_expression RELOP simple_expression");
														$$=$1;
														//later


													}
		;



				
simple_expression : term  {
							printNOW("Matched Rule>>>simple_expression : term ");
							$$=$1;
						}
		  


		  | simple_expression ADDOP term  {
		  										printNOW("Matched Rule>>>simple_expression : simple_expression ADDOP term");

		  								//will come later

		  									$$=$1;

		  								}
		  ;



					
term :	unary_expression	{
								printNOW("Matched Rule>>>term :unary_expression");
								$$=$1;

							}
     


     |  term MULOP unary_expression		{
     										printNOW("Matched Rule>>>term : term MULOP unary_expression");
     										if($2=="*"){
     											if($1->getType()==$3->getType()&&$1->getType()=="INT")$1->iVal*=$3->iVal;

     											else if($1->getType()=="INT"&&$3->getType()=="FLOAT"){
     												$1->dVal=($1->iVal*$3->dVal);
     												$1->setType("FLOAT");
     											}
     											else if($1->getType()=="FLOAT"&&$3->getType()=="INT")$1->dVal=($1->dVal*$3->iVal);
     											else $1->dVal*=$3->dVal;
     										}

     										else if($2=="/"){
     											if($1->getType()=="FLOAT"||$3->getType()=="FLOAT"){
     												if($1->getType()=="FLOAT"&&$3->getType()=="FLOAT"){
     													$1->dVal=$1->dVal/($3->dVal);
     												}
     												else if($1->getType()=="FLOAT"){
     													$1->dVal=$1->dVal/($3->iVal);
     												}
     												else{
     													$1->dVal=$1->iVal/($3->dVal);
     													$1->setType("FLOAT");
     												}
     											}

     										}
     										else if($2=="%"){
     											if($1->getType()==$3->getType()&&$1->getType()=="INT"){
     												$1->iVal=$1->iVal % $3->iVal;
     											}
     											//else error??
     										}

     										$$=$1;
     							

     									}
     ;





unary_expression : ADDOP unary_expression   {
												printNOW("Matched Rule>>>unary_expression : ADDOP unary_expression");

												if($1=="-"){
													string s=$2->getType();

													if(s=="INT")$2->iVal=-($2->iVal);
													else if(s=="FLOAT")$2->dVal=-($2->dVal);

												}

												$$=$2;
											}
		 


		 | NOT unary_expression 	{
		 								printNOW("Matched Rule>>>unary_expression : NOT unary_expression ");
		 								string s=$2->getType();

		 								if(s=="INT")$2->iVal=!($2->iVal);
		 								else if(s=="FLOAT")$2->dVal=!($2->dVal);

		 								$$=$2;
		 							}
		 


		 | factor {
		 			printNOW("Matched Rule>>>unary_expression : factor");
		 			$$=$1;
		 		}
		 ;
	


factor	: variable 	{
						printNOW("Matched Rule>>>factor : variable ");
						$$=$1;
					}
	


	| LPAREN expression RPAREN  {
									printNOW("Matched Rule>>>factor : LPAREN expression RPAREN");
									$$=$2;
								}
	


	| CONST_INT 	{
						printNOW("Matched Rule>>>factor : CONST_INT ");
						$$=$1;
					}
	


	| CONST_FLOAT	{
						printNOW("Matched Rule>>>factor : CONST_FLOAT ");
						$$=$1;
					}
	


	| CONST_CHAR	{
						printNOW("Matched Rule>>>factor : CONST_CHAR ");
						$$=$1;
					}
	


	| factor INCOP 	{
						printNOW("Matched Rule>>>factor : INCOP ");
						string s=$$->getType();
						if(s=="INT")$1->iVal++;
						else if(s=="FLOAT")$1->dVal++;
						else if(s=="CHAR")$1->chVal++;

						$$=$1;
					
					}
	


	| factor DECOP	{
						printNOW("Matched Rule>>>factor : DECOP ");
						
						string s=$$->getType();
						if(s=="INT")$1->iVal--;
						else if(s=="FLOAT")$1->dVal--;
						else if(s=="CHAR")$1->chVal--;

					}
	;
%%

main(int argc,char *argv[])
{
/*	//yydebug=1;
	yyparse();
	return 0;
*/
	
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
	
	logFile= fopen("1305043_log.txt","w");
	myTable=new SymbolTable(15);
	yyin=fin;
	yyparse();

	fprintf(logFile,"PRINTING SYMBOL TABLE\n");
	myTable->Print(logFile);

	
	fprintf(logFile,"\n\nPRINTING VARIABLE LIST\n");
	for(int i=0;i<var_count;i++){
		fprintf(logFile,"%s %s %s\n",declaredInfo[i]->getName().c_str(),declaredInfo[i]->getType().c_str(),declaredInfo[i]->varType.c_str());
	}


	fclose(yyin);
	fprintf(logFile,"\n\nTOTAL LINES: %03d\n",line_count);
	fclose(logFile);

	return 0;
}
