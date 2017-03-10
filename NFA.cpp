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
#include "NFA.h"

void ModifyPair(Pair<intVector>& pair, int num) {
	intVector* v = &pair.secEl;
	int sz = v->GetSize();
	for (int i = 0; i < sz; i++) {
		(*v)[i] += num;
	}
}

//----------------------------------------------------------
NFA::NFA() {
	//the default NFA will have 3 states
	trans = new PairArr[3];
}

//constructor for NFAs which number of states is known in advance
//such as the result NFA from Concatenation, Union, Kleene star operations
NFA::NFA(int st) {
	stCnt = st;
	trans = new PairArr[stCnt];
}

//constructor for NFAs which recognise single character strings
NFA::NFA(char c) {
	stCnt = 2;
	trans = new PairArr[2];
	intVector iv;
	iv.Push(1);
	Pair<intVector> p(c, iv);
	trans[0].Push(p);
	finalState = 1;
	//if c is a letter, nfa has to be able 
	//to recognise its upper/lower equivalent
	if (c >= 65 && c <= 90) {
		p = Pair<intVector>(c + 32, iv);
		trans[0].Push(p);
	}
	if (c >= 97 && c <= 122) {
		p = Pair<intVector>(c - 32, iv);
		trans[0].Push(p);
	}
}

//constructor for the special transitions
NFA::NFA(const char* str) {
	stCnt = 2;
	trans = new PairArr[2];
	intVector iv;
	iv.Push(1);
	Pair<intVector> p;
	if (*str == *"alphabet") {
		for (int let = 65; let < 91; let++) {
			p = Pair<intVector>(let, iv);
			trans[0].Push(p);
		}
		for (int let = 97; let < 123; let++) {
			p = Pair<intVector>(let, iv);
			trans[0].Push(p);
		}
	}
	if (*str == *"digits") {
		for (int d = 48; d < 58; d++) {
			p = Pair<intVector>(d, iv);
			trans[0].Push(p);
		}
	}
	if (*str == *"spaces") {
		p = Pair<intVector>(' ', iv);
		trans[0].Push(p);
		p = Pair<intVector>('\t', iv);
		trans[0].Push(p);
		p = Pair<intVector>('\n', iv);
		trans[0].Push(p);
	}
	finalState = 1;
}

NFA::NFA(const NFA& other) {
	stCnt = other.stCnt;
	trans = new PairArr[stCnt];
	for (int i = 0; i < stCnt; i++) {
		trans[i] = other.trans[i];
	}
	finalState = other.finalState;
}

NFA& NFA::operator=(const NFA& other) {
	if (this != &other) {
		stCnt = other.stCnt;
		delete[] trans;
		trans = new PairArr[stCnt];
		for (int i = 0; i < stCnt; i++) {
			trans[i] = other.trans[i];
		}
		finalState = other.finalState;
	}
	return *this;
}

NFA::~NFA() {
	delete[] trans;
}

NFA NFA::Concat(NFA& other) {
	NFA result(stCnt + other.stCnt);

	//copy the first nfa transitions
	for (int i = 0; i < stCnt; i++) {
		result.trans[i] = trans[i];
	}

	//add the e-transition from the first nfa final state to the second nfa start state
	intVector iv;
	iv.Push(stCnt);
	Pair<intVector> p(eps, iv);
	result.trans[finalState].Push(p);

	//copy the second nfa transitions
	for (int i = 0; i < other.stCnt; i++) {
		int pairsCnt = other.trans[i].GetSize();
		for (int j = 0; j < pairsCnt; j++)
			ModifyPair(other.trans[i][j], stCnt);
		result.trans[i + stCnt] = other.trans[i];
	}

	result.finalState = result.stCnt - 1;
	return result;
}

NFA NFA::Union(NFA& other) {
	NFA result(stCnt + other.stCnt + 2);

	//set epsilon transtitions from result first state 
	//to nfa1 start state and nfa2 start state
	intVector iv;
	iv.Push(1);           //nfa1 start state No.= 1
	iv.Push(stCnt + 1);   //nfa2 start state No.= stCnt+1 
	Pair<intVector> p(eps, iv);
	result.trans[0].Push(p);

	//copy the first nfa transitions
	for (int i = 0; i < stCnt; i++) {
		int pairsCnt = trans[i].GetSize();
		for (int j = 0; j < pairsCnt; j++)
			ModifyPair(trans[i][j], 1);
		result.trans[i + 1] = trans[i];
	}

	//copy the second nfa transitions
	for (int i = 0; i < other.stCnt; i++) {
		int pairsCnt = other.trans[i].GetSize();
		for (int j = 0; j < pairsCnt; j++)
			ModifyPair(other.trans[i][j], stCnt + 1);
		result.trans[i + stCnt + 1] = other.trans[i];
	}

	//set epsilon transitions from nfa1 and nfa2
	//final states to result final state
	intVector iv2;
	iv2.Push(stCnt + other.stCnt + 1);    //result final state No.
	Pair<intVector>p2(eps, iv2);
	result.trans[stCnt].Push(p2);
	result.trans[stCnt + other.stCnt].Push(p2);

	result.finalState = stCnt + other.stCnt + 1;
	return result;
}

