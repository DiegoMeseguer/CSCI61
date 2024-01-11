#ifndef BINARY_SEARCH_TREE_H 
#define BINARY_SEARCH_TREE_H
#include <cstdlib>     // Provides NULL and size_t
#include "bintree.h"   // Provides binary_tree_node and related functions
#include <cassert>
#include "node.h"

using namespace std;

template <class Item>
class bag {
public:

	// TYPEDEFS
	typedef std::size_t size_type;

	// CONSTRUCTORS and DESTRUCTOR
	bag( );
	bag(const bag& source);
	~bag( );

	// MODIFICATION FUNCTIONS
	size_type erase(const Item& target);
	bool erase_one(const Item& target);
	void insert(const Item& entry);
	void operator +=(const bag& addend);
	void operator =(const bag& source);
	void convert_to_linked_list(node*& head, node*& tail);

	template <class X>
	friend void join(bag& top, bag& left, bag& right);


	// CONSTANT FUNCTIONS
	size_type size( ) const;
	size_type count(const Item& target) const;
	void print_bst() const;

private:
	binary_tree_node<Item> *root_ptr; // Root pointer of binary search tree
	void insert_all(binary_tree_node<Item>* addroot_ptr);
};



// NONMEMBER functions for the bag<Item> template class
template <class Item>
bag<Item> operator +(const bag<Item>& b1, const bag<Item>& b2);


template <class Item>
void join(bag<Item>& top, bag<Item>& left, bag<Item>& right) {
	top.root_ptr->set_left(left.root_ptr);
	top.root_ptr->set_right(right.root_ptr);
	left.root_ptr = NULL;
	right.root_ptr = NULL;
}

//helper function for convert_to_linked_list()
template <class Item>
void tree_to_linked(binary_tree_node<Item> *root, node*& head, node*& tail) {
	if (root != NULL) {
		tree_to_linked(root->left(), head, tail);
		list_tail_insert(head, tail, root->data());
		tree_to_linked(root->right(), head, tail);
	}
}

//Implementation of the class

template <class Item>
void bag<Item>::convert_to_linked_list(node*& head, node*& tail) {
	tree_to_linked(root_ptr, head, tail);
	return;
}

template <class Item> //default constructor
bag<Item>::bag() {
	root_ptr = NULL;
}

template <class Item> //copy constructor
bag<Item>::bag(const bag<Item>& source) {
	root_ptr = tree_copy(source.root_ptr);
}

template <class Item> //destructor
bag<Item>::~bag( ) {
	tree_clear(root_ptr);
}

template <class Item> //asignment operator
void bag<Item>::operator =(const bag<Item>& source) {
	if (root_ptr == source.root_ptr)
		return;

	tree_clear(root_ptr);
	root_ptr = tree_copy(source.root_ptr);
}


template <class Item>
typename bag<Item>::size_type bag<Item>::size( ) const {
	return tree_size(root_ptr);
}

template <class Item>
typename bag<Item>::size_type bag<Item>::count(const Item& target) const {
	size_type answer = 0;
	binary_tree_node<Item> *cursor;

	cursor = root_ptr;

	while(cursor != NULL) {
		if(target == cursor->data()) {
			answer += 1;
			cursor = cursor->left();
		}
		else if(target < cursor->data())
			cursor = cursor->left();
		else if(target > cursor->data())
			cursor = cursor->right();
	}

	return answer;
}

template <class Item>
void bag<Item>::insert(const Item& entry) {
	binary_tree_node<Item> *cursor;
	bool done = false;

	if (root_ptr == NULL) { // Add the first node of the binary search tree:
		root_ptr = new binary_tree_node<Item>(entry);
		return;
	}

	// Move down the tree and add a new leaf:
	cursor = root_ptr;

	while(!done) {
		if(entry <= cursor->data()) {
			if (cursor->left() == NULL) { //check left pointer
				cursor->set_left(new binary_tree_node<Item>(entry));
				done = true;
			}
			else
				cursor = cursor->left();
		}
		else {
			if (cursor->right() == NULL) {
				cursor->set_right(new binary_tree_node<Item>(entry));
				done = true;
			}
			else
				cursor = cursor->right();
		}
	}
}


