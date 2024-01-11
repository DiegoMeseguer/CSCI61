#include "node.h"

node::node() {
  data_ = 0;
  link_ = nullptr;
}

node::node(const int & initdata, node * initlink) {
	data_ = initdata;
	link_ = initlink;
}

int node::data() const {
	return data_;
}

node * node::link() {
	return link_;
}

//returns constant node pointer
//This is a const function - I promise the function doesn't change anything - 
//On a const node*, you can only call const functions
const node * node::link() const {
	return link_;
}

void node::set_data(const int & newdata) {
	data_ = newdata;
}

void node::set_link(node * newlink) {
	link_ = newlink;
}

//returns the number of items in the linked list
std::size_t list_size(const node * head) {
	std::size_t count = 0;

	for(const node * p = head; p!=nullptr; p = p->link()) {
		count++;
	}

	 return count;
}

// In a link list it's easier to insert at the head, than the tail.
void list_head_insert(node * & head, node * & tail, const int & value) {
	// node x(value, head);
	// head = &x;
	// x is local, and so is destroyed at the end of the function call.
	// MUST use new.
	head = new node(value, head);
	
	if(tail == nullptr) {
		tail = head;
	}
}

void list_tail_insert(node * & head, node * & tail, const int & value) {

	node * temp = new node(value, nullptr);
	tail->set_link(temp);
	tail = temp;
	if(head == nullptr)
		head = tail;

}

std::ostream & operator<<(std::ostream & out, const node * head) {
	for(const node * p = head; p!=nullptr; p = p->link()) {
		if(p->link()==nullptr)
			out<<p->data()<<std::endl;
		else
			out<<p->data()<<", ";
	}

	return out;
}

// Same with the head, removing the head in a linked list is easier to
// do than removing the tail.
void list_head_remove(node * & headptr, node * & tailptr) {
	node * temp = headptr;

	if(headptr==nullptr)    //there's nothing in the list
		return;
	else if(headptr==tailptr) {  //There's one thing in the list
		delete headptr;
		headptr = tailptr = nullptr;
	}
	else {
		//reassign head
		headptr = headptr->link();
		delete temp;
	}
}

void list_tail_remove(node * & headptr, node * & tailptr) {
	if(headptr == nullptr)  //there's nothing in the list
		return;
	else if(headptr == tailptr) {//There's one thing in the list
		delete headptr;
		headptr = tailptr = nullptr;
	}
	else {
		// reassign tail
		for(node * p = headptr; p != nullptr; p = p->link()) {
			if(p->link()->link() == nullptr) {
				p->set_link(nullptr);
				delete tailptr;
				tailptr = p;
			}
		}
	}
}

void list_remove(node * & previous, node * & tailptr) {
	//check to see if previous link is the tailptr
	if(previous->link()==tailptr) {
		list_tail_remove(previous, tailptr);
	}
	else {
		node * temp = previous->link();
		previous->set_link(previous->link()->link());
		delete temp;
	}
}

// Remember, we already have head insert and tail insert
void list_insert(node * previous, const int & value) {
  node * temp = new node(value, previous->link());
  previous->set_link(temp);
}

