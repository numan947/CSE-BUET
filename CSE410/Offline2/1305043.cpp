#include <bits/stdc++.h>
using namespace std;


#define pb push_back
#define pf push_front
#define mp make_pair
#define fi first
#define se second


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

/************************************/



const int INF = (int) 1e9;

class Perspective
{
	double fovY,aspectRatio,near,far;
	vector<string>toks;
public:
	Perspective(string p)
	{
		toks.clear();
		tokenize(p,toks," ");
		fovY=stringToDouble(toks[0]);
		aspectRatio=stringToDouble(toks[1]);
		near=stringToDouble(toks[2]);
		far=stringToDouble(toks[3]);

	}
	void print()
	{
		printf("fovY: %lf, aspectRatio: %lf, near: %lf, far: %lf\n",this->fovY,this->aspectRatio,this->near,this->far);
	}
};

class LookAt
{
	double ex,ey,ez,lx,ly,lz,ux,uy,uz;
	vector<string>toks;
public:
	LookAt(string e,string l, string u)
	{
		toks.clear();
		tokenize(e,toks," ");
		ex=stringToDouble(toks[0]);
		ey=stringToDouble(toks[1]);
		ez=stringToDouble(toks[2]);

		toks.clear();
		tokenize(l,toks," ");
		lx=stringToDouble(toks[0]);
		ly=stringToDouble(toks[1]);
		lz=stringToDouble(toks[2]);

		toks.clear();
		tokenize(u,toks," ");
		ux=stringToDouble(toks[0]);
		uy=stringToDouble(toks[1]);
		uz=stringToDouble(toks[2]);

	}


	void print()
	{
		printf("eye--> %lf %lf %lf\n",ex,ey,ez);

		printf("look--> %lf %lf %lf\n",lx,ly,lz);

		printf("up--> %lf %lf %lf\n",ux,uy,uz);
	}
};




class Matrix
{
private:
	int rows,cols;
	double **mat;
public:

	Matrix(int rows=3,int cols=3) //by default 3x3 matrix
	{	
		if(rows<=0||cols<=0){
			printf("ERROR");
		}
		else{
			this->rows=rows;
			this->cols=cols;
			//allocate space
			mat=new double*[rows];
			for(int i=0;i<rows;i++){
				mat[i]=new double[cols];
			}

			//initialize as identity
			for(int i=0;i<rows;i++)
				for(int j=0;j<cols;j++){
					mat[i][j]=0;
				}
		}
	}
	Matrix(const Matrix &m)
	{

		this->rows=m.rows;
		this->cols=m.cols;
		//allocate space
		mat=new double*[rows];
		for(int i=0;i<rows;i++){
			mat[i]=new double[cols];
		}

		//initialize as identity
		for(int i=0;i<rows;i++)
			for(int j=0;j<cols;j++)
				mat[i][j]=0;


	    for (int i = 0;i<rows;i++) {
	        for (int j=0;j<cols;j++) {
	            mat[i][j] = m.mat[i][j];
	        }
	    }
	}

	Matrix copy()
	{
		Matrix temp(rows,cols);
	    
	    for (int i=0;i<rows;i++){
	        for (int j=0;j<cols;j++){
	            temp.mat[i][j] = mat[i][j];
	        }
	    }
	    return temp;
	}


	void print()
	{
		for(int i=0;i<rows;i++){
			printf("%lf",mat[i][0]);
			for(int j=1;j<cols;j++){
				printf(" %lf",mat[i][j]);
			}
			printf("\n");
		}
	}


	int rowSize()
	{return rows;}
	int colSize()
	{return cols;}

	void setVal(int r,int c,double val)
	{
		if(r<0||r>=rows||c<0||c>=cols){
			printf("ERROR in MATRIX, setVal\n");
			return;
		}
		mat[r][c]=val;

	}
	double getVal(int r,int c)
	{
		if(r<0||r>=rows||c<0||c>=cols){
			printf("ERROR in MATRIX, setVal\n");
			return -INF;
		}
		return mat[r][c];
	}

	Matrix transpose()
	{	
	    Matrix temp(cols,rows);
	    
	    for (int i=0;i<rows;i++){
	        for (int j=0;j<cols;j++){
	            temp.mat[j][i] = mat[i][j];
	        }
	    }
	    return temp;
	}


	~Matrix()
	{
    	for (int i = 0; i < rows; ++i) {
        	delete[] mat[i];
    	}
    
    	delete[] mat;
	}


	static Matrix createIdentity(int size)
	{
		Matrix temp(size, size);
		for (int i=0;i<temp.rows;i++) {
			for (int j=0;j<temp.cols;j++) {
				if (i==j) {
					temp.mat[i][j]=1;
				} 
				else {
					temp.mat[i][j]=0;
				}
			}
		}
		return temp;
	}

};





class Triangle
{

private:
	Matrix *p1,*p2,*p3;
	vector<string>toks;

	void tokenizeAndAdd(Matrix *p, string in)
	{
		
		toks.clear();
		tokenize(in,toks," ");
		
		p->setVal(0,0,stringToDouble(toks[0]));
		p->setVal(1,0,stringToDouble(toks[1]));
		p->setVal(2,0,stringToDouble(toks[2]));
	}

public:
	Triangle(string v1,string v2,string v3)
	{
		p1=new Matrix(4,1);
		p2=new Matrix(4,1);
		p3=new Matrix(4,1);
		p1->setVal(3,0,1);
		p2->setVal(3,0,1);
		p3->setVal(3,0,1);

		tokenizeAndAdd(p1,v1);

		tokenizeAndAdd(p2,v2);

		tokenizeAndAdd(p3,v3);


	}

