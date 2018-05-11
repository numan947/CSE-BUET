#include <bits/stdc++.h>
using namespace std;


#define pb push_back
#define pf push_front
#define mp make_pair
#define fi first
#define se second
#define pi (2*acos(0.0))

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

			//initialize as 0
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
			printf("%0.7lf",mat[i][0]);
			for(int j=1;j<cols;j++){
				printf(" %0.7lf",mat[i][j]);
			}
			printf("\n");
		}
	}

	string getPrintableString()
	{
		string ss="";
		for(int i=0;i<rows;i++){
			// printf("%0.7lf",mat[i][0]);
			ss+=doubleToString(mat[i][0]);
			for(int j=1;j<cols;j++){
				//printf(" %0.7lf",mat[i][j]);
				ss+=" "+doubleToString(mat[i][j]);
			}
			ss+="\n";
		}
		return ss;
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

	Matrix* transpose()
	{	
	    Matrix* temp=new Matrix(cols,rows);
	    
	    for (int i=0;i<rows;i++){
	        for (int j=0;j<cols;j++){
	            temp->mat[j][i] = mat[i][j];
	        }
	    }
	    return temp;
	}

	Matrix* extract(int rs, int re, int cs, int ce)
	{
		if(re<rs || ce<cs){
			printf("Invalid extraction\n");
			return 0;
		}
		int new_r=re-rs+1;
		int new_c=ce-cs+1;
		Matrix *tmp=new Matrix(new_r,new_c);

		for(int i=0;i<new_r;i++)
			for(int j=0;j<new_c;j++)
				tmp->mat[i][j]=this->mat[rs+i][cs+j];

		return tmp;

	}

	void normalize()//must be column matrix
	{
		double sum=0;
		for(int j=0;j<rows;j++){
			sum+=(mat[j][0]*mat[j][0]);
			//printf("%lf\n",mat[j][0] );
		}
		sum=sqrt(sum);

		//printf("NORMALIZING BY %lf %d\n",sum,rows);
		for(int j=0;j<rows;j++)
			mat[j][0]/=sum;

	}
	



	~Matrix()
	{
    	for (int i = 0; i < rows; ++i) {
        	delete[] mat[i];
    	}
    
    	delete[] mat;
	}

	static double dotProduct(Matrix* a, Matrix* b) //must be column matrix
	{
		if((a->rows!=b->rows) || (a->cols!= b->cols)){
			printf("ERROR\n");
			return 0;
		}

    	double sum = 0;
    	for(int j=0;j<a->rows;j++)
    		sum+=(a->getVal(j,0)*b->getVal(j,0));
    	return sum;
	}
	static Matrix* createIdentity(int size)
	{
		Matrix* temp =  new Matrix(size, size);
		for (int i=0;i<temp->rows;i++) {
			for (int j=0;j<temp->cols;j++) {
				if (i==j) {
					temp->mat[i][j]=1;
				} 
				else {
					temp->mat[i][j]=0;
				}
			}
		}
		return temp;
	}

	static Matrix* multiplyMatrices(Matrix* a, Matrix* b)
	{
		if(a->cols!=b->rows){
			printf("NOT POSSIBLE\n");
			return 0;
		}

		Matrix* tmp=new Matrix(a->rows,b->cols);

		for(int i=0;i<tmp->rows;i++){
			for(int j=0;j<tmp->cols;j++){
				for(int k=0;k<a->cols;k++){
					tmp->mat[i][j]+=(a->mat[i][k]*b->mat[k][j]);
				}
			}
		}

		return tmp;
	}

	static Matrix* multiplyByConstant(Matrix* a,double constant)
	{
		
		Matrix* tmp=new Matrix(*a);

		for(int i=0;i<a->rows;i++)
			for(int j=0;j<a->cols;j++)
				tmp->mat[i][j]*=constant;
		return tmp;
	}

	static Matrix* divideByConstant(Matrix* a,double constant)
	{
		if(constant==0){
			printf("DIVIDE BY ZERO ERROR\n");
			return 0;
		}
		
		Matrix* tmp=new Matrix(*a);

		for(int i=0;i<a->rows;i++)
			for(int j=0;j<a->cols;j++)
				tmp->mat[i][j]/=constant;
		return tmp;
	}

	static Matrix* pointNormalize(Matrix* m,int i,int j)
	{	
		double val=m->getVal(i,j);
		//printf("NORMALIZING BY %lf\n",val);
		return divideByConstant(m,val);
	}


	static Matrix* addMatrices(Matrix *a ,Matrix *b)
	{
		if((a->rows!=b->rows) || (a->cols!= b->cols)){
			printf("ERROR\n");
			return 0;
		}

		Matrix* tmp=new Matrix(a->rows,a->cols);

		for(int i=0;i<a->rows;i++){
			for(int j=0;j<a->cols;j++){
				tmp->mat[i][j]=a->mat[i][j]+b->mat[i][j];
			}
		}
		return tmp;
	}

	static Matrix* subMatrices(Matrix *a ,Matrix *b)
	{
		if((a->rows!=b->rows) || (a->cols!= b->cols)){
			printf("%d != %d %d != %dERROR\n",a->rows,b->rows,a->cols,b->cols);
			return 0;
		}

		Matrix* tmp=new Matrix(a->rows,a->cols);

		for(int i=0;i<a->rows;i++){
			for(int j=0;j<a->cols;j++){
				tmp->mat[i][j]=(a->mat[i][j])-(b->mat[i][j]);
			}
		}
		return tmp;
	}

	static Matrix* crossProduct(Matrix* a, Matrix* b) //a,b need to be 3D column matrix
	{
		if((a->rows!=b->rows) || (a->cols!= b->cols)){
			printf("ERROR\n");
			return 0;
		}

		Matrix* tmp=new Matrix(3,1);

		tmp->setVal(0,0,a->mat[1][0]*b->mat[2][0]-a->mat[2][0]*b->mat[1][0]);
		tmp->setVal(1,0,a->mat[2][0]*b->mat[0][0]-a->mat[0][0]*b->mat[2][0]);
		tmp->setVal(2,0,a->mat[0][0]*b->mat[1][0]-a->mat[1][0]*b->mat[0][0]);

		return tmp;

/*
		return Vect(
			a[1][0]*b[2][0]-a[2][0]*b[1][0],
			a[2][0]*b[0][0]-a[0][0]*b[2][0],
			a[0][0]*b[1][0]-a[1][0]*b[0][0]
					);*/
	}


	static Matrix* augmentMatrices(Matrix* A, Matrix* B,bool dim)//dim==1-->horizontal stacking
																//dim==0-->vertical stacking
	{
	
		if(dim){
			if(A->rows!=B->rows){
				printf("ERROR IN AUGMENT MATRIX\n");
				return 0;
			}

			Matrix* AB = new Matrix(A->rows,A->cols+B->cols);
		    
		    for (int i=0;i<AB->rows;i++){
		        int k=0;
		        for (int j=0;j<AB->cols;j++){
		            if (j<A->cols){
		                AB->mat[i][j]=A->mat[i][j];
		            }
		            else{
		                AB->mat[i][j]=B->mat[i][k];
		            	k++;
		            }
		        }
		    }
		    return AB;
		}
		
		else{
		
			if(A->cols!=B->cols){
				printf("ERROR IN AUGMENT MATRIX\n");
				return 0;
			}


			Matrix* AB = new Matrix(A->rows+B->rows,A->cols);
			
			//printf("HELIOS %d %d\n",AB->rows,AB->cols);
			int k=0;
			for (int i=0;i<AB->rows;i++){
			    for (int j=0;j<AB->cols;j++){
			        
			        if (i<A->rows){
			            AB->mat[i][j]=A->mat[i][j];
			            //printf("asdf1\n");
			        }
			        else{
			            AB->mat[i][j]=B->mat[k][j];
			            //printf("asdf2 %d -- %d\n",i,i-B->rows);
			        }

			    }
			    if(i>=A->rows)
			    	k++;
			}	

			return AB;
		}

		return 0;
	    
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
		//update.print();
		p1=Matrix::multiplyMatrices(&update,p1);

		p2=Matrix::multiplyMatrices(&update,p2);

		p3=Matrix::multiplyMatrices(&update,p3);
		return;
	}



	void print()
	{
		p1->transpose()->print();
		p2->transpose()->print();
		p3->transpose()->print();
	}

	Matrix* getTriangle()
	{
		Matrix *tmp1=Matrix::pointNormalize(p1,3,0);
		Matrix *tmp2=Matrix::pointNormalize(p2,3,0);
		Matrix *tmp3=Matrix::pointNormalize(p3,3,0);

		Matrix* ret=Matrix::augmentMatrices(tmp1->transpose(),tmp2->transpose(),0);
		ret=Matrix::augmentMatrices(ret,tmp3->transpose(),0);

		ret=ret->extract(0,2,0,2);

		return ret;
	}


	~Triangle(){
		delete p1;
		delete p2;
		delete p3;
	}

};




