// addrspace.cc 
//	Routines to manage address spaces (executing user programs).
//
//	In order to run a user program, you must:
//
//	1. link with the -N -T 0 option 
//	2. run coff2noff to convert the object file to Nachos format
//		(Nachos object code format is essentially just a simpler
//		version of the UNIX executable object code format)
//	3. load the NOFF file into the Nachos file system
//		(if you haven't implemented the file system yet, you
//		don't need to do this last step)
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "addrspace.h"
#include "synch.h"
#include "memorymanager.h"
#include <algorithm>
#include <string>
#include <sstream>
using namespace std;

extern MemoryManager *memoryManager;
extern Lock *memoryLock;


//----------------------------------------------------------------------
// SwapHeader
// 	Do little endian to big endian conversion on the bytes in the 
//	object file header, in case the file was generated on a little
//	endian machine, and we're now running on a big endian machine.
//----------------------------------------------------------------------

static void 
SwapHeader (NoffHeader *noffH)
{
	noffH->noffMagic = WordToHost(noffH->noffMagic);
	noffH->code.size = WordToHost(noffH->code.size);
	noffH->code.virtualAddr = WordToHost(noffH->code.virtualAddr);
	noffH->code.inFileAddr = WordToHost(noffH->code.inFileAddr);
	noffH->initData.size = WordToHost(noffH->initData.size);
	noffH->initData.virtualAddr = WordToHost(noffH->initData.virtualAddr);
	noffH->initData.inFileAddr = WordToHost(noffH->initData.inFileAddr);
	noffH->uninitData.size = WordToHost(noffH->uninitData.size);
	noffH->uninitData.virtualAddr = WordToHost(noffH->uninitData.virtualAddr);
	noffH->uninitData.inFileAddr = WordToHost(noffH->uninitData.inFileAddr);
}

//----------------------------------------------------------------------
// AddrSpace::AddrSpace
// 	Create an address space to run a user program.
//	Load the program from a file "executable", and set everything
//	up so that we can start executing user instructions.
//
//	Assumes that the object code file is in NOFF format.
//
//	First, set up the translation from program memory to physical 
//	memory.  For now, this is really simple (1:1), since we are
//	only uniprogramming, and we have a single unsegmented page table
//
//	"executable" is the file containing the object code to load into memory
//----------------------------------------------------------------------

