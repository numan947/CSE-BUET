#include "consumer.h"
#include <iostream>
#include <cstdlib>
using namespace std;

Consumer::Consumer( string name)
{
	this->name = name;
}

Consumer::~Consumer()
{

}

string Consumer::getName()
{
	return this->name;
}

void Consumer::consumeFood(queue<int>&foodTable)
{
	cout<<"Consuming...."<<foodTable.front()<<endl;
	foodTable.pop();

	int randomLoop=rand()%4000;
	for(int i=0;i<randomLoop;i++){
		//random loop
	}

}