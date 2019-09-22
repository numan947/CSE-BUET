#include<stdio.h>
#include<stdlib.h>
#include<bits/stdc++.h>
#define debug(x) printf("PING AT POINT %d\n",x)
#define NULL_VALUE -999999
#define refINFINITY 999999
#define WHITE 1
#define GREY 2
#define BLACK 3
using namespace std;



class Queue
{
    int queueInitSize ;
    int queueMaxSize;
    int * data;
    int length;
    int front;
    int rear;
public:
    Queue();
    ~Queue();
    void enqueue(int item); //insert item in the queue
    int dequeue(); //returns the item according to FIFO
    bool empty(); //return true if Queue is empty
};

Queue::Queue()
{
    queueInitSize = 2 ;
    queueMaxSize = queueInitSize;
    data = new int[queueMaxSize] ; //allocate initial memory
    length = 0 ;
    front = 0;
    rear = 0;
}


void Queue::enqueue(int item)
{
	if (length == queueMaxSize)
	{
		int * tempData ;
		//allocate new memory space for tempList
		queueMaxSize = 2 * queueMaxSize ;
		tempData = new int[queueMaxSize] ;
		int i, j;
		j = 0;
		for( i = rear; i < length ; i++ )
		{
			tempData[j++] = data[i] ; //copy items from rear
		}
		for( i = 0; i < rear ; i++ )
		{
			tempData[j++] = data[i] ; //copy items before rear
		}
		rear = 0 ;
		front = length ;
		delete[] data ; //free the memory allocated before
		data = tempData ; //make list to point to new memory
	}

	data[front] = item ; //store new item
	front = (front + 1) % queueMaxSize ;
	length++ ;
}


bool Queue::empty()
{
	if(length == 0) return true ;
	else return false ;
}


int Queue::dequeue()
{
	if(length == 0) return NULL_VALUE ;
	int item = data[rear] ;
	rear = (rear + 1) % queueMaxSize ;
	length-- ;
	return item ;
}


Queue::~Queue()
{
    if(data) delete[] data; //deallocate memory
    data = 0; //set to NULL
}

//****************Queue class ends here************************

//****************Dynamic ArrayList class based************************
class ArrayList
{
	int * list;
	int length ;
	int listMaxSize ;
	int listInitSize ;
public:
	ArrayList() ;
	~ArrayList() ;
	int searchItem(int item) ;
    void insertItem(int item) ;
	void removeItem(int item) ;
	void removeItemAt(int position);
	int getItem(int position) ;
	int getLength();
	bool empty();
	void printList();
} ;


ArrayList::ArrayList()
{
	listInitSize = 2 ;
	listMaxSize = listInitSize ;
	list = new int[listMaxSize] ;
	length = 0 ;
}

void ArrayList::insertItem(int newitem)
{
	int * tempList ;
	if (length == listMaxSize)
	{
		//allocate new memory space for tempList
		listMaxSize = 2 * listMaxSize ;
		tempList = new int[listMaxSize] ;
		int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ; //copy all items from list to tempList
        }
        delete[] list ; //free the memory allocated before
        list = tempList ; //make list to point to new memory
	};

	list[length] = newitem ; //store new item
	length++ ;
}

int ArrayList::searchItem(int item)
{
	int i = 0;
	for (i = 0; i < length; i++)
	{
		if( list[i] == item ) return i;
	}
	return NULL_VALUE;
}

void ArrayList::removeItemAt(int position) //do not preserve order of items
{
	if ( position < 0 || position >= length ) return ; //nothing to remove
	list[position] = list[length-1] ;
	length-- ;
}


void ArrayList::removeItem(int item)
{
	int position;
	position = searchItem(item) ;
	if ( position == NULL_VALUE ) return ; //nothing to remove
	removeItemAt(position) ;
}


int ArrayList::getItem(int position)
{
	if(position < 0 || position >= length) return NULL_VALUE ;
	return list[position] ;
}

int ArrayList::getLength()
{
	return length ;
}

bool ArrayList::empty()
{
    if(length==0)return true;
    else return false;
}