AddrSpace::AddrSpace(OpenFile *executable)
{
    NoffHeader noffH;


    unsigned int i, j, size;

    executable->ReadAt((char *)&noffH, sizeof(noffH), 0);
    if ((noffH.noffMagic != NOFFMAGIC) && 
		(WordToHost(noffH.noffMagic) == NOFFMAGIC))
    	SwapHeader(&noffH);
    ASSERT(noffH.noffMagic == NOFFMAGIC);

// how big is address space?
    size = noffH.code.size + noffH.initData.size + noffH.uninitData.size 
			+ UserStackSize;	// we need to increase the size
						// to leave room for the stack
    numPages = divRoundUp(size, PageSize);
    size = numPages * PageSize;

   // ASSERT(numPages <= NumPhysPages);		// check we're not trying
						// to run anything too big --
						// at least until we have
						// virtual memory

    DEBUG('a', "Initializing address space, num pages %d, size %d\n", 
					numPages, size);
// first, set up the translation 
    pageTable = new TranslationEntry[numPages];
    for (i = 0; i < numPages; i++) {
    	pageTable[i].virtualPage = i;	// for now, virtual page # = phys page #
    	//pageTable[i].physicalPage = i;
        // if(memoryManager->IsAnyPageFree() == true)
        //     pageTable[i].physicalPage = memoryManager->AllocPage();
        // else
        // {
        //     for(j = 0; j < i; ++j)
        //         memoryManager->FreePage(pageTable[j].physicalPage);
        //     ASSERT(false);
        // }

        pageTable[i].physicalPage = -1;
    	pageTable[i].valid = false;
    	pageTable[i].use = false;
    	pageTable[i].dirty = false;
    	pageTable[i].readOnly = false;  // if the code segment was entirely on 
                    					// a separate page, we could set its 
                    					// pages to be read-only
    }
    
    // zero out the entire address space, to zero the unitialized data segment 
    // and the stack segment
    //bzero(machine->mainMemory, size);
   /* memoryLock->Acquire();
    for(i = 0; i < numPages; ++i)
    {
        bzero(&machine->mainMemory[pageTable[i].physicalPage * PageSize], PageSize);
    }

    
    // then, copy in the code and data segments into memory
    unsigned int numPagesForCode = divRoundUp(noffH.code.size, PageSize);
    DEBUG('a', "Initializing code segment, at 0x%x, size %d\n", 
		noffH.code.virtualAddr, noffH.code.size);
    for(i = 0; i < numPagesForCode; ++i)
    {
        executable->ReadAt(&(machine->mainMemory[ pageTable[i].physicalPage * PageSize ]),
                            PageSize, 
                            noffH.code.inFileAddr + i * PageSize);
    }

    unsigned int numPagesForData = divRoundUp(noffH.initData.size, PageSize);

    DEBUG('a', "Initializing data segment, at 0x%x, size %d\n", 
        noffH.initData.virtualAddr, noffH.initData.size);
    for(j = numPagesForCode; j < numPagesForCode + numPagesForData; ++j)
    {
        executable->ReadAt(&(machine->mainMemory[ pageTable[i].physicalPage * PageSize ]),
                            PageSize, 
                            noffH.initData.inFileAddr + (j - numPagesForCode) * PageSize);
    }
    memoryLock->Release();*/

    printf("TOTAL SWAP MEMORY NEEDED--- %d Bytes\nTotal Machine Memory Available--- %d Bytes\n\n",size,MemorySize);
    printf("NOFFHEADER CHECK -- CodeSeg %d %d %d InitSeg %d %d %d  UninitSeg %d %d %d\n",noffH.code.virtualAddr,noffH.code.inFileAddr,noffH.code.size,
                                                noffH.initData.virtualAddr,noffH.initData.inFileAddr,noffH.initData.size,
                                                noffH.uninitData.virtualAddr,noffH.uninitData.inFileAddr,noffH.uninitData.size);

    this->memberNoffH = noffH;  
    this->localExecutable = executable; //numan947
    
    printf("Member NOFFHEADER CHECK -- CodeSeg %d %d %d InitSeg %d %d %d  UninitSeg %d %d %d\n",memberNoffH.code.virtualAddr,memberNoffH.code.inFileAddr,memberNoffH.code.size,
                                                memberNoffH.initData.virtualAddr,memberNoffH.initData.inFileAddr,memberNoffH.initData.size,
                                                memberNoffH.uninitData.virtualAddr,memberNoffH.uninitData.inFileAddr,memberNoffH.uninitData.size);

    

    //creating swapFile
    stringstream ss;
    ss<<currentThread->id;
    string swapFileName = "swap"+ss.str()+".swp";

    printf("SWAP FILE for process %d is %s\n",currentThread->id,swapFileName.c_str());

    if(!fileSystem->Create(swapFileName.c_str(),size)){
        printf("SwapFile of same name exists, so deleting and recreating\n");
        fileSystem->Remove(swapFileName.c_str());
        bool x = fileSystem->Create(swapFileName.c_str(),size);
        ASSERT(x!=false);
    }

    //initializing swapMap
    this->swapMap = new BitMap(numPages);

}

//----------------------------------------------------------------------
// AddrSpace::~AddrSpace
// 	Dealloate an address space.  Nothing for now!
//----------------------------------------------------------------------

AddrSpace::~AddrSpace()
{
   delete pageTable;
   delete localExecutable;
}

//----------------------------------------------------------------------
// AddrSpace::InitRegisters
// 	Set the initial values for the user-level register set.
//
// 	We write these directly into the "machine" registers, so
//	that we can immediately jump to user code.  Note that these
//	will be saved/restored into the currentThread->userRegisters
//	when this thread is context switched out.
//----------------------------------------------------------------------

void
AddrSpace::InitRegisters()
{
    int i;

    for (i = 0; i < NumTotalRegs; i++)
	machine->WriteRegister(i, 0);

    // Initial program counter -- must be location of "Start"
    machine->WriteRegister(PCReg, 0);	

    // Need to also tell MIPS where next instruction is, because
    // of branch delay possibility
    machine->WriteRegister(NextPCReg, 4);

   // Set the stack register to the end of the address space, where we
   // allocated the stack; but subtract off a bit, to make sure we don't
   // accidentally reference off the end!
    machine->WriteRegister(StackReg, numPages * PageSize - 16);
    DEBUG('a', "Initializing stack register to %d\n", numPages * PageSize - 16);
}

