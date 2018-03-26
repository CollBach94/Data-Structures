//Collin Bachman
//ToUpper Homework
//Data Structures
//DUE March 25th, 2018
//This homeworks requires the change of the toLower function into a toUpper
//function. Rather than a function to make all the letters in a word lowercase,
//make a function that makes all of the letters uppercase.
//I kept the original toLower function in the code to compare it to toUpper.

#include <string>
#include <fstream>
#include <iostream>

using namespace std;

/**
* @FunctionName: toLower
* @Description:
*     The function reads a word, changing any uppercase letters to
lowercase letters. If that letter is already a lowercase letter, then
that letter is skipped and the function goes onto the next letter.
* @Params:
*    string w; The word that will be made into all lowercase letters
* @Returns:
*    string
*/
string toLower(string w) {
	for (int i = 0; i<w.length(); i++) {
		//Since upper case ASCII values from 65 to 90
		if ((int)w[i] >= 65 && (int)w[i] <= 90) {
			//Add 32 to make a letter lowercase
			w[i] = w[i] + 32;
		}
	}
	return w;
};

/**
* @FunctionName: toUpper
* @Description:
*     The function reads a word, changing any lowercase letters to
uppercase letters. If that letter is already an uppercase letter, then
that letter is skipped and the function goes onto the next letter.
* @Params:
*    string w; The word that will be made into all uppercasecase letters
* @Returns:
*    string
*/
string toUpper(string w) {
	for (int i = 0; i<w.length(); i++) {
		//Since lower ASCII values from 97 to 122
		if ((int)w[i] >= 97 && (int)w[i] <= 122) {
			//Subtract 32 to make a letter uppercase
			w[i] = w[i] - 32;
		}
	}
	return w;
};

int main (){
	//toLower function
	string Name = "MarCO";			//Testing lower with mixed case name
	cout << toLower(Name) << endl;	//All letters should be lower case

	//toUpper function
	Name = "POlo";					//Testing lower with new mixed case name
	cout << toUpper(Name) << endl;	//All letters should be upper case

	system("pause");				//Needed to see the results.
	return 0;
}
