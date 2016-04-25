#include <cstdio>
#include <cmath>
#include <iostream>
#include <cstring>
#define INF 100000
#define MAX 3000
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

    LOCAL SEQENCE ALIGNMENT PROBLEM
    INPUT:
        GCATGCU
        GATTACA

        mississippi
        issp

        catdogfish
        dog
    */

    freopen("G:\\Important\\C,C++\\input.txt","r",stdin);
    gets(seq1);
    gets(seq2);


    int n1=strlen(seq1);
    int n2=strlen(seq2);


    //base cases
    for(int i=0;i<=n1;i++)dp[i][0]=0;
    for(int j=0;j<=n2;j++)dp[0][j]=0;


    int mx=0,mi,mj;
    for(int i=0;i<n1;i++){
        for(int j=0;j<n2;j++){
            if(seq1[i]==seq2[j])dp[i+1][j+1]=MATCH+dp[i][j];
            else{
                dp[i+1][j+1]=max(dp[i+1][j+1],dp[i][j]-MISMATCH);
            }

            dp[i+1][j+1]=max(dp[i+1][j+1],dp[i+1][j]-GAP);
            dp[i+1][j+1]=max(dp[i+1][j+1],dp[i][j+1]-GAP);
            dp[i+1][j+1]=max(dp[i+1][j+1],0);

            if(dp[i+1][j+1]>=mx){
                mx=dp[i+1][j+1];
                mi=i;
                mj=j;
            }
        }
    }
    cout<<mx<<endl;

    for(int i=0;i<=n1;i++)
    {
        for(int j=0;j<=n2;j++)printf("%3d ",dp[i][j]);
        cout<<endl;
    }


    //ACTUAL LOCAL ALIGNMENT PRINTING
    string res1="",res2="";


    while(mx>0){

        if(mi>-1&&mj>-1&& dp[mi+1][mj+1]==dp[mi][mj]+MATCH&&seq1[mi]==seq2[mj]){//match case
            res1=seq1[mi]+res1;
            res2=seq2[mj]+res2;
            mi--;mj--;
            mx-=MATCH;
            //cout<<"IN MATCH: "<<i<<"   "<<j<<endl;
        }
        else if(mi>-1&&mj>-1&& dp[mi+1][mj+1]==dp[mi][mj]-MISMATCH){
            res1=seq1[mi]+res1;
            res2=seq2[mj]+res2;
            mi--;mj--;
            mx+=MISMATCH;
            //cout<<"IN MISMATCH: "<<i<<"   "<<j<<endl;
        }
        else if(mi>-1&&dp[mi+1][mj+1]==dp[mi][mj+1]-GAP){
            res1=seq1[mi]+res1;
            res2="_"+res2;
            mi--;
            mx+=GAP;
            //cout<<"IN j gap: "<<i<<"   "<<j<<endl;
        }
        else if(mj>-1&&dp[mi+1][mj+1]==dp[mi+1][mj]-GAP) {
            res1="_"+res1;
            res2=seq2[mj]+res2;
            mj--;
            mx+=GAP;
            //cout<<"IN i GAP: "<<i<<"   "<<j<<endl;
        }
        //cout<<mi<<"   "<<mj<<endl;
    }

    cout<<endl<<seq1<<endl<<seq2<<endl<<endl;;
    cout<<"Optimal Local Alignment:"<<endl;
    cout<<res1<<endl;
    for(int i=0;i<res1.size();i++)cout<<"|";
    cout<<endl;
    cout<<res2<<endl;
    return 0;
}

