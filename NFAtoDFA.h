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
#ifndef NFA_TO_DFA_H
#define NFA_TO_DFA_H
#include "NFA.h"
#include "DFA.h"
#include "LinkedList.h"
#include "Triple.h"

DFA nfa_to_dfa(NFA& nfa) {
	int tracker = 0;
	//nfa.Display();
	Vector<Triple> transInfo;
	intVector DFAfinals;
	//dfa start state is the epsilon closure of the nfa start state
	intVector startSet = nfa.GetEpsClosure(0);
	//this queue will hold the dfa states, which are subsets of the nfa states 
	LinkedList queue;
	queue.Enqueue(startSet);
	int currSetID = 0;
	Node* node = queue.head;
	while (node) {
		intVector currSet = node->iv;
		int currSetSz = currSet.GetSize();
		if (currSet.Contains(nfa.finalState)) {
			DFAfinals.Push(currSetID);
		}
	
		for (int let = 0; let < ALPH_SIZE && let != eps; let++) {
			intVector newSet;
			bool present = false;
			for (int j = 0; j < currSetSz; j++) {
				if (nfa.HasSuchTrans(currSet[j], let)) {
					present = true;
					//the new state to which current state will lead taking symbol 'let'
					//is the epsilon closure of the destination states
					//of the transition (currSet[j],let)

					newSet += nfa.GetEpsClosure(nfa.trans[currSet[j]][0].secEl);
					
					//we take the vector of the first pair in PairArr ([0])
					//because it(the vector) is the same for all pairs
				}
			}
			if (present) {

				int newSetID;
				//determine the value of newSetID
				if (queue.Contains(newSet)) {
					newSetID = queue.GetNumber(newSet);
				}
				else {
					queue.Enqueue(newSet);
					tracker++;
					newSetID = tracker;
				}
				Triple t(currSetID, let, newSetID);
				transInfo.Push(t);
			}


		}//for alphabet

		currSetID++;
		node = node->next;
	}//while node

	int size = transInfo.GetSize();
	DFA dfa(currSetID);  //currSetID holds the number of dfa states
	for (int i = 0; i < size; i++) {
		int from = transInfo[i].from;
		char sym = transInfo[i].sym;
		int to = transInfo[i].to;
		dfa.table[from][sym] = to;
		printf("Transition: %d, %c -> %d\n", from, sym, to);
	}
	dfa.finalStates = DFAfinals;
	return dfa;
}


#endif // !NFA
