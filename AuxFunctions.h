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
#ifndef AUX_FUNCTIONS_H
#define AUX_FUNCTIONS_H

bool isOperator(const char c) {
	return (c == '|' || c == '.' || c == '*');
}

bool isOperand(const char c) {
	return (!(isOperator(c) || c == '(' || c == ')'));
}




#endif // !AUX_FUNCTIONS_H
