#pragma once
#ifndef REGEX_TO_NFA_NEW

#include "C:\Users\User\Documents\Visual Studio 2015\Projects\Directory\Directory\NFAnew.h"
#include "Stack.h"
#include "AuxFunctions.h"

NFA ReToNFA(String& re) {
	Stack<NFA> st;
	int len = re.GetSize();
	for (int i = 0; i < len; i++) {
		char c = re[i];
		if (isOperand(c)) {
			if (c == '\\') {
				char cc = re[++i];
				switch (cc) {
				case 'd': {
					NFA res("digits");
					st.Push(res);
					break;
				}
				case 's': {
					NFA res ("spaces");
					st.Push(res);
					break;
				}
				case 'e': {
					NFA newNFA('|');
					st.Push(newNFA);
					break;
				}
				case 'a': {
					NFA res("alphabet");
					st.Push(res);
					break;
				}
				case '\\': {
					NFA newNFA('\\');
					st.Push(newNFA);
					break;
				}
				default: {
					throw bslex;
				}
				}
			}
			else {
				NFA newNFA(c);
				st.Push(newNFA);
			}

		}
		else {
			//c is '*' or '.' or '|' or '(' or ')'
			switch (c) {
			case '*': {
				st.Top().Kleene();
				break;
			}
			case '.': {
				NFA op2 = st.Top();
				st.Pop();
				NFA op1 = st.Top();
				st.Pop();
				NFA result = (op1.Concat(op2));
				st.Push(result);
				break;
			}
			case '|': {
				NFA op2 = st.Top();
				st.Pop();
				NFA op1 = st.Top();
				st.Pop();
				NFA result = (op1.Union(op2));
				st.Push(result);
				break;
			}
			default: {
				throw brex;
			}
			}
		}
	}
	return st.Top();
}



#endif // !REGEX_TO_NFA_NEW
