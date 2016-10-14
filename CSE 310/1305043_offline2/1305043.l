%option noyywrap

%x mlcomment
%x mlstring
%x helpState

%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
using namespace std;
#include"1305043_symbolTable.cpp"

int line_count=1;
int error_count=0;

FILE *logFile;
FILE *tokenFile;
SymbolInfo myInfo;
SymbolTable *myTable;

string buff;
int myCount;
bool checkInsert;

%}

WHITESPACE [ \t\f\r\v]+

INT_LIT [0-9]+

FLOAT_LIT ([0-9]*\.[0-9]+)([eE][-+]?[0-9]+)?

NEWLINE \n

IDENTIFIER [a-zA-Z_]+[a-zA-Z_0-9]*

CHAR_LIT '(.|\\n|\\t|\\\\|\\\"|\\a|\\f|\\r|\\b|\\v|\\0)'

SNGL_CMNT "//".*

MULT_CMNT "/*"

STRING_LIT \"

TOO_MANY_DECIMAL ([0-9]*\.[0-9]*){2,}([eE][-+]?[0-9]+)?

ILL_FORMED_NUMBR ([0-9]*\.[0-9]+)([eE]\.*[-+]*\.*[0-9]*\.*[0-9]*)

INVALID_PREFIX [0-9]+[a-zA-Z\.]+[a-zA-Z0-9\.]*

MULTI_CHAR_CONST '(..)+.*'

QUOTE_ERROR '[^'\n;]*


%%


{NEWLINE} {line_count++;}

{WHITESPACE} {}


"if"	{
			fprintf(tokenFile,"<IF>");
			fprintf(logFile,"Line no %3d: TOKEN <IF> Lexeme <%s> found\n",line_count,yytext);
			fprintf(logFile,"\n\n");
		}
		
"else"	{
			fprintf(tokenFile,"<ELSE>");
			fprintf(logFile,"Line no %3d: TOKEN <ELSE> Lexeme <%s> found\n",line_count,yytext);
			fprintf(logFile,"\n\n");
		}
"for"	{
			fprintf(tokenFile,"<FOR>");
			fprintf(logFile,"Line no %3d: TOKEN <FOR> Lexeme <%s> found\n",line_count,yytext);
			fprintf(logFile,"\n\n");
		}
"while"	{
			fprintf(tokenFile,"<WHILE>");
			fprintf(logFile,"Line no %3d: TOKEN <WHILE> Lexeme <%s> found\n",line_count,yytext);
			fprintf(logFile,"\n\n");
		}
"do"	{
			fprintf(tokenFile,"<DO>");
			fprintf(logFile,"Line no %3d: TOKEN <DO> Lexeme <%s> found\n",line_count,yytext);
			fprintf(logFile,"\n\n");
		}
"break"	{
			fprintf(tokenFile,"<BREAK>");
			fprintf(logFile,"Line no %3d: TOKEN <BREAK> Lexeme <%s> found\n",line_count,yytext);
			fprintf(logFile,"\n\n");
		}
"int"	{
			fprintf(tokenFile,"<INT>");
			fprintf(logFile,"Line no %3d: TOKEN <INT> Lexeme <%s> found\n",line_count,yytext);
			fprintf(logFile,"\n\n");
		}
"char"	{
			fprintf(tokenFile,"<CHAR>");
			fprintf(logFile,"Line no %3d: TOKEN <CHAR> Lexeme <%s> found\n",line_count,yytext);
			fprintf(logFile,"\n\n");
		}
"float"	{
			fprintf(tokenFile,"<FLOAT>");
			fprintf(logFile,"Line no %3d: TOKEN <FLOAT> Lexeme <%s> found\n",line_count,yytext);
			fprintf(logFile,"\n\n");
		}
"double"	{
			fprintf(tokenFile,"<DOUBLE>");
			fprintf(logFile,"Line no %3d: TOKEN <DOUBLE> Lexeme <%s> found\n",line_count,yytext);
			fprintf(logFile,"\n\n");
		}
"void"	{
			fprintf(tokenFile,"<VOID>");
			fprintf(logFile,"Line no %3d: TOKEN <VOID> Lexeme <%s> found\n",line_count,yytext);
			fprintf(logFile,"\n\n");
		}
"return"	{
			fprintf(tokenFile,"<RETURN>");
			fprintf(logFile,"Line no %3d: TOKEN <RETURN> Lexeme <%s> found\n",line_count,yytext);
			fprintf(logFile,"\n\n");
		}
"switch"	{
			fprintf(tokenFile,"<SWITCH>");
			fprintf(logFile,"Line no %3d: TOKEN <SWITCH> Lexeme <%s> found\n",line_count,yytext);
			fprintf(logFile,"\n\n");
		}
