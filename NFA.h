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
#ifndef NFA_H
#define NFA_H
#include "Pair.h"
#include "Vector.h"

//PairArr is the array of pairs p: p<char, destination states>
typedef  Vector<Pair<intVector> >  PairArr;
const char eps = '|';

struct NFA {	
	
	int finalState;
	int stCnt;
	//array "trans" will hold pair arrays for each state
	PairArr* trans;
	

	NFA();
	NFA(int st);
	NFA(char c);
	NFA(const char* str);
	NFA(const NFA& other);
	NFA& operator =(const NFA& other);
	~NFA();	
	NFA Concat(NFA& other);
	NFA Union(NFA& other);
	void Kleene();
	intVector GetEpsClosure(int st);
	intVector GetEpsClosure(intVector& states);
	void Display();
	bool HasSuchTrans(int st, char sym);
};

#endif // !NFA_H

