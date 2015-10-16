#include<iostream>
#include<cstdio>
#define dbg(x) printf("HERE COMES THE PACKAGE %d\n",x)
using namespace std;

class Element {
private:
    Element * next;
	Element * prev;
	int value;
public:
	void setNext(Element *n) {
		next = n;
	}
	Element * getNext() {
		return next;
	}
	void setPrev(Element *p) {
		prev  = p;
	}
	Element * getPrev() {
		return prev;
	}
	void setValue(int v) {
		value = v;
	}
	int getValue() {
		return value;
	}
};

class LinkedListBase {
protected:
	Element * head;
	Element * tail;
	int size;
public:
	LinkedListBase() {
        head=new Element;
        tail=new Element;
		head->setNext(tail);
		tail->setPrev(head);
		size = 0;
    }
	int getSize() {
		return size;
	}
	~LinkedListBase() {
		delete head;
		delete tail;
	}
};

class LinkedList: public LinkedListBase {
private:
    void PRINT(Element *h)
    {
        if(h==0)return;
        cout<<h->getValue()<<" ";
        PRINT(h->getNext());
    }

public:
    LinkedList()
    {
        this->head=this->tail=0;
        this->size=0;
    }
    void print()
    {
        if(head==0){
            cout<<"List is empty"<<endl;
            return;
        }
        PRINT(this->head);
    }

    void HEAD()//HEAD ONLY
    {
        cout<<this->head->getValue()<<endl;
    }
    void TAIL()//TAIL ONLY
    {
        cout<<this->tail->getValue()<<endl;
    }

    Element* searchPos(Element *h,int pos)
    {
        if(pos==0)return h;
        searchPos(h->getNext(),pos-1);
    }
    bool contains(Element e)
    {
        Element * temp ;
        temp = head;
        while (temp != 0)
        {
            if (temp->getValue() == e.getValue()) return true ;
            temp = temp->getNext() ;
        }
        return false;
    }

    void add(Element e)/*Appends the specified element to the end of this list.*/
    {
        Element *newElement;
        newElement=new Element;
        newElement->setValue(e.getValue());

        if(this->getSize()==0) //inserting the first item
        {
            newElement->setNext(0);
            newElement->setPrev(0);
            this->head=newElement;
            this->tail=newElement;
        }
        else{

            newElement->setPrev(this->tail);
            newElement->setNext(this->tail->getNext());
            tail->setNext(newElement);
            tail=newElement;
        }
        this->size+=1;
    }

    void addLast(Element e)//Appends the specified element to the end of this list.
    {
        add(e);
    }

    void addFirst(Element e)//Inserts the specified element at the beginning of this list.
    {
        Element *newElement;
        newElement=new Element;
        newElement->setValue(e.getValue());

        if(this->getSize()==0) //inserting the first item
        {
            newElement->setNext(0);
            newElement->setPrev(0);
            this->head=newElement;
            this->tail=newElement;
        }
        else{
            newElement->setNext(head);
            newElement->setPrev(head->getPrev());
            head=newElement;
        }
        this->size+=1;
    }
    void add(int index,Element element)/*Inserts the specified element at the specified position in this list.*/
    {
        Element *newElement;
        newElement=new Element;
        newElement->setValue(element.getValue());
        if(index==this->size)add(element);
        else if(index==0)addFirst(element);
        else if(index<this->size){
            Element* temp=searchPos(this->head,index);
            newElement->setNext(temp);
            newElement->setPrev(temp->getPrev());
            temp->getPrev()->setNext(newElement);
            temp->setPrev(newElement);
            this->size+=1;
        }
    }
    void clear()
    {
        delete head;
        delete tail;
        size=0;
        head=tail=0;
    }
    int Size()
    {
        return this->size;
    }

    Element get(int index)
    {
        Element* temp;
        temp=head;
        Element p;
        while(index--){
            temp=temp->getNext();
        }
        p=*temp;
        return p;
    }
    Element getFirst()
    {
        return *head;
    }
    Element getLast()
    {
        return *tail;
    }
    int indexOf(Element e)
    {
        Element * temp ;
        temp = head;
        int i=0;
        while (temp != 0)
        {
            if (temp->getValue() == e.getValue()) return i ;
            temp = temp->getNext() ;
            i++;
        }
        return -1;

    }

    int lastIndexOf(Element e)
    {
        Element *temp;
        temp=tail;
        int i=size-1;
        while(temp!=0){
            if(temp->getValue()==e.getValue())return i;
            temp=temp->getPrev();
        }
        return -1;
    }
    Element removeFirst()
    {
        Element ret=*head;
        head->getNext()->setPrev(0);
        head=head->getNext();
        size--;
        return ret;
    }
    Element removeLast()
    {
        Element ret=*tail;
        tail->getPrev()->setNext(0);
        tail=tail->getPrev();
        size--;
        return ret;
    }


    Element remove(int idx)
    {
        Element ret;
        ret.setValue(-1000);
        if(idx<0||idx>=size)return ret;
        Element* temp=searchPos(this->head,idx);
        ret=*temp;

        if(temp==head)return removeFirst();
        else if(temp==tail)return removeLast();

        temp->getNext()->setPrev(temp->getPrev());
        temp->getPrev()->setNext(temp->getNext());
        this->size-=1;
        return ret;
    }





};

// a very simple main

int main()
{
    LinkedList ll;int p;Element q;
        printf("1. Insert new item. 2.Insert at pos_>>pos>>elem. 3. addLast. \n");
        printf("4. Add first. 5.print.\n");
        printf("6. SizeofList. 7.Clear list 8.check if item is in the list 9.get idx's value 10.remove i'th index's val & show\n");
    while(1)
    {


        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int item;
            scanf("%d", &item);
            q.setValue(item);
            ll.add(q);
        }
        else if(ch==2)
        {
            int item,pos;
            scanf("%d %d",&pos, &item);
            q.setValue(item);
            ll.add(pos,q);
        }
        else if(ch==3)
        {
            int item;
            scanf("%d", &item);
            q.setValue(item);
            ll.addLast(q);
        }
        else if(ch==4)
        {
            int item;
            scanf("%d", &item);
            q.setValue(item);
            ll.addFirst(q);
        }
        else if(ch==5)
        {
            ll.print();
            cout<<endl;
        }
        else if(ch==6){
            cout<<ll.Size()<<endl;

        }
        else if(ch==7)
        {
            ll.clear();
        }
        else if(ch==8){
            int i;scanf("%d",&i);
            q.setValue(i);
            if(ll.contains(q))cout<<"YES"<<endl;
            else cout<<"NO"<<endl;
        }
        else if(ch==9){
            int idx;scanf("%d",&idx);
            cout<<ll.get(idx).getValue()<<endl;
        }
        else if(ch==10){
            int id;cin>>id;
            cout<<ll.remove(id).getValue()<<endl;
        }
    }

}
