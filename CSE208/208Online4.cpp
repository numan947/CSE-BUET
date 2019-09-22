#include <cstdio>
#include <cmath>
#include <iostream>
#include <cstring>
#define INF 100000
#define MAX 3000
#define dbg(x) printf("HELLO WORLD %d\n",x)
using namespace std;

int num[MAX];int n;

void PRINT()
{
    for(int i=1;i<=n;i++)cout<<num[i]<<" ";
    cout<<endl;
}


void revArray(int i,int j)
{
    while(i<j)
    {
        int a=num[i];
        num[i]=num[j];
        num[j]=a;
        i++;
        j--;
    }
}

int getCorrect()
{
    int t=-1;
    for(int i=1;i<=n;i++)
    {
        if(num[i]==i)t=i;
        else break;
    }

    return t;
}




int REVERSI(){

    int cnt=0;
    int crr=0;
    cout<<endl;
    PRINT();
    cout<<"STARTING ALGORITHM:"<<endl;

    while(crr!=n){
       crr=getCorrect();
        for(int i=crr+1;i<=n;i++){
            if(num[i]==crr+1){
                if(i+1<=n&&num[i+1]==num[i]+1){//CASE: INCRESING
                    int j=i+1;
                    while(j+1<=n&&num[j+1]==num[j]+1)j++;//counting till the end of the increasing valid seq
                    //cout<<"SPECIAL REVERSE"<<endl;
                    revArray(i,j);
                    PRINT();
                    revArray(crr+1,j);
                    PRINT();
                    cnt+=2;
                }
                else {//CASE: DECRESING
                    //cout<<"GENERAL REV"<<endl;
                    revArray(crr+1,i);
                    PRINT();
                    cnt++;
                }
            }
        }
    }
    return cnt;
}







int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)cin>>num[i];

    cout<<endl<<endl<<"REVERSE COUNT: "<<endl<<REVERSI()<<endl;
return 0;
}
