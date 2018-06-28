#include <bits/stdc++.h>
#include "bitmap_image.hpp"
using namespace std;


#define pb push_back
#define pf push_front
#define mp make_pair
#define fi first
#define se second
#define pi (2*acos(0.0))
#define ms(s, n) memset(s, n, sizeof(s))
const int INF = (int) 1e9;
const double eps = 1e-9;


inline void tokenize(string str,vector<string> &tokens, string delim){ tokens.clear();size_t s = str.find_first_not_of(delim), e=s; while(s!=std::string::npos){e=str.find(delim,s);tokens.push_back(str.substr(s,e-s));s=str.find_first_not_of(delim,e);}}
inline string strip(string s){int i=0;while(i<s.size()){if(isspace(s[i]))i++;else break;}s.erase(0,i);i = s.size()-1;while(i>=0){if(isspace(s[i]))i--;else break;}s.erase(i+1,s.size()-i-1);return s;}
void testFunctionality();
void realMain();
vector<string>tokens;


//utility functions
/************************************/
double stringToDouble(string s)
{	
	double f;
	stringstream ss(s);
	ss>>f;
	return f;
}

string doubleToString(double dd)
{
	ostringstream ostr;
	ostr.precision(6);
	ostr<<fixed;
	ostr<<dd;
	return ostr.str();
}


int myRand()
{int max = 255;int min =1;int randNum = (rand()*rand()) % (max - min + 1) + min;return randNum;}

int myRound(double dd)
{
	if(dd-(int)dd>0.5)return (int)dd + 1;
	else return (int)dd;
}

double close_enough(double a, double b)
{
	return fabs(a-b)<=eps;
}

/************************************/


class Point{
public:
	double x,y,z;

	Point()
	{
		this->x = INF;
		this->y = INF;
		this->z = INF;
	}

	Point(double xx, double yy, double zz)
	{
		this->x=xx;
		this->y=yy;
		this->z=zz;
	}

	void printPoint()
	{
		printf("%lf %lf %lf\n",this->x,this->y,this->z);
	}

	void printPoint2D()
	{
		printf("%lf %lf \n",this->x,this->y);
	}

	bool isValid2D()
	{
		return x!=INF && y!=INF;
	}
	void clear()
	{
		this->x = INF;
		this->y = INF;
		this->z = INF;
	}

	static void swap(Point &p1, Point &p2){
		std::swap(p1.x,p2.x);
		std::swap(p1.y,p2.y);
		std::swap(p1.z,p2.z);
	}
	static bool isSame(Point &p1, Point &p2){
		return fabs(p1.x-p2.x)<eps && fabs(p1.y-p2.y)<eps && fabs(p1.z-p2.z)<eps;
	}

};

class Vect
{
public:
	double x,y,z;

	Vect(Point p1,Point p2)
	{
		this->x = p2.x - p1.x;
		this->y = p2.y - p1.y;
		this->z = p2.z - p1.z;
	}

	Vect(double x, double y, double z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

};

Vect crossProduct(Vect a,Vect b)
{
	Vect tmp(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);
 	return tmp;
}





class Triangle{
private:
	unsigned char color[3];

	Point* tokenizeAndAdd(string in){

		tokens.clear();
		tokenize(in,tokens," ");
		
		Point *p = new Point(
				stringToDouble(tokens[0]),
				stringToDouble(tokens[1]),
				stringToDouble(tokens[2])
				);
		return p;
	}
public:
	Point *point[3];
	bool inOutFlag;
	double p_a,p_b,p_c,p_d;
	int id;



