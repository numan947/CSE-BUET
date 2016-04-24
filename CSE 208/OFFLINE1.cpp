#include <cstdio>
#include <cmath>
#include <iostream>
#define MAX 300000
using namespace std;


///HEAP START
class item{
public:
    double avg;
    int id;
};
class Heap{
private:
    item *ara;
    int n;

public:
    Heap(int sz)
    {
        n=sz;
        //ara=new item[n];
    }

    void setAra(item *pp)
    {
        ara=pp;
    }

    void maxHeapify(int i)
    {
        int l=2*i;
        int r=2*i+1;
        int large=-1;
        if(l<n&&ara[l].avg>ara[r].avg)large=l;///may need to change
        else large=i;                  ///may need to change
        if(r<n&&ara[r].avg>ara[large].avg)large=r;///may need to change
        if(large!=i){
            item v=ara[i];
            ara[i]=ara[large];//may need to change
            ara[large]=v;
            maxHeapify(large);
        }
    }

    void buildHeap()
    {
        for(int i=(n/2)-1;i>=0;i--){
            maxHeapify(i);
        }
    }

    int getMax()
    {
        if(n==0)return -1;
        return ara[0].id;//change
    }

    int extractMax()
    {
        if(n==0)return -1;
        int mx=ara[0].id;//change
        ara[0]=ara[n-1];
        n--;
        maxHeapify(0);
        return mx;

    }

    int getHeapSize()
    {
        return n;
    }

    ~Heap()
    {
        delete []ara;
        ara=0;
    }

};
///HEAP END


class ITEM1{
public:
    int weight,value;
    ITEM1()
    {

    }
    ITEM1(int w,int v)
    {
        weight=w;
        value=v;
    }
};

class ITEM2{
public:
    int weight,number;
    ITEM2()
    {

    }
    ITEM2(int w,int num)
    {
        weight=w;
        number=num;
    }
};



ITEM1 given[MAX];
ITEM2 taken[MAX];
item ara[MAX];




int main()
{
    //freopen("input.txt","r",stdin);

    int cap;
    int n;

    cin>>n>>cap;

    Heap h(n);

    for(int i=0;i<n;i++){
        cin>>given[i].weight>>given[i].value;
        ara[i].id=i;
        ara[i].avg=1.0*given[i].value/given[i].weight;
    }

    h.setAra(ara);
    h.buildHeap();
    int take=0;
    double total_cost=0.0;

    while(cap>0&&h.getMax()!=-1){
        int idx=h.extractMax();
        taken[take].number=idx+1;
        if(given[idx].weight<=cap)
        {
            taken[take].weight=given[idx].weight;
            cap-=given[idx].weight;
            total_cost+=given[idx].value;
            take++;
        }
        else
        {
            taken[take].weight=cap;
            total_cost+=((1.0*given[idx].value/given[idx].weight)*cap);
            cap=0;
            take++;
        }
    }
    for(int i=0;i<take;i++){
        cout<<taken[i].number<<"  "<<taken[i].weight<<endl;
    }
    cout<<"TOTAL VALUE TAKEN: "<<total_cost<<endl;


}







