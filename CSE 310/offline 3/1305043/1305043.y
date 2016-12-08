
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

int line_count=1;
int error_count=0;
int match_count=0;
int var_count=0;

bool err;
int ii;
int marker;


void printError(string s)
{
	
	fprintf(logFile,"Error at line no: %d--%s\n\n\n\n",line_count,s.c_str());

}


void yyerror(char *s){
	printf("Error at line %d:  %s\n",line_count,s);
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
}

%}

%union {
	SymbolInfo* idInfo;
	SymbolInfo* helpInfo;
	const char* helpString;
}


%error-verbose


%start Program


%token<helpString> IF ELSE FOR WHILE DO BREAK INT CHAR FLOAT DOUBLE VOID RETURN SWITCH CASE DEFAULT CONTINUE MAIN PRINTLN 


%token<helpInfo>CONST_INT CONST_FLOAT CONST_CHAR ADDOP INCOP DECOP MULOP RELOP ASSIGNOP LOGICOP LPAREN RPAREN LCURL RCURL LTHIRD RTHIRD COMMA SEMICOLON STRING NOT

%token<idInfo>ID

%type <helpString> Program compound_statement statements statement expression_statement var_declaration declaration_list type_specifier

%type <helpInfo> simple_expression rel_expression expression term unary_expression factor variable logic_expression 




%right DECOP INCOP NOT ASSIGNOP
%left MULOP ADDOP RELOP COMMA


%nonassoc HELP_ELSE_GET_PRECEDENCE
%nonassoc ELSE




%%

Program : INT MAIN LPAREN RPAREN compound_statement		{
														printNOW("Matched Rule>>>Program : INT MAIN LPAREN RPAREN compound_statement"); 
														string s=$5;
														$$=s.c_str();
														}
	;


compound_statement : LCURL var_declaration statements RCURL {
																printNOW("Matched Rule>>>compound_statement : LCURL var_declaration statements RCURL");

																string s=$2;
																$$=s.c_str();

															}
		   

		   | LCURL statements RCURL {
		   							printNOW("Matched Rule>>>compound_statement : LCURL statements RCURL");}
		   

		   | LCURL RCURL {
		   								printNOW("Matched Rule>>>compound_statement : LCURL RCURL");}
		   ;

			 
var_declaration	: type_specifier declaration_list SEMICOLON {
																printNOW("Matched Rule>>>var_declaration : type_specifier declaration_list SEMICOLON");


																//cout<<$1<<endl;

																for(int i=marker;i<var_count;i++){
																	declaredInfo[i]->varType=$1;
																}
																marker=var_count;
																
															}
		


		|  var_declaration type_specifier declaration_list SEMICOLON {
																		printNOW("Matched Rule>>>var_declaration : var_declaration type_specifier declaration_list SEMICOLON");

																		
																		//cout<<$2<<endl;

																		for(int i=marker;i<var_count;i++){
																			declaredInfo[i]->varType=$2;
																		}
																		marker=var_count;

																		
																		
																		

																	}
		;

