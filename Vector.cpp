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
#include "Vector.h"

template <class T>
Vector<T>::Vector() :DynamicArray<T>() {}

template <class T>
Vector<T>::Vector(const Vector& other) : DynamicArray<T>(other) {}


template <class T>
Vector<T>& Vector<T>::operator=(const Vector& other) {
	DynamicArray<T>::operator=(other);
	return *this;
}

template <class T>
Vector<T>::~Vector() {
}


template <class T>
bool Vector<T>::Contains(T& el) const{
	for (int i = 0; i < size; i++) {
		if (arr[i] == el)
			return true;
	}
	return false;
}

template <class T>
Vector<T>& Vector<T>::operator+= (const Vector& other) {
	for (int i = 0; i < other.size; i++) {
		if (! this->Contains(other[i])) {
			this->Push(other[i]);
		}
	}
	return *this;
}

template <class T>
bool Vector<T>::operator==(const Vector& other) {
	if (this->size != other.size)
		return false;
	else {
		for (int i = 0; i < size; i++) {
			//since we build the arrays we will compare
			//in the same way, they are completely identical-
			//equal elements stay on equal positions respectively
			if (arr[i] != other.arr[i])  
				return false;
		}
	}
	return true;
}
