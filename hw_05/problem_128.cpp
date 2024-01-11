#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
#include "statistics_hashing_table.h"
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
	tractor arr[792];

	for (int i = 0; i < 792; ++i) { //Create list of tractors.
		arr[i].key = random_key_gen();
		arr[i].brand = random_tractor_name_gen();
	}
	
	for (int i = 0; i < 792; ++i) //Insert tractors into hash table.
		tractorTable.insert(arr[i]);

	//Some formatting
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);

	cout<<"Records in hash table: "<<tractorTable.size()<<endl;
	cout<<"Statistical Data about Tractor Hash Table."<<endl;
	cout<<"The Table is under "<<tractorTable.load_factor()<<"% load.\n";
	cout<<"The TOTAL # of records examined when searching all records"
		<<" in the table is: "<<tractorTable.total_records_examined()<<endl;
	cout<<"The MAX # of records examined for any particular search"
		<<" in the table is: "<<tractorTable.max_records_examined()<<endl;
	cout<<"The AVERAGE # of records examined during a successful search"
		<<" is: "<<tractorTable.avg_records_examined()<<endl;

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

