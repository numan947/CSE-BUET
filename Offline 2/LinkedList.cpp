#include<iostream>
#include<cstdio>
#define dbg(x) printf("HERE COMES THE PACKAGE %d\n",x)
using namespace std;

void intToString(string &s,int p)
{
    //cout<<p<<endl;
    if(p<10){
        s+=(char)(p+'0');
        return;
    }
    else intToString(s,p/10);
    s+=(char)(p%10)+'0';
}



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
        if(h==tail)return;
        cout<<h->getValue()<<" ";
        PRINT(h->getNext());
    }


public:

    void print()
    {
        if(head->getNext()==tail){
            cout<<"List is empty"<<endl;
            return;
        }
        PRINT(this->head->getNext());
    }


    Element* searchPos(Element *h,int pos)
    {
        if(pos==0)return h;
        searchPos(h->getNext(),pos-1);
    }


    bool contains(Element e)
    {
        Element * temp ;
        temp = head->getNext();
        while (temp != tail)
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
        //cout<<"HEAD-->>"<<head->getNext()<<"  "<<"TAIL-->>"<<tail->getPrev()<<endl;
        if(this->getSize()==0) //inserting the first item
        {
            newElement->setNext(tail);
            newElement->setPrev(head);
            head->setNext(newElement);
            tail->setPrev(newElement);
        }
        else{
            newElement->setPrev(tail->getPrev());
            newElement->setNext(tail);
            tail->getPrev()->setNext(newElement);
            tail->setPrev(newElement);
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
            newElement->setNext(tail);
            newElement->setPrev(head);
            head->setNext(newElement);
            tail->setPrev(newElement);
        }
        else{
            newElement->setNext(head->getNext());
            newElement->setPrev(head);
            head->getNext()->setPrev(newElement);
            head->setNext(newElement);
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
            Element* temp=searchPos(this->head->getNext(),index);
            newElement->setNext(temp);
            newElement->setPrev(temp->getPrev());
            temp->getPrev()->setNext(newElement);
            temp->setPrev(newElement);
            this->size+=1;
        }
    }


    int Size()
    {
        return getSize();
    }


    void clear()
    {
        delete head;
        delete tail;
        head=new Element;
        tail=new Element;
		head->setNext(tail);
		tail->setPrev(head);
		size = 0;
    }


    Element getFirst()
    {
        return *(head->getNext());
    }


    Element getLast()
    {
        return *(tail->getPrev());
    }


    Element get(int index)
    {
        if(index==0)return getFirst();
        else if(index==getSize()-1)return getLast();

        Element* temp;
        temp=head->getNext();
        while(index--){
            temp=temp->getNext();
        }
        return *temp;
    }


    int indexOf(Element e)
    {
        Element * temp ;
        temp = head->getNext();
        int i=0;
        while (temp != tail)
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
        temp=tail->getPrev();
        int i=size-1;
        while(temp!=head){
            if(temp->getValue()==e.getValue())return i;
            temp=temp->getPrev();
            i--;
        }
        return -1;
    }


    Element removeFirst()
    {
        Element* ret=(head->getNext());
        head->setNext(ret->getNext());
        ret->getNext()->setPrev(head);
        size--;
        return *ret;
    }


    Element removeLast()
    {
        Element* ret=(tail->getPrev());
        tail->setPrev(ret->getPrev());
        ret->getPrev()->setNext(tail);
        size--;
        return *ret;
    }


    Element remove(int idx)
    {
        //if(idx<0||idx>=size)return ret;
        Element* temp=searchPos(this->head->getNext(),idx);

        if(temp==head)return removeFirst();
        else if(temp==tail)return removeLast();

        temp->getNext()->setPrev(temp->getPrev());
        temp->getPrev()->setNext(temp->getNext());
        this->size-=1;
        return *temp;
    }


    bool remove(Element e)
    {
        int idx=indexOf(e);
        if(idx==-1)return false;
        remove(idx);
        return true;
    }


    bool removeFirstOccurrence(Element e)
    {
        remove(e);
    }


    bool removeLastOccurrence(Element e)
    {
        int idx=lastIndexOf(e);
        if(idx==-1)return false;
        remove(idx);
        return true;
    }


    bool isEmpty()
    {
        return size==0;
    }


    string toString()
    {
        string ret="";
        if(isEmpty())return ret;

        Element* temp=head->getNext();
        string t="";
        intToString(t,temp->getValue());
        ret+=t;
        temp=temp->getNext();
        while(temp!=tail){
            t="";
            intToString(t,temp->getValue());
            ret+=",";
            ret+=t;
            temp=temp->getNext();
        }
        return ret;
    }

};

