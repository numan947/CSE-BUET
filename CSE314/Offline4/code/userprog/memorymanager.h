#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H

#ifndef BITMAP_H
#include "bitmap.h"
#endif

#ifndef SYNCH_H
#include "synch.h"
#endif

class MemoryManager{
public:
	MemoryManager(int numPages);
	~MemoryManager();
	int AllocPage();
	int AllocPage(int processNo, TranslationEntry &entry);
	int AllocByForce();

	void FreePage(int physPageNum);
	bool PageIsAllocated(int physPageNum);
	bool IsAnyPageFree();
	int NumFreePages();


	int AllocPage(int processNo,TranslationEntry &entry);
	int AllocByForce();
	int getProcessNo(int physPageNum);
	TranslationEntry* getTranslationEntry(int physPageNum);
private:
	BitMap *bitMap;
	Lock *lock;

	int* processMap;
	TranslationEntry **entries;
	int physPageNum;

};

#endif