void NFA::Kleene() {
	PairArr* newTrans = new PairArr[stCnt + 2];

	for (int i = 0; i < stCnt; i++) {
		int pairsCnt = trans[i].GetSize();
		for (int j = 0; j < pairsCnt; j++)
			ModifyPair(trans[i][j], 1);
		newTrans[i + 1] = trans[i];
	}

	intVector iv;
	iv.Push(1);          //nfa start state No.
	iv.Push(stCnt + 1);  //result final state No.
	Pair<intVector> p(eps, iv);
	//add epsilon transitions:
	//-from result start state to nfa start state and result final state
	//-from    nfa final state to nfa start state and result final state
	newTrans[0].Push(p);
	newTrans[stCnt].Push(p);

	delete[] trans;
	trans = newTrans;
	stCnt = stCnt + 2;
	finalState = stCnt - 1;
}


intVector NFA::GetEpsClosure(int st) {
	intVector* closure = new intVector;
	closure->Push(st);

	//if from this state there is no transition with epsilon,
	//return the vector with the state itself
	if (trans[st][0].firstEl != eps) {
		return *closure;
	}

	*closure += trans[st][0].secEl;
	int sz1 = closure->GetSize();
	//start from index 1 because new states are on indices >0
	for (int i = 1; i < sz1; i++) {
		if (trans[(*closure)[i]][0].firstEl == eps) {
			intVector additionCl = trans[(*closure)[i]][0].secEl;
			int sz2 = additionCl.GetSize();
			for (int j = 0; j < sz2; j++) {
				if (!closure->Contains(additionCl[j])) {
					*closure += GetEpsClosure(additionCl[j]);
				}
			}
		}
	}
	return *closure;
}


void NFA::Display() {
	for (int i = 0; i < stCnt; i++) {
		int pairsCnt = trans[i].GetSize();
		for (int j = 0; j < pairsCnt; j++) {
			printf("st %d, %c->", i, trans[i][j].firstEl);
			for (int k = 0; k < trans[i][j].secEl.GetSize(); k++) {
				printf("%d  ", trans[i][j].secEl[k]);
			}
		}

		printf("\n");
	}
}

intVector NFA::GetEpsClosure(intVector& states) {
	intVector closure;
	int sz = states.GetSize();
	for (int i = 0; i < sz; i++) {
		closure += GetEpsClosure(states[i]);
	}
	return closure;
}

//There are 5 types of transitions according to the symbol:
//1.symbol is a single charcter - not a letter
//       -> then the PairArray contains only one pair: (+,iv)
//2.symbol is a single charcter - a letter
//       -> then the PairArray contains two pairs: (A,iv) and (a,iv)
//3.symbol is a random digit
//       -> then the PairArray contains ten pairs: (0,iv) ,..., (9,iv)
//4.symbol is a random space character
//       -> then the PairArray contains three pairs: ( ,iv) , (\t,iv) , (\n,iv)
//5.symbol is a random letter
//       -> then the PairArray contains 52 pairs: (A,iv) ,..., (Z,iv) , (a,iv) ,..., (z,iv)
bool NFA::HasSuchTrans(int st, char sym) {
	if (trans[st].GetSize() == 1) {
		//we have a single charachter going out of st 
		if (trans[st][0].firstEl == sym)
			return true;
	}
	if (trans[st].GetSize() == 2) {
		//we have upper and lower case letters going out of st 
		if (trans[st][0].firstEl == sym ||
			trans[st][1].firstEl == sym)
			return true;
	}
	if (trans[st].GetSize() == 52) {
		//we have the whole alphabet going out of st
		if (sym >= 65 && sym <= 90 || sym >= 97 && sym <= 122)
			return true;
	}
	if (trans[st].GetSize() == 3) {
		//we have space, tab and newline transitions
		if (sym == ' ' || sym == 9 || sym == 10)
			return true;
	}
	if (trans[st].GetSize() == 10) {
		//we have all digits transitions going out of st
		if (sym >= 48 && sym <= 57)
			return true;
	}
	return false;
}