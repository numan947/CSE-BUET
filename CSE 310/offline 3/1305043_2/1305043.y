
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

%type <helpString> type_specifier

%type <helpInfo> statement expression_statement declaration_list var_declaration statements compound_statement Program simple_expression rel_expression expression term unary_expression factor variable logic_expression 




%right DECOP INCOP NOT ASSIGNOP
%left MULOP ADDOP RELOP COMMA


%nonassoc HELP_ELSE_GET_PRECEDENCE
%nonassoc ELSE




%%

Program : INT MAIN LPAREN RPAREN compound_statement		{
														printNOW("Program : INT MAIN LPAREN RPAREN compound_statement"); 

														//todo insert appropriate data segment register initialization code and others like main proc


														$$=$5;

														ofstream fout;
														fout.open("1305043_code.asm");

														fout<<"TITLE PROGRAM:numan947\n";
														fout<<".model small\n.stack 100h\n";


														fout<<$$->code;

														fout<<"\nmain endp\nend main\n";
														fout.close();


														codetracker<<$$->code;

														}
	;


compound_statement : LCURL var_declaration statements RCURL {
																printNOW("compound_statement : LCURL var_declaration statements RCURL");

																$$=new SymbolInfo("COPY","COPY");
																$$->code="\n.data\n\n";

																$$->code+=$2->code;
																for(int i=0;i<temp_count;i++){
																	tl.str("");
																	tl<<i;
																	$$->code+="t"+tl.str()+" dw ?\n";
																}

																$$->code+="\n.code\n\nmain proc\n\nmov ax ,@data\nmov ds ,ax\n";
																$$->code+=$3->code;

																codetracker<<$$->code;
															}
		   

		   | LCURL statements RCURL {
		   							printNOW("compound_statement : LCURL statements RCURL");
		   							$$=$2;


		   							codetracker<<$$->code;
		   						}
		   

		   | LCURL RCURL {
		   					printNOW("compound_statement : LCURL RCURL");
		   					$$=new SymbolInfo("compound_statement","DUMMY");
		   					

		   					codetracker<<$$->code;		

		   				}
		   ;

			 
var_declaration	: type_specifier declaration_list SEMICOLON {
																printNOW("var_declaration : type_specifier declaration_list SEMICOLON");


																for(int i=marker;i<var_count;i++){
																	declaredInfo[i]->varType=$1;
																}
																marker=var_count;

																$$=$2;
																

																codetracker<<$$->code;
															}
		


		|  var_declaration type_specifier declaration_list SEMICOLON {
																		printNOW("var_declaration : var_declaration type_specifier declaration_list SEMICOLON");

																		
																		//cout<<$2<<endl;

																		for(int i=marker;i<var_count;i++){
																			declaredInfo[i]->varType=$2;
																		}
																		marker=var_count;



																		$$=$1;
																		$$->code+=$3->code;

																		codetracker<<$$->code;

																	}
		;

type_specifier	: INT {
							printNOW("type_specifier : INT");
							$$="INT";
					}
		

		| FLOAT {
					printNOW("type_specifier : FLOAT");
					$$="FLOAT";
				}
		


		| CHAR 	{
					printNOW("type_specifier : CHAR");

					$$="CHAR";
				}
		;
			



