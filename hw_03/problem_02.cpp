#include <iostream>
#include "node.h"
using namespace std;

void linked_insertion_sort(int arr[], size_t size);
void new_line();

int main() {

	int integerList[10];
	string ans;

    do
    {
        cout << "Please write 10 integers" << endl;
        for (int i = 0; i < 10; ++i) {
        	cout<<"Integer "<<i + 1<<": ";
        	cin>>integerList[i];
        }
        
        cout<<"Your list is: \n";
        for (int x : integerList)
        	cout<<x<<" ";
        cout<<"\n";
       
       linked_insertion_sort(integerList, 10);
 
        cout << "Would you like to sort a new list? (yes/no)" << endl;
        cin>>ans;
        new_line();
    } while ((ans[0] == 'Y') || (ans[0] == 'y'));


	return 0;
}


void linked_insertion_sort(int arr[], size_t size) {
	node *head, *tail;
	head = tail = nullptr;

	for (int i = 0; i < size; ++i) {
		if(i == 0) // First element of the list, only need head_insert
			list_head_insert(head, tail, arr[i]);
		else if(i == 1) {// There's one thing in the linked list, either head_insert of tail_insert
			if(arr[0] < arr[1])
				list_tail_insert(head, tail, arr[i]);
			else
				list_head_insert(head, tail, arr[i]);
		}
		else {
			for(node * p = head; p != nullptr; p = p->link()) { // There's two or more in the linked list
				if(p == head && p->data() >= arr[i]) {
					list_head_insert(head, tail, arr[i]); // Insert front of linked list
					break;	// We need this to avoid infinite loop
				}
				
				else if(p != tail && p->link()->data() >= arr[i]) { // Insert middle of linked list
					list_insert(p, arr[i]);
					break; // We need this to avoid infinite looop
				}

				else if(p->link() == nullptr && arr[i] > p->data()) // Insert tail of linked list
					list_tail_insert(head, tail, arr[i]);
			}
		}
	}

	cout<<"Your sorted list is:\n"<<head<<endl;
}

void new_line() {
    char temp;

    do
    {
        cin.get(temp);
    } while (temp != '\n');
}

