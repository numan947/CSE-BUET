%option noyywrap

%x mlcomment
%x mlstring
%x WTFSTATE


%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"1305043_symbolTable.cpp"

int line_count=1;

FILE *logFile;
FILE *tokenFile;
SymbolTable *myTable;

string buff;
int myCount;

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

NOT_FINISHED_STR (.)*[<<EOF>>]

QUOTE_ERROR  [\'.*$]{-}[']


%%


{NEWLINE} {line_count++;}
{WHITESPACE} {}


"if"	{
			fprintf(tokenFile,"<IF>");
			fprintf(logFile,"Line no %d: TOKEN <IF> Lexeme %s found\n",line_count,yytext);
		}
		
"else"	{
			fprintf(tokenFile,"<ELSE>");
			fprintf(logFile,"Line no %d: TOKEN <ELSE> Lexeme %s found\n",line_count,yytext);
		}
"for"	{
			fprintf(tokenFile,"<FOR>");
			fprintf(logFile,"Line no %d: TOKEN <FOR> Lexeme %s found\n",line_count,yytext);
		}
"while"	{
			fprintf(tokenFile,"<WHILE>");
			fprintf(logFile,"Line no %d: TOKEN <WHILE> Lexeme %s found\n",line_count,yytext);
		}
"do"	{
			fprintf(tokenFile,"<DO>");
			fprintf(logFile,"Line no %d: TOKEN <DO> Lexeme %s found\n",line_count,yytext);
		}
"break"	{
			fprintf(tokenFile,"<BREAK>");
			fprintf(logFile,"Line no %d: TOKEN <BREAK> Lexeme %s found\n",line_count,yytext);
		}
"int"	{
			fprintf(tokenFile,"<INT>");
			fprintf(logFile,"Line no %d: TOKEN <INT> Lexeme %s found\n",line_count,yytext);
		}
"char"	{
			fprintf(tokenFile,"<CHAR>");
			fprintf(logFile,"Line no %d: TOKEN <CHAR> Lexeme %s found\n",line_count,yytext);
		}
"float"	{
			fprintf(tokenFile,"<FLOAT>");
			fprintf(logFile,"Line no %d: TOKEN <FLOAT> Lexeme %s found\n",line_count,yytext);
		}
"double"	{
			fprintf(tokenFile,"<DOUBLE>");
			fprintf(logFile,"Line no %d: TOKEN <DOUBLE> Lexeme %s found\n",line_count,yytext);
		}
"void"	{
			fprintf(tokenFile,"<VOID>");
			fprintf(logFile,"Line no %d: TOKEN <VOID> Lexeme %s found\n",line_count,yytext);
		}
"return"	{
			fprintf(tokenFile,"<RETURN>");
			fprintf(logFile,"Line no %d: TOKEN <RETURN> Lexeme %s found\n",line_count,yytext);
		}
"switch"	{
			fprintf(tokenFile,"<SWITCH>");
			fprintf(logFile,"Line no %d: TOKEN <SWITCH> Lexeme %s found\n",line_count,yytext);
		}
"case"	{
			fprintf(tokenFile,"<CASE>");
			fprintf(logFile,"Line no %d: TOKEN <CASE> Lexeme %s found\n",line_count,yytext);
		}
"default"	{
			fprintf(tokenFile,"<DEFAULT>");
			fprintf(logFile,"Line no %d: TOKEN <DEFAULT> Lexeme %s found\n",line_count,yytext);
		}
"continue"	{
			fprintf(tokenFile,"<CONTINUE>");
			fprintf(logFile,"Line no %d: TOKEN <CONTINUE> Lexeme %s found\n",line_count,yytext);
		}


"++"		|

"--"		{
			fprintf(tokenFile,"<INCOP,%s>",yytext);
			fprintf(logFile,"Line no %d: TOKEN <INCOP> Lexeme %s found\n",line_count,yytext);
			//insert in symbol table and print symbol table content(only non empty buckets)
			// There is a '|' in "+"'s rule, this means match execute the action for following rule
		}



