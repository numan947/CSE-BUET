#include <queue>
#include <string>
using namespace std;


class Consumer
{
public:
	Consumer(string name);
	~Consumer();
	void consumeFood(queue<int>&foodTable);
	string getName();
private:
	string name;

};