Matrix* initializeTranslation(string params)
{
	int SIZE=4;

	tokens.clear();
	tokenize(params,tokens," ");
	if(tokens.size()!=(SIZE-1))return 0;
	Matrix* tmp = Matrix::createIdentity(SIZE);
	
	for(int i=0;i<(SIZE-1);i++)
		tmp->setVal(i,(SIZE-1),stringToDouble(tokens[i]));
	return tmp;
}


Matrix* initializeTranslation(Matrix *params)
{
	int SIZE=4;

	Matrix* tmp = Matrix::createIdentity(SIZE);	
	for(int i=0;i<(SIZE-1);i++)
		tmp->setVal(i,(SIZE-1),params->getVal(i,0));
	return tmp;
}

Matrix* initializeScale(string params)
{
	int SIZE=4;

	tokens.clear();
	tokenize(params,tokens," ");
	if(tokens.size()!=(SIZE-1))return 0;
	Matrix* tmp = Matrix::createIdentity(SIZE);
	
	for(int i=0;i<(SIZE-1);i++)
		tmp->setVal(i,i,stringToDouble(tokens[i]));
	return tmp;
}


Matrix* rodriguesFormula(Matrix* x, Matrix *a, double theta)
{
	double cosTheta=cos(theta*pi/180.0);
	double sinTheta=sin(theta*pi/180.0);

	//printf("COS(%lf) = %lf\nSIN(%lf) = %lf\n",theta,cosTheta,theta,sinTheta);
	

	Matrix* tmp1=Matrix::multiplyByConstant(x,cosTheta);

	double dotP=Matrix::dotProduct(a,x);
	Matrix* tmp2=Matrix::multiplyByConstant(a,dotP*(1-cosTheta));

	Matrix* tmp3=Matrix::crossProduct(a,x);

	tmp3=Matrix::multiplyByConstant(tmp3,sinTheta);


	Matrix* tmp=Matrix::addMatrices(tmp1,tmp2);
	tmp=Matrix::addMatrices(tmp,tmp3);

	//tmp->print();




	return tmp;
}




