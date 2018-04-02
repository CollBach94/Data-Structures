///////////////////////////////////////////////////////////////////////////////
// Title:            Priority Queue (Program 2)
// Files:            Source.cpp, input_data.txt, priority_out.txt
// Semester:         Spring 2018
//
// Author:           Collin Bachman
// Email:            cbbachman0504@my.mwsu.edu
// Description:
//			The program reads in a .txt file with two commands; push (with an
// animal name) and pop. Overall, the program will add (push) and remove (pop)
// animal names. All the names are sorted by the program bases on the length 
// of the name and alphabetically. When the program pops, it will take of items
// from the front of the list (the shortest names.) and file them under a 
// "popped" list. Any animals remaining in the queue will be shown at the end
// of the program.
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/**
* Struct Node:
*      Provides the data types used for the program.
* Params:
*      [string] val - value of item being pushed
*	   [Node] *next - holds adress of next value (val)
*/
struct Node
{
	string val;			//will the the value of that node.
	Node *next;			//points to the next node in the list
	Node()
	{
		val = " ";
		next = NULL;
	}
	Node(string v)
	{
		val = v;
		next = NULL;
	}
};

/**
* class Queue
*     This class houses the front and back points used for a list-based queue.
*	  It also houses all of the functions used in the program.
* Methods:
*  - Queue()			  : constructor
*  - string pop()		  :
*  - void push(string v)  : Adds an item to the queue
*  - bool empty()		  : Identifies if the queue is empty
*  - void print()		  : Prints all items in queue.
*  - void bubbleListSort(): Responsible for sorting the data in queue.
*/
class Queue
{
private:
	Node *Front;	//Identifies the beginning of the list
	Node *Rear;		//Identifies the beginning of the list

public:
	/**
	* Queue
	*	Sets Front and Rear to NULL
	*
	* params:
	*     - none
	*/
	Queue()
	{
		Front = Rear = NULL;
	}

	/**
	* string pop:
	*      removes the first item in the queue.
	*	   Does nothing if there are no items in queue.
	* Params:
	*      NULL
	* Returns
	*      string
	*/
	string pop()
	{
		if (!empty())
		{
			Node *temp = Front;   // temp pointer so we can delete node
			string v = temp->val; // grab value out of node
			Front = Front->next;  // move pointer to next node
			delete temp;          // give mem back to system
			return v;			  //Return the item that was popped off.
		}
		else
		{
			//cout << "error: cannot pop off empty queue." << endl;
			return " ";			  //Return only spaces if there are no items
		}
	}

	/**
	* void push:
	*      Adds an item to the queue
	*
	* Params:
	*      [string] v: the nitem that will be added to the queue
	* Returns
	*      void
	*/
	void push(string v)
	{
		Node *n = new Node(v);

		// handle the empty case
		if (empty())
		{
			Front = n;		//Set both Front and Rear
			Rear = n;		//To the first value
		}
		else
		{
			// not empty, add to rear
			Rear->next = n;
			Rear = n;
		}
		bubbleListSort(); //Sort list after adding the new item.
	}
	/**
	* Bool:
	*      identifies if the queue is empty.
	* Params:
	*      NULL
	* Returns
	*      bool (true or false)
	*/
	bool empty()	
	{
		return (Front == NULL);
	}

	/**
	* void print:
	*      prints the items in a queue to the file/screen.
	* Params:
	*      NULL
	* Returns
	*      void
	*/
	void print()
	{
		Node *temp = Front;
		while (temp)
		{
			cout << temp->val << "->";
			temp = temp->next;
		}
		cout << endl;
	}
	/**
	* bool pop:
	*      can pop off all of the items on a queue.
	* Params:
	*      string &v
	* Returns
	*      bool
	*/
	bool pop(string &v)
	{
		if (!empty())			  //if empty() returns false, 
								  //begin popping off item(s)
		{
			Node *temp = Front;   // temp pointer so we can delete node
			string t = temp->val; // grab value out of node
			Front = Front->next;  // move pointer to next node
			delete temp;          // give mem back to system
			v = t;
			return true;		
		}
		else
		{
			//cout << "error: cannot pop off empty queue." << endl;
			return false;
		}
	}
	/**
	* void bubbleListSort():
	*      Sorts the queue by word length. If there are two words of the same
	*	   length, then its sorts alphabetically.
	* Params:
	*      NULL
	* Returns
	*      void
	*/
	void bubbleListSort() {

		Node* t1 = Front;
		Node* t2 = Front;

		string temp = "";

		bool swapped = false;

		while (t1) {
			swapped = false;
			t2 = t1->next;
			while (t2) {
				//if the word t1 is larger in length, move it down
				if (t1->val.length() > t2->val.length()) {
					swapped = true;
					temp = t1->val;
					t1->val = t2->val;
					t2->val = temp;
				}
				//If the word t1 is equal in length, sort by alphabet
				//If is larger, then move it down the list.
				if (t1->val.length() == t2->val.length()) {
					if (t1->val > t2->val) {
						swapped = true;
						temp = t1->val;
						t1->val = t2->val;
						t2->val = temp;
					}
				}
				t2 = t2->next;
			}
			t1 = t1->next;
		}
		//If theres no swap, then just return.
		if (!swapped) {
			return;
		}
	}
};

int main()
{
	string Direc = " ";		//Directs which function to call
	string Word = " ";		//Holds the needed word (if push is used)
	ifstream infile;
	ofstream outfile;
	infile.open("input_data.txt");
	outfile.open("priority_out.txt");
	Queue Q;
	string animal;
	string PopHold = " ";	//Temporarily holds the string for pop function
	int Counter = 1;		//For listing the animals in the outfile

	//Header for Popped animals
	outfile << "Animals Popped off Queue:" << endl << endl;
	
	while (!infile.eof())
	{
		infile >> Direc;	//Reading in the action to take
		
		if (Direc == "push") //If push, read in name and add to queue
		{
			infile >> Word;			//Read in a word.
			Q.push(Word);			//Push.
			Word = " ";				//Clearing Word.
		}
		if (Direc == "pop")	//If pop, remove the first item in the queue.
		{
			PopHold = Q.pop();			//Temporarily place popped item in PopHold
			if (PopHold != " ")			//If PopHold does not contain only spaces.
			{
				outfile << Counter << " " << PopHold << endl;
				Counter++;
				PopHold = " ";			//Reset PopHold
			}
			//Otherwise, skip and contenue reading items.
		}
		Direc = " ";					//Reset Direc
	}
	outfile << endl;
	//Header for showing animals that remain on the queue.
	outfile << "Animals Remaining on the Queue (in order of priority):";
	outfile << endl << endl;
	Counter = 1;			//Reset counter for remaining animals on queue.
	while (Q.pop(animal))	//While there are items in this queue.
	{
		outfile << Counter << " " << animal << endl;
		Counter++;
	}
	//Closing the files before ending the program

	system("pause");
}