"+"		|

"-"		{
			fprintf(tokenFile,"<ADDOP,%s>",yytext);
			fprintf(logFile,"Line no %d: TOKEN <ADDOP> Lexeme %s found\n",line_count,yytext);
			//insert in symbol table and print symbol table content(only non empty buckets)
			// There is a '|' in "+"'s rule, this means match execute the action for following rule
		}
"*"		|
"/"		|
"%"		{
			fprintf(tokenFile,"<MULOP,%s>",yytext);
			fprintf(logFile,"Line no %d: TOKEN <MULOP> Lexeme %s found\n",line_count,yytext);
			//insert in symbol table and print symbol table content(only non empty buckets)
			// There is a '|' in "+"'s rule, this means match execute the action for following rule
		}

"<"		|
"<="	|
">"		|
">="	|
"=="	|
"!="	{
			fprintf(tokenFile,"<RELOP,%s>",yytext);
			fprintf(logFile,"Line no %d: TOKEN <RELOP> Lexeme %s found\n",line_count,yytext);
			//insert in symbol table and print symbol table content(only non empty buckets)
			// There is a '|' in "+"'s rule, this means match execute the action for following rule
		}

"="		{
			fprintf(tokenFile,"<ASSIGNOP,%s>",yytext);
			fprintf(logFile,"Line no %d: TOKEN <ASSIGNOP> Lexeme %s found\n",line_count,yytext);
			//insert in symbol table and print symbol table content(only non empty buckets)
			// There is a '|' in "+"'s rule, this means match execute the action for following rule
		}

"&&"	|
"||"	|
"!"		{
			fprintf(tokenFile,"<LOGICOP,%s>",yytext);
			fprintf(logFile,"Line no %d: TOKEN <LOGICOP> Lexeme %s found\n",line_count,yytext);
			//insert in symbol table and print symbol table content(only non empty buckets)
			// There is a '|' in "+"'s rule, this means match execute the action for following rule
		}

"("		|
")"		{
			fprintf(tokenFile,"<PAREN,%s>",yytext);
			fprintf(logFile,"Line no %d: TOKEN <PAREN> Lexeme %s found\n",line_count,yytext);
			//insert in symbol table and print symbol table content(only non empty buckets)
			// There is a '|' in "+"'s rule, this means match execute the action for following rule
		}

"{"		|
"}"		{
			fprintf(tokenFile,"<CURL,%s>",yytext);
			fprintf(logFile,"Line no %d: TOKEN <CURL> Lexeme %s found\n",line_count,yytext);
			//insert in symbol table and print symbol table content(only non empty buckets)
			// There is a '|' in "+"'s rule, this means match execute the action for following rule
		}

"["		|
"]"		{
			fprintf(tokenFile,"<BRACKET,%s>",yytext);
			fprintf(logFile,"Line no %d: TOKEN <BRACKET> Lexeme %s found\n",line_count,yytext);
			//insert in symbol table and print symbol table content(only non empty buckets)
			// There is a '|' in "+"'s rule, this means match execute the action for following rule
		}


","		{
			fprintf(tokenFile,"<COMMA,%s>",yytext);
			fprintf(logFile,"Line no %d: TOKEN <COMMA> Lexeme %s found\n",line_count,yytext);
			//insert in symbol table and print symbol table content(only non empty buckets)
			// There is a '|' in "+"'s rule, this means match execute the action for following rule
		}

";"		{
			fprintf(tokenFile,"<SEMICOLON,%s>",yytext);
			fprintf(logFile,"Line no %d: TOKEN <SEMICOLON> Lexeme %s found\n",line_count,yytext);
			//insert in symbol table and print symbol table content(only non empty buckets)
			// There is a '|' in "+"'s rule, this means match execute the action for following rule
		}