Matrix* initializeRotation(string params)
{
	tokens.clear();
	tokenize(params,tokens," ");

	Matrix*tmp = Matrix::createIdentity(3);

	
	Matrix*i = tmp->extract(0,2,0,0);
	Matrix*j = tmp->extract(0,2,1,1);
	Matrix*k = tmp->extract(0,2,2,2);

	Matrix* a=new Matrix(3,1);


	double angle=stringToDouble(tokens[0]);

	for(int i=0;i<3;i++)
		a->setVal(i,0,stringToDouble(tokens[i+1]));

	a->normalize();

	Matrix* c1=rodriguesFormula(i,a,angle);
	Matrix* c2=rodriguesFormula(j,a,angle);
	Matrix* c3=rodriguesFormula(k,a,angle);

	tmp=Matrix::createIdentity(4);

	for(int i=0;i<3;i++){
		double cc1=c1->getVal(i,0);
		double cc2=c2->getVal(i,0);
		double cc3=c3->getVal(i,0);
		tmp->setVal(i,0,cc1);
		tmp->setVal(i,1,cc2);
		tmp->setVal(i,2,cc3);
	}

	return tmp;


}

Matrix* initializeLookAt(string pm)
{
	tokens.clear();
	tokenize(pm,tokens," ");

	Matrix* tmp=new Matrix(tokens.size(),1);

	for(int i=0;i<tokens.size();i++)
		tmp->setVal(i,0,stringToDouble(tokens[i]));

	return tmp;
}






