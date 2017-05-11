#include "table.h"




Table::Table(int size)
{
	this->managerOfVoidPointers = new BitMap(size);
	this->lock = new Lock("Table Lock");
}

Table::~Table()
{
	delete managerOfVoidPointers;
	delete lock;
}

int Table::Alloc(void *object)
{
	this->lock->Acquire();

	int positionAllcated = managerOfVoidPointers->Find();

	this->lock->Release();

	if(positionAllcated!=-1){
		arrayOfVoidPointers[ positionAllcated ] = object; 
	}

	return positionAllcated;

}

void* Table::Get(int index)
{
	this->lock->Acquire();

	bool isSet = this->managerOfVoidPointers->Test(index);

	this->lock->Release();

	if(isSet)
		return arrayOfVoidPointers[ index ];

	return 0; 
}


void Table::Release(int index)
{
	this->lock->Acquire();

	this->managerOfVoidPointers->Clear(index);

	this->lock->Release();
	
}