type_specifier	: INT {
							printNOW("Matched Rule>>>type_specifier : INT");
							$$="INT";
					}
		

		| FLOAT {
					printNOW("Matched Rule>>>type_specifier : FLOAT");
					$$="FLOAT";
				}
		


		| CHAR 	{
					printNOW("Matched Rule>>>type_specifier : CHAR");

					$$="CHAR";
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
														
														printNOW(s);
														myTable->Print(logFile);
														fprintf(logFile,"\n\n\n\n");
													}
													else{
														printError("multiple declarations for "+s);
														error_count++;
													}





												}
		 

		 | declaration_list COMMA ID LTHIRD CONST_INT RTHIRD	{
		 											printNOW("Matched Rule>>>declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD");
		 										
		 											$3->arrayLength=$5->iVal;

													$3->array=true;

													for(int i=0;i<$3->arrayLength;i++)$3->arrayStorage[i]=-1;


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
														
														printNOW(s);
														myTable->Print(logFile);
														fprintf(logFile,"\n\n\n\n");
													}
													else{
														stringstream ss;
														ss<<$3->line;

														printError("multiple declarations for "+s);
														error_count++;
													}

													

		 										}
		 


		 | ID 	{	
		 			printNOW("declaration_list : ID");
					
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
						printNOW(s);
						myTable->Print(logFile);
						fprintf(logFile,"\n\n\n\n");

					}
						else{
									printError("multiple declarations for "+s);
									error_count++;
					}

					

		 		}
		 


		 |  ID LTHIRD CONST_INT RTHIRD  {
		 								
		 								printNOW("declaration_list : ID LTHIRD CONST_INT RTHIRD");

										$1->arrayLength=$3->iVal;
										$1->array=true;
										for(int i=0;i<$1->arrayLength;i++)$1->arrayStorage[i]=-1;
										

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
											
											printNOW(s);
											myTable->Print(logFile);
											fprintf(logFile,"\n\n\n\n");
										}
										else{
											printError("multiple declarations for "+s);
														error_count++;
										}

										
		 									
		 							}
		 ;







statements : statement 	{
							printNOW("statements : statement");

						}
	   


	   | statements statement 	{
	   								printNOW("statements : statements statement");
	   								//??

	   							}
	   ;






statement  : expression_statement 	{
										printNOW("statement  : expression_statement");
										//??
									}
	   

	   | compound_statement 	{
	   								printNOW("statement  : compound_statement");
	   								//??
	   							}
	   


	   | FOR LPAREN expression_statement expression_statement expression RPAREN statement 	{
	   																			
	   																			printNOW("statement  : FOR LPAREN expression_statement expression_statement expression RPAREN statement");


	   																			//LATER??

	   																		}
	   


	   | IF LPAREN expression RPAREN statement %prec HELP_ELSE_GET_PRECEDENCE	{
	   																				printNOW("statement  : IF LPAREN expression RPAREN statement");
	   																				
	   																				//LATER??
	   																			}
	   


	   | IF LPAREN expression RPAREN statement ELSE statement 	{
	   																printNOW("statement  : IF LPAREN expression RPAREN statement ELSE statement");

	   																//LATER??
	   															}
	   


	   | WHILE LPAREN expression RPAREN statement 	{
	   													printNOW("statement  : WHILE LPAREN expression RPAREN statement");
	   												}
	   


	   | PRINTLN LPAREN ID RPAREN SEMICOLON 	{
	   												printNOW("statement  : PRINTLN LPAREN ID RPAREN SEMICOLON ");

	   												if($3->varType=="")$3=findInDeclaration($3->getName());

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
	   											}
	   


	   | RETURN expression SEMICOLON 	{
	   										printNOW("statement  : RETURN expression SEMICOLON");
	   									}
	   ;






expression_statement	: SEMICOLON		{
							printNOW("expression_statement : SEMICOLON");

						}			
			


			| expression SEMICOLON 	{
										printNOW("expression_statement : expression SEMICOLON");

									}
			;
			


variable : ID 	{
						printNOW("variable : ID ");
						//FLAG
						

						SymbolInfo* target=findInDeclaration($1->getName());
						if(target==0){
							printError("undeclared variable "+$1->getName());
							error_count++;
							$$=new SymbolInfo();//dummy??
							$$->varType="DUMMY";

						}
						else if(target->array==true){
							target->pIndex=-1;
							$$=target;
							}

						else $$=target;
				}				
	 


	 | ID LTHIRD expression RTHIRD  {
	 									//cout<<$1->getName()<<endl;
	 									printNOW("variable : ID LTHIRD expression RTHIRD ");
										
										SymbolInfo* target=findInDeclaration($1->getName());

										if($3->varType=="")$3=findInDeclaration($3->getName());

										
										if(target==0){
											printError("undeclared variable "+$1->getName());
											error_count++;
											$$=new SymbolInfo();//dummy??
											$$->varType="DUMMY";
										}
										else if($3->varType!="INT"){
											printError("Index for array "+$1->getName()+" is not INT");
											error_count++;
											$$=new SymbolInfo();//dummy??									
										}
										
										else{
											$$=target;
											$$->pIndex=$3->iVal;
										}

	 								}
	 ;
			





