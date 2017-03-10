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

#include "stdafx.h"
#include "LinkedList.h"

LinkedList::LinkedList(){
	head = nullptr;
}

bool LinkedList::isEmpty() const {
	return head == nullptr;
}

void LinkedList::Enqueue(intVector& intVector) {
	Node* newNode  = new Node(intVector);
	Node* current = head;
	if (current == nullptr) {
		head = newNode;
	}
	else {
		while (current->next != nullptr) {
			current = current->next;
		}
		current->next = newNode;
	}
}


int LinkedList::GetNumber(intVector& iv) {
	Node* node = head;
	int cnt = 0;
	while (node) {
		if (node->iv == iv)
			return cnt;
		else {
			node = node->next;
			cnt++;
		}
	}
	return cnt;
}

bool LinkedList::Contains(intVector& iv) {
	Node* node = head;
	while (node) {
		if (node->iv == iv)
			return true;
		node = node->next;
	}
	return false;
}

LinkedList::LinkedList(LinkedList& other) {
	Node* node = other.head;
	while (node) {
		this->Enqueue(node->iv);
		node = node->next;
	}
}

void LinkedList::Destroy() {
	Node* current = head;
	while (current) {
		Node* temp = current->next;
		delete current;
		current = temp;
	}
}


LinkedList& LinkedList::operator = (LinkedList& other) {
	if (this != &other) {
		this->Destroy();
		Node* node = other.head;
		while (node) {
			this->Enqueue(node->iv);
			node = node->next;
		}
	}
	return *this;
}

LinkedList::~LinkedList() {
	this->Destroy();
}