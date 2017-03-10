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
#ifndef DFA_H
#define DFA_H
#include "Vector.h"


struct DFA {
	intVector finalStates;
	int stCnt;
	int** table;
	/*intVector transArr;
	intVector displacements;
	intVector checkV;*/

	DFA();
	DFA(int st);
	DFA(const DFA& other);
	DFA& operator =(const DFA& other);
	~DFA();
	bool MatchString(char* line);
	/*void ShrinkTable();

private:
	int GetValue(int r, int l);*/
	
};

#endif // !DFA_H
