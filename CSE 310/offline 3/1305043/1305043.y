
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
														printNOW("ERROR!! "+s+" re-declared!!");
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
														printNOW("ERROR!! "+s+" re-declared!!");
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
						printNOW("ERROR!! "+s+" re-declared!!");
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
											printNOW("ERROR!! "+s+" re-declared!!");
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
						if(target==0)printNOW("ERROR!! Undeclared variable: "+$1->getName());
						else $$=$1;
				}				
	 


	 | ID LTHIRD expression RTHIRD  {
	 									printNOW("variable : ID LTHIRD expression RTHIRD ");
										
										SymbolInfo* target=findInDeclaration($1->getName());

										if($3->varType=="")$3=findInDeclaration($3->getName());

										
										if(target==0){
											printNOW("ERROR!! Undeclared variable: "+$1->getName());
											yyerror("ERROR!! Undeclared variable");
										}
										else if($3->varType!="INT"){
											printNOW("ERROR!!: ARRAY INDEX MUST BE INT");
											yyerror("ERROR!!: ARRAY INDEX MUST BE INT");
										}
										
										else{
											$$=target;
											$$->pIndex=$3->iVal;

											/*printNOW($$->getName());
											stringstream o;
 											o<<$$->pIndex;
 											printNOW(o.str());*/
										}

	 								}
	 ;
			





expression : logic_expression	{
									printNOW("expression : logic_expression");
									$$=$1;
								}
	   


	   | variable ASSIGNOP logic_expression 	{
	   												printNOW("expression : variable ASSIGNOP logic_expression");

	   												SymbolInfo* target=findInDeclaration($1->getName());

	   												if($3->varType=="")$3=findInDeclaration($3->getName());

	   												if(target==0){
	   													printNOW("ERROR!! Undeclared variable: "+$1->getName());
	   												}


	   												else{

	   													if(target->array==false){

	   														if(target->varType=="INT"&&$3->varType=="INT")target->iVal=$3->iVal;
	   														else if(target->varType=="FLOAT"&&$3->varType=="FLOAT")target->dVal=$3->dVal;
	   														else if(target->varType=="CHAR"&&$3->varType=="CHAR")target->chVal=$3->chVal;
	   														else printNOW("TYPE MISMATCH");

				   											/*stringstream o;
		 													if(target->varType=="INT")o<<target->iVal;
		 													else if(target->varType=="FLOAT")o<<target->dVal;
		 													printNOW(o.str());*/
	   													}


	   													else{
															
	   														if(target->varType=="INT"){
		   														if($3->varType=="INT")target->arrayStorage[target->pIndex]=(int)$3->iVal;
		   														else if($3->varType=="FLOAT")target->arrayStorage[target->pIndex]=(int)$3->dVal;
		   														else if($3->varType=="CHAR")target->arrayStorage[target->pIndex]=(int)$3->chVal;
		   													}
		   													else if(target->varType=="FLOAT"){
		   														if($3->varType=="INT")target->arrayStorage[target->pIndex]=(double)$3->iVal;
		   														else if($3->varType=="FLOAT")target->arrayStorage[target->pIndex]=(double)$3->dVal;
		   														else if($3->varType=="CHAR")target->arrayStorage[target->pIndex]=(double)$3->chVal;
		   													}
		   													else if(target->varType=="CHAR"){
		   														if($3->varType=="INT")target->arrayStorage[target->pIndex]=(char)$3->iVal;
		   														else if($3->varType=="FLOAT")target->arrayStorage[target->pIndex]=(char)$3->dVal;
		   														else if($3->varType=="CHAR")target->arrayStorage[target->pIndex]=(char)$3->chVal;
		   													}

		   													/*stringstream o;
		 													if(target->varType=="INT")o<<(int)target->arrayStorage[target->pIndex];
		 													else if(target->varType=="FLOAT")o<<(double)target->arrayStorage[target->pIndex];
		 													printNOW(o.str());


		 													for(int i=0;i<target->arrayLength;i++)fprintf(logFile,"%d ",(int)target->arrayStorage[i]);*/

	   													}

	   													$$=target;
	   													myTable->Print(logFile);
	   													fprintf(logFile,"\n\n\n\n");
	   												}

	   											}
	   ;



			