declaration_list : declaration_list COMMA ID 	{
													printNOW("declaration_list : declaration_list COMMA ID");

													//todo code;

													$$=$1;

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

														string retCode=s+" dw "+"?\n";

														//concat the code to print
														$$->code+=retCode;

													}
													else{
														printError("multiple declarations for "+s);
														error_count++;
													}


													codetracker<<$$->code;


												}
		 

		 | declaration_list COMMA ID LTHIRD CONST_INT RTHIRD	{
		 											printNOW("declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD");
		 											
		 											//todo code

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


														//code
														string retCode=s+" dw "+"?";

														for(int a=0;a<declaredInfo[var_count-1]->arrayLength-1;a++){
															retCode+=" ,?";												
														}
														retCode+="\n";

														//concat the code to print
														$$->code+=retCode;




													}
													else{
														stringstream ss;
														ss<<$3->line;

														printError("multiple declarations for "+s);
														error_count++;
													}

													codetracker<<$$->code;
													

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


						//code
						string retCode=s+" dw "+"?\n";

						//copy the code from SymbolInfo
						$$=new SymbolInfo("COPY","COPY");
						$$->code= retCode;
						


					}
					else{	
							printError("multiple declarations for "+s);
							error_count++;

							//code
							SymbolInfo *copy=new SymbolInfo("ERROR","ERROR");

							tl.str("");
							tl<<line_count;

							copy->code="Error at "+tl.str()+"\n";
							$$=copy;
						}

						codetracker<<$$->code;

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



											//code
											string retCode=s+" dw "+"?";

											for(int a=0;a<declaredInfo[var_count-1]->arrayLength-1;a++){
												retCode+=" ,?";												
											}
											retCode+="\n";
											
											//copy the code for printing :)
											$$=new SymbolInfo("COPY","COPY");
											$$->code=retCode;


										}
										else{
											printError("multiple declarations for "+s);
											error_count++;
											SymbolInfo *copy=new SymbolInfo("ERROR","ERROR");
											
											tl.str("");
											tl<<line_count;

											copy->code="Error at "+tl.str()+"\n";
											$$=copy;
										}
									codetracker<<$$->code;
		 									
		 				}
		 ;







statements : statement 	{
							printNOW("statements : statement");
							$$=$1;
							codetracker<<$$->code;

						}
	   


	   | statements statement 	{
	   								printNOW("statements : statements statement");
	   								$$=$1;
	   								$$->code+=$2->code;

	   								codetracker<<"SPC11: \n"<<$1->code<<"\n";
	   								codetracker<<"SPC22: \n"<<$2->code<<"\n";

	   								codetracker<<$$->code;
	   							}
	   ;






statement  : expression_statement 	{
										printNOW("statement  : expression_statement");
										$$=$1;
										codetracker<<$$->code;
									}
	   

	   | compound_statement 	{
	   								printNOW("statement  : compound_statement");
	   								$$=$1;
	   								codetracker<<$$->code;
	   							}
	   


	   | FOR LPAREN expression_statement expression_statement expression RPAREN statement 	{
	   																			
	   																			printNOW("statement  : FOR LPAREN expression_statement expression_statement expression RPAREN statement");


	   																			//todo code

	   																		}
	   


	   | IF LPAREN expression RPAREN statement %prec HELP_ELSE_GET_PRECEDENCE	{
	   																				printNOW("statement  : IF LPAREN expression RPAREN statement");
	   																				
	   																				$$=$3;

	   																				string label=newLabel();
	   																				$$->code+="mov ax, "+$3->getName()+"\n";
	   																				$$->code+="cmp ax, 1\n";
	   																				$$->code+="jne "+label+"\n";
	   																				$$->code+=$5->code;
	   																				$$->code+=label+":\n";


	   																				codetracker<<$$->code;

	   																			}
	   


	   | IF LPAREN expression RPAREN statement ELSE statement 	{
	   																printNOW("statement  : IF LPAREN expression RPAREN statement ELSE statement");

	   																//todo code

	   																string l1=newLabel();
	   																string l2=newLabel();

	   																$$=$3;
	   																$$->code+="mov ax, "+$3->getName()+"\n";
	   																$$->code+="cmp ax, 1\n";
	   																$$->code+="jl "+l1+"\n";
	   																$$->code+=$5->code;
	   																$$->code+="jump "+l2+"\n";
	   																$$->code+=l1+":\n"+$7->code;
	   																$$->code+=l2+":\n";

	   																codetracker<<$$->code;
	   															}
	   


	   | WHILE LPAREN expression RPAREN statement 	{
	   													printNOW("statement  : WHILE LPAREN expression RPAREN statement");

	   													//todo code

	   												}
	   


	   | PRINTLN LPAREN ID RPAREN SEMICOLON 	{
	   												printNOW("statement  : PRINTLN LPAREN ID RPAREN SEMICOLON ");

	   												//todo code

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
	   										
	   										//asm-code

	   										$$=$2;
	   										$$->code+="mov ah, 4ch\nint 21h\n";

	   										codetracker<<$$->code;

	   									}
	   ;






