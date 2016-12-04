#include "TopSpin.h"

#include <iostream>

TopSpin::TopSpin(int size, int spinSize) {
	//If the inputted value of spinSize is larger than the size of the board, default to 4 and 20
	if (spinSize > size) {
		m_size = 20;
		m_spinSize = 4;
	}
	//Otherwise the size and the spinSize paramaters should be set to the attributes of the top spin object
	else {
		m_size = size;
		m_spinSize = spinSize;
	}
	//Adding m_size number of nodes backwards, starting at the last value
	for (int k = 0; k < m_size; ++k)
		board.addHead(m_size - k);
}

TopSpin::~TopSpin() {
	//When the top spin object is destroyed, it will print out thank you for playing
	cout << "Thank you for playing." << endl;
}

//shifts the pieces 1 time to the left
void TopSpin::shiftLeft() {
	board.shift(0, 1);
}

//shifts the pieces 1 time to the left
void TopSpin::shiftRight() {
	board.shift(1, 1);
}

//shifts the pieces j number of times to the left
void TopSpin::shiftLeft(int j) {
	board.shift(0, j);
}

//shifts the pieces j number of times to the right
void TopSpin::shiftRight(int j) {
	board.shift(1, j);
}

//reverses the pieces in the spin mechanism
void TopSpin::spin() {
	//Creating 2 iterators to hold the value of the head
	CircularDoublyLinkedList<int>::Iterator g(board.getHead());
	CircularDoublyLinkedList<int>::Iterator here(board.getHead());
	//Moving one of the iterators to point to the end of the spin mechanism
	for (int i = 1; i < (m_spinSize); ++i) {
		++g;
	}
	//Iterating to half way of the mechanism while switching values to spin the mechanism
	for (int k = 1; k <= (m_spinSize / 2); k++) {
		int temp = here.getValue(); //tempaorary variable to hold of the current poistion of the head
		here.setValue(g.getValue()); //Setting the value of the current position to the symmetric part of the mechanism 
		g.setValue(temp); 
		++here; //Making it point to the next value from the begining of the spin mechanism
		--g; //Making it point to the previous value from the end of the spin mechanism
	}
}

//checks to see if the puzzle is solved that is to say the pieces are in numerical order 1 - 20
bool TopSpin::isSolved()
{
	//2 variable to hold the values of the position of 1 in the linked list
	CircularDoublyLinkedList<int>::Iterator k(board.getHead());
	//First finding where the 1 is in the list, iterating until one is found, after 1 is found, it breaks 
	while (1) {
		if (k.getValue() == 1) { break; }
		++k; 
	}
	
	int nextVal = 1;
	//Comparing the subsequent forward values and making sure they are incrementing propperly starting from 1, if they are, it's solved
	while (nextVal <= m_size) {
		//Making sure the values of the subsequent values are true
		if (nextVal == k.getValue()) {
			++k; ++nextVal;
			//if it's true for the last value (m_size + 1 as we increase nextVAL by 1 after the final comparison), print Congrats
			if (nextVal == m_size+1) {
				cout << "CONGRATUALTIONS!" << endl;
				return 1;
			}
		}
		else
			return 0;
	}
}

ostream& operator << (ostream& os, const TopSpin& s) {
	//Creating an iterator to point at the head
	CircularDoublyLinkedList<int>::Iterator a1 = (s.board).begin();
	//Printing out the outline for the spin mechanism and overriding the operator to print out all the values
	cout << "|";
	for (int i = 0; i <= s.m_spinSize; i++) {
		if (i < s.m_spinSize)
			cout << "--";
		else if (i == s.m_spinSize)
			cout << "-";
	}
	cout << "|" << endl << "| ";
	for (int i = 1; i <= s.m_size; i++, ++a1) {
		if (i == s.m_spinSize + 1)
			cout << "|" << " ";
		os << a1.getValue() << " ";
	}
	cout << endl << "|";
	for (int i = 0; i <= s.m_spinSize; i++) {
		if (i < s.m_spinSize)
			cout << "--";
		else if (i == s.m_spinSize)
			cout << "-";
	}
	cout << "|" << endl;
	return os;
}