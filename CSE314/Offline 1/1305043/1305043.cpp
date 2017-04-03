#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <queue>
#include <stdlib.h>
#include <unistd.h>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <sstream>
#include <iostream>
using namespace std;

struct gen_pass{
	int id;
	string password;
};


queue<int>ACE_Q;
sem_t ACE_Q_full;
sem_t ACE_Q_empty;
pthread_mutex_t ACE_Q_lock;


int B_Q;
sem_t B_Q_empty;
sem_t B_Q_full;
pthread_mutex_t B_Q_lock;


vector<int>duplicate_checking_Q;
sem_t duplicate_checking_Q_full;
pthread_mutex_t duplicate_checking_Q_lock;

vector<gen_pass>generated_password_Q;
sem_t generated_password_Q_empty;
pthread_mutex_t generated_password_Q_lock;

vector<gen_pass>ready_password_Q;
sem_t ready_password_Q_empty;
pthread_mutex_t ready_password_Q_lock;



void init_all()
{
	
	sem_init(&ACE_Q_empty,0,10);
	sem_init(&ACE_Q_full,0,0);
	pthread_mutex_init(&ACE_Q_lock,0);


	sem_init(&B_Q_empty,0,1);
	sem_init(&B_Q_full,0,0);
	pthread_mutex_init(&B_Q_lock,0);


	sem_init(&duplicate_checking_Q_full,0,0);
	pthread_mutex_init(&duplicate_checking_Q_lock,0);


	sem_init(&generated_password_Q_empty,0,0);
	pthread_mutex_init(&generated_password_Q_lock,0);


	sem_init(&ready_password_Q_empty,0,0);
	pthread_mutex_init(&ready_password_Q_lock,0);

}




//basically a producer
void *student_Func(void *arg)
{
	int *id = (int*)arg;
	printf("%d\n",*id);

	//queue id for ACE,PRODUCER
	sem_wait(&ACE_Q_empty); //reduce empty
	pthread_mutex_lock(&ACE_Q_lock); //lock the Q

	ACE_Q.push(*id); //queue id

	pthread_mutex_unlock(&ACE_Q_lock); //unlock the Q
	sem_post(&ACE_Q_full); //increase full





	//queue id for B,PRODUCER
	sem_wait(&B_Q_empty);
	pthread_mutex_lock(&B_Q_lock);

	B_Q=*id;

	pthread_mutex_unlock(&B_Q_lock);
	sem_post(&B_Q_full);





	//poll password from D,CONSUMER
	gen_pass pass;
	bool breaker;
	while(true) //lock: find,if not found: unlock,
				//if found : increase empty,remove item,unlock,break
	{
		pthread_mutex_lock(&ready_password_Q_lock);

		for(int i=0;i<ready_password_Q.size();i++){
			if(ready_password_Q[i].id==*id){//found
				breaker=true;
				pass=ready_password_Q[i];
				ready_password_Q.erase(ready_password_Q.begin()+i);
				break;
			}
		}
		pthread_mutex_unlock(&ready_password_Q_lock);

		if(breaker)break;

		printf("HELLO %d\n",*id);
		sleep(1.5);

		//delay??


	}


	//todo: wrap the whole code around a while??
}

void *ACE_Func(void *arg)
{
	char* myID=(char*)arg;

	
	while(true){
		//pop the id from the ACE_Q, CONSUMER
		sem_wait(&ACE_Q_full); //decrease full
		pthread_mutex_lock(&ACE_Q_lock); //lock the Q
		

		int cur=ACE_Q.front();
		ACE_Q.pop();

		printf("%c popping %d from ACE_Q\n",*myID,cur);


		pthread_mutex_unlock(&ACE_Q_lock);
		sem_post(&ACE_Q_empty);



		//push the id to duplicate checking queue, PRODUCER
		pthread_mutex_lock(&duplicate_checking_Q_lock);


		duplicate_checking_Q.push_back(cur);
		printf("%c pushing %d to duplicate_checking_Q\n",*myID,cur);

		pthread_mutex_unlock(&duplicate_checking_Q_lock);
		sem_post(&duplicate_checking_Q_full);
	}
}


void *B_Func(void *arg)
{
	char* myID=(char*)arg;

	while(true){
		
		// B gets the input from its 'Q',CONSUMER
		sem_wait(&B_Q_full);
		pthread_mutex_lock(&B_Q_lock);

		int cur=B_Q;

		pthread_mutex_unlock(&B_Q_lock);
		sem_post(&B_Q_empty);


		// now B checks for duplicate

		pthread_mutex_lock(&duplicate_checking_Q_lock);

		int pos,sid;
		int cnt=count(duplicate_checking_Q.begin(),duplicate_checking_Q.end(),cur);

		if(cnt==1){
			
			//determine the position
			pos=find(duplicate_checking_Q.begin(),duplicate_checking_Q.end(),cur)-duplicate_checking_Q.begin();
			
			//copy the id
			sid=duplicate_checking_Q[pos];
			
			//remove it from the Q
			duplicate_checking_Q.erase(duplicate_checking_Q.begin()+pos);

			//unlock the list
			pthread_mutex_unlock(&duplicate_checking_Q_lock);
		}
		else{//todo: do nothing, duplicate OR
			pthread_mutex_unlock(&duplicate_checking_Q_lock);
		}

		

		if(cnt==1){
			//generate the password
			stringstream ss;
			ss<<sid;
			string s=ss.str()+"_"+"THIS_IS_BUET";


			gen_pass pass;
			pass.id=sid;
			pass.password=s; 


			pthread_mutex_lock(&generated_password_Q_lock);
			

			generated_password_Q.push_back(pass);
			printf("%c putting generted password to generated_password_Q for %d: %s\n",*myID,sid,s.c_str());


			pthread_mutex_unlock(&generated_password_Q_lock);

		}
		
	


	}



}



void *D_Func(void *arg)
{




}








int main()
{
	pthread_t student_threads[10];
	pthread_t A,B,C,D,E;
	init_all();

	int id[10];
	for(int i=0;i<10;i++)id[i]=i;
	char teach1='A';
	char teach2='B';
	char teach3='C';
	char teach4='D';
	char teach5='E';

	pthread_create(&A,NULL,ACE_Func,(void*)&teach1);
	pthread_create(&C,NULL,ACE_Func,(void*)&teach3);
	pthread_create(&E,NULL,ACE_Func,(void*)&teach5);
	pthread_create(&B,NULL,B_Func,(void*)&teach2);
	//pthread_create(&A,NULL,ACE_Func,NULL);



	for(int i=0;i<10;i++)
		pthread_create(&student_threads[i],NULL,student_Func,(void*)&id[i]);







	//joining from launcher thread
	for(int i=0;i<10;i++)pthread_join(student_threads[i],NULL);
	return 0;
}