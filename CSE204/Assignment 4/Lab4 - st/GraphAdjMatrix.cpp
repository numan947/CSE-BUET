#include<stdio.h>
#include<stdlib.h>
#include<bits/stdc++.h>
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


//******************Graph class starts here**************************
class Graph
{
	int nVertices, nEdges ;
	bool directed ;
	int ** matrix ; //adjacency matrix to store the graph
    int *color,*parent,*dist;//define other variables required for bfs such as color, parent, and dist
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
};


Graph::Graph(bool dir)
{
	nVertices = 0 ;
	nEdges = 0 ;
	matrix = 0 ;
	parent=0;
	color=0;
	dist=0;
	directed = dir ; //set direction of the graph
	//define other variables to be initialized
}

void Graph::setnVertices(int n)
{
	this->nVertices = n ;

	//allocate space for the matrix
    matrix = new int*[nVertices];
    for(int i=0;i<nVertices;i++)
    {
        matrix[i] = new int[nVertices];
        for(int j=0;j<nVertices;j++)
            matrix[i][j] = 0; //initialize the matrix cells to 0
    }
	if(parent!=0)delete[] parent;
	if(color!=0)delete[]color;
	if(dist!=0)delete[]dist;
	parent=new int[nVertices];
	color=new int[nVertices];
	dist=new int[nVertices];
}

void Graph::addEdge(int u, int v)
{
    //write your code here
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return;
    this->nEdges++;
    matrix[u][v] = 1;
    if(!directed) matrix[v][u] = 1;

}

void Graph::removeEdge(int u, int v)
{
    //write this function
    if(u<0 || u>=nVertices || v<0 || v>=nVertices||this->nEdges==0) return;
    matrix[u][v]=0;
    if(!directed)matrix[v][u]=0;
    this->nEdges--;
}

bool Graph::isEdge(int u, int v)
{
    //returns true if (u,v) is an edge, otherwise should return false
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return 0;
    return matrix[u][v];
}

int Graph::getDegree(int u)
{
    //returns the degree of vertex u
    if(u<0 || u>=nVertices) return 0;
    int cnt=0;
    for(int i=0;i<nVertices;i++){
        if(matrix[u][i])cnt++;
        /*if(directed){
            if(matrix[i][u])cnt++;
        }*/
    }
    return cnt;
}

void Graph::printAdjVertices(int u)
{
    //prints all adjacent vertices of a vertex u
    if(u<0 || u>=nVertices) return;
    printf("adjacent vertices of %2d:",u);
    for(int i=0;i<nVertices;i++){
        if(matrix[u][i])printf(" %d",i);
    }
}

bool Graph::hasCommonAdjacent(int u, int v)
{
    //returns true if vertices u and v have common adjacent vertices
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return 0;
    for(int i=0;i<nVertices;i++){
        if(matrix[u][i]&&matrix[v][i])return true;
    }
    return false;

}


void Graph::bfs(int source)
{

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
        for(int i=0;i<nVertices;i++){
            if(matrix[u][i]&&color[i]==WHITE){
                int v=i;
                dist[v]=1+dist[u];
                color[i]=GREY;
                parent[i]=u;
                q.enqueue(i);
            }
        }
        color[u]=BLACK;
    }
}


int Graph::getDist(int u, int v)
{
    //returns the shortest path distance from u to v
    //must call bfs using u as the source vertex, then use distance array to find the distance
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return refINFINITY;
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
        for(int j=0; j<nVertices;j++)
        {
            if(matrix[i][j]==1)
                printf(" %d", j);
        }
        printf("\n");
    }
}

Graph::~Graph()
{
    //write your destructor here
    for(int i=0;i<nVertices;i++)delete[]matrix[i];
    delete[]matrix;
    delete[]parent;
    delete[]dist;
    delete[]color;
    matrix=0;
    parent=dist=color=0;
}


//**********************Graph class ends here******************************


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
        printf("5. Print Graph  6.hasCommonAdjacent 7.bfs with source 8.getDist of two nodes 9.is Edge 10.break\n");

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
            break;
        }
    }
}
