%x mlcomment
%x mlstring
%x helpState

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;
#include "1305043_symbolTable.cpp"

# include "y.tab.h"
void yyerror(char*);


extern YYSTYPE yylval;
extern SymbolTable *myTable;
extern FILE* logFile;



extern int line_count;
extern int error_count;

string buff1;
int myCount;
bool checkInsert;
SymbolInfo* dummy;


void printNow(string token,string lexeme,int line_no,bool s,SymbolInfo* info)
{
	if(!s){
			//fprintf(logFile,"LEXER RESPONSE: Line no %03d: TOKEN <%s> Lexeme <%s> found\n",line_no,token.c_str(),lexeme.c_str());
			//fprintf(logFile,"\n\n");
			yylval.helpString=lexeme.c_str();

	}
	else{
		/*checkInsert=myTable->Insert(info);
		fprintf(logFile,"LEXER RESPONSE: Line no %03d: TOKEN <%s> Lexeme <%s> found\n",line_count,token.c_str(),lexeme.c_str());
		if(!checkInsert)fprintf(logFile,"<%s : %s> already exists\n",lexeme.c_str(),token.c_str());
		fprintf(logFile,"\n\n");
		myTable->Print(logFile);
		fprintf(logFile,"\n\n");*/
		//SymbolInfo* mm=new SymbolInfo(lexeme,token);
		//cout<<token<<"  "<<lexeme<<endl;
		if(token=="ID")yylval.idInfo=info;
		else yylval.helpInfo=info;
		//cout<<yylval.helpInfo->getType()<<"  "<<yylval.helpInfo->getName()<<endl;
	}

}



%}

WHITESPACE [ \t\f\r\v]+

INT_LIT [0-9]+

FLOAT_LIT [0-9]*(\.[0-9]+)?(e|E[+-]?[0-9]+)?

NEWLINE \n

IDENTIFIER [a-zA-Z_]+[a-zA-Z_0-9]*

CHAR_LIT '(.|\\n|\\t|\\\\|\\\"|\\a|\\f|\\r|\\b|\\v|\\0)'

SNGL_CMNT "//".*

MULT_CMNT "/*"

STRING_LIT \"

TOO_MANY_DECIMAL ([0-9]*\.[0-9]*){2,}([eE][-+]?[0-9]+)? 

ILL_FORMED_NUMBR ([0-9]*\.[0-9]+)([eE]\.*[-+]*\.*[0-9]*\.*[0-9]*)

INVALID_PREFIX [0-9]+[a-zA-Z\.]+[a-zA-Z0-9\.]*

MULTI_CHAR_CONST '([^\'\n]+[^\'\n]+)+[^\'\n]*'

QUOTE_ERROR '[^'\n;]*


%%


{NEWLINE} {line_count++;}

{WHITESPACE} {}


"if"	{
			string buff="";buff+=yytext;
			printNow("IF",buff,line_count,false,dummy);
			return IF; 
		}
		
"else"	{
			string buff="";buff+=yytext;
			printNow("ELSE",buff,line_count,false,dummy);
			return ELSE; 
		}
"for"	{
			string buff="";buff+=yytext;
			printNow("FOR",buff,line_count,false,dummy);
			return FOR; 
		}
"while"	{	
			string buff="";buff+=yytext;
			printNow("WHILE",buff,line_count,false,dummy);
			return WHILE; 
		}
"do"	{	
			string buff="";buff+=yytext;
			printNow("DO",buff,line_count,false,dummy);
			return DO;
		}
"break"	{
			string buff="";buff+=yytext;
			printNow("BREAK",buff,line_count,false,dummy);
			return BREAK;
		}
"int"	{
			
			string buff="";buff+=yytext;
			printNow("INT",buff,line_count,false,dummy);
			return INT;
		}
"char"	{
			string buff="";buff+=yytext;
			printNow("CHAR",buff,line_count,false,dummy);
			return CHAR;
		}
"float"	{
			string buff="";buff+=yytext;
			printNow("FLOAT",buff,line_count,false,dummy);
			return FLOAT;
		}
"double" {
			string buff="";buff+=yytext;
			printNow("DOUBLE",buff,line_count,false,dummy);
			return DOUBLE;
		}