	Triangle(vector<string>vs,int id)
	{
		if(vs.size()>3){
			printf("Error in --> TRIANGLE:init, too many vertices\n");
		}
		else{
			for(int i=0;i<3;i++)
				point[i]=tokenizeAndAdd(vs[i]);
			

			Vect *A = new Vect(*point[0],*point[1]);
			Vect *B = new Vect(*point[0],*point[2]);

			Vect planeVector = crossProduct(*A,*B);

			this->p_a = planeVector.x;
			this->p_b = planeVector.y;
			this->p_c = planeVector.z;
			this->p_d = (-p_a*(point[0]->x))+(-p_b*point[0]->y)+(-p_c*point[0]->z);
			this->inOutFlag = false;
			this->id = id;
		}

	}
	void setColor(unsigned char r,unsigned char g, unsigned char b)
	{
		color[0]=r;color[1]=g;color[2]=b;
	}

	double getZValue(double x, double y)
	{
		//cout<<p_a <<" "<<p_b<<" "<<p_c<<" "<<p_d<<endl;
		return (-1.0*p_d - 1.0*p_a*x - 1.0*p_b*y)/p_c;
	}

	unsigned char getR()
	{
		return color[0];
	}
	unsigned char getG()
	{
		return color[1];
	}
	unsigned char getB()
	{
		return color[2];
	}

	void printTriangle()
	{
		for(int i=0;i<3;i++)
			point[i]->printPoint();
		printf("\n");
	}

	void printPolygon()
	{
		printf("%d|%lfX+%lfY+%lfZ+%lf|(%d,%d,%d)|%d",id,p_a,p_b,p_c,p_d,color[0],color[1],color[2],inOutFlag);

	}

	~Triangle()
	{
		for(int i=0;i<3;i++){
			delete point[i];
			
		}
	}
};



class EdgeBucket{
public:
	double x,dX,zAtx;
	int id,tableIdx,yMax;


	EdgeBucket(int tableIdx,int yMax,double x, double dX,double zAtx, int id)
	{
		this->tableIdx = tableIdx;
		this->yMax = yMax;
		this->x = x;
		this->dX = dX;
		this->id = id;
		this->zAtx = zAtx;
	}

    void printEdgeBucket()
    {
    	cout<<"tableIdx: "<<tableIdx<<endl;
    	cout<<"id: "<<id<<endl;
    	cout<<"yMax: "<<yMax<<endl;
    	cout<<"x(at yMin): "<<x<<endl;
    	cout<<"dX: "<<dX<<endl;
    }

    void printEdgeBucket2()
    {
    	cout<<"tableIdx: "<<tableIdx<<" yMax: "<<yMax<<"| x: "<<x<<"|dX: "<<dX<<"|"<<id;
    }
};



bool comparePtrToNode(EdgeBucket* a, EdgeBucket* b) 
{ 
	//printf("Hello %d\n",(fabs(a->x - b->x)<=eps || a->x < b->x));
	if(fabs(a->x - b->x)<=eps){
		if(fabs(a->zAtx - b->zAtx)<=eps){
			return a->id<b->id;
		}
		return a->zAtx < b->zAtx;
	}

	return (a->x < b->x); 
}


class EdgeTableEntry{
public:
	vector<EdgeBucket*>edgeBucketList;

	EdgeTableEntry(){

	}

	void addEdgeBucket(EdgeBucket* edgeBucket)
	{
		edgeBucketList.pb(edgeBucket);
	}

	void sortEdgeBucketList()
	{
		//printf("WHY WHY %d\n",edgeBucketList.size());
		// for(int i=0;i<edgeBucketList.size();i++){
		// 	edgeBucketList[i]->printEdgeBucket2();
		// 	cout<<endl;
		// }
		sort(edgeBucketList.begin(),edgeBucketList.end(),comparePtrToNode);
	}

	void printEdgeTableEntry()
	{
		if(edgeBucketList.size()){
			cout<<"|";
			edgeBucketList[0]->printEdgeBucket2();
			cout<<"|--->";
			for(int i=1;i<edgeBucketList.size();i++)
			{
				cout<<"|";
				edgeBucketList[i]->printEdgeBucket2();
				cout<<"|--->";
			}
			cout<<"END"<<endl;
		}
	}