"case"	{
			fprintf(tokenFile,"<CASE>");
			fprintf(logFile,"Line no %3d: TOKEN <CASE> Lexeme <%s> found\n",line_count,yytext);
			fprintf(logFile,"\n\n");
		}
"default"	{
			fprintf(tokenFile,"<DEFAULT>");
			fprintf(logFile,"Line no %3d: TOKEN <DEFAULT> Lexeme <%s> found\n",line_count,yytext);
			fprintf(logFile,"\n\n");
		}
"continue"	{
			fprintf(tokenFile,"<CONTINUE>");
			fprintf(logFile,"Line no %3d: TOKEN <CONTINUE> Lexeme <%s> found\n",line_count,yytext);
			fprintf(logFile,"\n\n");
		}


"++"		|

"--"		{
			fprintf(tokenFile,"<INCOP,%s>",yytext);
			fprintf(logFile,"Line no %3d: TOKEN <INCOP> Lexeme <%s> found\n",line_count,yytext);
			myInfo.setType("INCOP");
			myInfo.setName(yytext);
			checkInsert=myTable->Insert(myInfo);
			if(!checkInsert)fprintf(logFile,"<%s : INCOP> already exists\n",yytext);
			myTable->Print(logFile);
			fprintf(logFile,"\n\n");
		}



"+"		|

"-"		{
			fprintf(tokenFile,"<ADDOP,%s>",yytext);
			fprintf(logFile,"Line no %3d: TOKEN <ADDOP> Lexeme <%s> found\n",line_count,yytext);
			myInfo.setType("ADDOP");
			myInfo.setName(yytext);
			checkInsert=myTable->Insert(myInfo);
			if(!checkInsert)fprintf(logFile,"<%s : ADDOP> already exists\n",yytext);
			myTable->Print(logFile);
			fprintf(logFile,"\n\n");
		}
"*"		|
"/"		|
"%"		{
			fprintf(tokenFile,"<MULOP,%s>",yytext);
			fprintf(logFile,"Line no %3d: TOKEN <MULOP> Lexeme <%s> found\n",line_count,yytext);
			myInfo.setType("MULOP");
			myInfo.setName(yytext);
			checkInsert=myTable->Insert(myInfo);
			if(!checkInsert)fprintf(logFile,"<%s : MULOP> already exists\n",yytext);
			myTable->Print(logFile);
			fprintf(logFile,"\n\n");
		}

"<"		|
"<="	|
">"		|
">="	|
"=="	|
"!="	{
			fprintf(tokenFile,"<RELOP,%s>",yytext);
			fprintf(logFile,"Line no %3d: TOKEN <RELOP> Lexeme <%s> found\n",line_count,yytext);
			myInfo.setType("RELOP");
			myInfo.setName(yytext);
			checkInsert=myTable->Insert(myInfo);
			if(!checkInsert)fprintf(logFile,"<%s : RELOP> already exists\n",yytext);
			myTable->Print(logFile);
			fprintf(logFile,"\n\n");

		}

"="		{
			fprintf(tokenFile,"<ASSIGNOP,%s>",yytext);
			fprintf(logFile,"Line no %3d: TOKEN <ASSIGNOP> Lexeme <%s> found\n",line_count,yytext);
			myInfo.setType("ASSIGNOP");
			myInfo.setName(yytext);
			checkInsert=myTable->Insert(myInfo);
			if(!checkInsert)fprintf(logFile,"<%s : ASSIGNOP> already exists\n",yytext);
			myTable->Print(logFile);
			fprintf(logFile,"\n\n");
		}

"&&"	|
"||"	|
"!"		{
			fprintf(tokenFile,"<LOGICOP,%s>",yytext);
			fprintf(logFile,"Line no %3d: TOKEN <LOGICOP> Lexeme <%s> found\n",line_count,yytext);
			myInfo.setType("LOGICOP");
			myInfo.setName(yytext);
			checkInsert=myTable->Insert(myInfo);
			if(!checkInsert)fprintf(logFile,"<%s : LOGICOP> already exists\n",yytext);
			myTable->Print(logFile);
			fprintf(logFile,"\n\n");
		}

"("		|
")"		{
			fprintf(tokenFile,"<PAREN,%s>",yytext);
			fprintf(logFile,"Line no %3d: TOKEN <PAREN> Lexeme <%s> found\n",line_count,yytext);
			myInfo.setType("PAREN");
			myInfo.setName(yytext);
			checkInsert=myTable->Insert(myInfo);
			if(!checkInsert)fprintf(logFile,"<%s : PAREN> already exists\n",yytext);
			myTable->Print(logFile);
			fprintf(logFile,"\n\n");
		}