"void"	{
			string buff="";buff+=yytext;
			printNow("VOID",buff,line_count,false,dummy);
			return VOID;
		}
"return" {
			string buff="";buff+=yytext;
			printNow("RETURN",buff,line_count,false,dummy);
			return RETURN;
		}
"switch" {
			string buff="";buff+=yytext;
			printNow("SWITCH",buff,line_count,false,dummy);
			return SWITCH;
		}
"case"	{
			string buff="";buff+=yytext;
			printNow("CASE",buff,line_count,false,dummy);
			return CASE;
		}
"default"	{
			string buff="";buff+=yytext;
			printNow("DEFAULT",buff,line_count,false,dummy);
			return DEFAULT;
		}
"continue"	{
			string buff="";buff+=yytext;
			printNow("CONTINUE",buff,line_count,false,dummy);
			return CONTINUE;
		}
	
"println"	{
			string buff="";buff+=yytext;
			printNow("PRINTLN",buff,line_count,false,dummy);
			return PRINTLN;
			}

"main"		{
			string buff="";buff+=yytext;
			printNow("MAIN",buff,line_count,false,dummy);
			return MAIN;
			}

"!"		{
			string buff="";buff+=yytext;
			SymbolInfo* info=new SymbolInfo(buff,"NOT");
			printNow("NOT",buff,line_count,true,info);
			return NOT;
		}


"++"		|

"--"		{
				string buff="";buff+=yytext;
					if(buff=="++"){
					SymbolInfo* info=new SymbolInfo(buff,"INCOP");
					printNow("INCOP",buff,line_count,true,info);
					return INCOP;
				}
				else{
					SymbolInfo* info=new SymbolInfo(buff,"DECOP");
					printNow("DECOP",buff,line_count,true,info);
				 	return DECOP;
				 }
			}



"+"		|

"-"		{
			string buff="";buff+=yytext;
			SymbolInfo* info=new SymbolInfo(buff,"ADDOP");
			printNow("ADDOP",buff,line_count,true,info);
			return ADDOP;
		}
"*"		|
"/"		|
"%"		{
			string buff="";buff+=yytext;
			SymbolInfo* info=new SymbolInfo(buff,"MULOP");
			printNow("MULOP",buff,line_count,true,info);
			return MULOP;
		}

"<"		|
"<="	|
">"		|
">="	|
"=="	|
"!="	{
			string buff="";buff+=yytext;
			SymbolInfo* info=new SymbolInfo(buff,"RELOP");
			printNow("RELOP",buff,line_count,true,info);
			return RELOP;
		}

"="		{
			string buff="";buff+=yytext;
			SymbolInfo* info=new SymbolInfo(buff,"ASSIGNOP");
			printNow("ASSIGNOP",buff,line_count,true,info);
			return ASSIGNOP;
		}

"&&"	|
"||"	{
			string buff="";buff+=yytext;
			buff="";buff+=yytext;
			SymbolInfo* info=new SymbolInfo(buff,"LOGICOP");
			printNow("LOGICOP",buff,line_count,true,info);
			return LOGICOP;
		}

"("		|
")"		{
			string buff="";buff+=yytext;
			if(buff=="("){
				SymbolInfo* info=new SymbolInfo(buff,"LPAREN");
				printNow("LPAREN",buff,line_count,true,info);
				return LPAREN;
			}
			else{
				SymbolInfo* info=new SymbolInfo(buff,"RPAREN");
				printNow("RPAREN",buff,line_count,true,info);
				return RPAREN;	
			} 
		}

"{"		|
"}"		{
			 string buff="";buff+=yytext;
			if(buff=="{"){
				SymbolInfo* info=new SymbolInfo(buff,"LCURL");
				printNow("LCURL",buff,line_count,true,info);
				return LCURL;
			}
			else{
				SymbolInfo* info=new SymbolInfo(buff,"RCURL");
				printNow("RCURL",buff,line_count,true,info);
				return RCURL;
			}
		}

