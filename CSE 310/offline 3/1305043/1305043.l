%x mlcomment
%x mlstring
%x helpState

%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
using namespace std;
#include"1305043_symbolTable.cpp"

# include "y.tab.h"
void yyerror(char*);


extern YYSTYPE yylval;
extern SymbolTable *myTable;
extern FILE* logFile;



extern int line_count;
extern int error_count;

string buff;
int myCount;
bool checkInsert;
SymbolInfo dummy;


void printNow(string token,string lexeme,int line_no,bool insert,SymbolInfo info)
{
	if(!insert){
			fprintf(logFile,"LEXER RESPONSE: Line no %03d: TOKEN <%s> Lexeme <%s> found\n",line_no,token.c_str(),lexeme.c_str());
			fprintf(logFile,"\n\n");
			yylval.helpString=lexeme.c_str();
	}
	else{
		checkInsert=myTable->Insert(info);
		fprintf(logFile,"LEXER RESPONSE: Line no %03d: TOKEN <%s> Lexeme <%s> found\n",line_count,token.c_str(),lexeme.c_str());
		if(!checkInsert)fprintf(logFile,"<%s : %s> already exists\n",lexeme.c_str(),token.c_str());
		fprintf(logFile,"\n\n");
		myTable->Print(logFile);
		fprintf(logFile,"\n\n");
		yylval.helpInfo=&info;
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
			buff="";buff+=yytext;
			printNow("IF",buff,line_count,false,dummy);
			return IF; 
		}
		
"else"	{
			buff="";buff+=yytext;
			printNow("ELSE",buff,line_count,false,dummy);
			return ELSE; 
		}
"for"	{
			buff="";buff+=yytext;
			printNow("FOR",buff,line_count,false,dummy);
			return FOR; 
		}
"while"	{	
			buff="";buff+=yytext;
			printNow("WHILE",buff,line_count,false,dummy);
			return WHILE; 
		}
"do"	{	
			buff="";buff+=yytext;
			printNow("DO",buff,line_count,false,dummy);
			return DO;
		}
"break"	{
			buff="";buff+=yytext;
			printNow("BREAK",buff,line_count,false,dummy);
			return BREAK;
		}
"int"	{
			
			buff="";buff+=yytext;
			printNow("INT",buff,line_count,false,dummy);
			return INT;
		}
"char"	{
			buff="";buff+=yytext;
			printNow("CHAR",buff,line_count,false,dummy);
			return CHAR;
		}
"float"	{
			buff="";buff+=yytext;
			printNow("FLOAT",buff,line_count,false,dummy);
			return FLOAT;
		}
"double" {
			buff="";buff+=yytext;
			printNow("DOUBLE",buff,line_count,false,dummy);
			return DOUBLE;
		}
"void"	{
			buff="";buff+=yytext;
			printNow("VOID",buff,line_count,false,dummy);
			return VOID;
		}
"return" {
			buff="";buff+=yytext;
			printNow("RETURN",buff,line_count,false,dummy);
			return RETURN;
		}
"switch" {
			buff="";buff+=yytext;
			printNow("SWITCH",buff,line_count,false,dummy);
			return SWITCH;
		}
"case"	{
			buff="";buff+=yytext;
			printNow("CASE",buff,line_count,false,dummy);
			return CASE;
		}
"default"	{
			buff="";buff+=yytext;
			printNow("DEFAULT",buff,line_count,false,dummy);
			return DEFAULT;
		}
"continue"	{
			buff="";buff+=yytext;
			printNow("CONTINUE",buff,line_count,false,dummy);
			return CONTINUE;
		}
	
"println"	{
			buff="";buff+=yytext;
			printNow("PRINTLN",buff,line_count,false,dummy);
			return PRINTLN;
			}

"main"		{
			buff="";buff+=yytext;
			printNow("MAIN",buff,line_count,false,dummy);
			return MAIN;
			}

"!"		{
			buff="";buff+=yytext;
			SymbolInfo* info=new SymbolInfo(buff,"NOT");
			printNow("NOT",buff,line_count,false,*info);
			return NOT;
		}


"++"		|

"--"		{
				buff="";buff+=yytext;
					if(buff=="++"){
					SymbolInfo* info=new SymbolInfo(buff,"INCOP");
					printNow("INCOP",buff,line_count,false,*info);
					return INCOP;
				}
				else{
					SymbolInfo* info=new SymbolInfo(buff,"DECOP");
					printNow("DECOP",buff,line_count,false,*info);
				 	return DECOP;
				 }
			}



"+"		|

"-"		{
			buff="";buff+=yytext;
			SymbolInfo* info=new SymbolInfo(buff,"ADDOP");
			printNow("ADDOP",buff,line_count,false,*info);
			return ADDOP;
		}
"*"		|
"/"		|
"%"		{
			buff="";buff+=yytext;
			SymbolInfo* info=new SymbolInfo(buff,"MULOP");
			printNow("MULOP",buff,line_count,false,*info);
			return ADDOP;
		}

"<"		|
"<="	|
">"		|
">="	|
"=="	|
"!="	{
			buff="";buff+=yytext;
			SymbolInfo* info=new SymbolInfo(buff,"RELOP");
			printNow("RELOP",buff,line_count,false,*info);
			return RELOP;
		}

"="		{
			buff="";buff+=yytext;
			SymbolInfo* info=new SymbolInfo(buff,"ASSIGNOP");
			printNow("ASSIGNOP",buff,line_count,false,*info);
			return ASSIGNOP;
		}

"&&"	|
"||"	{
			buff="";buff+=yytext;
			buff="";buff+=yytext;
			SymbolInfo* info=new SymbolInfo(buff,"LOGICOP");
			printNow("LOGICOP",buff,line_count,false,*info);
			return LOGICOP;
		}

"("		|
")"		{
			buff="";buff+=yytext;
			if(buff=="("){
				SymbolInfo* info=new SymbolInfo(buff,"LPAREN");
				printNow("LPAREN",buff,line_count,false,*info);
				return LPAREN;
			}
			else{
				SymbolInfo* info=new SymbolInfo(buff,"RPAREN");
				printNow("RPAREN",buff,line_count,false,*info);
				return RPAREN;	
			} 
		}

"{"		|
"}"		{
			buff="";buff+=yytext;
			if(buff=="{"){
				SymbolInfo* info=new SymbolInfo(buff,"LCURL");
				printNow("LCURL",buff,line_count,false,*info);
				return LCURL;
			}
			else{
				SymbolInfo* info=new SymbolInfo(buff,"RCURL");
				printNow("RCURL",buff,line_count,false,*info);
				return RCURL;
			}
		}

"["		|
"]"		{
			buff="";buff+=yytext;
			if(buff=="["){
				SymbolInfo* info=new SymbolInfo(buff,"LTHIRD");
				printNow("LTHIRD",buff,line_count,false,*info);
				return LTHIRD;
			}
			else{
				SymbolInfo* info=new SymbolInfo(buff,"RTHIRD");
				printNow("RTHIRD",buff,line_count,false,*info);

				return RTHIRD;
			}
		}


","		{
			buff="";buff+=yytext;
			SymbolInfo* info=new SymbolInfo(buff,"COMMA");
			printNow("COMMA",buff,line_count,false,*info);
			return COMMA;
		}

";"		{
			buff="";buff+=yytext;
			SymbolInfo* info=new SymbolInfo(buff,"SEMICOLON");
			printNow("SEMICOLON",buff,line_count,false,*info);
			return SEMICOLON;
		}

{IDENTIFIER} {
				buff="";buff+=yytext;
				SymbolInfo* info=new SymbolInfo(buff,"ID");
				printNow("ID",buff,line_count,true,*info);
				return ID;
			}
			

		
{INT_LIT} 	{
				buff="";buff+=yytext;
				SymbolInfo* info=new SymbolInfo(buff,"CONST_INT");
				printNow("CONST_INT",buff,line_count,true,*info);

				return CONST_INT;
			}

{FLOAT_LIT} {
				buff="";buff+=yytext;
				SymbolInfo* info=new SymbolInfo(buff,"CONST_FLOAT");
				printNow("CONST_FLOAT",buff,line_count,true,*info);

				return CONST_FLOAT;
			}

{CHAR_LIT} 	{
				buff="";buff+=yytext;
				SymbolInfo* info=new SymbolInfo(buff,"CONST_CHAR");
				printNow("CONST_CHAR",buff,line_count,true,*info);
				return CONST_CHAR;
			}



{MULT_CMNT}		{

				myCount=line_count;
				buff="";
				buff+=yytext;		
				BEGIN(mlcomment);
					
			}
<mlcomment>\n 	{
					line_count++;
					buff+=yytext;
				} 
<mlcomment>[^*\n]+	{
					buff+=yytext;

					}
<mlcomment>("*"+[^/\n])* {
					buff+=yytext;

				}
<mlcomment>"*"+"/" {
					buff+=yytext;
					fprintf(logFile,"Line no %03d: TOKEN <COMMENT> Lexeme <%s> found\n",myCount,buff.c_str());
					fprintf(logFile,"\n\n");	
					BEGIN(INITIAL);
				}
<mlcomment><<EOF>> {
				fprintf(logFile,"Line no %03d: ERROR!! - Undeterminated comment %s\n",myCount,buff.c_str());
				fprintf(logFile,"\n\n");
				error_count++;
				BEGIN(INITIAL);
}


{SNGL_CMNT} {
				buff="";
				char *ch=yytext;
				while(*ch){
					if(*ch=='\r'){
						*ch++;
						continue;
					}
					buff+=*ch++;
				}
				fprintf(logFile,"Line no %03d: TOKEN <COMMENT> Lexeme <%s> found\n",line_count,buff.c_str());
				fprintf(logFile,"\n\n");
			}
			

{STRING_LIT} 	{
				myCount=line_count;
				buff="";
				buff+=yytext;
				BEGIN(mlstring);
			}
<mlstring>\\ {
	BEGIN(helpState);

}
<helpState>[^\n\r] {
	buff+=yytext;
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
				buff+='\\';*ch++;
			}
			else if(*ch=='n'){
				buff+='\n';*ch++;
			}
			else if(*ch=='t'){
				buff+='\t';*ch++;
			}
			else if(*ch=='b'){
				buff+='\b';*ch++;
			}
			else buff+=*ch++;
		}
	}
<mlstring>{STRING_LIT}	{
					buff+=yytext;
					BEGIN(INITIAL);
					SymbolInfo* info=new SymbolInfo(buff,"STRING");
					printNow("STRING",buff,line_count,false,*info);
					return STRING;
			}
<mlstring>[^\"\n] {
		char *ch=yytext;
		while(*ch){
			if(*ch=='\n'||*ch=='\r'||*ch=='\\'){
				*ch++;continue;
			}
			buff+=*ch++;
		}
}
<mlstring><<EOF>> {
				char *ch=yytext;
				while(*ch){
						if(*ch=='\n'||*ch=='\r'||*ch=='\\'){
						*ch++;continue;
					}
					buff+=*ch++;
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
					buff+=*ch++;
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