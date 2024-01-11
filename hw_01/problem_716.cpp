#include <iostream>
#include <string>
#include "stack1.h"
using namespace std;
using namespace main_savitch_7A;

int main() {
	
	stack<int> a;

	a.push(98);
	a.push(101);
	a.push(12);
	a.push(34);
	a.push(23);
	a.push(6);	

	a.flip();

	while(!a.empty()) {
		cout<<a.top()<<", ";
		a.pop();
	}
	cout<<endl;	

	stack<string> c;

	c.push("Orc");
	c.push("Human");
	c.push("Undead");	
	c.push("Night Elf");

	c.flip();

	while(!c.empty()) {
		cout<<c.top()<<", ";
		c.pop();
	}
	cout<<endl;	

	return 0;
}

