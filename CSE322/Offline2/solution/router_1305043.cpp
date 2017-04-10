#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <map>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>
#include <algorithm>
#define INF -999999
using namespace std;

int strToInt(string s)
{
	stringstream ss;
	ss<<s;
	int tmp;
	ss>>tmp;
	return tmp;
}

void printRoutingTable(map<string,pair<string,int> >table)
{
	map<string,pair<string,int> >::iterator it;

	printf("destination--------nexthop--------cost\n\n");

	for(it=table.begin();it!=table.end();it++){
		printf("%s-------%s-------%d\n",(it->first).c_str(),(it->second).first.c_str(),(it->second).second);
		//cout<<it->first<<endl;
		//cout<<(it->second).first<<endl;
	}



}




int main(int argc, char *argv[])
{
	map<string,pair<string,int> >routingTable;
	int socket;
	int bindFlag;
	int sentBytes;
	int receivedBytes;
	string myIpAddress;

	struct sockaddr_in serverAddress;
	struct sockaddr_in clientAddress;

	char buffer[1024];


	if(argc!=3){
		printf("<ipaddress><space><topology file>");
	}

	//saving my ipaddress
	myIpAddress=argv[1];



	//opening the topology file to read
	ifstream fin(argv[2]);
	if(!fin.is_open()){
		printf("NOT OPENING FILE!!! WHY WHY WHY???");
	}

	//variables to hold the read data from the topology file
	string n1,n2;int cost;

	while(!fin.eof()){
		fin>>n1;
		fin>>n2;
		fin>>cost;


		//check if first router is ME, hence neighbour
		if(n1==myIpAddress){
			//printf("Hello1\n");
			routingTable[n2]=make_pair(n2,cost);
		}
		//check if second router is ME, hence neighbour
		else if(n2==myIpAddress){
			//printf("Hello2\n");
			routingTable[n1]=make_pair(n1,cost);
		}
		//the connection is not between ME and someone, so let's save other routers in the network
		else{
			if(routingTable.find(n1)==routingTable.end())routingTable[n1]=make_pair("NOT CONNECTED",INF);
			if(routingTable.find(n2)==routingTable.end())routingTable[n2]=make_pair("NOT CONNECTED",INF);
		}

	}

	//close the file
	fin.close();

	//first print
	printRoutingTable(routingTable);
	














	return 0;
}