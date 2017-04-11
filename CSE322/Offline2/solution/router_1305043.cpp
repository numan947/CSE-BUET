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
#include <cerrno>
#define INF 10000000

using namespace std;

struct linkToNeighbour
{
	string neighbourIp;
	int linkcost;
	int linkstatus;
};



vector<string> tokenizeString(string src,string delim)
{

	vector<string>tokens;
	int cur=0;
	string tkn;
	while((cur=src.find(delim))!=string::npos){
	    tkn=src.substr(0, cur);
	    tokens.push_back(tkn);
	    src.erase(0,cur+delim.length());
	}
	return tokens;
}



int strToInt(string s)
{
	stringstream ss;
	ss<<s;
	int tmp;
	ss>>tmp;
	return tmp;
}


string intToStr(int s)
{
	stringstream ss;
	ss<<s;
	return ss.str();
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
	printf("\n\n");
}




void updateCost(map<string,pair<string,int> >&routingTable,vector<linkToNeighbour>&neighbours,string myIpAddress,char* buffer)
{
   		char ip1[20],ip2[20];unsigned char costBuff[2];

		//get the ips from the buffer
		inet_ntop(AF_INET,buffer+4,ip1,sizeof(ip1));
		inet_ntop(AF_INET,buffer+8,ip2,sizeof(ip2));

		//get the cost from the buffer
		costBuff[0]=buffer[12];//lsb
		costBuff[1]=buffer[13];//msb
		int cost=costBuff[0]|(costBuff[1]<<8);

		string updateCostIp=(ip1==myIpAddress) ? ip2:ip1;
		
		map<string,pair<string,int> >::iterator it=routingTable.find(updateCostIp);
		
		if(it!=routingTable.end()){

			//link cost update
			linkToNeighbour x;
			for(int i=0;i<neighbours.size();i++)
				if(it->first==neighbours[i].neighbourIp){
					neighbours[i].linkcost=cost;
					x=neighbours[i];
					break;
				}

			//routing table update

			//nexthop neighbour, so need to update
			if(it->second.first==it->first){
				it->second.second=x.linkcost;
			}
			//case2: nexthop is not neighbour, so update if.... 
			else if((it->second.second>=x.linkcost)&&(x.linkstatus==1)){
				it->second.first=updateCostIp; //nexthop change
				it->second.second=x.linkcost; //cost change
			}


			//printf("WHYHWYHWY--");
			//cout<<updateCostIp<<" "<<it->first<<" "<<it->second.first<<" "<<it->second.second<<"\n";
			printf("Updating cost\n");
			printRoutingTable(routingTable);//dummy print;remove later
		}
}



string serializeRoutingTable(map<string,pair<string,int> >&routingTable)
{

	string serialized="";

	map<string,pair<string,int> >::iterator it;

	for(it=routingTable.begin();it!=routingTable.end();it++){
		serialized+=it->first+"$$$$";
		serialized+=it->second.first+"$$$$";
		serialized+=intToStr(it->second.second)+"$$$$";
	}
	printf("serialized string is %s\n",serialized.c_str());

	return serialized;
}

void sendToNeighbours(vector<linkToNeighbour>neighbours,string msgToSend,int socketDescriptor)
{
	int totalBytesSent;
	struct sockaddr_in remoteAddress;
	remoteAddress.sin_family=AF_INET;
	remoteAddress.sin_port=htons(4747);
	string ip;

	for(int i=0;i<neighbours.size();i++){


		ip=neighbours[i].neighbourIp;

		inet_pton(AF_INET,ip.c_str(),&remoteAddress.sin_addr);
		totalBytesSent=sendto(socketDescriptor,msgToSend.c_str(), 1024, 0, (struct sockaddr*) &remoteAddress, sizeof(sockaddr_in));
		
		printf("just sent %d to %s\n",totalBytesSent,ip.c_str());//remove later
	}

}


map<string,pair<string,int> >buildMap(vector<string>vct)
{
	map<string,pair<string,int> >neighbourTable;
	
	//entry 0 is "tabl", so avoid that
	for(int i=1;i<vct.size();i+=3){
		neighbourTable[vct[i]]=make_pair(vct[i+1],strToInt(vct[i+2]));
	}
	return neighbourTable;
}



void updateRoutingTable(map<string,pair<string,int> >&routingTable,map<string,pair<string,int> >&neighbourTable,vector<linkToNeighbour>&neighbours,string neighbour,string myIpAddress)
{
map<string,pair<string,int> >::iterator it1,it2;

	//update routing table using neighbour's routing table
	for(it1=routingTable.begin();it1!=routingTable.end();it1++){
		string dest=it1->first;
		string current_nexthop=it1->second.first;
		int current_cost=it1->second.second;

		it2=neighbourTable.find(dest);
		if(it2==neighbourTable.end())continue;//this case should arise only for neighbours
		string neighbour_nexthop=it2->second.first;
		int neighbour_cost=it2->second.second;

		it2=routingTable.find(neighbour);
		int cost_to_go_to_neighbour=it2->second.second;


		//split horizon || forced update
		if((neighbour_nexthop!=myIpAddress && (current_cost>cost_to_go_to_neighbour+neighbour_cost))||(neighbour==current_nexthop)){
			it1->second.first=neighbour;
			it1->second.second=cost_to_go_to_neighbour+neighbour_cost;
		}
	}

	//update routing table using my neighbour table

	for(int i=0;i<neighbours.size();i++){

		if(neighbours[i].linkstatus==0)continue;

		string ip=neighbours[i].neighbourIp;
		int cost=neighbours[i].linkcost;
		//int status=neighbours[i].linkstatus;

		it1=routingTable.find(ip);

		if(it1!=routingTable.end())
			if(it1->second.second>=cost){
				it1->second.first=ip;
				it1->second.second=cost;
			}
	}





}



