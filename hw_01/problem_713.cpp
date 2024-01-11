#include <iostream>
#include <string>
#include <stack>
using namespace std;

template<class T>
bool is_stack_equal(stack<T>& left, stack<T>& right);

int main() {
	
	//Tests
	stack<int> a, b;

	a.push(4);
	a.push(101);
	a.push(12);
	a.push(34);
	a.push(23);
	a.push(6);

	b.push(4);
	b.push(101);
	b.push(12);
	b.push(34);
	b.push(23);
	b.push(6);

	cout<<is_stack_equal(a, b)<<endl;

	// Print stack a and b to show that they are still the same
	while(!a.empty()) {
		cout<<a.top()<<", ";
		a.pop();
	}
	cout<<endl;

	while(!b.empty()) {
		cout<<b.top()<<", ";
		b.pop();
	}
	cout<<endl;

	//Tests
	stack<string> c, d;

	c.push("Orc");
	c.push("Human");
	c.push("Undead");	
	c.push("Night Elf");

	d.push("Orc");
	d.push("Human");
	d.push("Blood Elf");	
	d.push("Night Elf");

	cout<<is_stack_equal(c, d)<<endl;

	// Print stack c and d to show that they are still the same
	while(!c.empty()) {
		cout<<c.top()<<", ";
		c.pop();
	}
	cout<<endl;

	while(!d.empty()) {
		cout<<d.top()<<", ";
		d.pop();
	}
	cout<<endl;
	
	return 0;
}

template<class T>
bool is_stack_equal(stack<T>& left, stack<T>& right) {

	bool result = true;

	stack<T> temp_left;
	stack<T> temp_right;	

	//Compares sizes
	if (left.size() != right.size())
		return false;

	//Compare contents
	while(!left.empty()) {
		temp_left.push(left.top());
		temp_right.push(right.top());
		
		if(temp_left.top() != temp_right.top())
			result = false;
			// we can't return false like above because we still need to
			// restore the original stacks

		left.pop();
		right.pop();
	}
	
	//Regenerate stacks
	while(!temp_left.empty()) {
		left.push(temp_left.top());
		right.push(temp_right.top());
		temp_left.pop();
		temp_right.pop();
	}

	return result;
}