expression : logic_expression	{
									printNOW("expression : logic_expression");
									$$=$1;
								}
	   


	   | variable ASSIGNOP logic_expression 	{
	   												printNOW("expression : variable ASSIGNOP logic_expression");


	   												if($1->varType=="DUMMY")$$=$1;
	   												else if($3->varType=="DUMMY")$$=$3;

	   												else{

	   												SymbolInfo* target=findInDeclaration($1->getName());

	   												if($3->varType=="")$3=findInDeclaration($3->getName());

	   												if(target==0){
	   													//printNOW("ERROR!! Undeclared variable: "+$1->getName());
	   												}


	   												else{

		   													if(target->array==false){

		   														if(target->varType=="INT"&&$3->varType=="INT")target->iVal=$3->iVal;
		   														else if(target->varType=="FLOAT"&&$3->varType=="FLOAT")target->dVal=$3->dVal;
		   														else if(target->varType=="CHAR"&&$3->varType=="CHAR")target->chVal=$3->chVal;
		   														else if(target->varType=="FLOAT"){
		   															if($3->varType=="INT")target->dVal=$3->iVal;
		   															else if($3->varType=="CHAR")target->dVal=$3->chVal;
		   														}
		   														else {
		   															printError("Type Mismatch");
			   														error_count++;
		   														}
		   													}


		   													else if(target->pIndex>-1 && target->pIndex<target->arrayLength){
																
		   														if(target->varType=="INT"){
			   														if($3->varType=="INT")target->arrayStorage[target->pIndex]=(int)$3->iVal;
			   														else{
			   															printError("Type Mismatch");
			   															error_count++;
			   														}
			   													}
			   													else if(target->varType=="FLOAT"){
			   														if($3->varType=="INT")target->arrayStorage[target->pIndex]=(double)$3->iVal;
			   														else if($3->varType=="FLOAT")target->arrayStorage[target->pIndex]=(double)$3->dVal;
			   														else if($3->varType=="CHAR")target->arrayStorage[target->pIndex]=(double)$3->chVal;
			   													}
			   													else if(target->varType=="CHAR"){
			   														if($3->varType=="CHAR")target->arrayStorage[target->pIndex]=(char)$3->chVal;
			   														else {
			   															printError("Type Mismatch");
			   															error_count++;
			   														}
			   													}

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

		   													$$=target;
		   													myTable->Print(logFile);
		   													fprintf(logFile,"\n\n\n\n");
		   												}
	   												}

	   											}
	   ;


logic_expression : rel_expression 	{
										printNOW("logic_expression : rel_expression");
										$$=$1;

									}
		 


		 | rel_expression LOGICOP rel_expression 	{
		 												printNOW("logic_expression : rel_expression LOGICOP rel_expression");


		 												if($1->varType=="DUMMY")$$=$1;
														
														else if($3->varType=="DUMMY")$$=$3;
														
														else{

			 												SymbolInfo* res=new SymbolInfo();
			 												res->varType="INT";
			 												
			 												if($1->varType=="")$1=findInDeclaration($1->getName());
			 												if($3->varType=="")$3=findInDeclaration($3->getName());



			 												if($1->array||$3->array){
																printError("Logic operations on arrays");
																error_count++;
															}
															else{
																float a,b;
																if($1->varType=="INT")a=(double)$1->iVal;
																if($1->varType=="FLOAT")a=$1->dVal;
																if($1->varType=="CHAR")a=(double)$1->chVal;
																if($3->varType=="INT")b=(double)$3->iVal;
																if($3->varType=="FLOAT")b=$3->dVal;
																if($3->varType=="CHAR")b=(double)$3->iVal;

																if($2->getName()=="&&"){
																	res->iVal=(a&&b);
																}
																else if($2->getName()=="||"){
																	res->iVal=(a||b);
																}
																$$=res;
															}		 	
														}										
													}	
		 ;



			
rel_expression	: simple_expression  {
										printNOW("rel_expression : simple_expression");
										$$=$1;
									}
		


		| simple_expression RELOP simple_expression	 {
														//FLAG

														printNOW("rel_expression : simple_expression RELOP simple_expression");

														if($1->varType=="DUMMY")$$=$1;
														else if($3->varType=="DUMMY")$$=$3;
														else{

															SymbolInfo* res=new SymbolInfo();
															res->varType="INT";


															if($1->varType==""){
																$1=findInDeclaration($1->getName());
															}
															
															if($3->varType==""){
																$3=findInDeclaration($3->getName());
															}


															if($1->array||$3->array){
																printNOW("RELOP operations on arrays");
															}
															else{
																float a,b;
																if($1->varType=="INT")a=(double)$1->iVal;
																if($1->varType=="FLOAT")a=$1->dVal;
																if($1->varType=="CHAR")a=(double)$1->chVal;
																if($3->varType=="INT")b=(double)$3->iVal;
																if($3->varType=="FLOAT")b=$3->dVal;
																if($3->varType=="CHAR")b=(double)$3->iVal;

																if($2->getName()=="=="){
																	res->iVal=(a==b);
																}
																else if($2->getName()=="!="){
																	res->iVal=(a!=b);
																}
																else if($2->getName()=="<"){
																	res->iVal=(a<b);
																}
																else if($2->getName()=="<="){
																	res->iVal=(a<=b);
																}
																else if($2->getName()==">"){
																	res->iVal=(a>b);
																}
																else if($2->getName()==">="){
																	res->iVal=(a>=b);
																}
																$$=res;
															}
														}
													}
		;




				
simple_expression : term  {
							printNOW("simple_expression : term ");
							$$=$1;
						}
		  


		  | simple_expression ADDOP term  {

		  									printNOW("simple_expression : simple_expression ADDOP term");

		  									if($3->varType=="DUMMY")$$=$3;

		  									else{
			  									
			  									SymbolInfo* res=new SymbolInfo();
			  									

			  									if($1->varType==""){
			  											//cout<<"GO FIND NEMO "<<$1->getName()<<endl;
			  											$1=findInDeclaration($1->getName());

			  											//cout<<$1->iVal<<endl;
			  										}
			  									if($3->varType==""){
			  											//cout<<"GO FIND NEMO "<<$3->getName()<<endl;
			  											$3=findInDeclaration($3->getName());

			  										}
			  									


	 											if($1->varType=="CHAR"||$3->varType=="CHAR"){
	 													printError("Add operation on CHAR");
	 													error_count++;
	 														
	 											}

	 											if($1->array||$3->array){
	 												printError("Add operation on arrays");
	 												error_count++;
	 											}
	 											


	 											if($2->getName()=="+"){

		 											if($1->varType=="FLOAT"||$3->varType=="FLOAT"){
		 												
		 												if($1->varType=="FLOAT"&&$3->varType=="FLOAT"){
		 														$1->dVal+=$3->dVal;
		 														
		 													}
		 												
		 												else if($1->varType=="FLOAT"){
		 													
		 														$1->dVal+=$3->iVal;
		 													}
		 												
		 												else {
		 														$1->dVal=($1->iVal+$3->dVal);
		 														$1->varType="FLOAT";
		 													}
		 												}
		 											else{
		 													$1->iVal+=$3->iVal;
		 												}
	 											}
	 											else if($2->getName()=="-"){

		 											if($1->varType=="FLOAT"||$3->varType=="FLOAT"){
		 												if($1->varType=="FLOAT"&&$3->varType=="FLOAT")$1->dVal-=$3->dVal;
		 												else if($1->varType=="FLOAT")$1->dVal-=$3->iVal;
		 												else {
		 														$1->dVal=($1->iVal-$3->dVal);
		 														$1->varType="FLOAT";
		 													}
		 												}
		 											else $1->iVal-=$3->iVal;
	 											}

			  									$$=$1;
		  									}

		  								
		  								}
		  ;



					
term :	unary_expression	{
								printNOW("term :unary_expression");
								$$=$1;

							}
     


     |  term MULOP unary_expression		{
     										printNOW("term : term MULOP unary_expression");

     										if($3->varType=="DUMMY")$$=$3;



     										else{

	     										if($1->varType=="")$1=findInDeclaration($1->getName());
	     										if($3->varType=="")$3=findInDeclaration($3->getName());



	     										if($2->getName()=="*"){
	     											if($1->varType=="CHAR"||$3->varType=="CHAR"){
	     												printError("Multiplication operation on CHARs");
	     												error_count++;
	     											}

	     											else if($1->varType=="FLOAT"||$3->varType=="FLOAT"){
	     												if($1->varType=="FLOAT"&&$3->varType=="FLOAT")$1->dVal*=$3->dVal;
	     												else if($1->varType=="FLOAT")$1->dVal*=$3->iVal;
	     												else {
	     														$1->dVal=($1->iVal*$3->dVal);
	     														$1->varType="FLOAT";
	     													}
	     											}
	     											else $1->iVal*=$3->iVal;
	     											$$=$1;
	     										}


												else if($2->getName()=="/"){
	     											if($1->varType=="CHAR"||$3->varType=="CHAR"){
	     												printError("Division operations of CHARs");
	     												error_count++;
	     												}
	     											
	     											else if($1->varType=="FLOAT"||$3->varType=="FLOAT"){
	     												
	     												if($1->varType=="FLOAT"&&$3->varType=="FLOAT")$1->dVal/=$3->dVal;
	     												
	     												else if($1->varType=="FLOAT")$1->dVal/=(double)$3->iVal;
	     												
	     												else {
	     														$1->dVal=((double)$1->iVal/$3->dVal);
	     														$1->varType="FLOAT";
	     													}
	     											}

	     											else $1->iVal/=$3->iVal;
	     											$$=$1;
	     										}  



	     										else if($2->getName()=="%"){
	     											if($1->varType=="CHAR"||$3->varType=="CHAR"||$1->varType=="FLOAT"||$3->varType=="FLOAT"){
	     												printError("Non integer operands on MODULUS");
	     												error_count++;
	     												$1->iVal=-99999;
	     											}
	     											
	     											else $1->iVal%=$3->iVal;
	     											$$=$1;
	     										} 
     										}
  
     									}
     ;









unary_expression : ADDOP unary_expression   {
												printNOW("unary_expression : ADDOP unary_expression");

												if($2->varType=="DUMMY")$$=$2;

												else{
													if($2->varType=="")$2=findInDeclaration($2->getName());


													if($1->getName()=="-"){
														string s=$2->varType;

														if(s=="INT")$2->iVal=-($2->iVal);
														else if(s=="FLOAT")$2->dVal=-($2->dVal);
														else if(s=="CHAR"){
															printError("Can't use UNARYOP on CHARs");
															error_count++;
														}
													}

													$$=$2;
												}
											}
		 


		 | NOT unary_expression 	{
		 								printNOW("unary_expression : NOT unary_expression ");
		 								
		 								if($2->varType=="DUMMY")$$=$2;

		 								else{
			 								
			 								
			 								string s=$2->varType;
			 								
			 								if(s==""){
			 									$2=findInDeclaration($2->getName());
			 									s=$2->varType;
			 								}

			 								if(s=="INT")$2->iVal=!($2->iVal);
			 								else if(s=="FLOAT")$2->dVal=!($2->dVal);
			 								else if(s=="CHAR"){
															printError("Can't use UNARYOP on CHARs");
															error_count++;
														}
			 								$$=$2;
		 								}
		 							}
		 


		 | factor {
		 			printNOW("unary_expression : factor");
		 			$$=$1;
		 		}
		 ;
	










factor	: variable 	{
						//so that the acutal value of the variable remain unchanged

						printNOW("factor : variable ");
						
						if($1->varType=="DUMMY")$$=$1;

						else{
							SymbolInfo* real=findInDeclaration($1->getName());
							SymbolInfo* ret=new SymbolInfo(real->getName(),real->getType());
							ret->varType=real->varType;
							if($1->array){	
								if(real->varType=="INT")ret->iVal=(int)real->arrayStorage[real->pIndex];
								else if(real->varType=="FLOAT")ret->dVal=(double)real->arrayStorage[real->pIndex];
								else if(real->varType=="CHAR")ret->chVal=(char)real->arrayStorage[real->pIndex];
								$$=ret;
							}
							else{
								if(real->varType=="INT")ret->iVal=real->iVal;
								else if(real->varType=="FLOAT")ret->dVal=real->dVal;
								else if(real->varType=="CHAR")ret->chVal=real->chVal;
								$$=ret;
							}
						}
					}
	


	| LPAREN expression RPAREN  {
									printNOW("factor : LPAREN expression RPAREN");
									$$=$2;
								}
	


	| CONST_INT 	{
						printNOW("factor : CONST_INT ");
						$$=$1;
						printNOW($1->getName());
					}
	


	| CONST_FLOAT	{
						printNOW("factor : CONST_FLOAT ");
						$$=$1;
						printNOW($1->getName());
					}
	


	| CONST_CHAR	{
						printNOW("factor : CONST_CHAR ");
						$$=$1;
						printNOW($1->getName());
					}
	


	| factor INCOP 	{
						printNOW("factor : INCOP ");
						if($$->varType=="DUMMY")$$=$1;

						else{
							bool print=true;

							SymbolInfo* original=findInDeclaration($1->getName());
							if(original==0){
								original=$1;
								print=false;
							}
							
							string s=original->varType;
							if(s=="INT")original->iVal++;
							else if(s=="FLOAT")original->dVal++;
							else if(s=="CHAR")original->chVal++;
							$$=original;
							if(print){
								myTable->Print(logFile);
								fprintf(logFile,"\n\n\n\n");
							}
						}
					
					}
	


	| factor DECOP	{
						printNOW("factor : DECOP ");
						
						if($$->varType=="DUMMY")$$=$1;

						else{

							bool print=true;

							SymbolInfo* original=findInDeclaration($1->getName());
							if(original==0){
								original=$1;
								print=false;
							}
							
							string s=original->varType;
							if(s=="INT")original->iVal--;
							else if(s=="FLOAT")original->dVal--;
							else if(s=="CHAR")original->chVal--;
							$$=original;

							if(print){
								myTable->Print(logFile);
								fprintf(logFile,"\n\n\n\n");
							}
						}

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
	fprintf(logFile,"\n\n\n\n");

	
	fprintf(logFile,"\n\nPRINTING VARIABLE LIST\n");
	for(int i=0;i<var_count;i++){
		fprintf(logFile,"%s %s %s\n",declaredInfo[i]->getName().c_str(),declaredInfo[i]->getType().c_str(),declaredInfo[i]->varType.c_str());
	}


	fclose(yyin);
	fprintf(logFile,"\n\nTOTAL LINES: %03d\n",line_count);
	fprintf(logFile,"\n\nTOTAL ERRORS: %3d\n",error_count);
	fclose(logFile);

	return 0;
}
