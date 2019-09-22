#include "synch.h"
#include "bitmap.h"

class MemoryManager
{
public:
	MemoryManager(int numPages, Lock* lock);
	~MemoryManager();

	int AllocPage();

	void FreePage(int physPageNum);

	bool PageIsAllocated(int physPageNum);

	int GetAvailablePages();
	
private:
	Lock* lock;
	int totalPage;
	BitMap* mapForMemory;


};