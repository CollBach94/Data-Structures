//////////////////////////////////////////////////////////////////////////////
// ProgramName: Program 3 - Survival of the Lucky
// Author: Collin Bachman
// Description: 
//	This program reads in a list of animal names, before eliminating each of 
//  them one by one until only one animal remains. The program will print out 
//	the first eleminated animal, followed by every 11th animal. The last
//	remaining animal will be printed out as the winner.
// Course: 1063 Data Structures
// Semester: Spring 2018
// Date: 27 04 2018
//////////////////////////////////////////////////////////////////////////////

#include <string>
#include <iomanip>
#include <fstream>
#include <iostream>

using namespace std;

struct Node {
	string Name;
	Node *Next;
	Node *Prev;
	Node () {
		Name = " ";
		Next = NULL;
		Prev = NULL;
	}
};

class Circ {
private:
	Node* Head;
	Node* Current;
public:
	Circ() {
		Head = NULL;
		Current = NULL;
	}
	/**
	* Function: PlaceAni()
	* Description:
	*     Add an animal name to the list
	* Params:
	*    Name- an animal name to be placed into the list.
	* Returns:
	*    NULL
	*/
	void PlaceAni(string name) {
		Node* Temp = new Node;
		Temp->Name = name;

		if (!Head) {
			Head = Temp;
			Current = Temp;
			Temp->Next = Temp;
			Temp->Prev = Temp;
		}
		//Else...
		else {
			Temp->Prev = Current;
			Current->Next = Temp;
			Temp->Next = Head;
			Head->Prev = Temp;
			Current = Temp;
		}
	}
	/**
	* Function: RemoveAni()
	* Description:
	*     Removes the first item from the list (item pointed to by head)
	* Params:
	*    Space- The number of times the function goes through the list
	* Returns:
	*    string word
	*/
	string RemovAni(int Space) {
		Node* Traveller = new Node;		//Creating our navigator
		Node* TravPrev = new Node;
		Traveller = TravPrev = Head;
		int TravNum = 0;		//# of times we travel around the circle
		string Removed;			//Will contain the removed animal
		cout << "FIRST: ";

		while (Head->Next != Head) {		//BEGIN REMOVAL
			if (Space % 2 == 0) {
				for (int i = Space; i > 0; i--) {
					Traveller = Traveller->Next;
					TravPrev = Traveller->Next;
				}
			}
			else {
				for (int i = Space; i > 0; i--) {
					Traveller = Traveller->Prev;
					TravPrev = TravPrev->Prev;
				}
			}
		}
		Removed = Traveller->Name;
		TravPrev = Traveller->Prev;
		TravPrev->Next = Traveller->Next;
		Traveller->Next->Prev = TravPrev;
		delete Traveller;
		return Removed;
	}
	string Winner() {
		//return Head;
	}

	void Header(ofstream file) {
		cout << "////////////////////////////////////////////////////////////";
		cout << "//////////////////" << endl << "// ProgramName: Program 3 -";
		cout << "Survival of the Lucky" << endl << "// Author: Collin Bachman";
		cout << endl << "// Description:" << endl;
		cout << "//  This program reads in a list of animal names, before ";
		cout << "eliminating each of" << endl << "//  them one by one until";
		cout << "only one animal remains.The program will print out" << endl;
		cout << "//  the first eleminated animal, followed by every 11th";
		cout << "animal. The last" << endl << "//  remaining animal will";
		cout << "be printed out as the winner." << endl;
		cout << "// Course: 1063 Data Structures" << endl;
		cout << "// Semester: Spring 2018" << endl;
		cout << "// Date: 27 04 2018" << endl;
		cout << "/////////////////////////////////////////////////////////";
		cout << "/////////////////////" << endl << endl;
	}

};



int main() {
	Circ Live;
	string AniTemp;			//Temporarilly holds an animal name
	string AniExe;			//Conmmtains the executed animal.
	int Count = 0;			
	int ExeCount = 0;		//Tallies to print every 11th animal.
	int Seed = 0;			//Contains the seed for the RNG
	int Multi = 0;			//The user prompted multiplier
	int CHECK = 0;			//DEBUG int.
	int Length = 0;			//The product length after word length & multi

	ifstream fin("animal.txt");
	ofstream outfile("eliminated.txt");
	Live.Header();

	//Planting the seed
	cout << "Please input a seed number" << endl;
	cin >> Seed;
	srand(Seed);

	//Input all of the animal names
	while (!fin.eof()) {
		fin >> AniTemp;
		Count++;
		Live.PlaceAni(AniTemp);
		//cout << "Input " << AniTemp << " Index " << ++CHECK << endl;
	}

	//Resetting the file
	fin.clear();
	fin.seekg(0, std::ios::beg); // back to the start!

	//Prompt the multiplier (1 - 13 only)
	cout << "Please enter the multiplier the word length";
	cout << "will the multiplied by (1 - 13 ONLY): " << endl;
	cin >> Multi;
	while (Multi < 1 || Multi > 13) {
		//repeat the loop until the user types in the accepted value.
		cout << "Please enter a number between 1 and 13 ONLY" << endl;
		cin >> Multi;
	}
		cout << "You entered " << Multi << " as your multiplier. Let's begin!";
		cout << endl << endl;

	//Start removing animals until 1 is left.
		while (!fin.eof()) {
			fin >> AniTemp;
			for (int i = Count; i > 1; i--) {
				ExeCount++;
				//Finding how many spaces to move.
				Length = AniTemp.length() * Multi;
				//Call the function
				AniExe = Live.RemovAni(Length);
				//print the name of the first animal eliminated.
				if (ExeCount == 1) {
					cout << "FIRST-" << AniExe << endl;
				}
				//if ExeCount is a multiple of 11, print a name.
				if (ExeCount % 11 == 0) {
					cout << "- " << AniExe << endl;
				}
			}
		}

	//Declare the sole winner
		//AniTemp = Live.Winner;
		//cout << "Winner: " << AniTemp << "!!!" << endl;
}
