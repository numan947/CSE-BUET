#include<stdio.h>
#include<stdlib.h>


#define NULL_VALUE -99999
#define SUCCESS_VALUE 99999

struct listNode
{
    int item;
    struct listNode * next;
    struct listNode * prev;
};

struct listNode * list;

struct listNode * tail;

void initializeList()
{
    list = 0;  //initially set to NULL
    tail = 0;
}

int insertFirst(int item) //insert at the beginning
{
	struct listNode * newNode ;
	newNode = (struct listNode*) malloc (sizeof(struct listNode)) ;
	newNode->item = item ;

	if(list==0) //inserting the first item
    {
        newNode->next = 0;
        newNode->prev = 0;
        list = newNode;
        tail = newNode;
    }
    else
    {
        newNode->next = list;
        list->prev = newNode;
        newNode->prev = 0;
        list = newNode;
    }
	return SUCCESS_VALUE ;
}


int insertLast(int item)
{
    //write your codes here
    struct listNode *newNode;
    newNode=(struct listNode*)malloc(sizeof(struct listNode));
    newNode->item=item;
    if(tail==0) //inserting the first item
    {
        newNode->next = 0;
        newNode->prev = 0;
        list = newNode;
        tail = newNode;

    }
    else{
        newNode->prev=tail;
        newNode->next=tail->next;
        tail->next=newNode;
        tail=newNode;
    }
    return SUCCESS_VALUE;

}

int deleteLast()
{
    //write your codes here
    if(tail==0)return NULL_VALUE;
    int deleted;deleted=tail->item;
    struct listNode *temp;
    if(tail==list){

        free(tail);
        free(list);
        tail=0;
        list=0;
    }
    else{
        temp=tail->prev;
        temp->next=0;
        free(tail);
        tail=temp;
    }
    return deleted;
}


struct listNode * searchItem(int item)
{
	struct listNode * temp ;
	temp = list ; //start at the beginning
	while (temp != 0)
	{
		if (temp->item == item) return temp ;
		temp = temp->next ; //move to next node
	}
	return 0 ; //0 means invalid pointer in C, also called NULL value in C
}

void printListForward()
{
    struct listNode * temp;
    temp = list;
    //if(tail!=list)
    while(temp!=0)
    {
        printf("%d->", temp->item);
        temp = temp->next;
    }
    printf("\n");
}

void printListBackward()
{
	//will print the list backward starting from the tail position
    struct listNode * temp;
    temp = tail;
    while(temp!=0)
    {
        printf("<-%d", temp->item);
        temp = temp->prev;
    }
    printf("\n");

}


int main(void)
{
    initializeList();
    while(1)
    {
        printf("1. Insert new item (at the beginning). 2. Delete item. 3. Search item. \n");
        printf("4. Print forward. 5. Print backward.\n");
        printf("6. Insert new item at the end. 7.exit\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int item;
            scanf("%d", &item);
            insertFirst(item);
        }
        else if(ch==2)
        {
            int item = deleteLast();
            if(item!=NULL_VALUE) printf("Deleted: %d\n", item);
        }
        else if(ch==3)
        {
            int item;
            scanf("%d", &item);
            struct listNode * res = searchItem(item);
            if(res!=0) printf("Found.\n");
            else printf("Not found.\n");
        }
        else if(ch==4)
        {
            printListForward();
        }
        else if(ch==5)
        {
            printListBackward();
        }
        else if(ch==6){
            int item;
            scanf("%d",&item);
            insertLast(item);

        }
        else if(ch==7)
        {
            break;
        }
    }

}