expression_statement	: SEMICOLON		{
							printNOW("expression_statement : SEMICOLON");
							$$=new SymbolInfo(";","SEMICOLON");
							$$->code="";

							codetracker<<$$->code;
						}			
			


			| expression SEMICOLON 	{
										printNOW("expression_statement : expression SEMICOLON");

										$$=$1;

										codetracker<<$$->code;
									
									}
			;
			



variable : ID 	{
						printNOW("variable : ID ");
						//FLAG
						

						SymbolInfo* target=findInDeclaration($1->getName());
						

						if(target==0){
							printError("undeclared variable "+$1->getName());
							error_count++;
							$$=new SymbolInfo();
							$$->varType="DUMMY";

						}
						else if(target->array==true){
							SymbolInfo* fun=new SymbolInfo();
							*fun=*target;
							fun->setType("COPY");
							$$=fun;
							$$->pIndex=-1;
						}

						else {
							SymbolInfo* fun=new SymbolInfo();
							*fun=*target;
							fun->setType("COPY");
							$$=fun;

						}


						codetracker<<$$->code;
				}				
	 


	 | ID LTHIRD expression RTHIRD  {
	 									
	 									printNOW("variable : ID LTHIRD expression RTHIRD ");
										
										SymbolInfo* target=findInDeclaration($1->getName());

										if($3->varType=="")$3=findInDeclaration($3->getName());

										
										if(target==0){
											printError("undeclared variable "+$1->getName());
											error_count++;
											$$=new SymbolInfo();
											$$->varType="DUMMY";
										}

										else if($3->varType!="INT"){
											printError("Index for array "+$1->getName()+" is not INT");
											error_count++;
											$$=new SymbolInfo("DUMMY","DUMMY");
											$$->varType="DUMMY";								
										}
										
										else{

											printf("<%d>\n",$3->iVal);
											printf("<%s>\n",$3->getName().c_str());

											SymbolInfo* fun=new SymbolInfo();

											*fun=*target;
											fun->setType("COPY");

											$$=fun;

											$$->pIndex=$3->iVal;
											$$->code=$3->code;
											$$->expIndex=$3->getName();
										}


										codetracker<<$$->code;

	 								}
	 ;
			




