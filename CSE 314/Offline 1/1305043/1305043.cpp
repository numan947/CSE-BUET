#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <queue>
#include <stdlib.h>
#include <unistd.h>
#include <vector>
#include <string>
using namespace std;

struct gen_pass{
	int id;
	string password;
};


vector<int>ACE_Q;
sem_t ACE_Q_full;
sem_t ACE_Q_empty;
pthread_mutex_t ACE_Q_lock;


int B_Q;
sem_t B_Q_empty;
pthread_mutex_t B_Q_lock;

vector<int>duplicate_checking_Q;
sem_t duplicate_checking_Q_empty;
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
	pthread_mutex_init(&B_Q_lock,0);


	sem_init(&duplicate_checking_Q_empty,0,0);
	pthread_mutex_init(&duplicate_checking_Q_lock,0);


	sem_init(&generated_password_Q_empty,0,0);
	pthread_mutex_init(&generated_password_Q_lock,0);


	sem_init(&ready_password_Q_empty,0,0);
	pthread_mutex_init(&ready_password_Q_lock,0);

}







int main()
{

}