template <class Item>
bool bst_remove(binary_tree_node<Item>*& root_ptr, const Item& target) {
	binary_tree_node<Item> *oldroot_ptr;
	
	if (root_ptr == NULL) { //Also takes care of the case where we
				//try to delete something that is not there.
		return false;
	}

	if (target < root_ptr->data( )) {   
		// Continue looking in the left subtree
		// Note: Any change made to root_ptr->left by this recursive
		// call will change the actual left pointer (because the return
		// value from the left() member function is a reference to the
		// actual left pointer.
		return bst_remove(root_ptr->left( ), target);
	}


	if (target > root_ptr->data( )) {   
		// Continue looking in the right subtree
		// Note: Any change made to root_ptr->right by this recursive
		// call will change the actual right pointer (because the return
		// value from the right() member function is a reference to the
		// actual right pointer.
		return bst_remove(root_ptr->right( ), target);
	}
	
	if (root_ptr->left( ) == NULL) {   
		// Target was found and there is no left subtree, so we can
		// remove this node, making the right child be the new root.
		// We are going to use a root shift in three steps. Also works
		//if right side is NULL
		oldroot_ptr = root_ptr;
		root_ptr = root_ptr->right( );
		delete oldroot_ptr;
		return true;
	}
	
	// If code reaches this point, then we must remove the target from
	// the current node. We'll actually replace this target with the
	// maximum item in our left subtree.
	// Note: Any change made to root_ptr->left by bst_remove_max
	// will change the actual left pointer (because the return
	// value from the left() member function is a reference to the
	// actual left pointer.
	bst_remove_max(root_ptr->left( ), root_ptr->data( ));
	return true;
}


template <class Item>
void bst_remove_max(binary_tree_node<Item>*& root_ptr, Item& removed) {
// Precondition: root_ptr is a root pointer of a non-empty binary 
// search tree.
// Postcondition: The largest item in the binary search tree has been
// removed, and root_ptr now points to the root of the new (smaller) 
// binary search tree. The reference parameter, removed, has been set 
// to a copy of the removed item.
	binary_tree_node<Item> *oldroot_ptr;


	if(root_ptr->right() == NULL) {
		removed = root_ptr->data();
		oldroot_ptr = root_ptr;
		root_ptr = root_ptr->left();
		delete oldroot_ptr;
	}
	else {
		bst_remove_max(root_ptr->right(), removed);
	}
}


template <class Item>
bool bag<Item>::erase_one(const Item& target) {
	return bst_remove(root_ptr, target);
}



template <class Item>
void bag<Item>::operator +=(const bag<Item>& addend) {
	if (root_ptr == addend.root_ptr) {
	//have to be carefull about adding the BST to itself
		bag<Item> copy = addend;
		insert_all(copy.root_ptr);
	}
	else
		insert_all(addend.root_ptr);
}

template <class Item>
bag<Item> operator +(const bag<Item>& b1, const bag<Item>& b2) {
	bag<Item> answer = b1;
	answer += b2;
	return answer;
}

template <class Item>
void bag<Item>::insert_all(binary_tree_node<Item>* addroot_ptr) {
	// Precondition: addroot_ptr is the root pointer of a binary search tree that
	// is separate for the binary search tree of the bag that activated this
	// method.
	// Postcondition: All the items from the addroot_ptr's binary search tree
	// have been added to the binary search tree of the bag that activated this
	// method.

	if (addroot_ptr != NULL) {
		insert(addroot_ptr->data( ));
		insert_all(addroot_ptr->left( ));
		insert_all(addroot_ptr->right( ));
	}
}

template <class Item>
typename bag<Item>::size_type bag<Item>::erase(const Item& target) {

	size_type counter = 0;

	while(erase_one(target))
		counter++;

	return counter;
}

template <class Item>
void bag<Item>::print_bst() const {
	size_t indentation = 0;
	print(root_ptr, indentation);
}


#endif