"{"		|
"}"		{
			fprintf(tokenFile,"<CURL,%s>",yytext);
			fprintf(logFile,"Line no %3d: TOKEN <CURL> Lexeme <%s> found\n",line_count,yytext);
			myInfo.setType("CURL");
			myInfo.setName(yytext);
			checkInsert=myTable->Insert(myInfo);
			if(!checkInsert)fprintf(logFile,"<%s : CURL> already exists\n",yytext);
			myTable->Print(logFile);
			fprintf(logFile,"\n\n");
		}

"["		|
"]"		{
			fprintf(tokenFile,"<BRACKET,%s>",yytext);
			fprintf(logFile,"Line no %3d: TOKEN <BRACKET> Lexeme <%s> found\n",line_count,yytext);
			myInfo.setType("BRACKET");
			myInfo.setName(yytext);
			checkInsert=myTable->Insert(myInfo);
			if(!checkInsert)fprintf(logFile,"<%s : BRACKET> already exists\n",yytext);
			myTable->Print(logFile);
			fprintf(logFile,"\n\n");
		}


","		{
			fprintf(tokenFile,"<COMMA,%s>",yytext);
			fprintf(logFile,"Line no %3d: TOKEN <COMMA> Lexeme <%s> found\n",line_count,yytext);
			myInfo.setType("COMMA");
			myInfo.setName(yytext);
			checkInsert=myTable->Insert(myInfo);
			if(!checkInsert)fprintf(logFile,"<%s : COMMA> already exists\n",yytext);
			myTable->Print(logFile);
			fprintf(logFile,"\n\n");
		}

";"		{
			fprintf(tokenFile,"<SEMICOLON,%s>",yytext);
			fprintf(logFile,"Line no %3d: TOKEN <SEMICOLON> Lexeme <%s> found\n",line_count,yytext);
			myInfo.setType("SEMICOLON");
			myInfo.setName(yytext);
			checkInsert=myTable->Insert(myInfo);
			if(!checkInsert)fprintf(logFile,"<%s : SEMICOLON> already exists\n",yytext);
			myTable->Print(logFile);
			fprintf(logFile,"\n\n");
		}

{IDENTIFIER} 	{
				fprintf(tokenFile,"<ID,%s>",yytext);
				fprintf(logFile,"Line no %3d: TOKEN <ID> Lexeme <%s> found\n",line_count,yytext);
				myInfo.setType("ID");
				myInfo.setName(yytext);
				checkInsert=myTable->Insert(myInfo);
				if(!checkInsert)fprintf(logFile,"<%s : ID> already exists\n",yytext);
				myTable->Print(logFile);
				fprintf(logFile,"\n\n");
			}
			

		
{INT_LIT} 	{
				fprintf(tokenFile,"<CONST_INT,%s>",yytext);
				fprintf(logFile,"Line no %3d: TOKEN <CONST_INT> Lexeme <%s> found\n",line_count,yytext);
				myInfo.setType("CONST_INT");
				myInfo.setName(yytext);
				checkInsert=myTable->Insert(myInfo);
				if(!checkInsert)fprintf(logFile,"<%s : CONST_INT> already exists\n",yytext);
				myTable->Print(logFile);
				fprintf(logFile,"\n\n");
			}

{FLOAT_LIT} 	{
				fprintf(tokenFile,"<CONST_FLOAT,%s>",yytext);
				fprintf(logFile,"Line no %3d: TOKEN <CONST_FLOAT> Lexeme <%s> found\n",line_count,yytext);
				myInfo.setType("CONST_FLOAT");
				myInfo.setName(yytext);
				checkInsert=myTable->Insert(myInfo);
				if(!checkInsert)fprintf(logFile,"<%s : CONST_FLOAT> already exists\n",yytext);
				myTable->Print(logFile);
				fprintf(logFile,"\n\n");
			}

{CHAR_LIT} 	{
				fprintf(tokenFile,"<CONST_CHAR,%s>",yytext);
				fprintf(logFile,"Line no %3d: TOKEN <CONST_CHAR> Lexeme <%s> found\n",line_count,yytext);
				myInfo.setType("CONST_CHAR");
				myInfo.setName(yytext);
				checkInsert=myTable->Insert(myInfo);
				if(!checkInsert)fprintf(logFile,"<%s : CONST_CHAR> already exists\n",yytext);
				myTable->Print(logFile);
				fprintf(logFile,"\n\n");
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
					fprintf(logFile,"Line no %3d: TOKEN <COMMENT> Lexeme <%s> found\n",myCount,buff.c_str());
					fprintf(logFile,"\n\n");	
					BEGIN(INITIAL);
				}
