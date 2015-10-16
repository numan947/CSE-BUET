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
    void prin(Element *h)
    {
        if(h==0)return;
        cout<<h->getValue()<<" ";
        prin(h->getNext());
    }

public:
    LinkedList()
    {
        this->head=this->tail=0;
        this->size=0;
    }
    void print()
    {
        prin(this->head);
    }

    void HEAD()//HEAD ONLY
    {
        cout<<this->head->getValue()<<endl;
    }
    void TAIL()//TAIL ONLY
    {
        cout<<this->tail->getValue()<<endl;
    }

    Element* searchPos(Element *head,int pos)
    {
        if(pos==0)return head;
        searchPos(head->getNext(),pos-1);
    }


    void add(Element e)
    {
        Element *newElement;
        newElement=new Element;
        newElement->setValue(e.getValue());

        //cout<<"TAIL POS=="<<tail<<endl;
        //scout<<"HEAD POS=="<<head<<endl;
        if(this->getSize()==0) //inserting the first item
        {
            newElement->setNext(0);
            newElement->setPrev(0);
            this->head=newElement;
            this->tail=newElement;
            dbg(9);
        }
        else{

            newElement->setPrev(this->tail);
            newElement->setNext(this->tail->getNext());
            tail->setNext(newElement);
            //delete tail;
            tail=newElement;
            dbg(11);
        }
        this->size+=1;
    }
    void add(int index,Element element)
    {
        if(index<this->size){
            Element* temp=searchPos(this->head,index);
            element.setNext(temp);
            element.setPrev(temp->getPrev());
            temp->getPrev()->setNext(&element);
            temp->setPrev(&element);
        }
    }





};

// a very simple main
int main() {
	LinkedList ll;int p;
	for(int i=0;i<5;i++){
        cin>>p;Element q;
        //q=new Element;
        q.setValue(p);
        q.setNext(0);
        q.setPrev(0);
        ll.add(q);
	}
	//q.setNext(0);
	//q.setPrev(0);
	//q.setValue(1000);

	ll.HEAD();
	ll.TAIL();

	cout<<endl<<endl<<endl;
	ll.print();


	cout << ll.getSize() << endl;
	return 0;
}