Matrix* performStage2(Matrix* look, Matrix* eye, Matrix* up)
{
	Matrix* l= Matrix::subMatrices(look,eye);
	l->normalize();
	Matrix* r= Matrix::crossProduct(l,up);
	r->normalize();
	Matrix* u= Matrix::crossProduct(r,l);
	
	// l->print();
	// printf("\n");
	// r->print();
	// printf("\n");
	// u->print();

	Matrix* negE=Matrix::multiplyByConstant(eye,-1);
	Matrix* negL=Matrix::multiplyByConstant(l,-1);

	Matrix* T = initializeTranslation(negE);
	// printf("\n");
	// eye->print();
	// printf("\n");
	// T->print();

	Matrix* R=Matrix::createIdentity(4);
	Matrix*pt;
	for(int i=0;i<3;i++){
		if(i==0)pt=r;
		if(i==1)pt=u;
		if(i==2)pt=negL;
		double cc1=pt->getVal(0,0);
		double cc2=pt->getVal(1,0);
		double cc3=pt->getVal(2,0);
		R->setVal(i,0,cc1);
		R->setVal(i,1,cc2);
		R->setVal(i,2,cc3);
	}


	// printf("\n");
	// R->print();
	Matrix* V = Matrix::multiplyMatrices(R,T);
	return V;
}



Matrix* performStage3(Matrix * pers)
{
	double fovY=pers->getVal(0,0);
	double aspect=pers->getVal(1,0);
	double near=pers->getVal(2,0);
	double far=pers->getVal(3,0);

	double fovX=fovY*aspect;
	double t=near*tan((fovY/2.0)*pi/180.0);
	double r=near*tan((fovX/2.0)*pi/180.0);

	Matrix* ret=new Matrix(4,4);

	ret->setVal(0,0,near/r);
	ret->setVal(1,1,near/t);
	ret->setVal(2,2,-(far+near)/(far-near));
	ret->setVal(2,3,-(2*far*near)/(far-near));
	ret->setVal(3,2,-1);

	return ret;
}




void printToFile(vector<Triangle*>triangles,string fileName)
{
	ofstream ofs;
	ofs.open(fileName.c_str());
	for(int i=0;i<triangles.size();i++){
		ofs<<triangles[i]->getTriangle()->getPrintableString();
		ofs<<"\n";
	}
	ofs.close();

}



int main()
{
//	testFunctionality();

	realMain();
	
	return 0; 
}




