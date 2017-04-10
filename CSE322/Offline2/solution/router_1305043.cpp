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
#define INF -999999

using namespace std;




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




void updateCost(map<string,pair<string,int> >&routingTable,string myIpAddress,char* buffer)
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
		
		map<string,pair<string,int> >::iterator it=routingTable.find(ip2);;
		
		if(it!=routingTable.end()){
			it->second.second=cost;
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

void sendToNeighbours(vector<string>neighbours,string msgToSend,int socketDescriptor)
{
	int totalBytesSent;
	struct sockaddr_in remoteAddress;
	remoteAddress.sin_family=AF_INET;
	remoteAddress.sin_port=htons(4747);


	for(int i=0;i<neighbours.size();i++){
		inet_pton(AF_INET,neighbours[i].c_str(),&remoteAddress.sin_addr);
		totalBytesSent=sendto(socketDescriptor,msgToSend.c_str(), 1024, 0, (struct sockaddr*) &remoteAddress, sizeof(sockaddr_in));
		
		printf("just sent %d to %s\n",totalBytesSent,neighbours[i].c_str());//remove later
	}

}


int main(int argc, char *argv[])
{
	map<string,pair<string,int> >routingTable;
	vector<string>myneighbours;
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
			myneighbours.push_back(n2);
		}
		//check if second router is ME, hence neighbour
		else if(n2==myIpAddress){
			//printf("Hello2\n");
			routingTable[n1]=make_pair(n1,cost);
			myneighbours.push_back(n1);
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
    		updateCost(routingTable,myIpAddress,buffer);
    	}
    	else if(!strcmp(command,"tabl")){
    		string neighbourIp=inet_ntoa(clientAddress.sin_addr);
    		string msg=buffer;

    		vector<string> parsed=tokenizeString(msg,"$$$$");

    		


    	}



    
    }












	return 0;
}