void ArrayList::printList()
{
    int i;
    for(i=0;i<length;i++)
        printf("%d ", list[i]);
    printf("Current size: %d, current length: %d\n", listMaxSize, length);
}

ArrayList::~ArrayList()
{
    if(list) delete [] list;
    list = 0 ;
}

//******************ArrayList class ends here*************************

//******************Graph class starts here**************************
class Graph
{
	int nVertices, nEdges ;
	bool directed ;
	ArrayList  * adjList ;
    int *color,*parent,*dist;
    int *visited;
	//define other variables required for bfs such as color, parent, and dist
	//you must use pointers and dynamic allocation

public:
	Graph(bool dir = false);
	~Graph();
	void setnVertices(int n);
	void addEdge(int u, int v);
	void removeEdge(int u, int v);
	bool isEdge(int u, int v);
    int getDegree(int u);
    void printAdjVertices(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
	void bfs(int source); //will run bfs in the graph
	void dfs(int source); //will run dfs in the graph
	void findComponents();
};


Graph::Graph(bool dir)
{
	nVertices = 0 ;
	nEdges = 0 ;
	adjList = 0 ;
	parent=0;
	color=0;
	dist=0;
	visited=0;
	directed = dir ; //set direction of the graph
	//define other variables to be initialized
}

void Graph::setnVertices(int n)
{
	this->nVertices = n ;
	if(adjList!=0) delete[] adjList ; //delete previous list
	if(parent!=0)delete[] parent;
	if(color!=0)delete[]color;
	if(dist!=0)delete[]dist;
	if(visited!=0)delete[]visited;
	adjList = new ArrayList[nVertices] ;
	parent=new int[nVertices];
	color=new int[nVertices];
	dist=new int[nVertices];
	visited=new int[nVertices];
}

void Graph::addEdge(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return; //vertex out of range
    this->nEdges++ ;
	adjList[u].insertItem(v) ;
	if(!directed) adjList[v].insertItem(u) ;
}

void Graph::removeEdge(int u, int v)
{
    //write this function
    if(u<0 || u>=nVertices || v<0 || v>=nVertices||this->nEdges==0) return;
    adjList[u].removeItem(v);
    if(!directed){
        adjList[v].removeItem(u);
    }
    this->nEdges--;
}

bool Graph::isEdge(int u, int v)
{
    //returns true if (u,v) is an edge, otherwise should return false
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return 0;
    if(adjList[u].searchItem(v)!=NULL_VALUE)return true;
    return false;
}

int Graph::getDegree(int u)
{
    //returns the degree of vertex u
    if(u<0 || u>=nVertices) return 0;
    int deg=adjList[u].getLength();
    /*if(directed){
        for(int i=0;i<nVertices;i++){
            if(i==u)continue;
            if(adjList[i].searchItem(u)!=NULL_VALUE)deg++;
        }*/
   // }

    return deg;
}

void Graph::printAdjVertices(int u)
{
    //prints all adjacent vertices of a vertex u
    if(u<0 || u>=nVertices) return;
    printf("Adjacent Nodes of %d:",u);
    for(int i=0;i<adjList[u].getLength();i++){
        printf(" %d",adjList[u].getItem(i));
    }
    printf("\n");
}

bool Graph::hasCommonAdjacent(int u, int v)
{
    //returns true if vertices u and v have common adjacent vertices
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return 0;
    for(int i=0;i<adjList[u].getLength();i++){
        int vertice=adjList[u].getItem(i);
        if(adjList[v].searchItem(vertice)!=NULL_VALUE)return true;
    }
    return false;
}


/*
void Graph::bfs(int source)
{
    //complete this function
    //initialize BFS variables
    if(source<0 || source>=nVertices) return;
    for(int i=0; i<nVertices; i++)
    {
        color[i] = WHITE ;
        parent[i] = -1 ;
        dist[i] = refINFINITY ;
    }
    Queue q ;
    color[source] = GREY;
    dist[source] = 0 ;
    q.enqueue(source) ;

    while( !q.empty() )
    {
        //complete this part
        int u=q.dequeue();

        for(int i=0;i<adjList[u].getLength();i++){
            int v=adjList[u].getItem(i);
            if(color[v]==WHITE){
                dist[v]=1+dist[u];
                parent[v]=u;
                color[v]=GREY;
                q.enqueue(v);
            }
        }
        color[u]=BLACK;
    }
}*/

int Graph::getDist(int u, int v)
{
    //returns the shortest path distance from u to v
    //must call bfs using u as the source vertex, then use distance array to find the distance
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return refINFINITY;
    for(int i=0;i<nVertices;i++)visited[i]=0;


    bfs(u);
    if(dist[v]!=refINFINITY)return dist[v];
    return refINFINITY ;
}

void Graph::printGraph()
{
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0;i<nVertices;i++)
    {
        printf("%d:", i);
        for(int j=0; j<adjList[i].getLength();j++)
        {
            printf(" %d", adjList[i].getItem(j));
        }
        printf("\n");
    }
}

