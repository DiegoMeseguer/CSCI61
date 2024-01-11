#include <iostream>
#include <cassert>
#include <vector>
using namespace std;

int binary_guess_game(vector<int> arr, int start, int end);
int game_setup(vector<int>& lista);
void new_line();

int main() {

	vector<int> guessList;
	int lastIndex;

	lastIndex = game_setup(guessList);
	binary_guess_game(guessList, 0, lastIndex);

	return 0;
}

int binary_guess_game(vector<int> arr, int start, int end){
	int middle;
	string answer;

	if (start == end) {
		cout<<"Your number is: "<<arr[start]<<endl;
		return arr[start];
	}
	else {
		middle = (start + end) / 2;
		cout<<"Is your number greater than "<<arr[middle]<<"?\n";
		cin>>answer;
		new_line();

		if((answer[0] == 'Y') || (answer[0] == 'y'))
			return(binary_guess_game(arr, middle + 1, end));
		else
			return(binary_guess_game(arr, start, middle));
	}
}

int game_setup(vector<int>& lista) {
	int n = 100;
	string answer;

	cout<<"Please think of a whole number from 1 to n (default n = 100).\n";
	cout<<"Change upper limit n? (Yes/No): \n";
	cin>>answer;
	new_line();

	if((answer[0] == 'Y') || (answer[0] == 'y')){
		cout<<"Enter new upper limit: \n";
		cin>>n;
		assert(n >= 1);
	}

	//Generates list of integers for guess game
	for (int i = 0; i < n; ++i)
		lista.push_back(i + 1);

	//Returns last of index of vector
	return n - 1;
}

void new_line() {
    char temp;

    do
    {
        cin.get(temp);
    } while (temp != '\n');
}

