#pragma once

#include <iostream>
using namespace std;

#include "TopSpinADT.h"
#include "CircularDoublyLinkedList.h"

class TopSpin : public TopSpinADT {
private:
	//Member variables
	int m_size;
	int m_spinSize;
	CircularDoublyLinkedList<int> board;

public:
	//Member functions
	TopSpin(int size, int spinSize);
	~TopSpin();
	void shiftLeft();
	void shiftRight();
	void shiftLeft(int j); 
	void shiftRight(int j);
	void spin(); 
	bool isSolved(); 
	friend ostream& operator<< (ostream& os, const TopSpin& s); 
};