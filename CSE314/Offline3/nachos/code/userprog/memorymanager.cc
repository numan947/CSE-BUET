#include "memorymanager.h"
#include <cstdio>
#include <iostream>
using namespace std;

MemoryManager::MemoryManager(int numPages, Lock* lock)
{
	this->totalPage = numPages;
	this->lock = lock;
	this->mapForMemory = new BitMap(numPages);
}

int MemoryManager::AllocPage()
{
	lock->Acquire(); //make it thread safe

	int allocatedPage = this->mapForMemory->Find(); //find one 'free' page, returns -1 on error, i.e not found

	lock->Release();

	return allocatedPage;
}


void MemoryManager::FreePage(int physPageNum)
{
	lock->Acquire();	//threadsafe, is it really needed here? Is it because, context switch can
						//happen inside the Clear() method #ask

	this->mapForMemory->Clear(physPageNum);

	lock->Release();
}


bool MemoryManager::PageIsAllocated(int physPageNum)
{
	lock->Acquire();

	bool status = this->mapForMemory->Test(physPageNum);

	lock->Release();

	return status;
}


int MemoryManager::getAvailablePages()
{
	lock->Acquire();

	int avaliable = this->mapForMemory->NumClear();

	lock->Release();

	return avaliable;

}