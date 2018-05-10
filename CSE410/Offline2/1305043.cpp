#include <bits/stdc++.h>
using namespace std;


#define pb push_back
#define pf push_front
#define mp make_pair
#define fi first
#define se second


inline void tokenize(string str,vector<string> &tokens, string delim){ tokens.clear();size_t s = str.find_first_not_of(delim), e=s; while(s!=std::string::npos){e=str.find(delim,s);tokens.push_back(str.substr(s,e-s));s=str.find_first_not_of(delim,e);}}
inline string strip(string s){int i=0;while(i<s.size()){if(isspace(s[i]))i++;else break;}s.erase(0,i);i = s.size()-1;while(i>=0){if(isspace(s[i]))i--;else break;}s.erase(i+1,s.size()-i-1);return s;}


const int INF = (int) 1e9;
const ll LINF = (ll) 1e18;






class Vect
{

private:
	vector<double>elems;

public:

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
	}
};






int main()
{
	vector<string>toks;
	ifstream inputFile("scene.txt");
	string command;

	Vect ss(1,2,3);
	ss.print();

	Vect ss2(5,6);

	ss2.print();

	Vect ss3(ss2,20);
	ss3.print();

/*
	while(true){
		getline(inputFile,command);
		cout<<command<<endl;
		command=strip(command);

		if(command=="triangle"){
			string tr1,tr2,tr3;
			getline(inputFile,tr1);
			getline(inputFile,tr2);
			getline(inputFile,tr3);
			cout<<tr1<<endl;
			cout<<tr2<<endl;
			cout<<tr3<<endl;
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

		}
		else if(command=="pop"){

		}
		else if(command=="end"){
			break;
		}

	}
*/


	return 0;
}