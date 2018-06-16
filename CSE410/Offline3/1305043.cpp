#include <bits/stdc++.h>
using namespace std;


#define pb push_back
#define pf push_front
#define mp make_pair
#define fi first
#define se second
#define pi (2*acos(0.0))

const int INF = (int) 1e9;


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
	ostr.precision(7);
	ostr<<fixed;
	ostr<<dd;
	return ostr.str();
}

/************************************/


class Point{
public:
	double x,y,z;

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
};



class Triangle{

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
	unsigned char color[3];

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

	void setColor(int pointPos,unsigned char val)
	{
		if(pointPos<0||pointPos>=3){
			printf("Error in --> TRIANGLE:setColor, value out of bound\n");
			return;
		}
		color[pointPos]=val;
	}



	void printTriangle()
	{
		for(int i=0;i<3;i++)
			point[i]->printPoint();
		printf("\n");
	}
};














double Screen_Width,Screen_Height,x_limit,y_limit,z_limit_f,z_limit_r;

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
	x_limit = stringToDouble(tmp);

	//3rd line
	getline(if1,tmp);
	y_limit = stringToDouble(tmp);

	//4th line
	getline(if1,tmp);
	tokens.clear();
	tokenize(tmp,tokens," ");
	z_limit_f = stringToDouble(tokens[0]);
	z_limit_r = stringToDouble(tokens[1]);


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
	cout<<x_limit<<" "<<y_limit<<" "<<z_limit_f<<" "<<z_limit_r<<endl;

	for(int i=0;i<triangles.size();i++)
		triangles[i]->printTriangle();*/
}



void initialize_z_buffer_and_frame_buffer()
{

}



int main()
{

	read_data();



	return 0;
}