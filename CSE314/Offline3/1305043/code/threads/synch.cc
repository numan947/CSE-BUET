// synch.cc 
//	Routines for synchronizing threads.  Three kinds of
//	synchronization routines are defined here: semaphores, locks 
//   	and condition variables (the implementation of the last two
//	are left to the reader).
//
// Any implementation of a synchronization routine needs some
// primitive atomic operation.  We assume Nachos is running on
// a uniprocessor, and thus atomicity can be provided by
// turning off interrupts.  While interrupts are disabled, no
// context switch can occur, and thus the current thread is guaranteed
// to hold the CPU throughout, until interrupts are reenabled.
//
// Because some of these routines might be called with interrupts
// already disabled (Semaphore::V for one), instead of turning
// on interrupts at the end of the atomic operation, we always simply
// re-set the interrupt state back to its original value (whether
// that be disabled or enabled).
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "synch.h"
#include "system.h"

//----------------------------------------------------------------------
// Semaphore::Semaphore
// 	Initialize a semaphore, so that it can be used for synchronization.
//
//	"debugName" is an arbitrary name, useful for debugging.
//	"initialValue" is the initial value of the semaphore.
//----------------------------------------------------------------------

Semaphore::Semaphore(const char* debugName, int initialValue)
{
    name = debugName;
    value = initialValue;
    queue = new List<Thread*>;
}

//----------------------------------------------------------------------
// Semaphore::Semaphore
// 	De-allocate semaphore, when no longer needed.  Assume no one
//	is still waiting on the semaphore!
//----------------------------------------------------------------------

Semaphore::~Semaphore()
{
    delete queue;
}

//----------------------------------------------------------------------
// Semaphore::P
// 	Wait until semaphore value > 0, then decrement.  Checking the
//	value and decrementing must be done atomically, so we
//	need to disable interrupts before checking the value.
//
//	Note that Thread::Sleep assumes that interrupts are disabled
//	when it is called.
//----------------------------------------------------------------------

void
Semaphore::P()
{
    IntStatus oldLevel = interrupt->SetLevel(IntOff);	// disable interrupts
    
    while (value == 0) { 			// semaphore not available
	queue->Append(currentThread);		// so go to sleep
	currentThread->Sleep();
    } 
    value--; 					// semaphore available, 
						// consume its value
    
    interrupt->SetLevel(oldLevel);		// re-enable interrupts
}

//----------------------------------------------------------------------
// Semaphore::V
// 	Increment semaphore value, waking up a waiter if necessary.
//	As with P(), this operation must be atomic, so we need to disable
//	interrupts.  Scheduler::ReadyToRun() assumes that threads
//	are disabled when it is called.
//----------------------------------------------------------------------

void
Semaphore::V()
{
    Thread *thread;
    IntStatus oldLevel = interrupt->SetLevel(IntOff);

    thread = queue->Remove();
    if (thread != NULL)	   // make thread ready, consuming the V immediately
	scheduler->ReadyToRun(thread);
    value++;
    interrupt->SetLevel(oldLevel);
}

// Dummy functions -- so we can compile our later assignments 
// Note -- without a correct implementation of Condition::Wait(), 
// the test case in the network assignment won't work!


Lock::Lock(const char* debugName) 
{
    this->name = debugName;
    this->threadQueue = new List<Thread*>;
    this->isFree = true;
    this->masterThread = NULL;
}


Lock::~Lock() 
{
    delete this->threadQueue;
}


void Lock::Acquire() 
{
    IntStatus oldLevel = interrupt->SetLevel(IntOff);


    if(this->isFree == true){
        //free so give ownership of the lock

        this->isFree = false;

        this->masterThread = currentThread;

    }
    else if( isHeldByCurrentThread() ){
        //do nothing
    }
    else{
        //not free, so make'em sleep :) 
        
        //while assures rechecking of lock's free state
        while(!(this->isFree)){
            this->threadQueue->Append(currentThread);
            currentThread->Sleep();
        }
        

        //if the thread can come out of the loop,
        //then isFree is definitely true, and it's no longer inside threadQueue,so give that access
        this->isFree = false;
        this->masterThread = currentThread;
    }

    //enable interrupts
    interrupt->SetLevel(oldLevel);

}




void Lock::Release()
{
    IntStatus oldLevel = interrupt->SetLevel(IntOff);


    if(isHeldByCurrentThread()){
        //release the lock and wake one of the waiting threads
        this->isFree = true;
        this->masterThread = NULL;

        Thread* toRunThread = threadQueue->Remove();

        if(toRunThread != NULL)
            scheduler->ReadyToRun(toRunThread);
    }

    //else do nothing
    interrupt->SetLevel(oldLevel);
}



//slef explanatory method
bool Lock::isHeldByCurrentThread()
{
    return currentThread == masterThread;
}



















Condition::Condition(const char* debugName, Lock* conditionLock) 
{ 

    this->name = debugName;

    this->conditionLock = conditionLock;

    this->threadQueue = new List<Thread*>;

}



Condition::~Condition() 
{ 
    delete this->threadQueue;
}


void Condition::Wait() 
{
    IntStatus oldLevel = interrupt->SetLevel(IntOff);

    if(conditionLock->isHeldByCurrentThread()) //explicit checking
    {
        //append to waitQueue
        threadQueue->Append(currentThread);

        //release lock and go to sleep
        conditionLock->Release();
        currentThread->Sleep();

        //someone woke this thread up, so acquire lock
        conditionLock->Acquire();
    }

    interrupt->SetLevel(oldLevel);

}

void Condition::Signal() 
{ 
    IntStatus oldLevel = interrupt->SetLevel(IntOff);

    if(conditionLock->isHeldByCurrentThread()){
        Thread* threadToWakeUp = threadQueue->Remove();

        //if someone was sleeping on this condition variable it'll be woken up
        if(threadToWakeUp != NULL)
            scheduler->ReadyToRun(threadToWakeUp);
    }

    interrupt->SetLevel(oldLevel);


}
void Condition::Broadcast() 
{
    IntStatus oldLevel = interrupt->SetLevel(IntOff);

    if(conditionLock->isHeldByCurrentThread())
    {
        Thread *threadToWakeUp=NULL;

        while(!(threadQueue->IsEmpty())){
            threadToWakeUp = threadQueue->Remove();
            scheduler->ReadyToRun(threadToWakeUp);
        }
    }

    interrupt->SetLevel(oldLevel);
}


