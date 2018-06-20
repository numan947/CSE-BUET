#include <bits/stdc++.h>
#include "bitmap_image.hpp"
using namespace std;


#define pb push_back
#define pf push_front
#define mp make_pair
#define fi first
#define se second
#define pi (2*acos(0.0))

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


	Triangle(vector<string>vs)
	{
		if(vs.size()>3){
			printf("Error in --> TRIANGLE:init, too many vertices\n");
		}
		else{
			for(int i=0;i<3;i++)
				point[i]=tokenizeAndAdd(vs[i]);
		}

	}
	void setColor(unsigned char r,unsigned char g, unsigned char b)
	{
		color[0]=r;color[1]=g;color[2]=b;
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

	~Triangle()
	{
		for(int i=0;i<3;i++){
			delete point[i];
			delete line[i];
		}
	}
};

class EdgeBucket{
public:
	double yMax,yMin,x,sign,dX,dY,sum;
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


EdgeBucket** edgeTable;



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
	while(getline(if2,tmp)){
		if(tmp.size()>=5){
			getline(if2,v2);
			getline(if2,v3);
			vs.clear();
			vs.pb(tmp);vs.pb(v2);vs.pb(v3);
			triangles.pb(new Triangle(vs));
		}
	}


	//validate

/*	cout<<Screen_Width<<" X "<<Screen_Height<<endl;
	cout<<x_left_limit<<" "<<y_bottom_limit<<" "<<z_front_limit<<" "<<z_rear_limit<<endl;

	for(int i=0;i<triangles.size();i++)
		triangles[i]->printTriangle();*/
}


void initialize_edge_table_and_polygon_table()
{

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
	
	//free image memeory
	delete image;
}


int main()
{

	read_data();

	//save();
	free_memory();

	return 0;
}