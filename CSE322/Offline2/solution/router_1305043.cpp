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
#define INF 123456789

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

	printf("\n\ndestination--------nexthop--------cost\n\n");

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

			//case1: neighbour's nexthop neighbour, so need to update
			//case2: neighbour's nexthop is not neighbour, 
			//		 but we can reach neighbour in less cost via updated link,so update
			int oldcost;
			if((it->second.first==it->first)||((it->second.second>=x.linkcost)&&(x.linkstatus==1))){
				it->second.first=updateCostIp; //nexthop change, cause we need to handle case2
				int oldcost=it->second.second; //old cost to reach this neighbour
				it->second.second=x.linkcost; //new cost to reach this neighbour
				
				// as our cost to the next hop changed we need to update the routing table
				// for those destinations whose next hop is this neighbour
				for(it=routingTable.begin();it!=routingTable.end();it++){
					if(it->second.first==updateCostIp && it->first!=updateCostIp){
						if(x.linkstatus)it->second.second+=(x.linkcost-oldcost);
						//else it->second.second=INF;// cost update if deadlinks
					}
				}
			}

			//cout<<updateCostIp<<" "<<it->first<<" "<<it->second.first<<" "<<it->second.second<<"\n";
			//printf("Updating cost\n");
			//printRoutingTable(routingTable);//dummy print;remove later
		}
}



void makeLinkDead(string neighbourIp,vector<linkToNeighbour>&neighbours,map<string,pair<string,int> >&routingTable)
{

	linkToNeighbour x;
	for(int i=0;i<neighbours.size();i++)
		if(neighbourIp==neighbours[i].neighbourIp){
			neighbours[i].linkstatus=0;
			x=neighbours[i];
			break;
		}

	map<string,pair<string,int> >::iterator it;

	for(it=routingTable.begin();it!=routingTable.end();it++){
		if(it->second.first==neighbourIp)it->second.second=INF;
	}

	//printf("making %s DEAD\n",neighbourIp.c_str());
}


