// exception.cc 
//	Entry point into the Nachos kernel from user programs.
//	There are two kinds of things that can cause control to
//	transfer back to here from user code:
//
//	syscall -- The user code explicitly requests to call a procedure
//	in the Nachos kernel.  Right now, the only function we support is
//	"Halt".
//
//	exceptions -- The user code does something that the CPU can't handle.
//	For instance, accessing memory that doesn't exist, arithmetic errors,
//	etc.  
//
//	Interrupts (which can also cause control to transfer from user
//	code into the Nachos kernel) are handled elsewhere.
//
// For now, this only handles the Halt() system call.
// Everything else core dumps.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "syscall.h"
#include "table.h"
#include "string"
using namespace std;
//----------------------------------------------------------------------
// ExceptionHandler
// 	Entry point into the Nachos kernel.  Called when a user program
//	is executing, and either does a syscall, or generates an addressing
//	or arithmetic exception.
//
// 	For system calls, the following is the calling convention:
//
// 	system call code -- r2
//		arg1 -- r4
//		arg2 -- r5
//		arg3 -- r6
//		arg4 -- r7
//
//	The result of the system call, if any, must be put back into r2. 
//
// And don't forget to increment the PC before returning. (Or else you'll
// loop making the same system call forever!
//
//	"which" is the kind of exception.  The list of possible exceptions 
//	are in machine.h.
//----------------------------------------------------------------------

#define MAX 105

extern Table *processIdTable;


void UpdateProgramCounter();
void HandleExecSysCall();
void HandleExitSysCall();
void HandleReadSysCall();
void HandleWriteSysCall();



void myThread(void* args)
{
	currentThread->space->InitRegisters();
	currentThread->space->RestoreState();

	machine->Run();

	ASSERT(false);
}

void
ExceptionHandler(ExceptionType which)
{
    int type = machine->ReadRegister(2);
    Lock *mylock =  new Lock("SYS LOCK");
    
    mylock->Acquire();
    if (which == SyscallException) {
			

			switch(type){
				case SC_Halt:
					DEBUG('a', "Shutdown, initiated by user program.\n");
	   				interrupt->Halt();
    				break;

    			case SC_Exec:
    				HandleExecSysCall();
    				UpdateProgramCounter();
    				break;
    			case SC_Exit:
    				HandleExitSysCall();
    				break;
    			case SC_Read:
    				printf("SYSCALL READ CALLED\n");
    				HandleReadSysCall();
    				UpdateProgramCounter();
    				break;
    			case SC_Write:
    				printf("SYSCALL WRITE CALLED\n");
    				HandleWriteSysCall();
    				UpdateProgramCounter();
    				break;
    			
			}
			printf("\n\nINIFINITE LOOP CHECKER\n\n");
				

    } 
    else {
	printf("Unexpected user mode exception %d %d\n", which, type);
	ASSERT(false);
    }
mylock->Release();
}



void HandleExecSysCall()
{
	int namePosInMem = machine->ReadRegister(4); //get the address of the name start

	
	char *nameOftheFile = new char[MAX];


	int size=0;

	do
	{
		bool stat = machine->ReadMem(namePosInMem + size, 1, (int*)&nameOftheFile[size]);
		
		if(!stat)return;
	}while(nameOftheFile[size++] != '\0' && size<MAX);


	OpenFile *executable = fileSystem->Open(nameOftheFile);

	printf("name of the file: %s\n",nameOftheFile );


	AddrSpace *space = new AddrSpace(executable);

	Thread *thread = new Thread("FORKED THREAD");

	int x = -1;
	if(executable != NULL){



		thread->space = space;

		x= processIdTable->Alloc(thread);

		if(x!=-1){
			machine->WriteRegister(2,x); //return the new process id
			thread->Fork(myThread,NULL);
		}
		else{
			machine->WriteRegister(2,-1);
		} 
	}
	else{
			machine->WriteRegister(2,-1);
		}
	
	if(x!=-1)processIdTable->Release(x);


}



void HandleExitSysCall()
{

	int exitStatus = machine->ReadRegister(4); //get the address of the name start

	printf("SYSTEM CALL EXIT STATUS: %d -- ThreadName %s \n",exitStatus,currentThread->getName());
	

	currentThread->Finish();
}

void HandleReadSysCall()
{
	int arg1 = machine->ReadRegister(4); //where do I store
	int arg2 = machine->ReadRegister(5); //how many do I read
	int arg3 = machine->ReadRegister(6); //from where do I read


	string fromConsole = customConsole->read(arg2);

	int totalRead = fromConsole.size();

	printf("JUST READ FROM CONSOLE -- %s\n",fromConsole.c_str() );

	for(int i=0;i<totalRead;i++){
		int a = fromConsole[i];
		if(!machine->WriteMem(arg1+i,sizeof(char),a)){
			machine->WriteRegister(2,-1); //failure
			return;
		}
	}

	machine->WriteRegister(2,totalRead);

}


void HandleWriteSysCall()
{
	int arg1 = machine->ReadRegister(4); //from where do I read
	int arg2 = machine->ReadRegister(5); //how many do I read
	int arg3 = machine->ReadRegister(6); //from where do I write



	string toWrite="";
	
	for(int i=0;i<arg2;i++){
		int tmp;
		if(!machine->ReadMem(arg1+i,sizeof(char), &tmp)){
			machine->WriteRegister(2,-1);
			return;//failure
		}

		toWrite+=(char)tmp;

	}


	printf("WRITING TO CONSOLE -- %d byte -- %s\n",arg2, toWrite.c_str());
	customConsole->write(toWrite);

	machine->WriteRegister(2,0);//success

}

void UpdateProgramCounter(){

		int curPC=-1, nextPC=-1, prevPC=-1;


		//printf("PC FOR THREAD: %s -- %d %d %d \n",currentThread->getName(),prevPC,curPC,nextPC);
		// Read PCs
		prevPC = machine->ReadRegister(PrevPCReg);
		curPC = machine->ReadRegister(PCReg);
		nextPC = machine->ReadRegister(NextPCReg);
		//printf("PC FOR THREAD: %s -- %d %d %d \n",currentThread->getName(),prevPC,curPC,nextPC);
		// Update PCs
		prevPC = curPC;
		curPC = nextPC;
		nextPC = nextPC + 4;	// PC incremented by 4 in MIPS
		//printf("PC FOR THREAD: %s -- %d %d %d \n",currentThread->getName(),prevPC,curPC,nextPC);
		// Write back PCs
		machine->WriteRegister(PrevPCReg, prevPC);
		machine->WriteRegister(PCReg, curPC);
		machine->WriteRegister(NextPCReg, nextPC);
		//printf("PC FOR THREAD: %s -- %d %d %d \n",currentThread->getName(),prevPC,curPC,nextPC);
	}

