#include <cstdio>
#include <bits/stdc++.h>
using namespace std;

#define DEFAULT_TABLE_SIZE 10


/**
 * Simple [utility function for comparing two strings]
 * @param  a [string 1]
 * @param  b [string 2]
 * @return   [true or false based on the testing]
 */

/**
 * [SymbolInfo class contain properties of an item in
 * SymbolTable]
 */
class SymbolInfo{

    string Name;
    string Type;

public:
    int iVal;
    double dVal;
    float fVal;
    int arrayLength;
    string sVal;
    char chVal;
    bool array;

    double arrayStorage[100000];// set max array length?


    SymbolInfo()
    {
        
    }
    SymbolInfo(string Name, string Type)
    {
        this->Name=Name;
        this->Type=Type;
    }

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


/**
 * [Utility class to get the column position of an item
 * and the item itself]
 */
class Position
{

public:
    int col;
    SymbolInfo val;
};



/**
 * [Utility class which makes the nodes in the linked list]
 */
class Node{

public:
    SymbolInfo val;
    Node *next;
    Node *prev;
};

/**
 * [Main linked list is implemented here]
 */
class LinkeList{

    Node *head,*tail;
    int length;

   /**
    * private [function which is used to find specific node itself]
    * @param  val [string which is part of an item in list]
    * @return     [pointer to the element containing the string]
    */
   Node* SearchItemInternal(string val)
    {
        Node *tmp=head;
        while(tmp!=0){
            if(compareString(tmp->val.getName(),val))return tmp;

            tmp=tmp->next;
        }
        return 0;
    }

  bool compareString(string a, string b)
	{
	    if(a.size()!=b.size())return false;

	    int len=a.size();
	    for(int i=0;i<len;i++)if(a[i]!=b[i])return false;

	    return true;
	}


public:
    /**
     * [Initializes the linked list]
     */
    void InitList()
    {
        head=tail=0;
        length=0;
    }

    /**
     * [inserts item at the first position of the linked list]
     * @param  val [self explanatory]
     * @return     [self explanatory]
     */
    Position InsertFirst(SymbolInfo val)
    {
        Position IP;
        IP.col=0;

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
        length++;
        return IP;
    }

    /**
     * [adds the item at the end of the linked list]
     * @param  val [self explanatory]
     * @return     [self explanatory]
     */
    Position InsertLast(SymbolInfo val)
    {
        Position IP;
        IP.col=length;

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
        length++;
        return IP;
    }
    /**
     * [Searches the table with name specified in val]
     * @param  val [self explanatory]
     * @return     [returns the position val is found or not]
     */
    Position SearchItem(string val) //todo: change return type may be....?
    {
        Position SP;
        SP.col=0;

        Node *tmp=head;

        while(tmp!=0){
            if(compareString(tmp->val.getName(),val)){
                SP.val.setName(tmp->val.getName());
                SP.val.setType(tmp->val.getType());
                return SP;
            }
            tmp=tmp->next;
            SP.col++;
        }
        SP.col=-1;//not found
        return SP;
    }

    /**
     * [prints linked list from first to last]
     */
    void PrintListForward(FILE *logFile)
    {
        if(head==0){
            //cout<<"List is empty"<<endl;
            return;
        }
        Node *tmp=head;
        while(tmp!=0){
            //cout<<" <"<<tmp->val.getName()<<" : "<<tmp->val.getType()<<">";
            fprintf(logFile," <%s : %s>",tmp->val.getName().c_str(),tmp->val.getType().c_str());
            tmp=tmp->next;
        }

    }
    /**
     * [Searches and delets the item if found in the table]
     * @param  val [self explanatory]
     * @return     [whether deletion is failed or not]
     */
    Position DeleteItem(string val)
    {
        Position DP;

        DP=SearchItem(val);
        if(DP.col==-1)return DP;


        Node* nodeToDelete=SearchItemInternal(val);

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
        length--;
        return DP;
    }
    /**
     * [returns the length of the linked list]
     * @return [self explanatory]
     */
    int GetLength()
    {
        return length;
    }

    ~LinkeList()
    {
        Node* tmp;
        while(head!=0)
        {
            tmp=head;
            head=head->next;
            delete tmp;
        }
        head=tail=0;
        length=0;
    }


};


class SymbolTable{

    LinkeList *table;
    int rowSize;

public:
    SymbolTable()
    {
        this->rowSize=DEFAULT_TABLE_SIZE;
        table=new LinkeList[rowSize];
        for(int i=0;i<rowSize;i++)table[i].InitList();

    }

    SymbolTable(int rowSize)
    {
        this->rowSize=rowSize;
        table=new LinkeList[rowSize];
        for(int i=0;i<rowSize;i++)table[i].InitList();
    }


