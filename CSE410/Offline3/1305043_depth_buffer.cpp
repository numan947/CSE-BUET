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




class Line2D{
public:
	double a,b,c; //ax+by=c
	Point p1,p2;

	Line2D(double a, double b, double c)
	{
		this->a = a;
		this->b = b;
		this->c = c;
	}

	Line2D(Point p1, Point p2){
		this->a = p2.y - p1.y;
		this->b = p1.x - p2.x;
		this->c = (this->a)*p1.x + (this->b)*p1.y;

		this->p1.x = p1.x;
		this->p1.y = p1.y;
		this->p2.x = p2.x;
		this->p2.y = p2.y;
	}


	void printLine()
	{
		// if(p1.isValid2D() && p2.isValid2D()){
		// 	p1.printPoint2D();
		// 	p2.printPoint2D();
		// }
		cout<<a<<"X+"<<b<<"Y = "<<c<<endl;
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
		
		double det = l1.a*l2.b - l2.a*l1.b;
		if(det==0)return false;



		p.x = (l2.b*l1.c - l1.b*l2.c) / det;
		p.y = (l1.a*l2.c - l2.a*l1.c) /det;

		return true;
	}

	static bool insideLineSegment(Point p1, Point p2, Point p3) //p3 inside the line segement defined by p1, p2
	{
		//return (min(p1.x,p2.x)<=p3.x)&&(p3.x<=max(p1.x,p2.x)) && (min(p1.y,p2.y)<=p3.y)&&(p3.y<=max(p1.y,p2.y));

		double minValX = min(p1.x,p2.x);
		double minValY = min(p1.y,p2.y);

		double maxValX = max(p1.x,p2.x);
		double maxValY = max(p1.y,p2.y);

		return
		(fabs(minValX - p3.x)<=eps || minValX < p3.x) && (fabs(minValY - p3.y)<=eps || minValY < p3.y)&&
		(fabs(maxValX - p3.x)<=eps || p3.x < maxValX) && (fabs(maxValY - p3.y)<=eps || p3.y < maxValY);  
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

	double p_a,p_b,p_c,p_d;

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


			Vect *A = new Vect(*point[0],*point[1]);
			Vect *B = new Vect(*point[0],*point[2]);

			Vect planeVector = crossProduct(*A,*B);

			this->p_a = planeVector.x;
			this->p_b = planeVector.y;
			this->p_c = planeVector.z;
			this->p_d = (-p_a*(point[0]->x))+(-p_b*point[0]->y)+(-p_c*point[0]->z);
		}

	}

	double getZValue(double x, double y)
	{
		//cout<<p_a <<" "<<p_b<<" "<<p_c<<" "<<p_d<<endl;
		return (-1.0*p_d - 1.0*p_a*x - 1.0*p_b*y)/p_c;
	}


	bool getScanLineIntersectPoints(double b,Point &p1, Point &p2){
		Line2D *tmp = new Line2D(0,1,b);

		bool l=false,r=false;

		vector<Point>pp;
		pp.clear();
		for(int i=0;i<3;i++){
			Point x;	
			Line2D::areIntersect(*tmp,*line[i],x);
			if(x.isValid2D()){
				if(Line2D::insideLineSegment(*point[i],*point[(i+1)%3],x))
					pp.pb(x);


			}
			
		}

		// for(int i=0;i<pp.size();i++)
		// 	pp[i].printPoint2D();

		if(pp.size()<2 ){
			printf("FIX IT FELIX --size-- %d\n",pp.size());
			cout<<"B value --> "<<b<<endl;
			// for(int i=0;i<invalid.size();i++){
			// 	invalid[i].printPoint2D();

			// 	cout<<Line2D::insideLineSegment(*point[0],*point[1],invalid[i])<<endl;
			// 	cout<<Line2D::insideLineSegment(*point[1],*point[2],invalid[i])<<endl;
			// 	cout<<Line2D::insideLineSegment(*point[2],*point[0],invalid[i])<<endl;
				
			// }

			// pp[0].printPoint2D();
			// line[0]->printLine();
			// line[1]->printLine();
			// line[2]->printLine();

			// tmp->printLine();


			// this->printTriangle();
			return false;

		}
		else{
			if(pp.size()==3){
				for(int i=0;i<2;i++){
					for(int j=i+1;j<3;j++){
						if(Point::isSame(pp[i],pp[j])){
							pp.erase(pp.begin()+i);
							break;
						}
					}
					if(pp.size()<3)break;
				}

			}


			if(pp[0].x<pp[1].x){
				p1.x = pp[0].x;
				p1.y = pp[0].y;

				p2.x = pp[1].x;
				p2.y = pp[1].y;
			}
			else{
				p2.x = pp[0].x;
				p2.y = pp[0].y;

				p1.x = pp[1].x;
				p1.y = pp[1].y;
			}
			return true;
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

	printf("Top_Y %lf Left_X %lf\n",Top_Y,Left_X);
	printf("dx %lf dy %lf\n",dx,dy);

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


int getRowNumber(double ss)
{
	int tp = myRound((Top_Y-ss)/dy);
	if(tp<0)tp = 0;
	else if(tp>=Screen_Height)tp = Screen_Height - 1;
	return tp;
}

double getRowValue(int row)
{
	return Top_Y - row*dy*1.0;
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


double getTopScanLine(double maxY)
{
	double ss = maxY;
	if(ss>y_top_limit)ss=y_top_limit;
	return ss;
}
double getBottomScanLine(double minY)
{
	double ss = minY;
	if(ss<y_bottom_limit)ss=y_bottom_limit;
	return ss;
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





void apply_procedure()
{
	
	double top_scan_line,bottom_scan_line,
		   left_clipping_line,right_clipping_line;

	int rr,rre,cc,cce;

	Point p1,p2;


	for(int i=0;i<triangles.size();i++)
	{
		Triangle* cur = triangles[i];

		cur->setColor(myRand(),myRand(),myRand()); //avoid 0 coloring

		top_scan_line = getTopScanLine(cur->getMaxY());
		bottom_scan_line = getBottomScanLine(cur->getMinY());


		printf("HEllo\n");
		p1.clear();
		p2.clear();

		rr = getRowNumber(top_scan_line);
		rre = getRowNumber(bottom_scan_line);

		printf("Scan Line %d to %d --------------------------\n",rr,rre);
		printf("Scan Line %lf to %lf --------------------------\n",getRowValue(rr),getRowValue(rre));

		while(rr<=rre){
			//printf("Scan Line %d to %d --------------------------\n",rr,rre);
			//printf("Scan Line %lf to %lf --------------------------\n",getRowValue(rr),getRowValue(rre));

			if(cur->getScanLineIntersectPoints(getRowValue(rr),p1,p2)){
			

				left_clipping_line = getLeftClippingLine(p1.x);
				right_clipping_line = getRightClippingLine(p2.x);

				cc = getColNumber(left_clipping_line);
				cce = getColNumber(right_clipping_line);

				//cout<<cc<<" "<<cce<<endl;

				cout<<getColValue(cc)<<"  "<<getRowValue(rr)<<endl;
				cout<<cur->getZValue(getColValue(cc),getRowValue(rr))<<endl;
				//break;

				while(cc<=cce){
					double zVal = cur->getZValue(getColValue(cc),getRowValue(rr));
					if(zVal>=z_front_limit && zVal<=z_rear_limit && zVal<z_buffer[rr][cc]){
						z_buffer[rr][cc]=zVal;
						image->set_pixel(cc,rr,cur->getR(),cur->getG(),cur->getB());
					}
					cc++;
				}
			}
			rr++;

		}



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
	//srand(time(NULL));
	freopen("debug2.txt", "w", stdout);
	read_data();
	initialize_z_buffer_and_frame_buffer();
	apply_procedure();
	save();
	free_memory();

	return 0;
}