expression : logic_expression	{
									printNOW("expression : logic_expression");
									$$=$1;

									codetracker<<$$->code;
								}
	   


	   | variable ASSIGNOP logic_expression 	{
	   												printNOW("expression : variable ASSIGNOP logic_expression");

	   												

	   												//todo code

	   												if($1->varType=="DUMMY")$$=$1;
	   												
	   												else if($3->varType=="DUMMY")$$=$3;

	   												

	   												else{

		   												SymbolInfo* target=findInDeclaration($1->getName());

		   												if($3->varType=="")$3=findInDeclaration($3->getName());

		   												if($1->getType()=="COPY"){
		   													target->expIndex=$1->expIndex;
		   													target->pIndex=$1->pIndex;
		   												}

		   												//code-asm
		   												$$=new SymbolInfo("COPY","COPY");
		   												$$->code=$3->code+target->code;
		   												$$->code+="mov ax, "+$3->getName()+"\n";


		   												if(target==0){
		   													//check for error later :/ 
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
			   														$$->code+="mov "+target->getName()+", ax\n";
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


				   													$$->code+="lea di, "+target->getName()+"\n";

				   													tl.str("");
				   													
				   													tl<<target->expIndex;

				   													for(int i=0;i<2;i++){
				   														$$->code+="add di, "+tl.str()+"\n";
				   													}
				   													$$->code+="mov [di], ax\n";

				   													$$->pIndex=-1;


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

		   												codetracker<<$$->code;

	   											}
	   ;


logic_expression : rel_expression 	{
										printNOW("logic_expression : rel_expression");
										$$=$1;

										codetracker<<$$->code;

									}
		 


		 | rel_expression LOGICOP rel_expression 	{
		 												printNOW("logic_expression : rel_expression LOGICOP rel_expression");

		 												//todo code

		 												if($1->varType=="DUMMY")$$=$1;
														
														else if($3->varType=="DUMMY")$$=$3;
														
														else{

			 												SymbolInfo* res=new SymbolInfo("COPY","COPY");
			 												res->varType="INT";
			 												
			 												if($1->varType=="")$1=findInDeclaration($1->getName());
			 												if($3->varType=="")$3=findInDeclaration($3->getName());

			 												//code-asm
			 												bool ok=true;
															$$=res;
															$$->code=$1->code+$3->code;
															

															string tmp=newTemp();
															string l1=newLabel();
															string l2=newLabel();




			 												if($1->array||$3->array){
																printError("Logic operations on arrays");
																error_count++;
																ok=false;
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


																	$$->code+="cmp "+$1->getName()+",1\n";
																	$$->code+="jne "+l1+"\n";
																	$$->code+="cmp "+$3->getName()+",1\n";
																	$$->code+="jne "+l1+"\n";

																	$$->code+="mov "+tmp+", 1\n";
																	$$->code+="jmp "+l2+"\n";
																	
																	$$->code+=l1+":\nmov "+tmp+", 0\n";
																	$$->code+=l2+":\n";
																}
																else if($2->getName()=="||"){
																	res->iVal=(a||b);


																	$$->code+="cmp "+$1->getName()+",1\n";
																	$$->code+="je "+l1+"\n";
																	$$->code+="cmp "+$3->getName()+",1\n";
																	$$->code+="je "+l1+"\n";

																	$$->code+="mov "+tmp+", 0\n";
																	$$->code+="jmp "+l2+"\n";
																	$$->code+=l1+":\nmov "+tmp+", 1\n";
																	$$->code+=l2+":\n";
																} 

																$$->setName(tmp);
																
															}		 	
														}		


														codetracker<<$$->code;								
													}	
		 ;



			
rel_expression	: simple_expression  {
										printNOW("rel_expression : simple_expression");
										$$=$1;

										codetracker<<$$->code;
									}
		


		| simple_expression RELOP simple_expression	 {
														//FLAG

														printNOW("rel_expression : simple_expression RELOP simple_expression");

														//todo code

														if($1->varType=="DUMMY")$$=$1;
														else if($3->varType=="DUMMY")$$=$3;
														else{

															SymbolInfo* res=new SymbolInfo("COPY","COPY");
															res->varType="INT";


															if($1->varType==""){
																$1=findInDeclaration($1->getName());
															}
															
															if($3->varType==""){
																$3=findInDeclaration($3->getName());
															}

															//code-asm

															bool ok=true;
															$$=res;
															$$->code=$1->code+$3->code;
															$$->code+="mov ax, "+$1->getName()+"\n";
															$$->code+="cmp ax, "+$3->getName()+"\n";

															string tmp=newTemp();
															string l1=newLabel();
															string l2=newLabel();






															if($1->array||$3->array){
																printNOW("RELOP operations on arrays");
																ok=false;

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
																	$$->code+="je "+l1+"\n";

																}
																else if($2->getName()=="!="){
																	res->iVal=(a!=b);
																	$$->code+="jne "+l1+"\n";
																}
																else if($2->getName()=="<"){
																	res->iVal=(a<b);
																	$$->code+="jl "+l1+"\n";
																}
																else if($2->getName()=="<="){
																	res->iVal=(a<=b);
																	$$->code+="jle "+l1+"\n";
																}
																else if($2->getName()==">"){
																	res->iVal=(a>b);
																	$$->code+="jg "+l1+"\n";
																}
																else if($2->getName()==">="){
																	res->iVal=(a>=b);
																	$$->code+="jge "+l1+"\n";
																}

																$$->code+="mov "+tmp+", 0\n";
																$$->code+="jmp "+l2+"\n";
																$$->code+=l1+":\nmov "+tmp+", 1\n";
																$$->code+=l2+":\n";
																$$->setName(tmp);
																
															}
														}

														codetracker<<$$->code;
													}
		;




				
