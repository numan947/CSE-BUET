#include <cstdio>
#include <cmath>
#include <iostream>
#include <cstring>
#define INF 100000
#define MAX 3000
using namespace std;

char seq1[MAX];
char seq2[MAX];


#define MATCH 1
#define MISMATCH 1
#define GAP 1

int main()
{
    freopen("input.txt","r",stdin);
    gets(seq1);
    gets(seq2);


    int n1=strlen(seq1);
    int n2=strlen(seq2);

    int *D0=new int[n1+1];
    int *D1=new int[n2+1];


    for(int j=0;j<=n2+1;j++)D0[j]=-j;

    for(int i=1;i<=n1+1;i++){
        D1[0]=-i;
        for(int j=1;j<=n2+1;j++){
            D1[j]=-INF;
            if(seq1[i-1]==seq2[j-1]){
                D1[j]=D0[j-1]+MATCH;
            }
            else{

                D1[j]=max(D1[j],D0[j-1]-MISMATCH);
                D1[j]=max(D1[j],D0[j]-GAP);
                D1[j]=max(D1[j],D1[j-1]-GAP);
            }
        }
        swap(D0,D1);
    }
    cout<<D1[n2+1];

}