	bool isEmpty()
	{
		return edgeBucketList.size()==0;
	}

	~EdgeTableEntry(){
		for(vector<EdgeBucket*>::iterator it = edgeBucketList.begin();it!=edgeBucketList.end();it++)
			delete *it;
		edgeBucketList.clear();
	}


};

double Screen_Width,
	   Screen_Height,
	   x_left_limit,
	   x_right_limit,
	   y_bottom_limit,
	   y_top_limit,
	   z_front_limit,
	   z_rear_limit,
	   Bottom_Y,
	   Left_X,
	   dx,
	   dy;

bitmap_image *image;

vector<Triangle*>triangles;


EdgeTableEntry *edgeTable;

int totalPolygons;
bool*activePolygonList;

vector<EdgeBucket*>activeEdgeList;


map<int,Triangle*>idToTriangle;

map<int,pair<int,int> >polygonEdge;


void read_data()
{
	ifstream if1("config.txt");
	ifstream if2("stage3.txt");

	string tmp;


	//parsing config.txt
	//1st line
	getline(if1,tmp);
	tokens.clear();
	tokenize(tmp,tokens," ");
	Screen_Width = stringToDouble(tokens[0]);
	Screen_Height = stringToDouble(tokens[1]);

	//2nd line
	getline(if1,tmp);
	x_left_limit = stringToDouble(tmp);
	x_right_limit = -x_left_limit;

	//3rd line
	getline(if1,tmp);
	y_bottom_limit = stringToDouble(tmp);
	y_top_limit = -y_bottom_limit;

	//4th line
	getline(if1,tmp);
	tokens.clear();
	tokenize(tmp,tokens," ");
	z_front_limit = stringToDouble(tokens[0]);
	z_rear_limit = stringToDouble(tokens[1]);


	string v2;
	string v3;
	vector<string>vs;
	//parsing stage3.txt
	int ids = 0;
	while(getline(if2,tmp)){
		if(tmp.size()>=5){
			getline(if2,v2);
			getline(if2,v3);
			vs.clear();
			vs.pb(tmp);vs.pb(v2);vs.pb(v3);
			Triangle* tt =new Triangle(vs,ids);
			idToTriangle[ids]=tt;
			triangles.pb(tt);
			ids++;
		}
	}

	totalPolygons = ids;
	


	//validate

/*	cout<<Screen_Width<<" X "<<Screen_Height<<endl;
	cout<<x_left_limit<<" "<<y_bottom_limit<<" "<<z_front_limit<<" "<<z_rear_limit<<endl;

	for(int i=0;i<triangles.size();i++)
		triangles[i]->printTriangle();*/
}

int getRowNumber(double ss)
{
	int tp = myRound((ss-Bottom_Y)/dy);
	if(tp<0)tp = 0;
	else if(tp>=Screen_Height)tp = Screen_Height - 1;
	return tp;
}

double getRowValue(int row)
{
	return Bottom_Y + row*dy*1.0;
}
int getColNumber(double ss)
{
	//cout<<"WTF  "<<round((ss-Left_X)/dx)<<endl; 
	int tp = myRound((1.0*ss-1.0*Left_X)/dx);
	if(tp<0)tp = 0;
	else if(tp>=Screen_Width)tp = Screen_Width - 1;
	return tp;
}
double getColValue(int col)
{
	return Left_X + col*1.0*dx;
}

double getRightClippingLine(double maxX)
{
	double ss = maxX;
	if(ss>x_right_limit)ss = x_right_limit;
	return ss;
}
double getLeftClippingLine(double minX)
{
	double ss = minX;
	if(ss<x_left_limit)ss = x_left_limit;
	return ss;
}



EdgeBucket* makeEdgeBucket(Point p1, Point p2,int id)
{
	EdgeBucket* ret;

	// p1.printPoint();
	// p2.printPoint();

	double dX = p1.x - p2.x;
	double dY = p1.y - p2.y;

	// if(dX*dY<0)dX = -1.0 * fabs(dX);
	// else dX = fabs(dX);

	double mX ;
	if(close_enough(dX,0))mX=0;
	else mX = dY/dX;

	if(fabs(p1.y - p2.y)<=eps || p1.y < p2.y){ //p1 has minY, p2 has maxY
		int tdx = getRowNumber(p1.y);
		ret = new EdgeBucket(tdx,getRowNumber(p2.y),p1.x,mX,p1.z,id);
	}
	else{
		int tdx = getRowNumber(p2.y);
		ret = new EdgeBucket(tdx,getRowNumber(p1.y),p2.x,mX,p2.z,id);
	}

	return ret;
}

void initialize_edge_table_and_polygon_table()
{
	printf("***************************************************************\n");
	//dx, dy
	dx = (x_right_limit - x_left_limit)/Screen_Width;
	dy = (y_top_limit - y_bottom_limit)/Screen_Height;

	//bottom, left
	Bottom_Y = y_bottom_limit+(dy/2.0);
	Left_X = x_left_limit+(dx/2.0);

	printf("Bottom_Y %lf Left_X %lf\n",Bottom_Y,Left_X);
	printf("dx %lf dy %lf\n",dx,dy);


	edgeTable = new EdgeTableEntry[myRound(Screen_Height)];

	Triangle* cur;

	for(int i=0;i<triangles.size();i++)
	{
		cur = triangles[i];
		cur->setColor(myRand(),myRand(),myRand());

		EdgeBucket* e1 = makeEdgeBucket(*(cur->point[0]),*(cur->point[1]),cur->id);
		EdgeBucket* e2 = makeEdgeBucket(*(cur->point[0]),*(cur->point[2]),cur->id);
		EdgeBucket* e3 = makeEdgeBucket(*(cur->point[1]),*(cur->point[2]),cur->id);

		
		if(e1->yMax!=e1->tableIdx){
			edgeTable[e1->tableIdx].addEdgeBucket(e1);
			polygonEdge[cur->id]=make_pair(e1->tableIdx,edgeTable[e1->tableIdx].edgeBucketList.size()-1);
		}
		
		if(e2->yMax!=e2->tableIdx){
			edgeTable[e2->tableIdx].addEdgeBucket(e2);
			polygonEdge[cur->id]=make_pair(e2->tableIdx,edgeTable[e2->tableIdx].edgeBucketList.size()-1);
		}
		
		if(e3->yMax!=e3->tableIdx){
			edgeTable[e3->tableIdx].addEdgeBucket(e3);
			polygonEdge[cur->id]=make_pair(e3->tableIdx,edgeTable[e3->tableIdx].edgeBucketList.size()-1);
		}

/*		e1->printEdgeBucket();

		cout<<endl;

		e2->printEdgeBucket();

		cout<<endl;

		e3->printEdgeBucket();
		cout<<endl;*/


	}

	printf("EDGE TABLE\n\n");
	for(int i=0;i<Screen_Height;i++)
	{
		if(!edgeTable[i].isEmpty()){
			edgeTable[i].sortEdgeBucketList();
			cout<<i<<"--->";
			edgeTable[i].printEdgeTableEntry();
		}
	}

	printf("\n\n");

	printf("POLYGON TABLE\n\n");

	for(int i=0;i<triangles.size();i++)
	{
		triangles[i]->printPolygon();
		cout<<endl;
	}


	image = new bitmap_image(Screen_Width,Screen_Height);
    for(int i=0;i<Screen_Width;i++){
        for(int j=0;j<Screen_Height;j++){
            image->set_pixel(i,j,0,0,0);
        }
    }



	//initialize activePolygonList
	activePolygonList = new bool[totalPolygons];


	printf("\n\n***************************************************************\n\n\n");
}


void printActiveEdgeList()
{
	for(int i=0;i<activeEdgeList.size();i++){
		activeEdgeList[i]->printEdgeBucket2();
		cout<<endl;
	}
}

void printActivePolygonList()
{
	for(int i=0;i<totalPolygons;i++)
		cout<<activePolygonList[i]<<" ";
	cout<<endl;
}




void updateActivePolygonList(int polyId)
{
	//printf("----%d-----\n",polyId);
	//printf("%d----->",activePolygonList[polyId] );
	activePolygonList[polyId]=!activePolygonList[polyId];
	//printf("%d\n",activePolygonList[polyId]);
	//printf("----%d-----\n",polyId);

/*	for(int i=0;i<activeEdgeList.size();i++){
		if(close_enough(activeEdgeList[i]->x,dd)){
			int polyId = activeEdgeList[i]->id;
			activePolygonList[polyId]=!activePolygonList[polyId];
		}
		else break;
	}*/


}

int getPolygonIdOfSmallestZ(double x, double y)
{
	int id = -1;
	double zmn = (double)INF;
	
	//cout<<getRowNumber(y)<<endl;

	for(int i=0;i<totalPolygons;i++){
		if(!activePolygonList[i])continue;
		double zz = idToTriangle[i]->getZValue(x,y);

		// idToTriangle[i]->printPolygon();
		// cout<<endl;
		// cout<<x<<" "<<y<<" "<<zz<<" "<<zmn<<endl;

		if(zz>=z_front_limit && zz<=z_rear_limit && zz<zmn){
			zmn = zz;
			id = i;
			//printf("zmn --> %lf -->%d\n",zmn,id);
		}
	

	}

	//cout<<"returning...."<<id<<endl;

	//printf("FINAL::::zmn --> %lf -->%d\n",zmn,id);
	
	if(getRowNumber(y)==107||getRowNumber(y)==108){
		sort(activeEdgeList.begin(),activeEdgeList.end(),comparePtrToNode);
		cout<<getRowNumber(y)<<"--> "<<activeEdgeList.size()<<endl;
		printActiveEdgeList();
		cout<<endl;
		printActivePolygonList();
		
		// for(int i=0;i<totalPolygons;i++){
		// 	if(!activePolygonList[i])continue;
		// 	double zz = idToTriangle[i]->getZValue(x,y);
		// 	printf("%d --> %lf %lf : %lf\n",i,x,y,zz);
		// }
		cout<<endl;

	}
/*	if(id==-1){
		cout<<"returning...."<<id<<" "<<x<<" "<<y<<endl;
		for(int i=0;i<totalPolygons;i++){
			if(!activePolygonList[i])continue;
			double zz = idToTriangle[i]->getZValue(x,y);
			printf("%d --> %lf %lf : %lf\n",i,x,y,zz);
		}
	}*/


	return id;
}

void updateActiveEdgeList(int y)
{	

	vector<int>toRemove;
	toRemove.clear();
	int sz = activeEdgeList.size();
	
	vector<EdgeBucket*>tmp;

	for(int i=0;i<sz;i++){
		if((activeEdgeList[i]->yMax)>(y+1))
			tmp.pb(activeEdgeList[i]);
	}

	activeEdgeList.clear();

	for(int i=0;i<tmp.size();i++)
		activeEdgeList.pb(tmp[i]);
	

	sz = activeEdgeList.size();
	for(int i=0;i<sz;i++){
		if(!close_enough(activeEdgeList[i]->dX,0))
			activeEdgeList[i]->x+=(dy/activeEdgeList[i]->dX);
	}

	tmp.clear();

	if(activeEdgeList.size()%2){
		//cout<<"ASDF  "<<y<<endl;
	}

	for(int i=0;i<activeEdgeList.size();i++){
		for(int j=i+1;j<activeEdgeList.size();j++){
			if(activeEdgeList[i]->id == activeEdgeList[j]->id){

			}
		}
	}
}

void apply_procedure()
{

	activeEdgeList.clear();

	for(int y=0;y<Screen_Height;y++){
		bool bb = false;
		//if(edgeTable[y].isEmpty())continue;
		if(!edgeTable[y].isEmpty()){
			int sz = edgeTable[y].edgeBucketList.size();
			for(int i=0;i<sz;i++)
				activeEdgeList.pb(edgeTable[y].edgeBucketList[i]);
		}


		sort(activeEdgeList.begin(),activeEdgeList.end(),comparePtrToNode);

		int sz = activeEdgeList.size();

		//if(sz)cout<<y<<"  "<<sz<<endl;

		// if(y==249){
		// 	for(int i=0;i<activeEdgeList.size();i++){
		// 		activeEdgeList[i]->printEdgeBucket2();
		// 		cout<<endl;
		// 	}
		// 	break;
		// }

		memset(activePolygonList,0,totalPolygons*sizeof(bool));

		//printActivePolygonList();

		for(int i=0;i<(sz-1);i++){
			//printActiveEdgeList();
			int polyId = activeEdgeList[i]->id;
			//idToTriangle[polyId]->inOutFlag = !(idToTriangle[polyId]->inOutFlag);
			updateActivePolygonList(polyId);

			//cout<<polyId<<endl;
			

/*			double clipped = getLeftClippingLine(activeEdgeList[i]->x);
			clipped = getRightClippingLine(clipped);

			
			int cc = getColNumber(clipped);

			cout<<cc<<endl;
			clipped = getColValue(cc);
			cout<<clipped<<" is clipped"<<endl;
			cout<<getRowValue(y)<<endl;*/

			polyId = getPolygonIdOfSmallestZ(activeEdgeList[i]->x,getRowValue(y));
	
			// if(y==292){
			// 	cout<<sz<<endl;
			// 	printActiveEdgeList();
			// 	cout<<polyId<<endl;
			// 	activeEdgeList[i]->printEdgeBucket2();
			// 	cout<<endl;
			// }			
			//cout<<polyId<<" "<<activeEdgeList[i]->x<<" "<<getRowValue(y)<<endl;

			if(polyId==-1)
				continue;
			


			int r = idToTriangle[polyId]->getR(),g = idToTriangle[polyId]->getG(),b = idToTriangle[polyId]->getB();

			int left = getColNumber(getLeftClippingLine(activeEdgeList[i]->x)),right = getColNumber(getRightClippingLine(activeEdgeList[i+1]->x));

			//if(y!=108 && y!=107)
			for(int j=left;j<=right;j++)
				image->set_pixel(j,Screen_Height-y,r,g,b);

			//if(y==45)break;
		}
		//if(bb)break;
		
		//if(y==45)break;

		updateActiveEdgeList(y);
		
		//printActiveEdgeList();
		

	}


}


void save()
{
	image->save_image("2.bmp");


	// ofstream ofs;
	// ofs.open("z_buffer.txt");

	// for(int r=0;r<Screen_Height;r++){
	// 	for(int c=0;c<Screen_Width;c++){
	// 		if(z_buffer[r][c]<z_rear_limit)
	// 			ofs<<doubleToString(z_buffer[r][c])<<"\t";
	// 	}
	// 	ofs<<"\n";
	// }
	// ofs.close();

}

void free_memory()
{
	//free objects memory
	for(vector<Triangle*>::iterator it = triangles.begin();it!=triangles.end();it++)
		delete *it;
	triangles.clear();

	idToTriangle.clear();
	
	delete activePolygonList;
	
	//free image memeory
	delete image;
}


int main()
{
	srand(time(NULL));
	freopen("debug.txt", "w", stdout);
	read_data();
	initialize_edge_table_and_polygon_table();
	apply_procedure();
	save();
	free_memory();

	return 0;
}