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


void
ExceptionHandler(ExceptionType which)
{
    int type = machine->ReadRegister(2);
    

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
			}
				

    } 
    else {
	printf("Unexpected user mode exception %d %d\n", which, type);
	ASSERT(false);
    }
}



void HandleExecSysCall()
{
	int namePosInMem = machine->ReadRegister(4); //get the address of the name start

	char *nameOftheFile = new char[MAX];
	char ch;

	bool isOk = machine->ReadMem(namePosInMem,1,(int*)&ch); //read one Byte at a time

	if(!isOk)return;

	int size=0;

	while(ch!=0 && size < MAX){

		nameOftheFile[size++] = (char)ch;

		namePosInMem++;

		isOk = machine->ReadMem(namePosInMem,1,(int*)&ch);

		if(!isOk)return;
	}

	nameOftheFile[size] = '\0';

	OpenFile *executable = fileSystem->Open(nameOftheFile);


	if(executable != NULL){

		AddrSpace *space = new AddrSpace(executable);

		Thread *thread = new Thread("FORKED THREAD");

		thread->space = space;

		int x = processIdTable->Alloc(thread);

		if(x!=-1){
			machine->WriteRegister(2,x); //return the new process id
			thread->Fork(myThread,NULL);
		}



	}




}


void UpdateProgramCounter(){

		int curPC, nextPC, prevPC;

		// Read PCs
		prevPC = machine->ReadRegister(PrevPCReg);
		curPC = machine->ReadRegister(PCReg);
		nextPC = machine->ReadRegister(NextPCReg);

		// Update PCs
		prevPC = curPC;
		curPC = nextPC;
		nextPC = nextPC + 4;	// PC incremented by 4 in MIPS

		// Write back PCs
		machine->WriteRegister(PrevPCReg, prevPC);
		machine->WriteRegister(PCReg, curPC);
		machine->WriteRegister(NextPCReg, nextPC);
	}

