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
#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H
const int ALPH_SIZE = 128;

template <class T>
class DynamicArray {
protected:
	int capacity;
	int size;
	T *arr = nullptr;
	T* reallocate();
	
public:
	DynamicArray();
	DynamicArray(const DynamicArray& other);
	DynamicArray& operator = (const DynamicArray& other);
	~DynamicArray();
	T& operator[](int index) const;
	int GetCapacity() const;
	int GetSize() const;
	void Push(const T& element);
};

#include "DynamicArray.cpp"
typedef DynamicArray<char> String;


#endif // !DYNAMIC_ARRAY_H
