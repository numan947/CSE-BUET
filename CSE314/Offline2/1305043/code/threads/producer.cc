#include "producer.h"
#include <iostream>
#include <cstdlib>
using namespace std;

Producer::Producer( string name)
{
	this->name = name;
}

Producer::~Producer()
{

}


string Producer::getName()
{
	return this->name;
}

void Producer::produceFood(queue<int>&foodTable)
{
	int food=rand()%300;
	cout<<"Producing...."<<food<<endl;
	foodTable.push(food);

	int randomLoop=rand()%4000;
	for(int i=0;i<randomLoop;i++){
		//random loop
	}

}






