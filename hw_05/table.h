#ifndef TABLE_H
#define TABLE_H

#include <iostream>
#include <cassert>
#include <cstdlib>

/* 
T must have a public member variable of type int
called key and this member holds the key of each
record. Each key must be a non-negative int and two
different records cannot have the same key
*/
template <class T>
class table {
public:
	//MEMBER CONSTANTS
	static const std::size_t CAPACITY = 811;

	//CONSTRUCTOR
	table();

	//MEMBER FUNCTIONS
	void insert(const T & entry);
	void remove(int key);

	//CONSTANT MEMBER FUNCTIONS
	void find(int key, bool & found, T & result) const;
	bool is_present(int key) const;
	std::size_t size() const;
	
private:
	//MEMBER VARIABLES
	T data[CAPACITY];
	std::size_t used;

	//MEMBER CONSTANTS
	static const int NEVER_USED = -1;
	static const int PREVIOUSLY_USED = -2;

	//MEMBER FUNCTIONS
	std::size_t hash(int key) const;
	std::size_t next_index(std::size_t index) const;
	void find_index(int key, bool & found, std::size_t & i) const;
	bool never_used(std::size_t index) const;
	bool is_vacant(std::size_t index) const;
};

template<class T>
table<T>::table() {
	used = 0;

	for (std::size_t i = 0; i < CAPACITY; ++i)
		data[i].key = NEVER_USED;
}

template<class T>
void table<T>::insert(const T & entry) {
	assert(entry.key >= 0);

	bool already_present; //True if entry.key is already in the table.
	std::size_t index; // data[index] is location for the new entry.

	//Set index so that data[index] is the spot to place the new entry.
	find_index(entry.key, already_present, index);

	//If the key wasn't already there, then find the location for the new entry.
	if (!already_present) {
		assert(size( ) < CAPACITY);
		index = hash(entry.key);

		while (!is_vacant(index))
			index = next_index(index);

		++used;
	}

	data[index] = entry;
}

template<class T>
void table<T>::remove(int key) {
	assert(key >= 0);

	bool found; //True if key occurs somewhere in the table.
	std::size_t index; //Spot where data[index].key = key

	find_index(key, found, index);

	if (found) {
		// The key was found, so remove this record and reduce used by 1.
		data[index].key = PREVIOUSLY_USED; //Indicates a spot that's no longer in use.
		--used;
	}
}

template<class T>
std::size_t table<T>::size() const {
	return used;
}

template<class T>
void table<T>::find(int key, bool & found, T & result) const {
	assert(key >= 0);

	std::size_t index;

	find_index(key, found, index);

	if(found)
		result = data[index];
}

template<class T>
bool table<T>::is_present(int key) const {
	assert(key >= 0);

	bool found;
	std::size_t index;

	find_index(key, found, index);

	return found;
}

template<class T>
std::size_t table<T>::hash(int key) const {
	return (key % CAPACITY);
}

template<class T>
std::size_t table<T>::next_index(std::size_t index) const {
	return ((index + 1) % CAPACITY);
}

template<class T>
void table<T>::find_index(int key, bool & found, std::size_t & i) const {

	std::size_t count; //Number of entries that have been examined

	count = 0;
	i = hash(key);

	while((count < CAPACITY) && (data[i].key != NEVER_USED) && (data[i].key != key)) {
		++count;
		i = next_index(i);
	}

	found = (data[i].key == key);
}

template<class T>
bool table<T>::never_used(std::size_t index) const {
	return (data[index].key == NEVER_USED);
}

template<class T>
bool table<T>::is_vacant(std::size_t index) const {
	return (data[index].key == NEVER_USED || data[index].key == PREVIOUSLY_USED);

}



#endif //TABLE_H

