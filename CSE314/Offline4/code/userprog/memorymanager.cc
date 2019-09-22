#include "memorymanager.h"

#include <stdlib.h>

MemoryManager::MemoryManager(int numPages)
{
	bitMap = new BitMap(numPages);

	printf("%d NumClear\n",bitMap->NumClear() );

	processMap = new int[numPages];
	entries = new TranslationEntry* [numPages];
	iterator=0;

	this->numPages = numPages;
	

	lock = new Lock("lock of memory manager");

	processMap = new int[numPages];
	entries = new TranslationEntry*[numPages];
	this->physPageNum = numPages;

}

MemoryManager::~MemoryManager()
{
	delete bitMap;
	delete lock;
	delete processMap;
	delete entries;
}

int
MemoryManager::AllocPage()
{
	lock->Acquire();
	int ret = bitMap->Find();
	lock->Release();
	return ret;
}

void
MemoryManager::FreePage(int physPageNum)
{
	lock->Acquire();
	bitMap->Clear(physPageNum);
	lock->Release();
}

bool
MemoryManager::PageIsAllocated(int physPageNum)
{
	lock->Acquire();
	bool ret = bitMap->Test(physPageNum);
	lock->Release();
	return ret;
}

bool
MemoryManager::IsAnyPageFree()
{
	lock->Acquire();
	bool ret;
	if(bitMap->NumClear() == 0)
		ret = false;
	else
		ret = true;
	lock->Release();
	return ret;
}

int
MemoryManager::NumFreePages()
{
	lock->Acquire();
	int ret = bitMap->NumClear();
	lock->Release();
	return ret;
}


int MemoryManager::AllocPage(int processNo,TranslationEntry &entry)
{
	lock->Acquire();
	int ret = bitMap->Find();

	entries[ret] = &entry;
	processMap[ret] = processNo;

	lock->Release();
	return ret;
}

int MemoryManager::AllocByForce()
{
	//normal replacement
	// lock->Acquire();
	// int ret = rand()%(this->physPageNum);
	// lock->Release();
	// return ret;

	//lru replacement

	TranslationEntry* iterator;
	
	int ret=-1;
	int least=123456789;

	for(int i=0;i<physPageNum;i++){
		iterator = entries[i];

		if(iterator!=NULL){
			if(iterator->lruCnt<least||ret==-1){
				ret = iterator->physicalPage;
				least = iterator->lruCnt;
			}
		}
	}

	return ret;


}

int MemoryManager::getProcessNo(int physPageNum)
{
	lock->Acquire();
	int ret= processMap[physPageNum];
	lock->Release();
	return ret;
}

TranslationEntry* MemoryManager:: getTranslationEntry(int physPageNum)
{
	lock->Acquire();
	TranslationEntry* tr = entries[physPageNum];
	lock->Release();
	return tr;
}