"["		|
"]"		{
			string buff="";buff+=yytext;
			if(buff=="["){
				SymbolInfo* info=new SymbolInfo(buff,"LTHIRD");
				printNow("LTHIRD",buff,line_count,true,info);
				return LTHIRD;
			}
			else{
				SymbolInfo* info=new SymbolInfo(buff,"RTHIRD");
				printNow("RTHIRD",buff,line_count,true,info);

				return RTHIRD;
			}
		}


","		{
			string buff="";buff+=yytext;
			SymbolInfo* info=new SymbolInfo(buff,"COMMA");
			printNow("COMMA",buff,line_count,true,info);
			return COMMA;
		}

";"		{
			string buff="";buff+=yytext;
			SymbolInfo* info=new SymbolInfo(buff,"SEMICOLON");
			printNow("SEMICOLON",buff,line_count,true,info);
			return SEMICOLON;
		}

{IDENTIFIER} {
				string buff="";buff+=yytext;

				SymbolInfo* info=new SymbolInfo(buff,"ID");
				printNow("ID",buff,line_count,true,info);

				return ID;
			}
			

		
{INT_LIT} 	{
				string buff="";buff+=yytext;
				SymbolInfo* info=new SymbolInfo(buff,"CONST_INT");

				info->varType="INT";

				istringstream is(buff);
				is>>info->iVal;

				printNow("CONST_INT",buff,line_count,true,info);
				return CONST_INT;
			}

{FLOAT_LIT} {
				string buff="";buff+=yytext;
				SymbolInfo* info=new SymbolInfo(buff,"CONST_FLOAT");

				info->varType="FLOAT";

				istringstream is(buff);
				is>>info->dVal;


				printNow("CONST_FLOAT",buff,line_count,true,info);

				return CONST_FLOAT;
			}

{CHAR_LIT} 	{
				string buff="";buff+=yytext;				
				SymbolInfo* info=new SymbolInfo(buff,"CONST_CHAR");
				
				info->varType="CHAR";

				istringstream is(buff);
				is>>info->chVal;

				printNow("CONST_CHAR",buff,line_count,true,info);
				return CONST_CHAR;
			}



{MULT_CMNT}		{

				myCount=line_count;
				string buff="";
				buff1+=yytext;		
				BEGIN(mlcomment);
					
			}
<mlcomment>\n 	{
					line_count++;
					buff1+=yytext;
				} 
<mlcomment>[^*\n]+	{
					buff1+=yytext;

					}
<mlcomment>("*"+[^/\n])* {
					buff1+=yytext;

				}
<mlcomment>"*"+"/" {
					buff1+=yytext;
					fprintf(logFile,"Line no %03d: TOKEN <COMMENT> Lexeme <%s> found\n",myCount,buff1.c_str());
					fprintf(logFile,"\n\n");	
					BEGIN(INITIAL);
				}
<mlcomment><<EOF>> {
				fprintf(logFile,"Line no %03d: ERROR!! - Undeterminated comment %s\n",myCount,buff1.c_str());
				fprintf(logFile,"\n\n");
				error_count++;
				BEGIN(INITIAL);
}


{SNGL_CMNT} {
				 buff1="";
				char *ch=yytext;
				while(*ch){
					if(*ch=='\r'){
						*ch++;
						continue;
					}
					buff1+=*ch++;
				}
				fprintf(logFile,"Line no %03d: TOKEN <COMMENT> Lexeme <%s> found\n",line_count,buff1.c_str());
				fprintf(logFile,"\n\n");
			}
			

{STRING_LIT} 	{
				myCount=line_count;
				string buff1="";
				buff1+=yytext;
				BEGIN(mlstring);
			}
<mlstring>\\ {
	BEGIN(helpState);

}
<helpState>[^\n\r] {
	buff1+=yytext;
	BEGIN(mlstring);
}

<helpState>\n {
		line_count++;
		BEGIN(mlstring);
	}

<mlstring>\\[nbt\\] {
		char *ch=yytext;
		ch++;
		while(*ch){
			if(*ch=='\n'||*ch=='\r'){
				*ch++;continue;
			}
			else if(*ch=='\\'){
				buff1+='\\';*ch++;
			}
			else if(*ch=='n'){
				buff1+='\n';*ch++;
			}
			else if(*ch=='t'){
				buff1+='\t';*ch++;
			}
			else if(*ch=='b'){
				buff1+='\b';*ch++;
			}
			else buff1+=*ch++;
		}
	}
