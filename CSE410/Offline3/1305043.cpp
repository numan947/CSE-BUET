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

/************************************/


class Point{
public:
	double x,y,z;

	Point()
	{

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

	static void swap(Point &p1, Point &p2){
		std::swap(p1.x,p2.x);
		std::swap(p1.y,p2.y);
		std::swap(p1.z,p2.z);
	}
};




class Line2D{
public:
	double a,b,c; //ax+by+c=0

	Line2D(double a, double b, double c)
	{
		this->a = a;
		this->b = b;
		this->c = c;
	}

	Line2D(Point a, Point b){
		if(fabs(a.x - b.x)<eps){ //vertical lines
			this->a = 1.0;
			this->b = 0;
			this->c = -a.x;
		}
		else{
			this->a = -(double)(a.y-b.y) / (a.x - b.x);
			this->b = 1.0;
			this->c = -(double)(this->a * a.x) - a.y;
		}
	}

	static bool areParallel(Line2D l1, Line2D l2)
	{
		return (fabs(l1.a-l2.a)<eps) && (fabs(l1.b-l2.b)<eps);
	}

	static bool areSame(Line2D l1, Line2D l2)
	{
		return Line2D::areParallel(l1,l2) && (fabs(l1.c-l2.c)<eps);
	}

	static bool areIntersect(Line2D l1, Line2D l2, Point &p){
		if(Line2D::areParallel(l1,l2))return false;
		
		double x = (l2.b*l1.c-l1.b*l2.c)/(l2.a*l1.b-l1.a*l2.b);

		double y;

		if(fabs(l1.b)>eps)y = -(l1.a*x + l1.c);
		else y = -(l2.a*x+l2.c);

		p.x = x;
		p.y = y;

		return true;
	}

	static bool insideLineSegment(Point p1, Point p2, Point p3) //p3 inside the line segement defined by p1, p2
	{
		return (min(p1.x,p2.x)<=p3.x)&&(p3.x<=max(p1.x,p2.x)) && (min(p1.y,p2.y)<=p3.y)&&(p3.y<=max(p1.y,p2.y));
	}

};



class Triangle{
private:
	Point *point[3];
	unsigned char color[3];

	Line2D *line[3];


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
	Triangle(vector<string>vs)
	{
		if(vs.size()>3){
			printf("Error in --> TRIANGLE:init, too many vertices\n");
		}
		else{
			for(int i=0;i<3;i++)
				point[i]=tokenizeAndAdd(vs[i]);


			for(int i=0;i<3;i++)
				line[i] = new Line2D(*point[i],*point[(i+1)%3]);
		}

	}


	void getScanLineIntersectPoints(double b,Point &p1, Point &p2){
		Line2D *tmp = new Line2D(0,1,-b);

		Point tp;

		bool xl=false,xr=false;


		if(Line2D::areIntersect(*tmp,*line[0],tp) && Line2D::insideLineSegment(*point[0],*point[1],tp)){
			xl = true;
			p1.x = tp.x;
			p1.y = tp.y;
			p1.z = tp.z;
		}
		else if(Line2D::areIntersect(*tmp,*line[1],tp) && Line2D::insideLineSegment(*point[1],*point[2],tp)){
			if(xl){
				xr=true;
				p2.x = tp.x;
				p2.y = tp.y;
				p2.z = tp.z;
			}
			else{
				xl=true;
				p1.x = tp.x;
				p1.y = tp.y;
				p1.z = tp.z;
			}
		}
		else if(Line2D::areIntersect(*tmp,*line[2],tp) && Line2D::insideLineSegment(*point[2],*point[0],tp)){
			p2.x = tp.x;
			p2.y = tp.y;
			p2.z = tp.z;
			xr = true;
			//this should only be executed if, xr = false
		}

		p1.printPoint2D();
		p2.printPoint2D();

		cout<<xl<<" "<<xr<<endl;


		if(p1.x>p2.x)
			Point::swap(p1,p2);
	}

