#pragma once
#include <stdlib.h>

template <class item>

class CircularDoublyLinkedList {
private:
	class Node {
	public:
		Node *next;
		Node *previous;
		item value;
		Node(item T, Node *nxt = NULL, Node *prev = NULL) : value(T), next(nxt), previous(prev) {}
	};
	Node * c_head;
	Node * c_tail;
	unsigned int c_size;
public:
	class Iterator {
	private:
		Node* m_ptr;
	public:
		Iterator(Node* ptr) { m_ptr = ptr; }
		void operator ++ () { m_ptr = m_ptr->next; }
		void operator-- () { m_ptr = m_ptr->previous; }
		bool operator!= (const Iterator& b) { return m_ptr != b.m_ptr; }
		item getValue() { return m_ptr->value; }
		void setValue(item val) { m_ptr->value = val; }
		Node *getIterator() { return m_ptr; }
		void setIterator(Node *ptr) { m_ptr = ptr; }
	};

	CircularDoublyLinkedList();
	~CircularDoublyLinkedList();
	void addHead(item i);
	Node* getHead() { return c_head; }
	Node* getTail() { return c_tail; }
	void shift(int i, int k);
	Iterator begin() const { return Iterator(c_head); }
	Iterator end() const { return Iterator(c_tail); }
	unsigned int size();
	bool isEmpty() const;
	item removeHead();
	item retrieveHead() const;
	void addTail(item val);
	item removeTail();
	item retrieveTail() const;
	void add(unsigned pos, item val);
	item replace(unsigned pos, item val);
	item remove(unsigned pos, item val);
	void swap(unsigned pos1, unsigned pos2);
};

//Constructor
template <class item>
CircularDoublyLinkedList<item>::CircularDoublyLinkedList() {
	//Pointing the head and the tail to null at first as no nodes have been created yet
	c_head = c_tail = NULL;
	c_size = 0;
}

//Destructor
template <class item>
CircularDoublyLinkedList<item>::~CircularDoublyLinkedList() {
	//Designating a Node pointer to start at the linked list, and creating a node to hold the next node in the list 
	Node * here = c_head, *nextNode;
	//Loop to go up to the tail, which it's next value is pointing at tail
	while (here->next != c_head) {
		//pointing next node to the next value of the first and subsequent nodes
		nextNode = here->next;
		//Deleting the memory in the here node
		delete here;
		here = nextNode; //re-setting the node to the next node
	}
}

//adds a head at the front of the list
template <class item>
void CircularDoublyLinkedList<item>::addHead(item i) {
	//Checking if this is the first head, if not
	if (c_tail != NULL) {
		c_tail->next = c_head = new Node(i, c_head, c_tail); //Pointing the tail next attribute to the new node, 
		//creating a new head with value i, and setting the next value to the previous head and setting the previous attribute to the tail
		(c_head->next)->previous = c_head; //Setting the previous head node previous attribute to the new head
	}
	//If this is the new head
	else if (c_tail == NULL) { 
		//Crearing a new node to act as the new head
		c_head = new Node(i);
		c_tail = c_head; //Making the head and the tail point to the same place 
		// making it circular by making the next point to the head and the previous to the head
		c_head->next = c_head; 
		c_head->previous = c_head;
	} 
	c_size++;
}

//Returns the current size (which is the number of elements in the list)
template <class item>
unsigned int CircularDoublyLinkedList<item>::size() {
	return c_size;
}

//Shift function that takes in 2 parameters, one to determine the direction and the other to determing the number of iterations
template <class item>
void CircularDoublyLinkedList<item>::shift(int i, int k) {
	//move head to the left
	for (int d = 0; d < k; d++) {
		if (i == 0) {
			c_head = c_head->next;
			c_tail = c_head->next;
		}
		//move head to the right 
		else if (i == 1) {
			c_head = c_head->previous;
			c_tail = c_tail->previous;
		}
	}
}
//Returns 1 if the CDLL is empty
template <class item>
bool CircularDoublyLinkedList<item>::isEmpty() const {
	return (c_size == 0);
}
//Removes the head of the list
template <class item>
item CircularDoublyLinkedList<item>::removeHead() {
	//Assigning the head to the new value
	Node *here = c_head;
	item value = c_head->value;
	c_head = c_head->next;
	//Deleting the old head
	delete here;
	here = NULL;
	//If after deleting the head, the head is pointing at NULL (meaning this was the only item in the list), make tail point to NULL as well
	if (c_head == NULL)
		c_tail = NULL;
	else {
		c_tail->next = c_head;
		c_head->previous = c_tail;
	}
	c_size--;
	return value;
}
//Returning the value of the head
template <class item>
item CircularDoublyLinkedList<item>::retrieveHead()const {
	return c_head->value;
}
//Adding a tail at the end of the list
template <class item>
void CircularDoublyLinkedList<item>::addTail(item val) {
	if (c_size == 0) 
		addHead(val);
	Node *here = c_tail;
	c_tail = new Node(val, c_head, here);
	here->next = c_tail;
	c_head->previous = c_tail;
	c_size++;
}

//Removes the tail in the linked list 
template <class item>
item CircularDoublyLinkedList<item>::removeTail() {
	Node *here = c_tail;
	item val = c_tail->value;
	c_tail = c_tail->previous;
	c_tail->next = c_head;
	delete here;
	here = NULL;
	//If after removing the tail, the tail is pointing to NULL, it means there was only 1 item in the list before it was removed thus now theres none
	if (c_tail == NULL)
		c_head = NULL;
	else
		c_head->previous = c_tail;
	c_size--;
	return val;
}

//Returning the value stored in the tail
template <class item>
item CircularDoublyLinkedList<item>::retrieveTail() const {
	return c_tail->value;
}

//Adding a node in any position in the list
template <class item>
void CircularDoublyLinkedList<item>::add(unsigned pos, item val) {
	if (pos == 1 || pos == 0)
		addHead(val);
	else if (pos == c_size)
		addTail(val);
	else {
		Node * here = m_head;
		for (unsigned int k = 1; k < n-1; k++)
			here = here->next;
		here->next = new Node(val, here - next, here);
		((here->next)->next)->previous = here->next;
		c_size++;
	}
}

//Replaces item values of any node in the list
template <class item>
item CircularDoublyLinkedList<item>::replace(unsigned pos, item val) {
	item returnValue;
	Node * here = m_head;
	for (unsigned int k = 1; k < pos; k++) here = here->next;
	returnValue = here->value;
	here->value = val;
	return returnValue;
}

//Removes a node from any position in the list
template <class item>
item CircularDoublyLinkedList<item>::remove(unsigned pos, item val){
	if (pos == 1)
		return removeHead();
	if (pos == size())
		return removeTail();

	Node * here = c_head;
	for (unsigned int k = 1; k < n - 1; k++)
		here = here->next;
	Node * kill = here->next;
	item returnVal = kill->value;
	here->next = kill->next;
	(here->next)->previous = here;
	delete kill;
	c_size--;
	return returnVal;
}

//Swaps the value in 2 nodes
template <class item>
void CircularDoublyLinkedList<item>::swap(unsigned pos1, unsigned pos2) {
	Node *here1 = c_head;
	Node *here = c_head;
	for (int i = 1; i < pos1; i++)
		here1 = here1->next;
	for (int i = 1; i < pos2; i++)
		here2 = here2->next;
	item temp = here1->value;
	replace(here1, here2->value);
	replace(here1, temp);
}