//----------------------------------------------------------------------
// AddrSpace::SaveState
// 	On a context switch, save any machine state, specific
//	to this address space, that needs saving.
//
//	For now, nothing!
//----------------------------------------------------------------------

void AddrSpace::SaveState() 
{}

//----------------------------------------------------------------------
// AddrSpace::RestoreState
// 	On a context switch, restore the machine state so that
//	this address space can run.
//
//      For now, tell the machine where to find the page table.
//----------------------------------------------------------------------

void AddrSpace::RestoreState() 
{
    machine->pageTable = pageTable;
    machine->pageTableSize = numPages;
}



int AddrSpace::loadIntoFreePage(int faultingPageAddr, int physicalPageNo)
{
    int vpn = faultingPageAddr/PageSize;

    pageTable[vpn].physicalPage = physicalPageNo;
    pageTable[vpn].valid =true;

    int virAdd = vpn*PageSize;

    bzero(machine->mainMemory + (pageTable[vpn].physicalPage*PageSize),PageSize);


    int startCodeSegment = memberNoffH.code.virtualAddr;
    int endCodeSegment = memberNoffH.code.virtualAddr + memberNoffH.code.size;

    int startDataSegment = memberNoffH.initData.virtualAddr;
    int endDataSegment = memberNoffH.initData.virtualAddr + memberNoffH.initData.size;

    int startUDataSegment = memberNoffH.uninitData.virtualAddr;
    int endUDataSegment = memberNoffH.uninitData.virtualAddr + memberNoffH.uninitData.size;


    int totalWrittenBytes = 0;

    bool debug = false; //for debugging

    //load into memory byte by byte so that, we don't need to do the extra checking of whether the segment
    //takes the full page or not ,i.e. no checking for 'code segment, data segment being multiple of PageSize'
    while(totalWrittenBytes < PageSize){
        int currentAddress  = virAdd + totalWrittenBytes; //current byte address

        if(memberNoffH.code.size > 0 && currentAddress < endCodeSegment && currentAddress >= startCodeSegment)
        {
            if(debug)printf("Loading into free page-- faultingPageAddr, CODE   %d  %d %d %d\n",faultingPageAddr,this->memberNoffH.code.virtualAddr,this->memberNoffH.code.inFileAddr,this->memberNoffH.code.size);

            loadMemoryToPage(vpn,totalWrittenBytes,memberNoffH.code.inFileAddr,currentAddress - startCodeSegment);
        }

        else if(memberNoffH.initData.size > 0 && currentAddress < endDataSegment && currentAddress >= startDataSegment)
        {
            if(debug)printf("Loading into free page-- faultingPageAddr, DATA   %d  %d %d %d\n",faultingPageAddr,this->memberNoffH.initData.virtualAddr,this->memberNoffH.initData.inFileAddr,this->memberNoffH.initData.size);

            loadMemoryToPage(vpn,totalWrittenBytes,memberNoffH.initData.inFileAddr,currentAddress - startDataSegment);
        }

        else if(memberNoffH.uninitData.size > 0 && currentAddress < endUDataSegment && currentAddress >= startUDataSegment)
        {
              if(debug)printf("Loading into free page-- faultingPageAddr, DATA   %d  %d %d %d\n",faultingPageAddr,this->memberNoffH.uninitData.virtualAddr,this->memberNoffH.uninitData.inFileAddr,this->memberNoffH.uninitData.size);

              loadMemoryToPage(vpn,totalWrittenBytes,memberNoffH.uninitData.inFileAddr,currentAddress - startUDataSegment);
        } 

        totalWrittenBytes++;
    }


    return 0;
}

void AddrSpace::loadMemoryToPage(int vpn, int currentByteOffSet, int inFileAddr, int inFileAddrOffset)
{
    this->localExecutable->ReadAt(&(machine->mainMemory[(pageTable[vpn].physicalPage * PageSize) + currentByteOffSet]),
                            1,inFileAddr + inFileAddrOffset);
}