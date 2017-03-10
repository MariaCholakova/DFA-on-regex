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
#include "Stack.h"

template <class T>
Stack<T>::Stack():DynamicArray<T>() {}

template <class T>
Stack<T>::Stack(const Stack& other) : DynamicArray<T>(other) {}


template <class T>
Stack<T>& Stack<T>::operator=(const Stack& other) {
	DynamicArray<T>::operator=(other);
	return *this;
}

template <class T>
Stack<T>::~Stack() {
}


template <class T>
void Stack<T>::Pop() {
	if (isEmpty()) {
		throw StackException();
	}
	else {
		size--;
	}
}

template <class T>
T& Stack<T>::Top() {
	if (isEmpty()) {
		throw StackException();
	}
	else {
		return arr[size - 1];
	}
}

template <class T>
bool Stack<T>::isEmpty() const{
	return size == 0;
}
