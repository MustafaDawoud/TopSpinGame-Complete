#include <iostream>
#include "TopSpin.h"

using namespace std;

int main() {
	//Declaring variables to hold values of the user inputs
	int qA = 0, //qA is responsible to hold the value of the menu that the user inputs
		randomMoves = 0; //random variable is responsible to hold the value of the number of random moves the user wants to make 

	TopSpin a(20, 4); //Creating top spin game object with the inputted values

	//Printing out what the game looks like initially
	cout << "This is what the puzzle looks like: " << endl << a << endl;

	//Randomizing game
	cout << "How many random moves would you like to make (number between 1 and 19 inclusive): " << endl << "Input: ";
	cin >> randomMoves;
	//Making sure the value inputted is positive 
	while (true) {
		if (randomMoves <= 0 || randomMoves >= 20) {
			cout << "Invalid input, please input a number of random moves between 1 and 19: " << endl << "Input: ";
			cin >> randomMoves;
		}
		else
			break;
	}
	//Randomizing the board
	for (int i = 1; i <= randomMoves; ++i) {
		a.shiftLeft();
		a.spin();
	}

	//Printing out what the game looks like after it has been randomized
	cout << "This is the current state of the puzzle after it has been randomized: " << endl; cout << a << endl;

	//Loop that has the condition of the user not quitting (inputting 3)
	while (qA != 3) {
		//Asking the user for a menu input
		cout << "Please choose from the following options enter your choice by entering the " <<
			"corresponding number : " << endl << "1. Shift" << endl << "2. Spin" << endl <<
			"3. Quit" << endl << "Input: ";
		cin >> qA;
		cout << endl;

		//If the user wants to shift
		if (qA == 1) {
			char directionOfShift = 'a'; //Holds the value of the direction of shift the user wants
			int numberOfShift = 1; //Holds the value of the number of shifts the user wants

			//Asking the user for the direction and number of iterations
			cout << "What direction would you like to spin (L or R): " << endl
				<< "Input: "; cin >> directionOfShift;
			cout << "How many shifts would you like to make: " << endl
				<< "Input: ";  cin >> numberOfShift;
			cout << endl;

			//If the user wants to shift to the left
			if (directionOfShift == 'L' || directionOfShift == 'l')
			{
				//Shift left that number of times
				a.shiftLeft(numberOfShift);
				//Print out the current state of the board
				cout << a << endl;
				//Checking if the board is solved
				if (a.isSolved()) 
					return 0;
			}

			//User wants to shift to the right
			else if (directionOfShift == 'R' || directionOfShift == 'r')
			{
				//Shifting to the right the number of times the user wants
				a.shiftRight(numberOfShift);
				//Printing out the current state of the board
				cout << a << endl;
				//Checking if the board is solved
				if (a.isSolved()) 
					return 0;
			}
		}
		//If the user wants to spin
		else if (qA == 2) {
			a.spin();
			//Printing out the current state of the board
			cout << a << endl;
			//Checking if the board is solved
			if (a.isSolved()) 
				return 0;
		}
	}
	return 0;
}