#include<stdio.h>
#include<stdlib.h>

#define LIST_INIT_SIZE 2
#define NULL_VALUE -99999
#define SUCCESS_VALUE 99999

int listMaxSize;
int * list;
int length;


void initializeList()
{
	listMaxSize = LIST_INIT_SIZE;
	list = (int*)malloc(sizeof(int)*listMaxSize) ;
	length = 0 ;
}
int shrink() ///TASK 3
{
    if(length<=(listMaxSize/2)&&listMaxSize>LIST_INIT_SIZE){
        int i,*tempList;
        listMaxSize/=2;
        tempList=(int*)malloc(listMaxSize*sizeof(int));
        for(i=0;i<length;i++)tempList[i]=list[i];
        free(list);
        list=tempList;
        return SUCCESS_VALUE;
    }
    return NULL_VALUE;
}



int searchItem(int item)
{
	int i = 0;
	for (i = 0; i < length; i++)
	{
		if( list[i] == item ) return i;
	}
	return NULL_VALUE;
}

int insertItem(int newitem)
{
	if(list==0){
        initializeList();
	}
	int * tempList ;
	if (length == listMaxSize)
	{
		//allocate new memory space for tempList
		listMaxSize = 2 * listMaxSize ;
		tempList = (int*) malloc (listMaxSize*sizeof(int)) ;
		int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ; //copy all items from list to tempList
        }
        free(list) ; //free the memory allocated before
        list = tempList ; //make list to point to new memory
	}

	list[length] = newitem ; //store new item
	length++ ;
	return SUCCESS_VALUE ;
}


int deleteItemAt(int position) //version 2, do not preserve order of items
{
	if ( position >= length ) return NULL_VALUE;
	list[position] = list[length-1] ;
	length-- ;
	shrink();
	return SUCCESS_VALUE ;
}


int deleteItem(int item)
{
	int position;
	position = searchItem(item) ;
	if ( position == NULL_VALUE ) return NULL_VALUE;
	deleteItemAt(position) ;
	shrink();
	return SUCCESS_VALUE ;
}

void printList()
{
    int i;
    for(i=0;i<length;i++)
        printf("%d ", list[i]);
    printf("Current size: %d, current length: %d\n", listMaxSize, length);
}
int getLength()/// TASK 1
{
    return length;
}


int insertItemAt(int pos, int item)/// TASK 2
{
    if(pos>=length)return NULL_VALUE;
	if (length==listMaxSize){
		listMaxSize=2*listMaxSize ;
		int *tempList=(int*)malloc(listMaxSize*sizeof(int)) ;
		int i;
        for(i=0;i<length;i++){
            tempList[i]=list[i] ;
        }
        free(list);
        list=tempList;
    }
    list[length++]=list[pos];
    list[pos]=item;
    return SUCCESS_VALUE;
}

int deleteLast()///TASK 4
{
    if(length==0)return NULL_VALUE;
    length--;
    shrink();
    return SUCCESS_VALUE;
}
void clear()///TASK 5
{
    length=0;
    listMaxSize=0;
    free(list);
    list=0;
}

void deleteAll()///TASK 6
{
    if(length>LIST_INIT_SIZE||listMaxSize>LIST_INIT_SIZE){
        free(list);
        list=(int*)malloc(LIST_INIT_SIZE*sizeof(int));
        listMaxSize=LIST_INIT_SIZE;
    }
    length=0;
}


int main(void)
{
    initializeList();
    while(1)
    {
        printf("1. Insert new item. 2. Delete item at. 3. Delete item.\n");
        printf("4. Print. 5. Get current length .\n");
        printf("6.insert a new item at a specific position. 7.trying to shrink the list\n");
        printf("8. delete the last item. 9. clear the list. 10. delete all elements. 11. exit\n");


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
            int pos;
            scanf("%d", &pos);
            deleteItemAt(pos);
        }
        else if(ch==3)
        {
            int item;
            scanf("%d", &item);
            deleteItem(item);
        }
        else if(ch==4)
        {
            printList();
        }
        else if(ch==5)
        {
            getLength();
            //printf("current length = %d\n",getLength());
        }
        else if(ch==6){
            int item,pos;
            scanf("%d %d",&item,&pos);
            //if(insertItemAt(pos,item)==SUCCESS_VALUE)printf("Insertion Successful\n");
            //else printf("insertion failed\n");
        }
        else if(ch==7){
            int curMax=listMaxSize;
            shrink();
            //printf("before %d\nafter%d\n",curMax,listMaxSize);
        }
        else if(ch==8){
            //printf("before last=%d\n",list[length-1]);
            deleteLast();
            //printf("after last=%d\n",list[length-1]);
        }
        else if(ch==9){
            clear();
            //printf("length %d listmaxsize %d\n",length,listMaxSize);
        }
        else if(ch==10){
            //printf("length %d listmaxsize %d\n",length,listMaxSize);
            deleteAll();
            //printf("length %d listmaxsize %d\n",length,listMaxSize);
        }
        else if(ch==11)break;
    }

}


/*
int main()
{
    initializeList();
    char input[1000];
    scanf("%s",input);
    int i,check=1,vcheck,l;
    for(i=0;input[i]!='\0';i++){
        if(input[i]=='('||input[i]=='{'||input[i]=='['){
            vcheck=insertItem((int)input[i]);
            continue;
        }
        else{
            l=getLength();
            if(l==0)check=0;
            else if(input[i]==')'&&list[l-1]=='('){
                check=1;
                if(deleteLast()==NULL_VALUE)exit(1);
            }
            else if(input[i]=='}'&&list[l-1]=='{'){
                check=1;
                if(deleteLast()==NULL_VALUE)exit(1);
            }
            else if(input[i]==']'&&list[l-1]=='['){
                check=1;
                if(deleteLast()==NULL_VALUE)exit(1);
            }
            else check=0;
        }
        if(check==0)break;
    }
    if(getLength()>0)check=0;
    if(check)printf("Balanced\n");
    else printf("Not Balanced\n");
    return 0;
}
*/


