#include <cstdlib> 
#include <iostream>    
using namespace std;

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

int main() {

    cout<<"Template Heapsort\n";
    
    cout<<"\nList of Unsorted Integers: "<<endl;
    int b[6] = {20, 30, 144, 5, 900, 32};
    print(b, 6);
    heapsort(b, 6);
    cout<<"Sorted: "<<endl;
    print(b, 6);

    cout<<"\nList of Unsorted Characters: "<<endl;
    char c[7] = {'f', 'i', 'a', 'z', 'o', 'l', 'w'};
    print(c, 7);
    heapsort(c, 7);
    cout<<"Sorted: "<<endl;
    print(c, 7);

    cout<<"\nList of Unsorted Strings: "<<endl;
    string a[4] = {"Orc", "Human", "Undead", "Night Elf"};
    print(a, 4);
    heapsort(a, 4);
    cout<<"Sorted: "<<endl;
    print(a, 4);
    
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