simple_expression : term  {
							printNOW("simple_expression : term ");
							$$=$1;
							codetracker<<$$->code;
						}
		  


		  | simple_expression ADDOP term  {

		  									printNOW("simple_expression : simple_expression ADDOP term");

		  									//todo code

		  									if($3->varType=="DUMMY")$$=$3;

		  									else{
			  									
			  									SymbolInfo* res=new SymbolInfo("COPY","COPY");
			  									

			  									if($1->varType==""){
			  											//cout<<"GO FIND NEMO "<<$1->getName()<<endl;
			  											$1=findInDeclaration($1->getName());

			  											//cout<<$1->iVal<<endl;
			  										}
			  									if($3->varType==""){
			  											//cout<<"GO FIND NEMO "<<$3->getName()<<endl;
			  											$3=findInDeclaration($3->getName());

			  										}

			  									//code-asm
			  									$$=$1;
			  									$$->code+=$3->code;

			  									bool ok=true;
			  									string tmp=newTemp();
			  									


	 											if($1->varType=="CHAR"||$3->varType=="CHAR"){
	 													printError("Add operation on CHAR");
	 													error_count++;
	 													ok=false;
	 											}

	 											if($1->array||$3->array){
	 												printError("Add operation on arrays");
	 												error_count++;
	 												ok=false;
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

		 											if(ok){
		 												//code-asm
		 												$$->code+="mov ax, "+$1->getName()+"\n";
		 												$$->code+="add ax, "+$3->getName()+"\n";
		 												$$->code+="mov "+tmp+", ax\n";

		 												$$->setName(tmp);


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


		 											if(ok){
		 												//code-asm
		 												$$->code+="mov ax, "+$1->getName()+"\n";
		 												$$->code+="sub ax, "+$3->getName();+"\n";
		 												$$->code+="mov "+tmp+", ax\n";

		 												$$->setName(tmp);


		 											}
	 											}

			  									
		  									}

		  								codetracker<<$$->code;
		  								}
		  ;



					
term :	unary_expression	{
								printNOW("term :unary_expression");
								$$=$1;
								codetracker<<$$->code;

							}
     


     |  term MULOP unary_expression		{
     										printNOW("term : term MULOP unary_expression");

     										if($3->varType=="DUMMY")$$=$3;

     										//todo code


     										else{

	     										if($1->varType=="")$1=findInDeclaration($1->getName());
	     										if($3->varType=="")$3=findInDeclaration($3->getName());


	     										$$=$1;
	     										
	     										//asm-code
	     										$$->code+=$3->code;
	     										$$->code+="mov ax, "+$1->getName()+"\n";
	     										$$->code+="mov bx, "+$3->getName()+"\n";

	     										string tmp=newTemp();
	     										bool ok=true;


	     										if($2->getName()=="*"){
	     											if($1->varType=="CHAR"||$3->varType=="CHAR"){
	     												printError("Multiplication operation on CHARs");
	     												error_count++;
	     												ok=false;
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

	     											if(ok){
		     											//code-asm

		     											$$->code+="mul bx\n";
		     											$$->code+="mov "+tmp+", ax\n";


		     											$$->setName(tmp);
	     											}
	     										}


												else if($2->getName()=="/"){
	     											if($1->varType=="CHAR"||$3->varType=="CHAR"){
	     												printError("Division operations of CHARs");
	     												error_count++;
	     												ok=false;
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

	     											if(ok){
		     											//code-asm
		     											$$->code+="xor dx, dx\n";

		     											$$->code+="div bx\n";
		     											$$->code+="mov "+tmp+", ax\n";


		     											$$->setName(tmp);
	     											}

	     										}  



	     										else if($2->getName()=="%"){
	     											if($1->varType=="CHAR"||$3->varType=="CHAR"||$1->varType=="FLOAT"||$3->varType=="FLOAT"){
	     												printError("Non integer operands on MODULUS");
	     												error_count++;
	     												$1->iVal=-99999;
	     												ok=false;
	     											}
	     											
	     											else $1->iVal%=$3->iVal;

	     											if(ok){
		     											//code-asm
		     											$$->code+="xor dx, dx\n";

		     											$$->code+="div bx\n";
		     											$$->code+="mov "+tmp+", dx\n";

		     											$$->setName(tmp);
	     											}

	     											
	     										} 
     										}
     										codetracker<<$$->code;
  
     									}
     ;









unary_expression : ADDOP unary_expression   {
												printNOW("unary_expression : ADDOP unary_expression");

												//todo code

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

													//code-asm
													string tmp=newTemp();
					 								$$->code="mov ax, "+$2->getName()+"\n";
					 								$$->code+="neg ax\n";
					 								$$->code+="mov "+tmp+", ax\n";

					 								$$->setName(tmp);



												}

												codetracker<<$$->code;
											}
		 


		 | NOT unary_expression 	{
		 								printNOW("unary_expression : NOT unary_expression ");
		 								
		 								//todo code

		 								if($2->varType=="DUMMY")$$=$2;

		 								else{
			 								
			 								
			 								string s=$2->varType;
			 								
			 								if(s==""){
			 									$2=findInDeclaration($2->getName());
			 									s=$2->varType;
			 								}

			 								if(s=="INT")$2->iVal=!($2->iVal);
			 								else if(s=="FLOAT")$2->dVal=!($2->dVal);
			 								else if(s=="CHAR")
			 								{
												printError("Can't use UNARYOP on CHARs");
												error_count++;
											}
			 								$$=$2;

			 								//code-asm
			 								string tmp=newTemp();
			 								$$->code="mov ax, "+$2->getName()+"\n";
			 								$$->code+="not ax\n";
			 								$$->code+="mov "+tmp+", ax\n";

			 								$$->setName(tmp);

		 								}

		 								codetracker<<$$->code;
		 							}
		 


		 | factor {
		 			printNOW("unary_expression : factor");
		 			$$=$1;

		 			codetracker<<$$->code;
		 		}
		 ;
	










factor	: variable 	{

						printNOW("factor : variable ");
						


						if($1->varType=="DUMMY")$$=$1;

						else{


							SymbolInfo* real=findInDeclaration($1->getName());
							SymbolInfo* ret=new SymbolInfo(real->getName(),real->getType());
							ret->varType=real->varType;

							
							real->pIndex=$1->pIndex;
							real->expIndex=$1->expIndex;
							

							if($1->array){	
								if(real->varType=="INT")ret->iVal=(int)real->arrayStorage[real->pIndex];
								else if(real->varType=="FLOAT")ret->dVal=(double)real->arrayStorage[real->pIndex];
								else if(real->varType=="CHAR")ret->chVal=(char)real->arrayStorage[real->pIndex];
								
								//printf("<<%s>>\n",$$->getName().c_str());

								
								//asm-code
								
								$$=ret;
								$$->code=$1->code;

								

								//printf("HELLOW WORLD %s\n ",$1->getName().c_str());
								$$->code+="lea di, "+$1->getName()+"\n";

								tl.str("");
								tl<<$1->expIndex;


								for(int i=0;i<2;i++){
									$$->code+="add di, "+tl.str()+"\n";
								}

								string tmp=newTemp();

								$$->code+="mov "+tmp+", [di]\n";
								$$->setName(tmp);
								$$->pIndex=0;


							}
							else{
								if(real->varType=="INT")ret->iVal=real->iVal;
								else if(real->varType=="FLOAT")ret->dVal=real->dVal;
								else if(real->varType=="CHAR")ret->chVal=real->chVal;
								$$=ret;


								//asm-code??
								

							}
						}

						codetracker<<$$->code;
					}
	


	| LPAREN expression RPAREN  {
									printNOW("factor : LPAREN expression RPAREN");
									$$=$2;

									codetracker<<$$->code;
								}
	


	| CONST_INT 	{
						printNOW("factor : CONST_INT ");
						$$=$1;
						printNOW($1->getName());

						codetracker<<$$->code;
					}
	


	| CONST_FLOAT	{
						printNOW("factor : CONST_FLOAT ");
						$$=$1;
						printNOW($1->getName());

						codetracker<<$$->code;
					}
	


	| CONST_CHAR	{
						printNOW("factor : CONST_CHAR ");
						$$=$1;
						printNOW($1->getName());

						codetracker<<$$->code;
					}
	


	| variable INCOP 	{
						printNOW("factor : INCOP variable ");
						//todo code
						if($$->varType=="DUMMY")$$=$1;

						else{
							bool print=true;

							SymbolInfo* original=findInDeclaration($1->getName());
							if(original==0){
								original=new SymbolInfo("DUMMY","DUMMY");
								original->varType="DUMMY";
								print=false;
							}

							else if($1->array){
								original->expIndex=$1->expIndex;
								original->pIndex=$1->pIndex;

								string s=original->varType;
								if(s=="INT")original->arrayStorage[original->pIndex]++;
								else if(s=="FLOAT")original->arrayStorage[original->pIndex]++;
								else if(s=="CHAR")original->arrayStorage[original->pIndex]++;
								

								
								$$=new SymbolInfo();
								*($$)=*original;
								$$->setType("COPY");


								//asm-code
								$$->code="lea di, "+original->getName()+"\n";
								for(int i=0;i<2;i++)$$->code+="add di, "+original->expIndex+"\n";
								$$->code+="inc [di]\n";
							}
							else{


								string s=original->varType;
								if(s=="INT")original->iVal++;
								else if(s=="FLOAT")original->dVal++;
								else if(s=="CHAR")original->chVal++;

								$$=new SymbolInfo();
								(*$$)=*original;
								$$->setType("COPY");


								//asm-code
								$$->code="inc "+original->getName()+"\n";
							}

							if(print){
								myTable->Print(logFile);
								fprintf(logFile,"\n\n\n\n");
							}
						}

						codetracker<<$$->code;
					
					}
	


	| variable DECOP	{
						printNOW("factor : DECOP variable ");
						

						//todo code
						if($$->varType=="DUMMY")$$=$1;

						else{
							bool print=true;

							SymbolInfo* original=findInDeclaration($1->getName());
							if(original==0){
								original=new SymbolInfo("DUMMY","DUMMY");
								original->varType="DUMMY";
								print=false;
							}

							else if($1->array){
								original->expIndex=$1->expIndex;
								original->pIndex=$1->pIndex;

								string s=original->varType;
								if(s=="INT")original->arrayStorage[original->pIndex]--;
								else if(s=="FLOAT")original->arrayStorage[original->pIndex]--;
								else if(s=="CHAR")original->arrayStorage[original->pIndex]--;
								

								
								$$=new SymbolInfo();
								*($$)=*original;
								$$->setType("COPY");


								//asm-code
								$$->code="lea di, "+original->getName()+"\n";
								for(int i=0;i<2;i++)$$->code+="add di, "+original->expIndex+"\n";
								$$->code+="dec [di]\n";
							}
							else{


								string s=original->varType;
								if(s=="INT")original->iVal--;
								else if(s=="FLOAT")original->dVal--;
								else if(s=="CHAR")original->chVal--;

								$$=new SymbolInfo();
								(*$$)=*original;
								$$->setType("COPY");


								//asm-code
								$$->code="dec "+original->getName()+"\n";
							}

							if(print){
								myTable->Print(logFile);
								fprintf(logFile,"\n\n\n\n");
							}
						}

						codetracker<<$$->code;
					
					}
	;
%%

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