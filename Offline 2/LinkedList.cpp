#include<iostream>
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
public:
    void add(Element e)
    {
        if(this->tail==0) //inserting the first item
        {
            e.setNext(0);
            e.setPrev(0);
            this->head=&e;
            this->tail=&e;
        }
        else{
            e.setPrev(tail);
            e.setNext(tail->getNext());
            tail->setNext(&e);
            tail=&e;
        }
        this->size+=1;
    }


};

// a very simple main
int main() {
	LinkedList ll;int p;Element q;
	for(int i=0;i<5;i++){
        cin>>p;
        q.setValue(p);
        q.setNext(0);
        q.setPrev(0);
        ll.add(q);
	}

	cout << ll.getSize() << endl;
	return 0;
}
