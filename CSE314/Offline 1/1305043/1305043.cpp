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
#define MAX 50000
using namespace std;

int requestCounter;

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
pthread_mutex_t duplicate_checking_Q_lock;

vector<gen_pass>generated_password_Q;
pthread_mutex_t generated_password_Q_lock;

// vector<gen_pass>ready_password_Q;
// pthread_mutex_t ready_password_Q_lock;

int s_req_pass;
sem_t s_req_pass_empty;
sem_t s_req_pass_full;
pthread_mutex_t s_req_pass_lock;



string s_pass;
sem_t s_pass_empty;
sem_t s_pass_full;
pthread_mutex_t s_pass_lock;



void init_all()
{
	
	sem_init(&ACE_Q_empty,0,10);
	sem_init(&ACE_Q_full,0,0);
	pthread_mutex_init(&ACE_Q_lock,0);


	sem_init(&B_Q_empty,0,1);
	sem_init(&B_Q_full,0,0);
	pthread_mutex_init(&B_Q_lock,0);


	pthread_mutex_init(&duplicate_checking_Q_lock,0);


	sem_init(&s_req_pass_empty,0,1);
	sem_init(&s_req_pass_full,0,0);
	pthread_mutex_init(&s_req_pass_lock,0);


	sem_init(&s_pass_empty,0,1);
	sem_init(&s_pass_full,0,0);
	pthread_mutex_init(&s_pass_lock,0);

}




//basically a producer
void *student_Func(void *arg)
{
	int *id = (int*)arg;
	

	int t=0;
	while(t<requestCounter){ //#WRAP AROUND WITH A WHILE
	

	printf("I am student %d REQUEST NO %d\n\n",*id,++t);
	
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
	string pass;
	bool breaker=false;
	while(true) //ask for password using s_req_pass,providing the sid,PRODUCER
				//
	{
		sem_wait(&s_req_pass_empty); //reduce empty, so that other gets blocked out
		pthread_mutex_lock(&s_req_pass_lock); //lock the variable before accessing

		s_req_pass=*id;

		pthread_mutex_unlock(&s_req_pass_lock);
		sem_post(&s_req_pass_full); //increase full, so that D can wake up

		
		sem_wait(&s_pass_full); // now we wait for password, CONSUMER
		pthread_mutex_lock(&s_pass_lock); //lock before accessing

		pass=s_pass;

		pthread_mutex_unlock(&s_pass_lock);
		sem_post(&s_pass_empty);

		if(pass!="NOT_FOUND")break;

	}
	

	//sleep before asking again
	//sleep(3);

	} //#wrap around with a while

	printf("EXITING: %d\n\n",*id);
	//todo: wrap the whole code around a while??
}



void *D_Func(void *arg)
{
	char *myID=(char*)arg;
	printf("HELLO ");

	while(true){

		//CONSUMER
		sem_wait(&s_req_pass_full); //block until someone asks for a question
		pthread_mutex_lock(&s_req_pass_lock);//lock before accessing
		
		int roll=s_req_pass;
		printf("%c : PASSWORD REQUEST found from %d\n",*myID,roll);

		pthread_mutex_unlock(&s_req_pass_lock);
		sem_post(&s_req_pass_empty);

		string pass;
		pass="NOT_FOUND";

		pthread_mutex_lock(&generated_password_Q_lock);
		for(int i=0;i<generated_password_Q.size();i++)
			if(generated_password_Q[i].id==roll){
				pass=generated_password_Q[i].password;
				break;
			}

		pthread_mutex_unlock(&generated_password_Q_lock);



		//PRODUCER
		sem_wait(&s_pass_empty);
		pthread_mutex_lock(&s_pass_lock);

		s_pass=pass;
		printf("%c : SENDING PASSWORD for %d, it's %s\n",*myID,roll,pass.c_str());


		pthread_mutex_unlock(&s_pass_lock);
		sem_post(&s_pass_full);

	}

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

		printf("%c popping %d from ACE_Q\n\n",*myID,cur);


		pthread_mutex_unlock(&ACE_Q_lock);
		sem_post(&ACE_Q_empty);



		//push the id to duplicate checking queue, PRODUCER
		pthread_mutex_lock(&duplicate_checking_Q_lock);


		duplicate_checking_Q.push_back(cur);
		printf("%c pushing %d to duplicate_checking_Q\n\n",*myID,cur);

		pthread_mutex_unlock(&duplicate_checking_Q_lock);
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


		// now B checks for duplicate and if not generates password and queues, PRODUCER
		int pos,cnt;

		while(true){
			pthread_mutex_lock(&duplicate_checking_Q_lock);
			cnt=count(duplicate_checking_Q.begin(),duplicate_checking_Q.end(),cur);
			if(cnt)break;
			pthread_mutex_unlock(&duplicate_checking_Q_lock);
		}
		if(cnt==1){
			
			//determine the position
			pos=find(duplicate_checking_Q.begin(),duplicate_checking_Q.end(),cur)-duplicate_checking_Q.begin();
			
			//remove it from the Q
			duplicate_checking_Q.erase(duplicate_checking_Q.begin()+pos);

			//unlock the list
			pthread_mutex_unlock(&duplicate_checking_Q_lock);
		}
		else{//todo: do nothing, duplicate OR
			if(cnt==0)printf("WHY AM I DISCARDED?? # %d\n\n",cur);
			pthread_mutex_unlock(&duplicate_checking_Q_lock);
		}

		

		if(cnt==1){
			//generate the password
			stringstream ss;
			ss<<cur;
			string s=ss.str()+"_"+"THIS_IS_BUET";


			gen_pass pass;
			pass.id=cur;
			pass.password=s; 


			pthread_mutex_lock(&generated_password_Q_lock);
			

			generated_password_Q.push_back(pass);
			printf("%c putting generted password to generated_password_Q for %d: %s\n\n",*myID,cur,s.c_str());


			pthread_mutex_unlock(&generated_password_Q_lock);

		}

	}



}