Graph::~Graph()///NEED SOME CHECKING :/
{
    //write your destructor here
    delete[] parent;
    delete[] color;
    delete[] dist;
    delete[]visited;
    parent=0;color=0;dist=0;
    delete[] adjList;
    adjList=0;
}
//**********************Graph class ends here******************************




/***************************ONLINE**************************************/
//Need to comment out original BFS assignment before using it, it is choice number 10 in the list



void Graph::bfs(int source)
{
    //complete this function
    //initialize BFS variables

    if(visited[source])return;
    if(source<0 || source>=nVertices) return;
    for(int i=0; i<nVertices; i++)
    {
        color[i] = WHITE ;
        parent[i] = -1 ;
        dist[i] = refINFINITY ;
    }

    Queue q ;
    color[source] = GREY;
    dist[source] = 0 ;
    visited[source]=1;
    q.enqueue(source) ;

    while( !q.empty() )
    {
        //complete this part
        int u=q.dequeue();

        for(int i=0;i<adjList[u].getLength();i++){
            int v=adjList[u].getItem(i);
            if(color[v]==WHITE&&!visited[v]){
                dist[v]=1+dist[u];
                parent[v]=u;
                color[v]=GREY;
                visited[v]=1;
                q.enqueue(v);
            }
        }
        color[u]=BLACK;
    }
}


void Graph::findComponents()
{
    for(int i=0;i<nVertices;i++){
        visited[i]=0;
    }

    int cnt=0;

    for(int i=0;i<nVertices;i++){
        if(!visited[i])bfs(i),cnt++;
    }
    cout<<"Number Of Components "<<cnt<<endl;
}

/***************************************************************************************/






//******main function to test your code*************************
int main(void)
{
    int n;int kase=0;
    Graph g;
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    g.setnVertices(n);


    while(1)
    {
        if(kase++)printf("\n");
        printf("1. Add edge. 2.Delete edge 3. getDegree 4. printAdjacent Vertices\n");
        printf("5. Print Graph  6.hasCommonAdjacent 7.bfs with source 8.getDist of two nodes 9.is Edge 10.findComponents 11.break\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            g.addEdge(u, v);
        }
        else if(ch==2)
        {
            int u,v;
            cin>>u>>v;
            g.removeEdge(u,v);
        }
        else if(ch==3)
        {
            int u;
            cin>>u;
            cout<<g.getDegree(u)<<endl;
        }
        else if(ch==4){
            int u;
            cin>>u;
            g.printAdjVertices(u);
        }
        else if(ch==5)
        {
            g.printGraph();
        }
        else if(ch==6)
        {
            int u,v;
            cin>>u>>v;
            if(g.hasCommonAdjacent(u,v))cout<<"YES"<<endl;
            else cout<<"NO"<<endl;
        }
        else if(ch==7){
            int src;
            cin>>src;
            g.bfs(src);
        }

        else if(ch==8){
            int u,v;
            cin>>u>>v;
            int dist=g.getDist(u,v);
            if(dist!=refINFINITY)cout<<dist<<endl;
            else cout<<"NO PATH FROM "<<u<<" TO "<<v<<endl;
        }
        else if(ch==9){
            int u,v;
            cin>>u>>v;
            cout<<g.isEdge(u,v)<<endl;
        }
        else if(ch==10){
            g.findComponents();
        }
        else if(ch==11){
            break;
        }
    }
}