void realMain()
{
	
	//manage manually, push_back, pop_back,back
	vector<Matrix*>transStack;
	

	Matrix* currentTransMatrix=Matrix::createIdentity(4);
	//cout<<currentTransMatrix<<endl;
	vector<Triangle*>triangles;
	//currentTransMatrix.print();


	ifstream inputFile("scene.txt");
	string command;

	string eyeS,lookS,upS,perspS;

	getline(inputFile,eyeS);
	getline(inputFile,lookS);
	getline(inputFile,upS);
	getline(inputFile,perspS);

	Matrix* eye=initializeLookAt(strip(eyeS));
	Matrix* look=initializeLookAt(strip(lookS));
	Matrix* up=initializeLookAt(strip(upS));

	//la.print();

	Matrix* pers=initializeLookAt(strip(perspS));

	//pers.print();


//STAGE 1
	while(true){
		getline(inputFile,command);

		//cout<<command<<endl;
		
		command=strip(command);

		if(command=="triangle"){
			string tr1,tr2,tr3;
			getline(inputFile,tr1);
			getline(inputFile,tr2);
			getline(inputFile,tr3);
			Triangle* tt=new Triangle(strip(tr1),strip(tr2),strip(tr3));
			
			//tt->print();printf("\n");

			//currentTransMatrix->print();
			tt->applyMatrix(*currentTransMatrix);
			
			//tt->print();printf("\n");



			triangles.pb(tt);
		}
		else if(command=="translate"){
			string trnsl;
			getline(inputFile,trnsl);
			//cout<<trnsl<<endl;
			Matrix* t=initializeTranslation(strip(trnsl));
			
			currentTransMatrix=Matrix::multiplyMatrices(currentTransMatrix,t);
			
			
		}
		else if(command=="scale"){
			string scl;
			getline(inputFile,scl);
			Matrix* t=initializeScale(strip(scl));
			currentTransMatrix=Matrix::multiplyMatrices(currentTransMatrix,t);
		}
		else if(command=="rotate"){
			string rot;
			getline(inputFile,rot);
			Matrix* t=initializeRotation(strip(rot));
			currentTransMatrix=Matrix::multiplyMatrices(currentTransMatrix,t);
		}
		else if(command=="push"){
			transStack.push_back(currentTransMatrix);
			currentTransMatrix=new Matrix(*currentTransMatrix);
		}
		else if(command=="pop"){
			if(transStack.size()>0){
				currentTransMatrix=transStack.back();
				transStack.pop_back();
			}
			else
				printf("ERROR POPPING AN EMPTY MATRIX\n");
		}
		else if(command=="end"){
			break;
		}

	}

	printToFile(triangles,string("stage1.txt"));


	//STAGE 2
	//printf("AFTER STAGE 2 APPLIED\n");
	Matrix* V = performStage2(look,eye,up);
	for(int i=0;i<triangles.size();i++)
	{
		//printf("\n");
		triangles[i]->applyMatrix(*V);
		//triangles[i]->print();
		//printf("\n");
	}

	printToFile(triangles,string("stage2.txt"));
	//STAGE 3
	//printf("AFTER STAGE 3 APPLIED\n");
	Matrix* P = performStage3(pers);

	for(int i=0;i<triangles.size();i++)
	{
		//printf("\n");
		triangles[i]->applyMatrix(*P);
		//triangles[i]->print();
		//printf("\n");
	}
	printToFile(triangles,string("stage3.txt"));

}






































void testFunctionality()
{
	Matrix* mm=Matrix::createIdentity(5);
	Matrix* mn=new Matrix(4,5);


	for(int i=0;i<4;i++)
		for(int j=0;j<5;j++)
			mn->setVal(i,j,i+j+20);

	mn->print();


	for(int i=0;i<5;i++)
		for(int j=0;j<5;j++)
			mm->setVal(i,j,5);

	mm->print();

	Matrix*res = Matrix::multiplyMatrices(mn,mm);
	printf("\n");
	res->print();

	mm=Matrix::multiplyByConstant(mm,5);

	printf("\n");
	mm->print();

	mn=Matrix::pointNormalize(mn,3,4);

	printf("\n");
	mn->print();


	Matrix* ex=mn->extract(0,2,2,2);

	printf("\n");
	ex->print();

	ex->normalize();
	printf("\n");
	ex->print();


	Matrix *ey=mn->extract(0,2,1,1);
	printf("\n");
	ey->print();

	ey->normalize();

	printf("\n");
	ey->print();

	double xx=Matrix::dotProduct(ex,ey);

	printf("%lf\n",xx);


	Matrix*tt=Matrix::addMatrices(ex,ey);

	tt->print();

	printf("\n");

	Matrix* cross=Matrix::crossProduct(ex,ey);

	cross->print();
	delete mm;
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