// a very simple main

int main()
{

    printf("1.add(Element e) 2.add(int index, Element element) 3.addFirst(Element e) 4.addLast(Element e)\n\n");

    printf("5.print() 6.contains(Element e) 7.get(int index) 8.getFirst() 9.getLast() 10.indexOf(Element e)\n\n");

    printf("11.lastIndexOf(Element e) 12.remove(int index) 13.remove(Element e) 14.removeFirst() 15.removeFirstOccurrence(Element e)\n");

    printf("16.removeLast() 17.removeLastOccurrence(Element e) 18.Size() 19.isEmpty() 20.toString() 21.clear() 22.exit\n");

    LinkedList ll;int p;Element q;

    while(1)
    {
        int ch;
        scanf("%d",&ch);

        if(ch==1){
            scanf("%d",&p);
            q.setValue(p);
            ll.add(q);
        }
        if(ch==2){
            int i;
            scanf("%d%d",&i,&p);
            q.setValue(p);
            ll.add(i,q);
        }
        if(ch==3){
            scanf("%d",&p);
            q.setValue(p);
            ll.addFirst(q);
        }
        if(ch==4){
            scanf("%d",&p);
            q.setValue(p);
            ll.addLast(q);
        }
        if(ch==5){
            ll.print();cout<<endl;
        }
        if(ch==6){
            scanf("%d",&p);
            q.setValue(p);
            if(ll.contains(q))cout<<"YES"<<endl;
            else cout<<"NO"<<endl;
        }

        if(ch==7){
            scanf("%d",&p);
            cout<<ll.get(p).getValue()<<endl;
        }

        if(ch==8){
            cout<<ll.getFirst().getValue()<<endl;
        }

        if(ch==9){
            cout<<ll.getLast().getValue()<<endl;
        }

        if(ch==10){
            scanf("%d",&p);
            q.setValue(p);
            cout<<ll.indexOf(q)<<endl;
        }

        if(ch==11){
            scanf("%d",&p);
            q.setValue(p);
            cout<<ll.lastIndexOf(q)<<endl;
        }
        if(ch==12){
            scanf("%d",&p);
            cout<<ll.remove(p).getValue()<<endl;
        }
        if(ch==13){
            scanf("%d",&p);
            q.setValue(p);
            cout<<ll.remove(q)<<endl;
        }
        if(ch==14){
            cout<<ll.removeFirst().getValue()<<endl;
        }

        if(ch==15){
            scanf("%d",&p);
            q.setValue(p);
            cout<<ll.removeFirstOccurrence(q)<<endl;
        }

        if(ch==16){
            cout<<ll.removeLast().getValue()<<endl;
        }

        if(ch==17){
            scanf("%d",&p);
            q.setValue(p);
            cout<<ll.removeLastOccurrence(q)<<endl;
        }

        if(ch==18){
            cout<<ll.Size()<<endl;
        }

        if(ch==19){
            cout<<ll.isEmpty()<<endl;
        }

        if(ch==20){
            string tt=ll.toString();
            cout<<tt<<endl;
        }

        if(ch==21){
            ll.clear();
        }

        if(ch==22){
            break;
        }

    }

}
