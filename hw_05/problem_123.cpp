#include <iostream>
#include <cstdlib>
#include <ctime>
#include "double_hashing_table.h"
using namespace std;

struct tractor {
	int key;
	string brand;
};

int random_key_gen();
string random_tractor_name_gen();

int main() {

	srand(time(0));

	table<tractor> tractorTable;
	tractor arr[622];

	for (int i = 0; i < 622; ++i) { //Create list of tractors.
		arr[i].key = random_key_gen();
		arr[i].brand = random_tractor_name_gen();
	}
	
	for (int i = 0; i < 622; ++i) //Insert tractors into hash table.
		tractorTable.insert(arr[i]);

	//Test functions
	cout<<tractorTable.size()<<endl;

	tractor lamborghini = {32, "Lamborghini"};
	tractor empty = {0, "none"};
	bool isThere;
	tractorTable.insert(lamborghini);
	tractorTable.find(lamborghini.key, isThere, empty);
	cout<<isThere<<endl;
	cout<<empty.key<<endl;
	cout<<empty.brand<<endl;
	tractorTable.remove(lamborghini.key);

	cout<<tractorTable.size()<<endl;

	return 0;
}

int random_key_gen() {
	return ((rand() % 500000) + 1);
}

string random_tractor_name_gen() {
	int stringLength = (rand() % 12) + 4;
	string tractorName = "";
	string alphabet{"abcdefghijklmnopqrstuvwxyz"};

	for (int i = 0; i < stringLength; ++i)
		tractorName.push_back(alphabet[rand() % 27]);
	
	return tractorName;
}