<mlcomment><<EOF>> {
				fprintf(logFile,"Line no %3d: ERROR!! - Undeterminated comment %s\n",myCount,buff.c_str());
				fprintf(logFile,"\n\n");
				error_count++;
				BEGIN(INITIAL);
}


{SNGL_CMNT} {
				buff="";
				char *ch=yytext;
				while(*ch){
					if(*ch=='\n'||*ch=='\r'){
						*ch++;
						continue;
					}
					buff+=*ch++;
				}
				fprintf(logFile,"Line no %3d: TOKEN <COMMENT> Lexeme <%s> found\n",line_count,buff.c_str());
				fprintf(logFile,"\n\n");
				//insert in symbol table and print symbol table content(only non empty buckets)
			}
			

{STRING_LIT} 	{
				myCount=line_count;
				buff="";
				buff+=yytext;
				BEGIN(mlstring);
				//insert in symbol table and print symbol table content(only non empty buckets)
			}
<mlstring>\\ {/*fprintf(logFile,"Line no. %d: backslash found\n",line_count);*/BEGIN(helpState);}

<helpState>\n {line_count++;BEGIN(mlstring);}

<mlstring>\\\" {
		char *ch=yytext;
		while(*ch){
			if(*ch=='\n'||*ch=='\r'||*ch=='\\'||*ch=='\\'){
				*ch++;continue;
			}
			buff+=*ch++;
		}
	}
<mlstring>{STRING_LIT}	{
					buff+=yytext;
					BEGIN(INITIAL);
					fprintf(tokenFile,"<STRING,%s>",buff.c_str());
					fprintf(logFile,"Line no %3d: TOKEN <STRING> Lexeme",myCount);
					fprintf(logFile," %s found\n",buff.c_str());
					fprintf(tokenFile,"<STRING,%s>",buff.c_str());
					fprintf(logFile,"\n\n");
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
				fprintf(logFile,"Line no %3d: ERROR!! - Unfinished String %s\n",myCount,buff.c_str());
				fprintf(logFile,"\n\n");
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
				fprintf(logFile,"Line no %3d: ERROR!! - Unfinished String %s\n",myCount,buff.c_str());
				fprintf(logFile,"\n\n");
				error_count++;
				BEGIN(INITIAL);
				//insert in symbol table and print symbol table content(only non empty buckets)
			}
{MULTI_CHAR_CONST} {
				fprintf(logFile,"Line no %3d: ERROR!! - Multi charachter constant %s\n",line_count,yytext);
				fprintf(logFile,"\n\n");
				error_count++;
				//insert in symbol table and print symbol table content(only non empty buckets)
			}


{ILL_FORMED_NUMBR} {
				fprintf(logFile,"Line no %3d: ERROR!! - Ill formed number %s\n",line_count,yytext);
				fprintf(logFile,"\n\n");
				error_count++;
				//insert in symbol table and print symbol table content(only non empty buckets)
			}

{TOO_MANY_DECIMAL} {
				fprintf(logFile,"Line no %3d: ERROR!! - Too many decimal points %s\n",line_count,yytext);
				fprintf(logFile,"\n\n");
				error_count++;
				//insert in symbol table and print symbol table content(only non empty buckets)
			}
{INVALID_PREFIX} {
				fprintf(logFile,"Line no %3d: ERROR!! - Invalid prefix %s\n",line_count,yytext);
				fprintf(logFile,"\n\n");
				error_count++;
				//insert in symbol table and print symbol table content(only non empty buckets)
			}

{QUOTE_ERROR} {
				fprintf(logFile,"Line no %3d: ERROR!! - Undetermined sequence %s\n",line_count,yytext);
				fprintf(logFile,"\n\n");
				error_count++;
				//insert in symbol table and print symbol table content(only non empty buckets)
			}



.			{
				fprintf(logFile,"Unrecognized charachter found at line %3d: %s\n",line_count,yytext);
				fprintf(logFile,"\n\n");
				error_count++;
				//insert in symbol table and print symbol table content(only non empty buckets)
			}




%%

int main(int argc,char *argv[]){
	
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
	tokenFile= fopen("1305043_token.txt","w");
	myTable=new SymbolTable(15);

	yyin=fin;
	yylex();

	fprintf(logFile,"\n\nTOTAL LINES: %3d\n",line_count);
	fprintf(logFile,"\n\nTOTAL ERRORS: %3d\n",error_count);

	fclose(yyin);
	fclose(tokenFile);
	fclose(logFile);
	return 0;
}