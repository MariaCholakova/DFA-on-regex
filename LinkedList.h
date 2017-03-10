/**
*
* Solution to homework task
* Data Structures Course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2016/2017
*
* @author Maria Cholakova
* @idnumber 61934
* @task 0
* @compiler VC
*
*/


#pragma once
#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include "Vector.h"

struct Node {
	intVector iv ;
	Node* next = nullptr;

	Node(){}
	Node(intVector& intv): iv(intv) , next(nullptr){};
	
};

struct LinkedList {
public:
	Node* head;
	LinkedList();
	LinkedList(LinkedList& other);
	LinkedList& operator=(LinkedList& other);
	~LinkedList();
	bool isEmpty() const;
	void Enqueue(intVector& iv);
	bool Contains(intVector& iv);
	int GetNumber(intVector& iv);

private:
	void Destroy();
};

#endif // !LINKED_LIST_H

