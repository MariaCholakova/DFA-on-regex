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
#ifndef PAIR_H
#define PAIR_H

template <typename T>
struct Pair {
	char firstEl;
	T secEl;

	Pair();
	Pair(char fe, T& se);
	Pair(const Pair& other);
	Pair& operator=(const Pair& other);
	~Pair();

};

#include "Pair.cpp"
#endif // !PAIR_H