{IDENTIFIER} 	{
				fprintf(tokenFile,"<ID,%s>",yytext);
				fprintf(logFile,"Line no %d: TOKEN <ID> Lexeme %s found\n",line_count,yytext);
				//insert in symbol table and print symbol table content(only non empty buckets)
			}
			

		
{INT_LIT} 	{
				fprintf(tokenFile,"<CONST_INT,%s>",yytext);
				fprintf(logFile,"Line no %d: TOKEN <CONST_INT> Lexeme %s found\n",line_count,yytext);
				//insert in symbol table and print symbol table content(only non empty buckets)
			}

{FLOAT_LIT} 	{
				fprintf(tokenFile,"<CONST_FLOAT,%s>",yytext);
				fprintf(logFile,"Line no %d: TOKEN <CONST_FLOAT> Lexeme %s found\n",line_count,yytext);
				//insert in symbol table and print symbol table content(only non empty buckets)
			}

{CHAR_LIT} 	{
				fprintf(tokenFile,"<CONST_CHAR,%s>",yytext);
				fprintf(logFile,"Line no %d: TOKEN <CONST_CHAR> Lexeme %s found\n",line_count,yytext);
				//insert in symbol table and print symbol table content(only non empty buckets)
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
					fprintf(logFile,"Line no %d: TOKEN <COMMENT> Lexeme %s found\n",myCount,buff.c_str());	
					BEGIN(INITIAL);
				}
<mlcomment><<EOF>> {
				fprintf(logFile,"Error at line %d: Undeterminated comment %s\n",line_count,buff.c_str());
				BEGIN(INITIAL);
}


{SNGL_CMNT} {
				fprintf(logFile,"Line no %d: TOKEN <COMMENT> Lexeme %s found\n",line_count,yytext);
				//insert in symbol table and print symbol table content(only non empty buckets)
			}
			

{STRING_LIT} 	{
				myCount=line_count;
				buff="";
				buff+=yytext;
				BEGIN(mlstring);
				//insert in symbol table and print symbol table content(only non empty buckets)
			}
<mlstring>\n {line_count++;}

<mlstring>[\\]. {
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
	fprintf(logFile,"Line no %d: TOKEN <STRING> Lexeme",myCount);
	fprintf(logFile," %s found\n",buff.c_str());
	fprintf(tokenFile,"<STRING,%s>",buff.c_str());
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
				fprintf(logFile,"Error at line %d: Unfinished String %s\n",myCount,buff.c_str());
				BEGIN(INITIAL);
				//insert in symbol table and print symbol table content(only non empty buckets)
			}
{MULTI_CHAR_CONST} {
				fprintf(logFile,"Error at line %d: Multi charachter constant %s\n",line_count,yytext);
				//insert in symbol table and print symbol table content(only non empty buckets)
			}


{ILL_FORMED_NUMBR} {
				fprintf(logFile,"Error at line %d: Ill formed number %s\n",line_count,yytext);
				//insert in symbol table and print symbol table content(only non empty buckets)
			}

{TOO_MANY_DECIMAL} {
				fprintf(logFile,"Error at line %d: Too many decimal points %s\n",line_count,yytext);
				//insert in symbol table and print symbol table content(only non empty buckets)
			}
{INVALID_PREFIX} {
				fprintf(logFile,"Error at line %d: Invalid prefix %s\n",line_count,yytext);
				//insert in symbol table and print symbol table content(only non empty buckets)
			}

{QUOTE_ERROR} {
				fprintf(logFile,"Error at line %d: Undetermined sequence %s\n",line_count,yytext);
				//insert in symbol table and print symbol table content(only non empty buckets)
			}



.			{
				fprintf(logFile,"Unrecognized charachter found at line %d: %s\n",line_count,yytext);
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
	
	logFile= fopen("log.txt","w");
	tokenFile= fopen("token.txt","w");
	myTable=new SymbolTable(15);

	yyin=fin;
	yylex();
	fclose(yyin);
	fclose(tokenFile);
	fclose(logFile);
	return 0;
}