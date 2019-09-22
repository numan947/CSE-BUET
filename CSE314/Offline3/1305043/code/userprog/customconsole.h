#ifndef CUSTOMCONSOLE_H
#define CUSTOMCONSOLE_H
#include "console.h"
#include "synch.h"
#include "string"
#include "iostream"
using namespace std;

class CustomConsole
{
public:
	CustomConsole();
	~CustomConsole();
	string read(int numByteToRead);
	void write(string stringToPrint);

private:
	Console* globalConsole;
	Lock* lock;
};

#endif