	void setColor(int pointPos,unsigned char val)
	{
		if(pointPos<0||pointPos>=3){
			printf("Error in --> TRIANGLE:setColor, value out of bound\n");
			return;
		}
		color[pointPos]=val;
	}


	double getMinY()
	{
		double mm = INF;
		for(int i=0;i<3;i++)
			mm = min(mm,point[i]->y);
		return mm;
	}

	double getMaxY()
	{
		double mm = -INF;
		for(int i=0;i<3;i++)
			mm = max(mm,point[i]->y);
		return mm;
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


double Screen_Width,
	   Screen_Height,
	   x_left_limit,
	   x_right_limit,
	   y_bottom_limit,
	   y_top_limit,
	   z_front_limit,
	   z_rear_limit,
	   Top_Y,
	   Left_X,
	   dx,
	   dy;

double **z_buffer;

bitmap_image *image;

vector<Triangle*>triangles;


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



void initialize_z_buffer_and_frame_buffer()
{
	
	//dx, dy
	dx = (x_right_limit - x_left_limit)/Screen_Width;
	dy = (y_top_limit - y_bottom_limit)/Screen_Height;

	//top, left
	Top_Y = y_top_limit-(dy/2.0);
	Left_X = x_left_limit+(dx/2.0);

	//z_buffer
	z_buffer = new double*[(int)Screen_Height];
	for(int i=0;i<Screen_Height;i++){
		z_buffer[i] = new double[(int)Screen_Width];
		for(int j=0;j<Screen_Width;j++){
			z_buffer[i][j]=z_rear_limit;
			//printf("%lf ",z_buffer[i][j]);
		}
		//printf("\n");
	}

	//image
	image = new bitmap_image(Screen_Width,Screen_Height);
    for(int i=0;i<Screen_Width;i++){
        for(int j=0;j<Screen_Height;j++){
            image->set_pixel(i,j,0,0,0);
        }
    }

    //todo : REMOVE
    //image->save_image("test.bmp");
}






double getTopScanLine(double maxY)
{
	double ss = maxY;
	if(ss>y_top_limit)ss=y_top_limit;
	cout<<"Top scan line "<<ss<<endl;
	return ss;
}
int getBottomScanline(double minY)
{
	double ss = minY;
	if(ss<y_bottom_limit)ss=y_bottom_limit;
	cout<<"Bottom scan line "<<ss<<endl;
	return ss;
}
void apply_procedure()
{
	for(int i=0;i<triangles.size();i++)
	{
		Triangle* cur = triangles[i];

		double top_scan_line = getTopScanLine(cur->getMaxY());
		double bottom_scan_line = getBottomScanline(cur->getMinY());

		double pp = top_scan_line;
		while(pp>=bottom_scan_line){
			Point p1,p2;
			cur->getScanLineIntersectPoints(pp,p1,p2);
			//p1.printPoint2D();
			//p2.printPoint2D();
			pp-=dy;
		}
		cout<<endl;

		cout<<dx<<" "<<dy<<endl;





	}
}


void save()
{
	image->save_image("1.bmp");


	ofstream ofs;
	ofs.open("z_buffer.txt");

	for(int r=0;r<Screen_Height;r++){
		for(int c=0;c<Screen_Width;c++){
			if(z_buffer[r][c]<z_rear_limit)
				ofs<<doubleToString(z_buffer[r][c])<<"\t";
		}
		ofs<<"\n";
	}
	ofs.close();

}

void free_memory()
{
	//free objects memory
	for(vector<Triangle*>::iterator it = triangles.begin();it!=triangles.end();it++)
		delete *it;
	triangles.clear();
	
	//free image memeory
	delete image;

	//free z_buffer memory
	for(int i=0;i<Screen_Height;i++){
		delete[] z_buffer[i];
	}
	delete z_buffer;
}


int main()
{

	read_data();
	initialize_z_buffer_and_frame_buffer();
	apply_procedure();
	//save();
	free_memory();

	return 0;
}