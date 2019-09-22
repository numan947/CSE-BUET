#include <iostream>
#include <stdio.h>
#include <cstring>
#include "vector"
#include "string"
using namespace std;


class Tokenizer{

public:
    vector<string> generateToken(string input,string delimeter)
    {
        vector<string>tokens;

        char*dlm=new char[delimeter.size()+1];
        copy(delimeter.begin(),delimeter.end(),dlm);
        dlm[delimeter.size()]='\0';

        char*inp=new char[input.size()+1];
        copy(input.begin(),input.end(),inp);
        inp[input.size()]='\0';

        char* tk;

        tk=strtok(inp,dlm);

        while(tk!=NULL){
            if(tk!=NULL){
                string t(tk);
                tokens.push_back(t);
            }
            tk=strtok(NULL,dlm);
        }
        return tokens;
    }
};

