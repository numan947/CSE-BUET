#include <cstdio>
#include <cmath>
#include <iostream>
#include <cstring>
#define INF 100000
#define MAX 3000
#define dbg(x) printf("HELLO WORLD %d\n",x)
using namespace std;

char seq1[MAX];
char seq2[MAX];

int dp[MAX][MAX];

#define MATCH 1
#define MISMATCH 1
#define GAP 1

int main()
{
    /*
    GLOBAL SEQENCE ALIGNMENT PROBLEM

    INPUT:
        GCATGCU
        GATTACA
    */


    freopen("G:\\Important\\C,C++\\input.txt","r",stdin);
    gets(seq1);
    gets(seq2);


    int n1=strlen(seq1);
    int n2=strlen(seq2);


    //base cases
    for(int i=0;i<=n1;i++)dp[i][0]=-i;
    for(int j=0;j<=n2;j++)dp[0][j]=-j;

    for(int i=0;i<n1;i++){
        for(int j=0;j<n2;j++){
            dp[i+1][j+1]=-INF;
            if(seq1[i]==seq2[j]){
                dp[i+1][j+1]=MATCH+dp[i][j];
            }
            else{
                dp[i+1][j+1]=max(dp[i+1][j+1],dp[i][j]-MISMATCH);
            }
            dp[i+1][j+1]=max(dp[i+1][j+1],dp[i+1][j]-GAP);
            dp[i+1][j+1]=max(dp[i+1][j+1],dp[i][j+1]-GAP);
        }
    }

    cout<<dp[n1][n2]<<endl;

    for(int i=0;i<=n1;i++)
    {
        for(int j=0;j<=n2;j++)printf("%3d ",dp[i][j]);
        cout<<endl;
    }

    cout<<seq1<<"  "<<seq2<<endl;


    //ACTUAL GLOBAL ALIGNMENT PRINTING
    string res1="",res2="";

    int i=n1-1,j=n2-1;

    while(i>-1||j>-1){

        if(i>-1&&j>-1&& dp[i+1][j+1]==dp[i][j]+MATCH&&seq1[i]==seq2[j]){//match case
            res1=seq1[i]+res1;
            res2=seq2[j]+res2;
            i--;j--;
            //cout<<"IN MATCH: "<<i<<"   "<<j<<endl;
        }
        else if(i>-1&&j>-1&& dp[i+1][j+1]==dp[i][j]-MISMATCH){
            res1=seq1[i]+res1;
            res2=seq2[j]+res2;
            i--;j--;
            //cout<<"IN MISMATCH: "<<i<<"   "<<j<<endl;
        }
        else if(i>-1&&dp[i+1][j+1]==dp[i][j+1]-GAP){
            res1=seq1[i]+res1;
            res2="_"+res2;
            i--;
           // cout<<"IN j gap: "<<i<<"   "<<j<<endl;
        }
        else if(j>-1&&dp[i+1][j+1]==dp[i+1][j]-GAP) {
            res1="_"+res1;
            res2=seq2[j]+res2;
            j--;
           // cout<<"IN i GAP: "<<i<<"   "<<j<<endl;
        }
        //cout<<i<<"   "<<j<<endl;
    }

    cout<<"Optimal Global Alignment:"<<endl;
    cout<<res1<<endl;
    for(int i=0;i<res1.size();i++)cout<<"|";
    cout<<endl;
    cout<<res2<<endl;

    return 0;
}

