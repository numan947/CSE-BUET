#include "customconsole.h"
	static Semaphore *consoleReadAvail;
	static Semaphore *consoleWriteDone;
	static void ConsoleReadAvail(void* arg);
	static void ConsoleWriteDone(void* arg);

CustomConsole::CustomConsole()
{
	this->globalConsole = new Console(NULL,NULL,ConsoleReadAvail,ConsoleWriteDone,NULL);
	consoleReadAvail = new Semaphore("console read avail", 0);
	consoleWriteDone = new Semaphore("console write done", 0);
	this->lock = new Lock("console lock");
}
CustomConsole::~CustomConsole(){
	delete globalConsole;
	delete consoleReadAvail;
	delete consoleWriteDone;
	delete lock;
}

void static ConsoleReadAvail(void* arg){
	consoleReadAvail->V();
}
void static ConsoleWriteDone(void* arg){
	consoleWriteDone->V(); 
}

string CustomConsole::read(int numByteToRead)
{
	lock->Acquire();
	char ch;
	string res = "";
	while(numByteToRead){
		consoleReadAvail->P();
		ch=globalConsole->GetChar();
		res+=ch;
		numByteToRead--;
	}


	lock->Release();
	return res;
}

void CustomConsole:: write(string stringToPrint)
{
	lock->Acquire();
	string toWrite = ""+stringToPrint;

	for(int i=0;i<toWrite.size();i++){
		globalConsole->PutChar(toWrite[i]);
		consoleWriteDone->P();
	}

	lock->Release();


}