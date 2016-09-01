#include <cstdio>
#include <bits/stdc++.h>
using namespace std;

bool compareString(string a, string b)
{
    if(a.size()!=b.size())return false;

    int len=a.size();
    for(int i=0;i<len;i++)if(a[i]!=b[i])return false;

    return true;
}

class Position
{
public:
    int col;

}






class SymbolInfo{
    string Name;
    string Type;
public:
    void setName(string name)
    {
        this->Name=name;
    }
    void setType(string type)
    {
        this->Type=type;
    }

    string getName()
    {
        return this->Name;
    }
    string getType()
    {
        return this->Type;
    }
};



class Node{
public:
    SymbolInfo val;
    Node *next;
    Node *prev;
};



class LinkeList{

    Node *head,*tail;


    Node* SearchItemInternal(string val)
    {
        Node *tmp=head;
        while(tmp!=0){
            if(compareString(tmp->val.getName(),val))return tmp;
            tmp=tmp->next;
        }
        return 0;
    }

public:
    void InitList()
    {
        head=tail=0;
    }

    bool InsertFirst(SymbolInfo val)
    {
        Node *newNode= new Node;
        newNode->val=val;

        if(head==0){
            head=tail=newNode;
            newNode->next=newNode->prev=0;
        }
        else{
            newNode->next=head;
            head->prev=newNode;
            newNode->prev=0;
            head=newNode;
        }
        return true;
    }

    bool InsertLast(SymbolInfo val)
    {
        Node *newNode=new Node;
        newNode->val=val;

        if(tail==0){
            head=tail=newNode;
            newNode->next=newNode->prev=0;
        }
        else{
            newNode->prev=tail;
            tail->next=newNode;
            newNode->next=0;
            tail=newNode;
        }
        return true;
    }

    bool SearchItem(string val) //todo: change return type may be....?
    {
        Node *tmp=head;

        while(tmp!=0){
            if(compareString(tmp->val.getName(),val))return true;
            tmp=tmp->next;
        }
        return false;
    }


    void PrintListForward()
    {
        if(head==0){
            cout<<"List is empty"<<endl;
            return;
        }
        Node *tmp=head;
        while(tmp!=0){
            cout<<"<"<<tmp->val.getName()<<","<<tmp->val.getType()<<">"<<endl;
            tmp=tmp->next;
        }

    }

    bool DeleteItem(string val)
    {
        Node* nodeToDelete=SearchItemInternal(val);
        if(nodeToDelete==0)return false;

        if(nodeToDelete==head && nodeToDelete==tail){
            head=tail=0;
            delete nodeToDelete;
        }

        else if(nodeToDelete==head){
            head=head->next;
            head->prev=0;
            delete nodeToDelete;
        }
        else if(nodeToDelete==tail){
            tail=tail->prev;
            tail->next=0;
            delete nodeToDelete;
        }
        else{
            nodeToDelete->prev->next=nodeToDelete->next;
            nodeToDelete->next->prev=nodeToDelete->prev;
            delete nodeToDelete;
        }
        return true;
    }
};







int main()
{
    LinkeList* mylist=new LinkeList;
    mylist->InitList();


    while(1)
    {
        string n,t;
        SymbolInfo vv;
        int val;
        bool get;
        scanf("%d", &val);
        if(val==128)break;


        switch(val)
        {
            case 1://insertfirst
                cin>>n>>t;
                vv.setName(n);
                vv.setType(t);
                get=mylist->InsertFirst(vv);
                get==0?cout<<"Not Inserted"<<endl : cout<<"Inserted"<<endl;
                break;
            case 2://insertlast
                cin>>n>>t;
                vv.setName(n);
                vv.setType(t);
                get=mylist->InsertLast(vv);
                get==0?cout<<"Not Inserted"<<endl : cout<<"Inserted"<<endl;
                break;
            case 3://searchItem
                cin>>n;
                get=mylist->SearchItem(n);
                get==0?cout<<"Not Found"<<endl : cout<<"Found"<<endl;
                break;
            case 4://deleteItem
                cin>>n;
                get=mylist->DeleteItem(n);
                get==0?cout<<"Not deleted (my be not found?)"<<endl : cout<<"Found & Deleted"<<endl;
                break;
            case 5:
                mylist->PrintListForward();
                break;
            default:
                cout<<"INVALID COMMAND, commands are from 1-5\nInput 128 to exit"<<endl;
                break;
        }
    }
    delete mylist;
    return 0;
}
