/**
 *
 * Solution to homework task
 * Data Structures Course
 * Faculty of Mathematics and Informatics of Sofia University
 * Winter semester 2016/2017
 *
 * @author Maria Cholakova
 * @idnumber 61934
 * @task 1
 * @compiler VC
 *
 */

#pragma once

#ifndef STACK_H
#define STACK_H

#include "Exception.h"
#include "DynamicArray.h"

template < class T > 
class Stack : public DynamicArray<T>{
public:
	Stack();
	Stack(const Stack& other);
	Stack& operator=(const Stack& other);
	~Stack();
	void Pop();
	T& Top();
	bool isEmpty() const;

private:
	T& operator[](int) {};  //stack container does not have operator []
};
#include "Stack.cpp"

#endif // !STACK_H
