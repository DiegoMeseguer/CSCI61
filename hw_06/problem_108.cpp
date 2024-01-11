#include <iostream>
#include "binary_search_tree.h" //bag<Item> and
								//convert_to_linked_list(head, tail)
								//come from here
#include "bintree.h"
#include "node.h"
using namespace std;

int main() {

	bag<int> test; //create binary search tree
	test.insert(45);
	test.insert(9);
	test.insert(53);
	test.insert(3);
	test.insert(17);
	test.insert(53);
	test.insert(54);
	test.print_bst();

	node *head, *tail;
	head = tail = nullptr;

	test.convert_to_linked_list(head, tail);

	cout<<head<<endl;
	cout<<"Linked list has: "<<list_size(head)<<" nodes."<<endl<<endl;
	
	bag<int> z;
	z.insert(45);
	z.insert(9);
	z.insert(54);
	z.insert(3);
	z.insert(53);
	z.insert(144);
	z.insert(17);
	z.insert(200);
	z.insert(13);
	z.print_bst();

	head = tail = nullptr;

	z.convert_to_linked_list(head, tail);
	cout<<head<<endl;
	cout<<"Linked list has: "<<list_size(head)<<" nodes."<<endl;

	return 0;
}