logic_expression : rel_expression 	{
										printNOW("logic_expression : rel_expression");
										$$=$1;

									}
		 


		 | rel_expression LOGICOP rel_expression 	{
		 												printNOW("logic_expression : rel_expression LOGICOP rel_expression");

		 												SymbolInfo* res=new SymbolInfo();
		 												res->varType="INT";
		 												
		 												if($1->varType=="")$1=findInDeclaration($1->getName());
		 												if($3->varType=="")$3=findInDeclaration($3->getName());



		 												if($1->varType!=$3->varType){
		 													printNOW("ERROR!! Type MISMATCH");
		 													yyerror("ERROR!! Type MISMATCH");
		 												}

		 												else if($2->getName()=="&&"){
															if($1->varType=="INT")res->iVal=($1->iVal&&$3->iVal);
															else if($1->varType=="FLOAT"){
																res->iVal=($1->dVal&&$3->dVal);
															}
															else if($1->varType=="CHAR"){
																res->iVal=($1->chVal&&$3->chVal);
															}
														}
														else if($2->getName()=="||"){
															if($1->varType=="INT")res->iVal=($1->iVal||$3->iVal);
															else if($1->varType=="FLOAT"){
																res->iVal=($1->dVal||$3->dVal);
															}
															else if($1->varType=="CHAR"){
																res->iVal=($1->chVal||$3->chVal);
															}
														}


		 												$$=res;
		 											}	
		 ;



			
rel_expression	: simple_expression  {
										printNOW("rel_expression : simple_expression");
										$$=$1;
									}
		


		| simple_expression RELOP simple_expression	 {
														//FLAG

														printNOW("rel_expression : simple_expression RELOP simple_expression");

														SymbolInfo* res=new SymbolInfo();
														res->varType="INT";


														if($1->varType==""){
															$1=findInDeclaration($1->getName());
														}
														
														if($3->varType==""){
															$3=findInDeclaration($3->getName());
														}


														if(($1->varType!=$3->varType)||($1->array&& (!$3->array))||(!$1->array&& ($3->array))){
															printNOW("ERROR!: Type mismatch!!");
															yyerror("ERROR!: Type mismatch!!");
														}

														else if($2->getName()=="=="){
															if($1->varType=="INT"){
																res->iVal=($1->iVal==$3->iVal);
															}
															else if($1->varType=="FLOAT"){
																res->iVal=($1->dVal==$3->dVal);
															}
															else if($1->varType=="CHAR"){
																res->iVal=($1->chVal==$3->chVal);
															}
														}
														else if($2->getName()=="!="){
															if($1->varType=="INT"){
																res->iVal=($1->iVal!=$3->iVal);
															}
															else if($1->varType=="FLOAT"){
																res->iVal=($1->dVal!=$3->dVal);
															}
															else if($1->varType=="CHAR"){
																res->iVal=($1->chVal!=$3->chVal);
															}
														}
														else if($2->getName()=="<"){
															if($1->varType=="INT")res->iVal=($1->iVal<$3->iVal);
															else if($1->varType=="FLOAT"){
																res->iVal=($1->dVal<$3->dVal);
															}
															else if($1->varType=="CHAR"){
																res->iVal=($1->chVal<$3->chVal);
															}
														}
														else if($2->getName()=="<="){
															if($1->varType=="INT")res->iVal=($1->iVal<=$3->iVal);
															else if($1->varType=="FLOAT"){
																res->iVal=($1->dVal<=$3->dVal);
															}
															else if($1->varType=="CHAR"){
																res->iVal=($1->chVal<=$3->chVal);
															}
														}
														else if($2->getName()==">"){
															if($1->varType=="INT")res->iVal=($1->iVal>$3->iVal);
															else if($1->varType=="FLOAT"){
																res->iVal=($1->dVal>$3->dVal);
															}
															else if($1->varType=="CHAR"){
																res->iVal=($1->chVal>$3->chVal);
															}
														}
														else if($2->getName()==">="){
															if($1->varType=="INT")res->iVal=($1->iVal>=$3->iVal);
															else if($1->varType=="FLOAT"){
																res->iVal=($1->dVal>=$3->dVal);
															}
															else if($1->varType=="CHAR"){
																res->iVal=($1->chVal>=$3->chVal);
															}
														}

														$$=res;
													}
		;



				