    unsigned long long getHash(string a)
    {
        unsigned long long hsh=4099;

        const char *ch=a.c_str();
        unsigned long long newhsh=hsh;

        for(int i=0;i<a.size();i++){
            newhsh=((newhsh<<7)+newhsh)+ch[i];
            //printf("%d\n",ch[i]);
        }
        return newhsh;
    }

    bool Insert(SymbolInfo symbol)
    {
        unsigned long long hsh=getHash(symbol.getName());
        int pos=hsh%rowSize;
        Position pp=table[pos].SearchItem(symbol.getName());
        if(pp.col!=-1){
            //cout<<"<"<<pp.val.getName()<<","<<pp.val.getType()<<"> "<<"already exists at(row,col) "<<pos<<", "<<pp.col<<endl;
            return false;
        }
        pp=table[pos].InsertLast(symbol);
        //cout<<"<"<<symbol.getName()<<","<<symbol.getType()<<"> "<<"Inserted at position(row,col) "<<pos<<", "<<pp.col<<endl;
        return true;
    }

    void LookUp(string name)
    {
        unsigned long long hsh=getHash(name);
        int pos=hsh%rowSize;

        Position pp=table[pos].SearchItem(name);

        if(pp.col==-1)cout<<name<<" not found"<<endl;
        else cout<<"<"<<name<<","<<pp.val.getType()<<">"<<" found at position(row,col) "<<pos<<", "<<pp.col<<endl;

    }

    void Delete(string name)
    {
        unsigned long long hsh=getHash(name);
        int pos=hsh%rowSize;

        Position pp=table[pos].DeleteItem(name);

        if(pp.col==-1)cout<<name<<" not found"<<endl;
        else cout<<"<"<<name<<","<<pp.val.getType()<<">"<<" deleted from(row,col) "<<pos<<", "<<pp.col<<endl;
    }



    void Print(FILE *logFile)
    {
        for(int i=0;i<rowSize;i++){
           if(table[i].GetLength()>0){
                //cout<<i<<" "<<"-->";
                fprintf(logFile, "%d -->",i );
                table[i].PrintListForward(logFile);
                //cout<<endl;
                fprintf(logFile, "\n" );
            }
        }
    }

    ~SymbolTable()
    {
        delete[]table;
    }


};


/*

int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);


    int totalRow;
    cin>>totalRow;
    SymbolTable *myTable=new SymbolTable(totalRow);

    char val;
    string nm,tp;
    SymbolInfo vv;
    Position pp;


    while(cin>>val)
    {
        cout<<val;
        switch(val)
        {
            case 'I'://insertlast
                cin>>nm>>tp;
                vv.setName(nm);
                vv.setType(tp);
                cout<<" "<<nm<<" "<<tp<<endl;
                myTable->Insert(vv);
                cout<<endl<<endl;
                break;

            case 'P'://printItem
                cout<<endl;
                myTable->Print();
                cout<<endl<<endl;
                break;
            case 'D':
                cin>>nm;
                cout<<" "<<nm<<endl;
                myTable->Delete(nm);
                cout<<endl<<endl;
                break;
            case 'L':
                cin>>nm;
                cout<<" "<<nm<<endl;
                myTable->LookUp(nm);
                cout<<endl<<endl;
                break;
            default:
                cout<<"INVALID COMMAND, commands are -\nto Insert: I name type\nto Lookup: L name\nto Delete: D name\nto Print the whole table: P\n"<<endl;
                break;
        }
    }
    return 0;

}



















int main()
{

    int totalRow;
    cin>>totalRow;

    SymbolTable *myTable=new SymbolTable(totalRow);


    while(1)
    {
        int val;


        string n,t;
        SymbolInfo vv;
        Position pp;



        scanf("%d", &val);
        if(val==128)break;


        switch(val)
        {
            case 2://insertfirst
                cin>>n>>t;
                vv.setName(n);
                vv.setType(t);

                pp=mylist->InsertFirst(vv);
                pp.col!=-1? cout<<"Inserted at "<<pp.col<<endl : cout<<"Not Inserted"<<endl;
                break;

            case 1://insertlast
                cin>>n>>t;
                vv.setName(n);
                vv.setType(t);

                pp=mylist->InsertLast(vv);
                pp.col!=-1? cout<<"Inserted at "<<pp.col<<endl : cout<<"Not Inserted"<<endl;
                break;

            case 3://searchItem
                cin>>n;
                pp=mylist->SearchItem(n);
                pp.col==-1?cout<<"Not Found"<<endl : cout<<"Found at "<<pp.col<<endl;
                break;
            case 4://deleteItem
                cin>>n;
                pp=mylist->DeleteItem(n);
                pp.col==-1?cout<<"Not deleted (my be not found?)"<<endl : cout<<"Found & Deleted from "<<pp.col<<endl;
                break;
            case 5:
                cout<<"length: "<<mylist->GetLength()<<endl;
            case 6:
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
*/
