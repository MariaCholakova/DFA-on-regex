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
#include "DynamicArray.h"

template<class T>
DynamicArray<T>::DynamicArray() {
	capacity = 15;
	size = 0;
	arr = new T[capacity];
}


template <class T>
int DynamicArray<T>::GetCapacity() const {
	return this->capacity;
}

template <class T>
int DynamicArray<T>::GetSize() const{
	return this->size;
}


template <class T>
T& DynamicArray<T>::operator[](int index) const{
	return arr[index];
}

template <class T>
T* DynamicArray<T>::reallocate() {
	T* temp = new T[capacity * 2];
	for (size_t i = 0; i < size; i++) {
		temp[i] = arr[i];
	}
	capacity *= 2;
	delete[] arr;
	return temp;
}

template <class T>
DynamicArray<T>::DynamicArray(const DynamicArray& other) {
	size = other.GetSize();
	capacity = other.GetCapacity();
	arr = new T[capacity];
	for (size_t i = 0; i < size; i++)
		arr[i] = other[i];
}

template <class T>
DynamicArray<T>& DynamicArray<T>::operator = (const DynamicArray& other) {
	if (this != &other){
		size = other.GetSize();
		capacity = other.GetCapacity();
		delete[] arr;
		arr = new T[capacity];
		for (int i= 0; i < size; i++)
			arr[i] = other[i];
	}
	return *this;
}


template <class T>
DynamicArray<T>::~DynamicArray() {
	//printf("destr DynArr\n");
	delete[] arr;
}

template <class T>
void DynamicArray<T>::Push(const T& element) {
	if (size >= capacity) {
		arr = reallocate();
	}
	arr[size] = element;
	size++;
}