simple_expression : term  {
							printNOW("simple_expression : term ");
							$$=$1;
						}
		  


		  | simple_expression ADDOP term  {
		  									printNOW("simple_expression : simple_expression ADDOP term");

		  									

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
 														printNOW("CAN'T use ADDOP on CHARS");
 														yyerror("ERROR!! CAN'T use ADDOP on CHARS");
 											}

 											
 											printNOW("HELLO SHOOTING STAR!!");


 											//cout<<"ADDOP  "<<$1->iVal<<"  "<<$3->iVal<<endl;


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
		  ;



					
term :	unary_expression	{
								printNOW("term :unary_expression");
								$$=$1;

							}
     


     |  term MULOP unary_expression		{
     										printNOW("term : term MULOP unary_expression");

     										
     										if($1->varType=="")$1=findInDeclaration($1->getName());
     										if($3->varType=="")$3=findInDeclaration($3->getName());



     										if($2->getName()=="*"){
     											if($1->varType=="CHAR"||$3->varType=="CHAR")printNOW("CAN'T MULTIPLY CHARS");
     											

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
     											if($1->varType=="CHAR"||$3->varType=="CHAR")printNOW("CAN'T DIVIDE CHARS");
     											
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
     											if($1->varType=="CHAR"||$3->varType=="CHAR")printNOW("CAN'T MOD CHARS");
     											
     											else if($1->varType=="FLOAT"||$3->varType=="FLOAT"){
     												printNOW("CAN'T MOD FLOATS");
     												$1->iVal=-99999;
     											}

     											else $1->iVal%=$3->iVal;
     											$$=$1;
     										} 


     										  

     									}
     ;









unary_expression : ADDOP unary_expression   {
												printNOW("unary_expression : ADDOP unary_expression");

												if($2->varType=="")$2=findInDeclaration($2->getName());


												if($1->getName()=="-"){
													string s=$2->varType;

													if(s=="INT")$2->iVal=-($2->iVal);
													else if(s=="FLOAT")$2->dVal=-($2->dVal);
													else if(s=="CHAR")printNOW("ERROR!! Unary "+$1->getName()+" has been done on CHAR: "+$2->getName());
												}

												$$=$2;
											}
		 


		 | NOT unary_expression 	{
		 								printNOW("unary_expression : NOT unary_expression ");
		 								
		 								string s=$2->varType;
		 								
		 								if(s==""){
		 									$2=findInDeclaration($2->getName());
		 									s=$2->varType;
		 								}

		 								if(s=="INT")$2->iVal=!($2->iVal);
		 								else if(s=="FLOAT")$2->dVal=!($2->dVal);
		 								else if(s=="CHAR")printNOW("ERROR!! Unary NOT has been done on CHAR: "+$2->getName());

		 								$$=$2;
		 							}
		 


		 | factor {
		 			printNOW("unary_expression : factor");
		 			$$=$1;
		 		}
		 ;
	










factor	: variable 	{
						//FLAG
						printNOW("factor : variable ");

						if($1->array){
							SymbolInfo* real=findInDeclaration($1->getName());
							SymbolInfo* ret=new SymbolInfo(real->getName(),real->getType());
							ret->varType=real->varType;
							if(real->varType=="INT")ret->iVal=(int)real->arrayStorage[real->pIndex];
							else if(real->varType=="FLOAT")ret->dVal=(double)real->arrayStorage[real->pIndex];
							else if(real->varType=="CHAR")ret->chVal=(char)real->arrayStorage[real->pIndex];
							$$=ret;
						}
						else $$=$1;
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
						string s=$1->varType;
						if(s=="INT")$1->iVal++;
						else if(s=="FLOAT")$1->dVal++;
						else if(s=="CHAR")$1->chVal++;
						else{
						//print ERROR
						}
						$$=$1;
					
					}
	


	| factor DECOP	{
						printNOW("factor : DECOP ");
						
						string s=$1->varType;
						if(s=="INT")$1->iVal--;
						else if(s=="FLOAT")$1->dVal--;
						else if(s=="CHAR")$1->chVal--;
						else{
							//print ERROR
						}

						$$=$1;

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
	fclose(logFile);

	return 0;
}
