#include <cstdio>
#include <cmath>
#include <iostream>
#define INF 100000
#define MAX 3000
using namespace std;

int MERGE(int *ara,int p,int q,int r)
{
    int inv_cnt=0;
    int n1=q-p+1;
    int n2=r-q;

    cout<<"merging ...."<<endl;;
    //cout<<"ara1"<<"\n";
    for(int i=p;i<=q;i++)cout<<ara[i]<<"  ";
    cout<<endl;

    cout<<"AND"<<endl;
    //cout<<"ara2"<<"\n";
    for(int i=q+1;i<=r;i++)cout<<ara[i]<<"  ";
    cout<<endl;
    cout<<"merge completed"<<endl<<endl;

    int left[n1+2];
    int right[n2+2];

    for(int i=1;i<=n1;i++)left[i]=ara[p+i-1];

    for(int i=1;i<=n2;i++)right[i]=ara[q+i];

    left[n1+1]=INF;
    right[n2+1]=INF;

    int i,j,k;
    i=j=1;
    k=p;
    while(i<=n1&&j<=n2)
    {
        if(left[i]<=right[j]){
            ara[k++]=left[i++];
        }
        else {
            ara[k++]=right[j++];
            inv_cnt+=n1-i+1;
        }
    }
    while(i<=n1)ara[k++]=left[i++];
    while(j<=n2)ara[k++]=right[j++];
    /*for(k=p;k<=r;k++){
        if(left[i]<right[j]){
            ara[k]=left[i];
            i++;
        }
        else{
            inv_cnt+=q-i;
            ara[k]=right[j];
            j++;
        }
    }*/
    return inv_cnt;
}



int MERGE_SORT(int *ara,int p,int r)
{
    int inv_cnt=0;
    if(p<r){
        int mid=(p+r)/2;

        cout<<"dividing sub array ["<<p<<","<<r<<"] into ara1["<<p<<","<<mid<<"] & ara2["<<mid+1<<","<<r<<"]"<<endl;
        cout<<"ara1"<<endl;


        for(int i=p;i<=mid;i++)cout<<ara[i]<<"  ";
        cout<<endl;
        cout<<"ara2"<<endl;
        for(int i=mid+1;i<=r;i++)cout<<ara[i]<<"  ";
        cout<<endl<<endl;

        inv_cnt+=MERGE_SORT(ara,p,mid);
        inv_cnt+=MERGE_SORT(ara,mid+1,r);
        inv_cnt+=MERGE(ara,p,mid,r);
    }
    return inv_cnt;
}


int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int n;
    cin>>n;
    int *ara=new int[n+2];

    for(int i=1;i<=n;i++)cin>>ara[i];

    cout<<MERGE_SORT(ara,1,n)<<endl;


    for(int i=1;i<=n;i++)cout<<ara[i]<<" ";
    cout<<endl;

}
