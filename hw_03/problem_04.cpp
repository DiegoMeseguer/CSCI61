#include <iostream>
#include <stack>
using namespace std;

void swap(int & a, int & b);
int partition(int arr[], int start, int end);
void stack_quick_sort(int arr[], int start, int end);
// void quick_sort(int arr[], int start, int end);

int main() {
	
	int b[6] = {20, 16, 144, 5, 900, 32};

	stack_quick_sort(b, 0, 5);

	cout<<"Sorted array is: "<<endl;
	for (int x : b)
		cout<<x<<" ";
	cout<<"\n";

	return 0;
}

int partition(int arr[], int start, int end) {
	int pivot = arr[end];
	int partIndex = start; // We will start to scan from here

	for (int i = start; i < end; ++i) {
		if(arr[i] <= pivot) {
			swap(arr[i], arr[partIndex]); // We want all the elements lesser than the pivot to the left
			partIndex++;				  // of partIndex
		}
	}
	swap(arr[partIndex], arr[end]);
	return partIndex;
}

void stack_quick_sort(int arr[], int start, int end) {
	stack<int> sorted;
	int partIndex;

	sorted.push(start);
	sorted.push(end);
	partIndex = partition(arr, start, end);
	
	while(!sorted.empty()) {

		if(start < end) {
			sorted.pop();
			sorted.pop();
		}

		partition(arr, start, partIndex - 1);
		partition(arr, partIndex + 1, end);

		end = partIndex - 1;
		start = partIndex + 1;
	}
}

void swap(int & a, int & b) {
	int temp;

	temp = a;
	a = b;
	b = temp;
}

// void quick_sort(int arr[], int start, int end) {
// 	if(start < end) {
// 		int partIndex = partition(arr, start, end);
// 		quick_sort(arr, start, partIndex - 1);
// 		quick_sort(arr, partIndex + 1, end);
// 	}
// }


