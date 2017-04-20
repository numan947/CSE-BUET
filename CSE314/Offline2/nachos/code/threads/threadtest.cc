// threadtest.cc 
//	Simple test case for the threads assignment.
//
//	Create several threads, and have them context switch
//	back and forth between themselves by calling Thread::Yield, 
//	to illustrate the inner workings of the thread system.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.
//
// Parts from Copyright (c) 2007-2009 Universidad de Las Palmas de Gran Canaria
//

#include "copyright.h"
#include "system.h"
#include "synch.h"
//----------------------------------------------------------------------
// SimpleThread
// 	Loop 10 times, yielding the CPU to another ready thread 
//	each iteration.
//
//	"name" points to a string with a thread name, just for
//      debugging purposes.
//----------------------------------------------------------------------

// Lock *myLock;

// void
// SimpleThread(void* name)
// {
//     // Reinterpret arg "name" as a string
//     char* threadName = (char*)name;
    
//     // If the lines dealing with interrupts are commented,
//     // the code will behave incorrectly, because
//     // printf execution may cause race conditions.
//     for (int num = 0; num < 10; num++) {
//         //IntStatus oldLevel = interrupt->SetLevel(IntOff);
// 	   myLock->Acquire();
//        printf("*** thread %s acquired lock %s\n",threadName,myLock->getName());
//        printf("*** thread %s looped %d times\n", threadName, num);
//        printf("*** thread %s about to release lock %s\n",threadName,myLock->getName());
// 	   myLock->Release();
//         //interrupt->SetLevel(oldLevel);
//         //currentThread->Yield();
//     }
//     //IntStatus oldLevel = interrupt->SetLevel(IntOff);
//     myLock->Acquire();
//     printf(">>> Thread %s has finished\n", threadName);
//     //interrupt->SetLevel(oldLevel);
//     myLock->Release();
// }

//----------------------------------------------------------------------
// ThreadTest
// 	Set up a ping-pong between several threads, by launching
//	ten threads which call SimpleThread, and finally calling 
//	SimpleThread ourselves.
//----------------------------------------------------------------------

#include "producer.h"
#include "consumer.h"
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <sstream>

using namespace std;


queue<int>foodTable; //let maxsize be 30
Lock *myLock;
Condition *producerWaitCondition;
Condition *consumerWaitCondition;
int maxsize;

void producerFunction(void *producer)
{
    Producer *myProducer = (Producer*)producer;

    string name = myProducer->getName();
    cout<< name <<" hearing loud and clear!\n"<<endl;

    while(true)
    {
        myLock->Acquire(); //acquire lock to the table

        cout<<myProducer->getName()<<" ACQUIRED access to the foodTable"<<endl;

        while(foodTable.size()>=maxsize)
        { //wait until there's some space for the food
            cout<<myProducer->getName()<<" is going to SLEEP"<<endl;
            producerWaitCondition->Wait();
        }

        myProducer->produceFood(foodTable);
        Delay(1);

        //wake up the waiting consumers
        consumerWaitCondition->Signal();

        cout<<myProducer->getName()<<" RELEASING access to the foodTable\n\n\n"<<endl;

        myLock->Release();

        //do some random stuff
        Delay(1);
        int randomLoop=rand()%4000;
        for(int i=0;i<randomLoop;i++){
        //random loop
         }
     }


}



void consumerFunction(void *consumer)
{
    Consumer *myConsumer = (Consumer*)consumer;

    cout<< myConsumer->getName()<<" hearing loud and clear!\n"<<endl;        

    while(true){
        myLock->Acquire(); //acquire the lock to the table


        cout<<myConsumer->getName()<<" ACQUIRED access to foodTable"<<endl;
        while(foodTable.empty())
        { // wait until there's some food
            cout<<myConsumer->getName()<<" is going to SLEEP"<<endl;
            consumerWaitCondition->Wait();
        }
        myConsumer->consumeFood(foodTable); //pass the queue for consuming
        Delay(1);
        //wake up the waiting producers
        producerWaitCondition->Signal();

        //done consuming so release lock
        cout<<myConsumer->getName()<<" RELEASING access to foodTable\n\n\n"<<endl;
        myLock->Release();

        //do some random stuff
        Delay(1);
        int randomLoop=rand()%4000;
        for(int i=0;i<randomLoop;i++){
        //random loop
         }
     }

}



string intToStr(int x)
{
    stringstream ss;
    ss<<x;
    return ss.str();
}


void
ThreadTest()
{
    DEBUG('t', "Entering SimpleTest");

    int prodNum, consNum;
    cout<<"Enter number of Producers and Consumers: <Producers><space><Consumers><max size of foodTable>"<<endl;
    
    cin>>prodNum>>consNum>>maxsize;

    // myLock = new Lock("owLock");

    // for ( int k=1; k<=10; k++) {
    //   char* threadname = new char[100];
    //   sprintf(threadname, "Hilo %d", k);
    //   Thread* newThread = new Thread (threadname);
    //   newThread->Fork (SimpleThread, (void*)threadname);
    // }
    
    // SimpleThread( (void*)"Hilo 0");

    myLock = new Lock("producer_consumer_critical_region_lock");
    producerWaitCondition = new Condition("Producers Wait in this queue",myLock);
    consumerWaitCondition = new Condition("Consumers Wait in this queue",myLock);

    Producer* p;
    Consumer* c;
    Thread* newThread;
/*
    for(int i = 0 ; i < prodNum ; i++){
        p = NULL;
        newThread = NULL;

        string name = "Producer #"+intToStr(i+1);
        // cout<<name<<endl;
        p = new Producer(name); 
        
        newThread = new Thread(name.c_str());
        newThread->Fork(producerFunction,(void*)p);
        
        prodNum--;

    }


    for(int i = 0 ; i < consNum ; i++){

        c = NULL;
        newThread = NULL;

        string name = "Consumer #"+intToStr(i+1);
        // cout<<name<<endl;
        c = new Consumer(name); 
        
        newThread = new Thread(name.c_str());
        newThread->Fork(consumerFunction,(void*)c);

    }
*/
    int i=0;
    while(consNum || prodNum){
        
        if(prodNum){
            p = NULL;
            newThread = NULL;

            string name = "Producer #"+intToStr(i+1);
            // cout<<name<<endl;
            p = new Producer(name); 
            
            newThread = new Thread(name.c_str());
            newThread->Fork(producerFunction,(void*)p);
            
            prodNum--;
        }

        if(consNum){

            c = NULL;
            newThread = NULL;

            string name = "Consumer #"+intToStr(i+1);
            // cout<<name<<endl;
            c = new Consumer(name); 
            
            newThread = new Thread(name.c_str());
            newThread->Fork(consumerFunction,(void*)c);

            consNum--;
        }

        i++;

    }








}