// FOR NORMAL CHECKING

int main()
{
	int totalStudent;
	printf("Input total student: <totalStudent> <requestCounter>\n\n");
	scanf("%d %d",&totalStudent,&requestCounter);


	pthread_t student_threads[MAX];
	pthread_t A,B,C,D,E;
	init_all();

	int id[MAX];
	for(int i=0;i<totalStudent;i++)id[i]=i;
	char teach1='A';
	char teach2='B';
	char teach3='C';
	char teach4='D';
	char teach5='E';

	pthread_create(&A,NULL,ACE_Func,(void*)&teach1);
	pthread_create(&C,NULL,ACE_Func,(void*)&teach3);
	pthread_create(&E,NULL,ACE_Func,(void*)&teach5);
	pthread_create(&B,NULL,B_Func,(void*)&teach2);
	pthread_create(&D,NULL,D_Func,(void*)&teach4);



	for(int i=0;i<totalStudent;i++)
		pthread_create(&student_threads[i],NULL,student_Func,(void*)&id[i]);

	//joining from launcher thread
	pthread_join(A,NULL);
	pthread_join(B,NULL);
	pthread_join(C,NULL);
	pthread_join(D,NULL);
	pthread_join(E,NULL);
	for(int i=0;i<totalStudent;i++)pthread_join(student_threads[i],NULL);
	return 0;
}


//FOR DUPLICATE CHECKING
/*
int main()
{
	int totalStudent;
	printf("Input total student: <totalStudent> <requestCounter>\n\n");
	scanf("%d %d",&totalStudent,&requestCounter);


	pthread_t student_threads[MAX];
	pthread_t A,B,C,D,E;
	init_all();

	int id[MAX];
	for(int i=0;i<totalStudent;i++)id[i]=i;
	char teach1='A';
	char teach2='B';
	char teach3='C';
	char teach4='D';
	char teach5='E';

	pthread_create(&A,NULL,ACE_Func,(void*)&teach1);
	pthread_create(&C,NULL,ACE_Func,(void*)&teach3);
	pthread_create(&E,NULL,ACE_Func,(void*)&teach5);
	pthread_create(&B,NULL,B_Func,(void*)&teach2);
	pthread_create(&D,NULL,D_Func,(void*)&teach4);



	for(int i=0;i<totalStudent+20;i++){
		int pp=rand()%totalStudent;
		pthread_create(&student_threads[i],NULL,student_Func,(void*)&id[pp]);
	}
	
	//joining from launcher thread
	pthread_join(A,NULL);
	pthread_join(B,NULL);
	pthread_join(C,NULL);
	pthread_join(D,NULL);
	pthread_join(E,NULL);
	for(int i=0;i<totalStudent+20;i++)pthread_join(student_threads[i],NULL);
	return 0;
}*/