	void setPoint(int num,double x, double y, double z)
	{
		if(num<0||num>2){
			printf("ERROR in TRIANGLE, setPoint\n");
			return;
		}
		if(num==0){
			p1->setVal(0,0,x);
			p1->setVal(1,0,y);
			p1->setVal(2,0,z);
		}
		if(num==1){
			p2->setVal(0,0,x);
			p2->setVal(1,0,y);
			p2->setVal(2,0,z);
		}
		if(num==2){
			p3->setVal(0,0,x);
			p3->setVal(1,0,y);
			p3->setVal(2,0,z);
		}
	}

	Matrix getPoint(int num)
	{
		if(num<0||num>2){
			printf("ERROR in TRIANGLE, getPoint\n");
			return Matrix();
		}
		if(num==0)return *p1;
		if(num==1)return *p2;
		if(num==2)return *p3;
	}

	void applyMatrix(Matrix &update)
	{
		//todo matrix multiplication and point update
		update.print();
		return;
	}



	void print()
	{
		p1->transpose().print();
		p2->transpose().print();
		p3->transpose().print();
	}

	~Triangle(){
		delete p1;
		delete p2;
		delete p3;
	}

};







Triangle initializeTriangle(string p1,string p2,string p3)
{



}

Matrix initializeTranslation(string params)
{
	//todo
}

Matrix initializeScale(string params)
{
	//todo
}
Matrix initializeRotation(string params)
{


	//todo
}







int main()
{
	//testFunctionality();

	realMain();
	
	return 0;
}




void realMain()
{
	
	//manage manually, push_back, pop_back,back
	vector<Matrix*>transStack;
	
	Matrix tmp=Matrix::createIdentity(4);

	Matrix* currentTransMatrix=new Matrix(tmp);

	cout<<currentTransMatrix<<endl;
	vector<Triangle*>triangles;
	//currentTransMatrix.print();


	ifstream inputFile("scene.txt");
	string command;

	string eyeS,lookS,upS,perspS;

	getline(inputFile,eyeS);
	getline(inputFile,lookS);
	getline(inputFile,upS);
	getline(inputFile,perspS);



	LookAt la(eyeS,lookS,upS);

	la.print();

	Perspective pers(perspS);

	pers.print();

	while(true){
		getline(inputFile,command);

		cout<<command<<endl;
		command=strip(command);

		if(command=="triangle"){
			string tr1,tr2,tr3;
			getline(inputFile,tr1);
			getline(inputFile,tr2);
			getline(inputFile,tr3);
			Triangle* tt=new Triangle(tr1,tr2,tr3);
			
			//tt->applyMatrix(currentTransMatrix);


			triangles.pb(tt);
		}
		else if(command=="translate"){
			string trnsl;
			getline(inputFile,trnsl);
			cout<<trnsl<<endl;
		}
		else if(command=="scale"){
			string scl;
			getline(inputFile,scl);
			cout<<scl<<endl;
		}
		else if(command=="rotate"){
			string rot;
			getline(inputFile,rot);
			cout<<rot<<endl;
		}
		else if(command=="push"){
			currentTransMatrix->print();
			transStack.push_back(currentTransMatrix);
			//currentTransMatrix.setVal(0,2,55);
		}
		else if(command=="pop"){
			if(transStack.size()>0){
				currentTransMatrix=transStack.back();
				//currentTransMatrix.print();
				transStack.pop_back();
			}
			else
				printf("ERROR POPPING AN EMPTY MATRIX\n");
		}
		else if(command=="end"){
/*			for(int i=0;i<triangles.size();i++){
				triangles[i]->print();
				printf("\n");
			}*/
			break;
		}

	}
}


void testFunctionality()
{
	Matrix mm=Matrix::createIdentity(5);
	mm.setVal(0,4,55);
	mm.print();
	printf("\n");
	mm.transpose().print();
}























/*class Vect
{

private:
	vector<double>elems;

public:

	Vect(){}
	Vect(double a, double b)
	{
		this->elems.pb(a);
		this->elems.pb(b);
	}


	Vect(double a, double b,double c)
	{
		this->elems.pb(a);
		this->elems.pb(b);
		this->elems.pb(c);
	}

	Vect(Vect other,double a)
	{
		for(int i=0;i<other.size();i++)
			this->elems.pb(other[i]);
		this->elems.pb(a);
	}


	void add(double new_elem)
	{
		this->elems.pb(new_elem);
	}

	int size()
	{
		return this->elems.size();
	}
	void print()
	{
		if(this->size()==0){
			printf("Vector is empty");
		}
		else{
			printf("%lf ",elems[0]);
			for(int i=1;i<this->size();i++){
				printf(" %lf",elems[i] );
			}
			printf("\n");
		}
	}

	double operator[](int j){ 
		if(j<0||j>=this->size()){
			printf("Index out of bounds.\n");
			return -1;
		}
		return this->elems[j]; 
	}


	static double DOTPRODUCT(Vect a, Vect b)
	{

		if(a.size()!=b.size()){
			printf("vectors of different sizes can not have dot product.\n");
			return -INF;
		}
		double res=0;
		int sz=a.size();
		for(int i=0;i<sz;i++){
			res+=(a[i]*b[i]);
		}
		return res;
	}



	static Vect CROSSPRODUCT(Vect a, Vect b) //a,b need to be 3D
	{
		if(a.size()!=3 || b.size()!=3){
			printf("Undefined for now\n");
			return Vect();
		}
		return Vect(
			a[1]*b[2]-a[2]*b[1],
			a[2]*b[0]-a[0]*b[2],
			a[0]*b[1]-a[1]*b[0]
					);
	}


};







*/