int main(int argc, char *argv[])
{
	map<string,pair<string,int> >routingTable;
	vector<linkToNeighbour>myneighbours;
	int socketDescriptor;
	int bindFlag;

	int totalBytesRead;
	string myIpAddress;



	socklen_t addressLength;
	struct sockaddr_in serverAddress;
	struct sockaddr_in clientAddress;

	char buffer[1024];


	if(argc!=3){
		printf("<ipaddress><space><topology file>\n");
		exit(1);
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

			linkToNeighbour a;
			a.neighbourIp=n2;
			a.linkcost=cost;
			a.linkstatus=1;
			myneighbours.push_back(a);
		}
		//check if second router is ME, hence neighbour
		else if(n2==myIpAddress){
			//printf("Hello2\n");
			routingTable[n1]=make_pair(n1,cost);

			linkToNeighbour a;
			a.neighbourIp=n1;
			a.linkcost=cost;
			a.linkstatus=1;

			myneighbours.push_back(a);
		}
		//the connection is not between ME and someone, so let's save other routers in the network
		else{
			if(routingTable.find(n1)==routingTable.end())routingTable[n1]=make_pair("waiting for calculation",INF);
			if(routingTable.find(n2)==routingTable.end())routingTable[n2]=make_pair("waiting for calculation",INF);
		}

	}

	//close the file
	fin.close();

	//first print
	printRoutingTable(routingTable);


	//setting up server
	serverAddress.sin_family=AF_INET;
	serverAddress.sin_port=htons(4747);
	inet_pton(AF_INET,myIpAddress.c_str(),&serverAddress.sin_addr);

	socketDescriptor=socket(AF_INET,SOCK_DGRAM,0);

	bindFlag=bind(socketDescriptor, (struct sockaddr*) &serverAddress, sizeof(sockaddr_in));

	if(bindFlag!=0){
		char errorBuffer[256];
    	char* errorMessage=strerror_r(errno,errorBuffer,256); // get string message from errno
    	printf("Error while opening socket: %s\n",errorMessage);
    	exit(1);
    }
    else printf("Succecssfully bound to the address %s\n",myIpAddress.c_str());


    while(true){
    	char extractedIp[20];
    	memset(extractedIp,0,sizeof(extractedIp));
    	memset(buffer,0,sizeof(buffer));

    	totalBytesRead=recvfrom(socketDescriptor,buffer,1024,0,(struct sockaddr*)&clientAddress,&addressLength);

    	//build up the command from the buffer
    	char command[10];
    	strncpy(command,buffer,4);
    	command[4]='\0';

    	//command list
    	//clk<space>
    	//mssg -- sent from neighbour to forward a message
    	//cost -- sent from driver
    	//send -- sent from driver
    	//tabl -- sent from neightbout with the routing table
    	//show -- sent from driver
    	printf("command is %s\n",command );
    	//printf("%s\n",buffer);






    	if(!strcmp(command,"clk ")){
    		string s=serializeRoutingTable(routingTable);
    		s="tabl$$$$"+s;
    		sendToNeighbours(myneighbours,s,socketDescriptor);
    		// inet_ntop(AF_INET,buffer+4,extractedIp,sizeof(extractedIp));
    		// printf("extractedIp is %s\n",extractedIp );
    		// printf("%s\n",inet_ntoa(clientAddress.sin_addr));
    	}
    	else if(!strcmp(command,"show")){
    		printRoutingTable(routingTable);
    	}
    	else if(!strcmp(command,"cost")){
    		updateCost(routingTable,myneighbours,myIpAddress,buffer);
    	}
    	else if(!strcmp(command,"tabl")){
    		string neighbourIp=inet_ntoa(clientAddress.sin_addr);
    		string msg=buffer;

    		vector<string> parsed=tokenizeString(msg,"$$$$");

    		map<string,pair<string,int> >neighbourTable=buildMap(parsed);

    		//for(int i=0;i<parsed.size();i++)printf("asdasd  %s\n",parsed[i].c_str() );

    		//printRoutingTable(neighbourTable);
    		updateRoutingTable(routingTable,neighbourTable,myneighbours,neighbourIp,myIpAddress);
    		printf("UPDATED ROUTING TABLE:\n");
    		printRoutingTable(routingTable);
    	}

    }












	return 0;
}