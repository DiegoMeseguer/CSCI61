#include <iostream>
#include "node2.h"
#include "queue_circular_linked.h"
using namespace std;
using namespace main_savitch_8C;

/* PROGRAMMING PROJECT 8.6
Test of circular linked list queue
*/

int main() {

	queue<int> intNodeQueue, copyInt;
	queue<string> strNodeQueue, copyStr;

	intNodeQueue.push(20);
	intNodeQueue.push(30);
	intNodeQueue.push(144);
	intNodeQueue.push(170);
	cout<<"Front of Int Queue: "<<intNodeQueue.front()<<endl;

	copyInt = intNodeQueue;
	cout<<"Front of Copy Int Queue: "<<copyInt.front()<<endl;

	intNodeQueue.push(144);
	cout<<"Size of Int Queue: "<<intNodeQueue.size()<<endl;
	intNodeQueue.pop();
	intNodeQueue.pop();
	intNodeQueue.pop();
	cout<<"Front of Int Queue: "<<intNodeQueue.front()<<endl;

	strNodeQueue.push("Orc");
	strNodeQueue.push("Human");
	strNodeQueue.push("Undead");
	strNodeQueue.push("Arc");
	cout<<"Front of String Queue: "<<strNodeQueue.front()<<endl;

	copyStr = strNodeQueue;
	cout<<"Front of Copy String Queue: "<<copyStr.front()<<endl;

	strNodeQueue.pop();
	strNodeQueue.pop();
	cout<<"Size of String Queue: "<<strNodeQueue.size()<<endl;
	strNodeQueue.push("Night Elf");
	cout<<"Front of String Queue: "<<strNodeQueue.front()<<endl;
	cout<<"Size of String Queue: "<<strNodeQueue.size()<<endl;

	return 0;
}

