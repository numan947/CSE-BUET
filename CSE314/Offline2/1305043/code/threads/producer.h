#include <queue>
#include <string>
using namespace std;


class Producer
{
public:
	Producer(string name);
	~Producer();
	void produceFood(queue<int>&foodTable);
	string getName();
private:
	string name;

};