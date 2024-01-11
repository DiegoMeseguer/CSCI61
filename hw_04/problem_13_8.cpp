#include <iostream>
#include <cstdlib>
#include <time.h>
#include <chrono>
#include <thread>
#include <algorithm>
using namespace std;

//== HEAPSORT ==
template <typename T>
void heapsort(T data[], size_t n); // Sorting algorithm
template <typename T>
void make_heap(T data[], size_t n); // This is the first step in the heapsort, uses reheap upward
template <typename T>
void reheapify_down(T data[], size_t n); // Regenerates the heap after we swap the root with the last unsorted index
template <typename T>
void print(T data[], size_t size);
size_t parent(size_t k); // Gives  the index of the parent node of k, so k cannot be the root node k != 0
size_t left_child(size_t k); // Gives the index of the left child of node k
size_t right_child(size_t k); // Gives the index of the right child of node k
void swap(int & a, int & b);

//== QUICKSORT ==
int partition(int arr[], int start, int end);
void quick_sort(int arr[], int start, int end);

const size_t BIG = 82000;

int main() {
	
	srand(time(0));
	int bigList[BIG];
	int orderedList[BIG];

	// Fill Big and Ordered list;
	for (size_t i = 0; i < BIG; ++i) {
		bigList[i] = rand() % 700 + 1;
	}
	for (size_t i = 0; i < BIG; ++i) {
		orderedList[i] = i + 1;
	}

    auto t1 = chrono::high_resolution_clock::now();
    heapsort(bigList, BIG);
    auto t2 = chrono::high_resolution_clock::now();
    std::cout << "For Unsorted List, Heapsort took "
              << chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count()
              << " milliseconds\n";

    auto t3 = chrono::high_resolution_clock::now();
    heapsort(orderedList, BIG);
    auto t4 = chrono::high_resolution_clock::now();
    std::cout << "For Sorted List, Heapsort took "
              << chrono::duration_cast<std::chrono::milliseconds>(t4-t3).count()
              << " milliseconds\n";

	for (size_t i = 0; i < BIG; ++i) {
		bigList[i] = rand() % 700 + 1;
	}
	for (size_t i = 0; i < BIG; ++i) {
		orderedList[i] = i + 1;
	}

	auto t5 = chrono::high_resolution_clock::now();
    quick_sort(bigList, 0, BIG - 1);
    auto t6 = chrono::high_resolution_clock::now();
    std::cout << "For Unsorted List, Quick Sort took "
              << chrono::duration_cast<std::chrono::milliseconds>(t6-t5).count()
              << " milliseconds\n";

	auto t7 = chrono::high_resolution_clock::now();
    quick_sort(orderedList, 0, BIG - 1);
    auto t8 = chrono::high_resolution_clock::now();
    std::cout << "For Sorted List, Quick Sort took "
              << chrono::duration_cast<std::chrono::milliseconds>(t8-t7).count()
              << " milliseconds\n";

	for (size_t i = 0; i < BIG; ++i) {
		bigList[i] = rand() % 700 + 1;
	}
	for (size_t i = 0; i < BIG; ++i) {
		orderedList[i] = i + 1;
	}

	auto t9 = chrono::high_resolution_clock::now();
    std::sort(std::begin(bigList), std::end(bigList));
    auto t10 = chrono::high_resolution_clock::now();
    std::cout << "For Unsorted List, std::sort took "
              << chrono::duration_cast<std::chrono::milliseconds>(t10-t9).count()
              << " milliseconds\n";

	auto t11 = chrono::high_resolution_clock::now();
    std::sort(std::begin(orderedList), std::end(orderedList));
    auto t12 = chrono::high_resolution_clock::now();
    std::cout << "For Sorted List, std::sort took "
              << chrono::duration_cast<std::chrono::milliseconds>(t12-t11).count()
              << " milliseconds\n";

	return 0;
}

template <typename T>
void heapsort(T data[], size_t n) {
    size_t unsorted;

    make_heap(data, n);

    unsorted = n;

    while (unsorted > 1) {
        --unsorted;
        swap(data[0], data[unsorted]);
        reheapify_down(data, unsorted);
    }
}

template <typename T>
void make_heap(T data[], size_t n) {
    size_t i;  // Index of next element to be added to heap
    size_t k;  // Index of new element as it is being pushed upward through the heap

    for (i = 1; i < n; ++i) {
        k = i;
        while ((k > 0) && (data[k] > data[parent(k)])) {
            swap(data[k], data[parent(k)]);
            k = parent(k);
        }
    }
}

template <typename T>
void reheapify_down(T data[], size_t n) {
    size_t current;          // Index of the node that's moving down
    size_t big_child_index;  // Index of the larger child of the node that's moving down
    bool heap_ok = false;    // Will change to true when the heap becomes correct

    current = 0;

    // Note: The loop keeps going while the heap is not okay, and while the current node has
    // at least a left child. The test to see whether the current node has a left child is
    // left_child(current) < n.
    while ((!heap_ok) && (left_child(current) < n))
    {
        // Compute the index of the larger child:
        if (right_child(current) >= n)
            // There is no right child, so left child must be largest
            big_child_index = left_child(current);
        else if (data[left_child(current)] > data[right_child(current)])
            // The left child is the bigger of the two children
            big_child_index = left_child(current);
        else
            // The right child is the bigger of the two children
            big_child_index = right_child(current);

        // Check whether the larger child is bigger than the current node. If so, then swap
        // the current node with its bigger child and continue; otherwise we are finished.
        if (data[current] < data[big_child_index])
        {
            swap(data[current], data[big_child_index]);
            current = big_child_index;
        }
        else
            heap_ok = true;
    }
}

size_t parent(size_t k) {
    return (k-1)/2;
}

size_t left_child(size_t k) {
    return 2*k + 1;
}

size_t right_child(size_t k) {
    return 2*k + 2;
}

void swap(int & a, int & b) {
    int temp;

    temp = a;
    a = b;
    b = temp;
}

template <typename T>
void print(T data[], size_t size) {
    for (int i = 0; i < size; ++i)
        cout<<data[i]<<" ";
    cout<<endl;
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

void quick_sort(int arr[], int start, int end) {
	if(start < end) {
		int partIndex = partition(arr, start, end);
		quick_sort(arr, start, partIndex - 1);
		quick_sort(arr, partIndex + 1, end);
	}
}


