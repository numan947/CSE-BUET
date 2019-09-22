#include <bits/stdc++.h>
using  namespace std;
#define MAX 700
#define refINF 100000000
#define dbg(x) printf("debug %d\n",x)


struct segment{
    int l,r;    //l & r are inclusive segments
    bool operator==(const segment &a)const{
        return a.l==l&&a.r==r;
    }
};


int ara[MAX],N,ans;
segment solution[MAX];


void printArray()
{
    for(int i=1;i<=N;i++)cout<<ara[i]<<" ";
    cout<<endl;
}


void revArray(int l,int r)
{
    while(l<r){
        int p=ara[l];
        ara[l]=ara[r];
        ara[r]=p;
        l++;r--;
    }
}


int countBreakPoints()
{
    int pp=0;
    for(int i=0;i<=N;i++)if(abs(ara[i]-ara[i+1])>1)pp++;
    return pp-1;
}


void getBreakPoints(segment *seg,int &tot)
{
    for(int i=0;i<=N;i++){
        if(abs(ara[i]-ara[i+1])>1){
            for(int j=i+2;j<=N;j++){
                if(abs(ara[j]-ara[j+1])>1){
                    seg[tot].l=i+1;
                    seg[tot].r=j;
                    tot++;
                }
            }
        }
    }
}


bool sortingByReversals(int revTillNow,int prevBreakPoints,segment pre)
{
    bool done=false;
    int breakPoints=countBreakPoints();


    if(breakPoints==0){                                 //array is sorted now
        if(revTillNow<ans){
            ans=revTillNow;
            return true;
        }
        return false;
    }

    if(breakPoints>prevBreakPoints)return false;       //break points decreasing or not check
    if(revTillNow+(breakPoints)/2>=ans)return false;    //lower bound check

    int tot=0;
    segment *listOfSegments=new segment[MAX];


    getBreakPoints(listOfSegments,tot);
    /*cout<<"number of reversals till now: "<<revTillNow<<endl;
    for(int i=0;i<tot;i++){
        cout<<listOfSegments[i].l<<"  "<<listOfSegments[i].r<<endl;
    }*/

    for(int i=0;i<tot;i++){

        if(listOfSegments[i]==pre)continue;
        revArray(listOfSegments[i].l,listOfSegments[i].r);
        bool m=sortingByReversals(revTillNow+1,breakPoints,listOfSegments[i]);
        if(m){
            solution[revTillNow]=listOfSegments[i];
            done=true;
        }
        revArray(listOfSegments[i].l,listOfSegments[i].r);

    }
    delete []listOfSegments;
    return done;
}


/*
inputs: 1 3 4 2 6 5
        1 4 5 7 6 3 2
*/



int main()
{
    //freopen("G:\Important\C,C++\\input.txt","r",stdin);
    cin>>N;
    {
        ara[0]=0;
        ara[N+1]=refINF;

        for(int i=1;i<=N;i++)cin>>ara[i];
        cout<<endl<<endl<<endl;
        ans=refINF;
        segment ss;
        ss.l=0;
        ss.r=N+1;
        if(sortingByReversals(0,MAX,ss))cout<<endl<<endl<<endl<<endl<<"NEEDED REVERSALS: "<<ans<<endl;
        else cout<<"SORTING NOT POSSIBLE"<<endl;
        if(ans!=refINF)
        for(int i=0;i<ans;i++){
            cout<<"reversing from "<<solution[i].l<<" to "<<solution[i].r<<endl;
            revArray(solution[i].l,solution[i].r);
            printArray();
        }
    }
}
