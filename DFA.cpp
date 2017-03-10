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
#include "DFA.h"
#include <cstring>

DFA::DFA(){

}

DFA::DFA(int st) {
	stCnt = st;
	table = new int*[stCnt];
	for (int i = 0; i < stCnt; i++) {
		table[i] = new int[ALPH_SIZE];
	}
	for (int i = 0; i < stCnt; i++) {
		for (int j = 0; j < ALPH_SIZE; j++) {
			table[i][j] = -1;
		}
	}
}

DFA::DFA(const DFA& other) {
	stCnt = other.stCnt;
	table = new int*[stCnt];
	for (int i = 0; i < stCnt; i++) {
		table[i] = new int[ALPH_SIZE];
	}
	for (int i = 0; i < stCnt; i++) {
		for (int j = 0; j < ALPH_SIZE; j++) {
			table[i][j] = other.table[i][j];
		}
	}
	
	finalStates = other.finalStates;
}

DFA& DFA::operator =(const DFA& other) {
	if (this != &other) {
		for (int i = 0; i < stCnt; i++) {
			delete[] table[i];
		}
		delete[] table;
		stCnt = other.stCnt;
		table = new int*[stCnt];
		for (int i = 0; i < stCnt; i++) {
			table[i] = new int[ALPH_SIZE];
		}
		for (int i = 0; i < stCnt; i++) {
			for (int j = 0; j < ALPH_SIZE; j++) {
				table[i][j] = other.table[i][j];
			}
		}
		
		finalStates = other.finalStates;
	}
	return *this;
}

DFA::~DFA() {
	for (int i = 0; i < stCnt; i++) {
		delete[] table[i];
	}
	delete[] table;
}


bool DFA::MatchString (char* line) {
	int len = strlen(line);
	//if string is empty, check if start state is among the final states
	if (len == 0) {
		int zero = 0;
		if (finalStates.Contains(zero))
			return true;
	}
	
	int currSt = 0;
	for (int i = 0; i < len; i++) {
		char c = line[i];
		int st = table[currSt][c];             
											//int st = this->GetValue(currSt,c);
		if (st == -1)
			return false;
		
		if (finalStates.Contains(st)) {
			if (i == len - 1)
				return true;
		}
		currSt = st;
	}
	return false;
}



/*
bool CanPushAhead(intVector& v, intVector& firstRow, 
				  intVector& checkV, int& displ, int** table, int row) {
	int sz = v.GetSize();
	int end = firstRow.GetSize();
	
	int l = 0;
	while (l < v[0]) {
		if (firstRow[l] == -1) {
			int dis = v[0] - l;
			bool possible = true;
			for (int i = 0; i < sz; i++) {
				if (firstRow[v[i] - dis] != -1)
					possible = false;
			}
			if (possible) {
				int k = l;
				displ = l - v[0];  //negative
				for (int i = 0; i < sz; i++) {
					checkV[k] = row;
					firstRow[k++] = table[row][v[i]];	
				}
				return true;
			}

		}
		l++;
	}
		
	return false;
}


int FirstNotFree(intVector& v, intVector& firstRow) {
	int sz = v.GetSize();
	int end = firstRow.GetSize();
	for (int i = 0; i < sz; i++) {
		//if we have gone out of scope
		if (v[i] > end) {
			return -1;
		}
		//first position which is not free
		if (firstRow[v[i]] != -1)
			return v[i];
	}
	//all positions up are free
	return 0;
}


void Shift(intVector& v, int displ) {
	int sz = v.GetSize();
	for (int i = 0; i < sz; i++) {
		v[i] += displ;
	}
}


void DFA::ShrinkTable() {
	for (int i = 0; i < ALPH_SIZE; i++)
		transArr.Push(table[0][i]);
	
	for (int r = 1; r < stCnt; r++) {
		intVector occupied;
		intVector ocInitial;
		for (int l = 0; l < ALPH_SIZE; l++) {
			if (table[r][l] != -1) {
				occupied.Push(l);
				ocInitial.Push(l);
			}
		}
		int displ;
		int ocSz = occupied.GetSize();
		if (!CanPushAhead(occupied, transArr,checkV,displ,table, r)) {
			int f = FirstNotFree(occupied, transArr);
			bool push = true;
			
			while (f != 0) {
				 displ = f + 1;
				int end = transArr.GetSize();
				//start searching for free positions , it may go out of scope
				while (displ < end && transArr[displ] != -1) {
					displ++;
				}
				//if we do not find any free position till the end,
				//just push the numbers
				if (displ == end) {
					for (int i = 0; i < ocSz; i++) {
						transArr.Push(table[r][ocInitial[i]]);
						checkV.Push(r);
					}
					push = false;
					displ = end - ocInitial[0];
					break;
				}

				Shift(occupied, displ - occupied[0]);
				f = FirstNotFree(occupied, transArr);
				//if we have gone out of res scope, just push the numbers
				if (f == -1) {
					displ = end - ocInitial[0];
					for (int i = 0; i < ocSz; i++) {
						transArr.Push(table[r][ocInitial[i]]);	
						checkV.Push(r);
					}
					push = false;
					break;
				}
			} //while (f)
			//if f == 0, all the corresponding positions immediately up are free
			if (push) {
				displ = occupied[0] - ocInitial[0];
				for (int i = 0; i < ocSz; i++) {
					transArr.Push(table[r][ocInitial[i]]);
					checkV[occupied[i]] = r;
				}
			}
		}
		//Push displacement for this row
		displacements.Push(displ);

	}//for rows
}


int DFA::GetValue(int st, int l) {
	if (checkV[displacements[st] + l] == st) {
		return transArr[displacements[st] + l];
	}
	else
		return -1;
}

*/
