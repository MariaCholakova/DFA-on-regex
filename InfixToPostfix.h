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
#ifndef INFIX_TO_POSTFIX_H
#define INFIX_TO_POSTFIX_H
#include <cstring>
#include "AuxFunctions.h"
#include "Stack.h"

String* CstringToString(const char* cstr) {
	String* str = new String;
	int len = strlen(cstr);
	for (int i = 0; i < len; i++) {
		 str->Push(cstr[i]);
	}
	return str;
}

void AddConcatSym(String& expression) {
	//this new expression will have '.' between operands
	String newExpr;
	int len = expression.GetSize();
	for (int i = 0; i<len; i++) {
		newExpr.Push(expression[i]);
		if (isOperand(expression[i]) ) {
			if (expression[i] != '\\') {
				if (i + 1 < len && isOperand(expression[i + 1])) 
				newExpr.Push('.');
			}
			else {
				//if we have "....\\...."
				if (i + 2 < len && expression[i + 2] == '\\') {
					newExpr.Push('\\');
					newExpr.Push('.');
					i++;
				}
			}
		}
		else 
			//if we saw an operator or a bracket
			if (expression[i] == '*') {
				if (i + 1 < len && isOperand(expression[i + 1])) {
					newExpr.Push('.');
				}
			}
	}
	expression = newExpr;
}

int getWeight(const char ch) {
	switch (ch) {
	case '.':return 2;
	case '|': return 1;
	default: return 0;
	}
}

void InfixToPostfix(String& infix) {
	Stack<char> st;
	String postfix;
	int weight;
	int i = 0;
	char ch;
	int size = infix.GetSize();
	
	while (i < size) {
		ch = infix[i];
		if (ch == '(') {
			st.Push(ch);
			i++;
			continue;
		}
		if (ch == ')') {
			// if we see a closing parenthesis, pop all the elements 
			// and append them to the postfix expression till 
			// we encounter an opening parenthesis
			while (!st.isEmpty() && st.Top() != '(') {
				postfix.Push(st.Top());
				st.Pop();
			}
			// pop the opening parenthesis as well
			if (!st.isEmpty()) {
				st.Pop();
			}
			i++;
			continue;
		}
		weight = getWeight(ch);
		if (weight == 0) {
			//if we see an operand or '*' , append it to postfix expression
			postfix.Push(ch);
		}
		
		else {
			// we saw an operator '.' or '|'
			if (st.isEmpty()) {	
				st.Push(ch);
			}
			else {
				// pop all the operators from the stack and append them to the
				// postfix expression till we see an operator with a lower precedence
				
				while (!st.isEmpty() && st.Top() != '(' &&
						weight <= getWeight(st.Top())) {
					postfix.Push(st.Top());
					st.Pop();

				}
				// push the current operator onto stack
				st.Push(ch);
			}
		}
		i++;
	}
	// pop of the remaining operators left in the stack
	// and append them to the postfix expression 
	while (!st.isEmpty()) {
		if (st.Top() == '(') {
			throw brex;
		}
		postfix.Push( st.Top());
		st.Pop();
	}
	infix = postfix;
}

#endif // !INFIX_TO_POSTFIX_H
