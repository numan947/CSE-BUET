#include<iostream>
#include<cstdio>
#define dbg(x) printf("Problem %d\n",x)/*Used for debugging purposes*/
using namespace std;



void intToString(string &s,int p)//converts an integer into a string
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

    void print()/*Prints The containing numbers*/
    {
        if(head->getNext()==tail){
            cout<<"List is empty";
            return;
        }
        PRINT(this->head->getNext());
    }


    Element* searchPos(Element *h,int pos)/*As it was needed in several functions to find the node given a certain index, I implemented this
    function for to work easily. I used head to tail traversal & recursion in this method*/
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
        LinkedListBase::size+=1;
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
        LinkedListBase::size+=1;
    }


    void add(int index,Element element)/*Inserts the specified element at the specified position in this list.*/
    {
        Element *newElement;
        newElement=new Element;
        newElement->setValue(element.getValue());
        if(index==LinkedListBase::size)add(element);
        else if(index==0)addFirst(element);
        else if(index<LinkedListBase::size){
            Element* temp=searchPos(this->head->getNext(),index);//Used the method I implemented here
            newElement->setNext(temp);
            newElement->setPrev(temp->getPrev());
            temp->getPrev()->setNext(newElement);
            temp->setPrev(newElement);
            LinkedListBase::size+=1;
        }
    }


    int size()/*Returns the number of elements in this list.*/
    {
        return getSize();
    }


    void clear()/*Removes all of the elements from this list.*/
    {
        delete head;
        delete tail;
        head=new Element;
        tail=new Element;
		head->setNext(tail);
		tail->setPrev(head);
		LinkedListBase::size = 0;
    }


    Element getFirst()/*Returns the first element in this list.*/
    {
        return *(head->getNext());
    }


    Element getLast()/*Returns the last element in this list.*/
    {
        return *(tail->getPrev());
    }


    Element get(int index)/*Returns the element at the specified position in this list.*/
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


    int indexOf(Element e)/*Returns the index of the first occurrence of the
    specified element in this list, or -1 if this list does not contain the element.*/
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


    int lastIndexOf(Element e)/*Returns the index of the last occurrence of the
specified element in this list, or -1 if this list does not contain the element.*/
    {
        Element *temp;
        temp=tail->getPrev();
        int i=LinkedListBase::size-1;
        while(temp!=head){
            if(temp->getValue()==e.getValue())return i;
            temp=temp->getPrev();
            i--;
        }
        return -1;
    }


    Element removeFirst()/*Removes and returns the first element from this list.*/
    {
        Element* ret=(head->getNext());
        head->setNext(ret->getNext());
        ret->getNext()->setPrev(head);
        LinkedListBase::size--;
        return *ret;
    }


    Element removeLast()/*Removes and returns the last element from this list.*/
    {
        Element* ret=(tail->getPrev());
        tail->setPrev(ret->getPrev());
        ret->getPrev()->setNext(tail);
        LinkedListBase::size--;
        return *ret;
    }


    Element remove(int idx)/*Removes the element at the specified position in
this list.*/
    {
        //if(idx<0||idx>=size)return ret;
        Element* temp=searchPos(this->head->getNext(),idx);//Used the method I implemented here

        if(temp==head)return removeFirst();
        else if(temp==tail)return removeLast();

        temp->getNext()->setPrev(temp->getPrev());
        temp->getPrev()->setNext(temp->getNext());
        LinkedListBase::size-=1;
        return *temp;
    }


    bool remove(Element e)/*Removes the first occurrence of the specified
element from this list, if it is present*/
    {
        int idx=indexOf(e);
        if(idx==-1)return false;
        remove(idx);
        return true;
    }


    bool removeFirstOccurrence(Element e)/*Removes the first occurrence
of the specified element in this list (when traversing the list from head to
tail).*/
    {
        remove(e);
    }


    bool removeLastOccurrence(Element e)/*Removes the last occurrence
of the specified element in this list (when traversing the list from head to
tail).*/
    {
        int idx=-1;
        int i=0;
        Element *temp=head->getNext();
        while(temp!=tail){
            if(temp->getValue()==e.getValue())idx=i;
            i++;
            temp=temp->getNext();
        }
        if(idx==-1)return false;
        remove(idx);
        return true;
    }


    bool isEmpty()/*Returns whether the list is empty or not.*/
    {
        return LinkedListBase::size==0;
    }


    string toString()/*Returns a string representation of this list, containing
the String representation of each element separated by comma(,).*/
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

    printf("5.clear() 6.contains(Element e) 7.get(int index) 8.getFirst() 9.getLast() 10.indexOf(Element e)\n\n");

    printf("11.lastIndexOf(Element e) 12.remove(int index) 13.remove(Element e) 14.removeFirst() 15.removeFirstOccurrence(Element e)\n");

    printf("16.removeLast() 17.removeLastOccurrence(Element e) 18.Size() 19.isEmpty() 20.toString() 21.print() 22.exit\n");

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
        if(ch==21){
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
            if(ll.remove(q))cout<<"Element "<<p<<" is deleted"<<endl;
            else cout<<"There's no element "<<p<<" in the list"<<endl;
        }
        if(ch==14){
            cout<<ll.removeFirst().getValue()<<endl;
        }

        if(ch==15){
            scanf("%d",&p);
            q.setValue(p);
            //cout<<ll.removeFirstOccurrence(q)<<endl;
            if(ll.removeFirstOccurrence(q))cout<<"The First occurrence of "<<p<<" is deleted"<<endl;
            else cout<<"There's no "<<p<<" in the list"<<endl;
        }

        if(ch==16){
            cout<<ll.removeLast().getValue()<<endl;
        }

        if(ch==17){
            scanf("%d",&p);
            q.setValue(p);
            if(ll.removeLastOccurrence(q))cout<<"The Last occurrence of "<<p<<" is deleted"<<endl;
            else cout<<"There's no "<<p<<" in the list"<<endl;
        }

        if(ch==18){
            cout<<"Number of elements in the list ";
            cout<<ll.size()<<endl;
        }

        if(ch==19){
            //cout<<ll.isEmpty()<<endl;
            if(ll.isEmpty())cout<<"The list is empty"<<endl;
            else cout<<"The list is not empty"<<endl;
        }

        if(ch==20){
            string tt=ll.toString();
            cout<<tt<<endl;
        }

        if(ch==5){
            ll.clear();
            cout<<"List is cleared"<<endl;
        }

        if(ch==22){
            break;
        }

    }

}
