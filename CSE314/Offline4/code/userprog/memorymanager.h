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

	TranslationEntry& getTranslationEntry(int physPageNum);
	int& getProcessId(int physPageNum);
private:
	BitMap *bitMap;
	Lock *lock;
	int numPages;

	int *processMap;
	TranslationEntry *entries;

	int iterator;
};

#endif