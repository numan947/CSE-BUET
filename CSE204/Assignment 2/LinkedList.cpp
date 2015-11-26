#include<stdio.h>
#include<stdlib.h>


#define NULL_VALUE -99999
#define SUCCESS_VALUE 99999

struct listNode
{
    int item;
    struct listNode * next;
};

struct listNode * list;

void initializeList()
{
    list = 0;  //initially set to NULL
}

int insertItem(int item) //insert at the beginning
{
	struct listNode * newNode ;
	newNode = (struct listNode*) malloc (sizeof(struct listNode)) ;
	newNode->item = item ;
	newNode->next = list ; //point to previous first node
	list = newNode ; //set list to point to newnode as this is now the first node
	return SUCCESS_VALUE ;
}


int deleteItem(int item)
{
	struct listNode *temp, *prev ;
	temp = list ; //start at the beginning
	while (temp != 0)
	{
		if (temp->item == item) break ;
		prev = temp;
		temp = temp->next ; //move to next node
	}
	if (temp == 0) return NULL_VALUE ; //item not found to delete
	if (temp == list) //delete the first node
	{
		list = list->next ;
		free(temp) ;
	}
	else
	{
		prev->next = temp->next ;
		free(temp);
	}
	return SUCCESS_VALUE ;
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

void printList()
{
    struct listNode * temp;
    temp = list;
    while(temp!=0)
    {
        printf("%d->", temp->item);
        temp = temp->next;
    }
    printf("\n");
}

int insertLast(int item)
{
    //write your codes here
    struct listNode *newnode,*temp;
    newnode=(struct listNode*)malloc(sizeof(struct listNode));
    newnode->item=item;
    temp=list;
    if(temp==0){
        insertItem(item);
    }
    else{
        while(temp->next!=0){
            temp=temp->next;
        }
        newnode->next=temp->next;
        temp->next=newnode;
    }
    return SUCCESS_VALUE;
}

int insertAfter(int oldItem, int newItem)
{
    //write your codes here
    struct listNode *newNode,*oldNode;

    oldNode=searchItem(oldItem);
    if(oldNode==NULL)return NULL_VALUE;
    newNode=(struct listNode*)malloc(sizeof(struct listNode));
    newNode->item=newItem;
    newNode->next=oldNode->next;
    oldNode->next=newNode;
    return SUCCESS_VALUE;
}

int deleteLast()
{
    //write your codes here
    if(list==0)return NULL_VALUE;
    struct listNode *temp,*prev;
    temp=list;
    prev=list;
    while(temp->next!=0){
        prev=temp,temp=temp->next;
    }
    if(temp==list){
        free(list);
        list=0;
    }
    else{
        prev->next=0;
        free(temp);
    }
    return SUCCESS_VALUE;
}

int deleteFirst()
{
    //write your codes here
    if(list==NULL)return NULL_VALUE;//list is empty
    struct listNode *temp;
    temp=list->next;
    free(list);
    list=temp;
    free(temp);
    return SUCCESS_VALUE;
}

///ONLINE
void PrefixSum(int item)
{
    struct listNode* temp=searchItem(item);

    if(temp==0){
        printf("Item Not Present\n");
        return;
    }
    else{
        struct listNode* temp2=list;
        int sum=0;

        while(temp2!=temp){
            sum+=temp2->item;
            printf("%d ",sum);
            temp2=temp2->next;
        }
        printf("%d\n",sum+temp2->item);
    }
}




int main(void)
{
    initializeList();

    while(1)
    {
        printf("1. Insert new item. 2. Delete item. 3. Search item. \n");
        printf("4. Insert new item at the end. 5.Insert after an existing item.\n6. Delete first item. 7. Delete last item.\n8. Print. 9.PrefixSum 10. exit.\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int item;
            scanf("%d", &item);
            insertItem(item);
        }
        else if(ch==2)
        {
            int item;
            scanf("%d", &item);
            deleteItem(item);
        }
        else if(ch==3)
        {
            int item;
            scanf("%d", &item);
            struct listNode * res = searchItem(item);
            if(res!=0) printf("Found.\n");
            else printf("Not found.\n");
        }
        else if(ch==4){
            int item;
            scanf("%d",&item);
            insertLast(item);
        }
        else if(ch==5){
            int Old,New;
            scanf("%d %d",&Old,&New);
            insertAfter(Old,New);
        }
        else if(ch==6){
            deleteFirst();
        }
        else if(ch==7){
            deleteLast();
        }
        else if(ch==8)
        {
            printList();
        }
        else if(ch==9){
            int item;scanf("%d",&item);
            PrefixSum(item);
        }

        else if(ch==10)
        {
            break;
        }
    }

}
