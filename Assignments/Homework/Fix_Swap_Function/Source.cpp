/*
Collin Bachman
Data Structures
Fix Swap Function Homework
DUE April 9th, 2018
The swap Neighbor function is supposed to swap only the neighboring set of
values, then going to the next set of values (1 2 3 4 becomes 2 1 4 3).
In the original swapNeighbors function, there was a problem where prev would
only go ahead 1, while temp would skip ahead 2. This would create a problem
where a  value will be swapped with anouther value 4 spots away.
(Ex: 1 2 3 4 5 to 5 2 3 4 1)
*/

#include <iostream>
#include <ctime>

using namespace std;
struct node {
	int data;
	node* next;
};

class intLinkedList {
private:
	node* Head;
public:
	intLinkedList() {
		Head = NULL;
	}
	void insert(int x) {
		//empty list case
		if (!Head) {
			Head = new node;
			Head->data = x;
			Head->next = NULL;
		}
		else {//not empty list
			node* T = new node;
			T->data = x;
			T->next = Head;
			Head = T;
		}
	}

	node* Find(int key) {
		node* temp = Head;
		while (temp) {
			if (temp->data == key) {
				return temp;
			}
			temp = temp->next;
		}
		return NULL;
	}

	node* Remove(int key) {
		node* result = Find(key);
		if (result) {
			node* temp = Head;
			while (temp->next != result) {
				temp = temp->next;
			}
			temp->next = result->next;
			delete result;
		}
	}

	void print() {
		node* p = Head;
		while (p) {
			cout << p->data << " ";
			p = p->next;
		}
		cout << endl;
	}

	void divideByX(int x) {
		node* banana = Head;

		while (banana) {
			banana->data /= x;
			banana = banana->next;
		}
	}

	//assumptions are list is >= length(2);
	// swaps sets of neighbors
	// 1: head->A->B->C->D->E->NULL
	// 2: head->B->A->D->C->E->NULL
	void swapNeighbors() {
		node* prev = Head;
		node* temp = Head->next;
		int tempvar;

		while (temp) {
			cout << "swap with " << prev->data << " and ";
			cout << temp->data << endl;

			//Swapping prev and temp, with the help of tempVar.
			tempvar = temp->data;
			temp->data = prev->data;
			prev->data = tempvar;

			cout << "swapped " << prev->data << " with ";
			cout << temp->data << endl;

			//Check to see if prev->next->next links to usable data.
			if (!prev->next->next) {
				//if not, then break out of the while loop.
				cout << "Hey! Don't link to NULL! Stop!!!" << endl;
				break;
			}
			//Otherwise, set up the next pieces of data to swap.
			prev = prev->next->next;
			temp = temp->next->next;

			cout << "More stuff? Then let's keep going!" << endl;

			system("pause");
		}
		//Only shows when we break out of the while loop.
		cout << "All done!" << endl << endl;
	}

};

int main() {
	srand(8734587);

	intLinkedList mylist;
	for (int i = 0; i<10; i++) {
		mylist.insert(rand() % 100);
	}
	//mylist.print();
	//cout<<mylist.Find(99)<<endl;
	//mylist.Remove(58);
	mylist.print();				//Printing list before swap
	mylist.swapNeighbors();		//The swap function
	mylist.print();				//Printing list after swap
	system("pause");

}
