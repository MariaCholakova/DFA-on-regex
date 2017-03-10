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
#ifndef VECTOR_H
#define VECTOR_H
#include "DynamicArray.h"

template < class T >
class Vector : public DynamicArray<T> {
public:
	Vector();
	Vector(const Vector& other);
	Vector& operator=(const Vector& other);
	~Vector();
	bool Contains(T& el) const;
	Vector& operator+= (const Vector& other);
	bool operator==(const Vector& other);
	
};
#include "Vector.cpp"
typedef Vector<int> intVector;

#endif // !VECTOR_H

