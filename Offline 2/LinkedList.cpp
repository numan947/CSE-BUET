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

    Element* searchPos(Element *head,int pos)
    {
        if(pos==0)return head;
        searchPos(head->getNext(),pos-1);
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



    void add(int index,Element element)/*Inserts the specified element at the specified position in this list.*/
    {
        Element *newElement;
        newElement=new Element;
        newElement->setValue(element.getValue());
        if(index==this->size)add(element);
        else if(index<this->size){
            Element* temp=searchPos(this->head,index);
            newElement->setNext(temp);
            newElement->setPrev(temp->getPrev());
            temp->getPrev()->setNext(newElement);
            temp->setPrev(newElement);
            this->size+=1;
        }
    }





};

// a very simple main
int main() {
	LinkedList ll;int p;Element q;
	for(int i=0;i<5;i++){
        cin>>p;
        //q=new Element;
        q.setValue(p);
        q.setNext(0);
        q.setPrev(0);
        ll.add(q);
	}
	//q.setNext(0);
	//q.setPrev(0);
	q.setValue(1000);
    ll.add(5,q);
	//ll.HEAD();
	//ll.TAIL();

	//cout<<endl<<endl<<endl;
	ll.print();


	cout <<endl<< ll.getSize() << endl;
	return 0;
}