<mlstring>{STRING_LIT}	{
					buff1+=yytext;
					BEGIN(INITIAL);
					SymbolInfo* info=new SymbolInfo(buff1,"STRING");
					printNow("STRING",buff1,line_count,true,info);
					return STRING;
			}
<mlstring>[^\"\n] {
		char *ch=yytext;
		while(*ch){
			if(*ch=='\n'||*ch=='\r'||*ch=='\\'){
				*ch++;continue;
			}
			buff1+=*ch++;
		}
}
<mlstring><<EOF>> {
				char *ch=yytext;
				while(*ch){
						if(*ch=='\n'||*ch=='\r'||*ch=='\\'){
						*ch++;continue;
					}
					buff1+=*ch++;
				}
				// fprintf(logFile,"Line no %03d: ERROR!! - Unfinished String %s\n",myCount,buff.c_str());
				// fprintf(logFile,"\n\n");
				error_count++;
				BEGIN(INITIAL);
				//insert in symbol table and print symbol table content(only non empty buckets)
			}

<mlstring>\n  	{
				line_count++;
				char *ch=yytext;
				while(*ch){
						if(*ch=='\n'||*ch=='\r'||*ch=='\\'){
						*ch++;continue;
					}
					buff1+=*ch++;
				}
				// fprintf(logFile,"Line no %03d: ERROR!! - Unfinished String %s\n",myCount,buff.c_str());
				// fprintf(logFile,"\n\n");
				error_count++;
				BEGIN(INITIAL);
				//insert in symbol table and print symbol table content(only non empty buckets)
			}

{MULTI_CHAR_CONST} {
				// fprintf(logFile,"Line no %03d: ERROR!! - Multi charachter constant %s\n",line_count,yytext);
				// fprintf(logFile,"\n\n");
				error_count++;
				//insert in symbol table and print symbol table content(only non empty buckets)
			}


{ILL_FORMED_NUMBR} {
				// fprintf(logFile,"Line no %03d: ERROR!! - Ill formed number %s\n",line_count,yytext);
				// fprintf(logFile,"\n\n");
				error_count++;
				//insert in symbol table and print symbol table content(only non empty buckets)
			}

{TOO_MANY_DECIMAL} {
				// fprintf(logFile,"Line no %03d: ERROR!! - Too many decimal points %s\n",line_count,yytext);
				// fprintf(logFile,"\n\n");
				error_count++;
				//insert in symbol table and print symbol table content(only non empty buckets)
			}
{INVALID_PREFIX} {
				// fprintf(logFile,"Line no %03d: ERROR!! - Invalid prefix %s\n",line_count,yytext);
				// fprintf(logFile,"\n\n");
				error_count++;
				//insert in symbol table and print symbol table content(only non empty buckets)
			}

{QUOTE_ERROR} {
				// fprintf(logFile,"Line no %03d: ERROR!! - Ill formed charachter error %s\n",line_count,yytext);
				// fprintf(logFile,"\n\n");
				error_count++;
				//insert in symbol table and print symbol table content(only non empty buckets)
			}



.			{
				// fprintf(logFile,"Line no %03d: ERROR!! - Unrecognized charachter found %s\n",line_count,yytext);
				// fprintf(logFile,"\n\n");
				error_count++;
				//insert in symbol table and print symbol table content(only non empty buckets)
			}




%%

int yywrap(void)
{
	return 1;
}



/*int main(int argc,char *argv[]){
	
	if(argc!=2){
		printf("No input file provided\n");
		return 0;
	}
	
	FILE *fin=fopen(argv[1],"r");
	if(fin==dummy){
		printf("File can't be opened\n");
		return 0;
	}
	
	logFile= fopen("1305043_log.txt","w");
	tokenFile= fopen("1305043_token.txt","w");
	myTable=new SymbolTable(15);

	yyin=fin;
	yylex();

	fprintf(logFile,"\n\nTOTAL LINES: %03d\n",line_count);
	fprintf(logFile,"\n\nTOTAL ERRORS: %03d\n",error_count);

	fclose(yyin);
	fclose(tokenFile);
	fclose(logFile);
	return 0;
}*/