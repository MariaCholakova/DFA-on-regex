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
#include "Pair.h"

template < typename T>
Pair<T>::Pair() {}

template < typename T>
Pair<T>::Pair(char fe, T& se): firstEl(fe), secEl(se) {}

template <typename T>
Pair<T>::Pair(const Pair& other){
	firstEl(other.firstEl);
	secEl(other.secEl);
}

template <typename T>
Pair<T>& Pair<T>::operator=(const Pair& other) {
	if (this != &other) {
		firstEl = other.firstEl;
		secEl = other.secEl;
	}
	return *this;
}

template <typename T>
Pair<T>::~Pair(){

}