void makeLinkAlive(string neighbourIp,vector<linkToNeighbour>&neighbours,map<string,pair<string,int> >&routingTable)
{
	
	//printf("making %s ALIVE\n",neighbourIp.c_str());
	linkToNeighbour x;
	for(int i=0;i<neighbours.size();i++)
		if(neighbourIp==neighbours[i].neighbourIp){
			neighbours[i].linkstatus=1;
			x=neighbours[i];
			break;
		}

	map<string,pair<string,int> >::iterator it=routingTable.find(neighbourIp);


	//only  update if we can reach that neighbour in less/equal cost via this link
	if(it->second.second>=x.linkcost){
		it->second.first=it->first; //nexthop is neighbour now
		int oldcost=it->second.second;
		it->second.second=x.linkcost; //updated cost


		//update those destination cost, whose nexthop is this neighbour,as we've updated the cost
		//to reach the neighbour, those should be updated accordingly
		for(it=routingTable.begin();it!=routingTable.end();it++){
			if(it->second.first==neighbourIp && it->first!=neighbourIp &&it->second.second!=INF)
				it->second.second+=(x.linkcost-oldcost);
		}
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
	//printf("serialized string is %s\n",serialized.c_str());

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
		
		//printf("just sent %d to %s\n",totalBytesSent,ip.c_str());//remove later
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
		if(it2==neighbourTable.end())continue;//this case should arise only for the neighbour itself
		string neighbour_nexthop=it2->second.first;
		int neighbour_cost=it2->second.second;

		it2=routingTable.find(neighbour);
		int cost_to_go_to_neighbour=it2->second.second;

		// cout<<dest<<" CCCC ";
		// cout<<current_nexthop<<" AAAAAA "<<neighbour_nexthop<<" BBBBBB "<<endl;  


		int d=(neighbour_cost==INF) ? INF:(cost_to_go_to_neighbour+neighbour_cost);

		//split horizon || forced update
		if((neighbour_nexthop!=myIpAddress && (current_cost>=d))||(neighbour==current_nexthop)){
			
			it1->second.first=neighbour;
			it1->second.second=d;
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


void sendMessage(map<string,pair<string,int> >&routingTable,char* buffer,int socketDescriptor,string myIpAddress)
{

   	char ip1[20],ip2[20];unsigned char lengthBuff[2];

	//get the ips from the buffer
	inet_ntop(AF_INET,buffer+4,ip1,sizeof(ip1));
	inet_ntop(AF_INET,buffer+8,ip2,sizeof(ip2));

	//get the cost from the buffer
	lengthBuff[0]=buffer[12];//lsb
	lengthBuff[1]=buffer[13];//msb
	int length=lengthBuff[0]|(lengthBuff[1]<<8);

	//printf("%d sadasdasdasdasda\n",length);
	//printf("%d %d\n",buffer[12],buffer[13]);

	string message="";
	for(int i=14;i<14+length;i++)
		message+=buffer[i];



	char newbuffer[8];
	strcpy(newbuffer,"frwd");
	
	//printf("aaaaaaaaaa->>>%s\n",newbuffer);

	string tmp=ip2;
	tmp+=".";
	vector<string>parsedAddress=tokenizeString(tmp,".");

	//for(int i=0;i<parsedAddress.size();i++)cout<<parsedAddress[i]<<endl;

	for(int i=4;i<8;i++)newbuffer[i]=strToInt(parsedAddress[i-4]);
	newbuffer[8]='\0';
	
	string msg=newbuffer;
	msg+=(unsigned char)lengthBuff[0];
	msg+=(unsigned char)lengthBuff[1];
	msg+=message;

	map<string,pair<string,int> >::iterator it=routingTable.find(ip2);

	if(it==routingTable.end()||it->second.second==INF){
		printf("NO PATH TO %s FROM %s\n",ip2,ip1);
		return;
	}



	struct sockaddr_in remoteAddress;
	remoteAddress.sin_family=AF_INET;
	remoteAddress.sin_port=htons(4747);
	string ip;


	ip=it->second.first;

	//printf("WILL SEND MESSAGE TO %s\n",ip.c_str());
	inet_pton(AF_INET,ip.c_str(),&remoteAddress.sin_addr);
	
	int totalBytesSent=sendto(socketDescriptor,msg.c_str(), 1024, 0, (struct sockaddr*) &remoteAddress, sizeof(sockaddr_in));
	
	//printf("just sent %d to %s\n",totalBytesSent,ip.c_str());//remove later


	printf("%s PACKET FORWARDED TO %s (PRINTED BY %s)\n",message.c_str(),ip.c_str(),myIpAddress.c_str());

}



void forwardMessage(map<string,pair<string,int> >&routingTable,char* buffer,int socketDescriptor,string myIpAddress)
{

   	char ipToSend[20];
   	unsigned char lengthBuff[2];

	//get the ips from the buffer
	inet_ntop(AF_INET,buffer+4,ipToSend,sizeof(ipToSend));

	lengthBuff[0]=buffer[8];//lsb
	lengthBuff[1]=buffer[9];//msb
	int length=lengthBuff[0]|(lengthBuff[1]<<8);

	//printf("%d %d\n",buffer[8],buffer[9]);

	//printf("HElooppppppppppppppppppppp %d\n",length);

	string message="";
	for(int i=10;i<10+length;i++)
		message+=buffer[i];

	if(ipToSend==myIpAddress){
		printf("%s PACKET REACHED DESTINATION (PRINTED BY %s)\n",message.c_str(),myIpAddress.c_str());
		return;
	}



	char newbuffer[8];
	strcpy(newbuffer,"frwd");
	
	//printf("aaaaaaaaaa->>>%s\n",newbuffer);

	string tmp=ipToSend;
	tmp+=".";
	vector<string>parsedAddress=tokenizeString(tmp,".");

	for(int i=0;i<parsedAddress.size();i++)cout<<parsedAddress[i]<<endl;

	for(int i=4;i<8;i++)newbuffer[i]=strToInt(parsedAddress[i-4]);
	newbuffer[8]='\0';
	
	string msg=newbuffer;
	msg+=(unsigned char)lengthBuff[0];
	msg+=(unsigned char)lengthBuff[1];
	msg+=message;

	map<string,pair<string,int> >::iterator it=routingTable.find(ipToSend);

	if(it==routingTable.end()||it->second.second==INF){
		printf("NO PATH TO %s FROM %s\n",ipToSend,myIpAddress.c_str());
		return;
	}



	struct sockaddr_in remoteAddress;
	remoteAddress.sin_family=AF_INET;
	remoteAddress.sin_port=htons(4747);
	string ip;


	ip=it->second.first;

	inet_pton(AF_INET,ip.c_str(),&remoteAddress.sin_addr);
	
	int totalBytesSent=sendto(socketDescriptor,msg.c_str(), 1024, 0, (struct sockaddr*) &remoteAddress, sizeof(sockaddr_in));
	
	//printf("just sent %d to %s\n",totalBytesSent,ip.c_str());//remove later


	printf("%s PACKET FORWARDED TO %s (PRINTED BY %s)\n",message.c_str(),ip.c_str(),myIpAddress.c_str());

}








int main(int argc, char *argv[])
{
	map<string,pair<string,int> >routingTable;
	vector<linkToNeighbour>myneighbours;
	map<string,int>neighbourNonResponsiveCounter;
	vector<string>responsiveNeighbours;


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
			neighbourNonResponsiveCounter[n2]=0;

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
			neighbourNonResponsiveCounter[n1]=0;

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
    	//frwd -- sent from neighbour to forward a message
    	//cost -- sent from driver
    	//send -- sent from driver
    	//tabl -- sent from neightbout with the routing table
    	//show -- sent from driver
    	//printf("command is %s\n",command );
    	//printf("%s\n",buffer);






    	if(!strcmp(command,"clk ")){
    		for(int i=0;i<myneighbours.size();i++){
    			string ip=myneighbours[i].neighbourIp;

    			if(count(responsiveNeighbours.begin(),responsiveNeighbours.end(),ip)==0){
    				//didn't response last time, so increase counter
    				neighbourNonResponsiveCounter[ip]++;
    				//printf("%s didn't respond\n",ip.c_str());
    			}
    		}
    		responsiveNeighbours.clear();

    		for(int i=0;i<myneighbours.size();i++){
    			string ip=myneighbours[i].neighbourIp;
    			
    			if(neighbourNonResponsiveCounter[ip]==3){
    				//neighbour dead, so update linkstatus in myneighbours and cost in routing table
    				//myneighbours[i].linkstatus=0; //dead link
    				makeLinkDead(ip,myneighbours,routingTable);
    			}
    		}





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
    		responsiveNeighbours.push_back(neighbourIp);
    		if(neighbourNonResponsiveCounter[neighbourIp]>=3)makeLinkAlive(neighbourIp,myneighbours,routingTable);
    		neighbourNonResponsiveCounter[neighbourIp]=0;

    		string msg=buffer;
    		vector<string> parsed=tokenizeString(msg,"$$$$");
    		map<string,pair<string,int> >neighbourTable=buildMap(parsed);

    		//for(int i=0;i<parsed.size();i++)printf("asdasd  %s\n",parsed[i].c_str() );

    		//printRoutingTable(neighbourTable);
    		updateRoutingTable(routingTable,neighbourTable,myneighbours,neighbourIp,myIpAddress);
    		//printf("UPDATED ROUTING TABLE:\n");
    		//printRoutingTable(routingTable);
    	}
    	else if(!strcmp(command,"send")){
    		sendMessage(routingTable,buffer,socketDescriptor,myIpAddress);
    	}
    	else if(!strcmp(command,"frwd")){
    		forwardMessage(routingTable,buffer,socketDescriptor,myIpAddress);
    	}

    }

	return 0;
}