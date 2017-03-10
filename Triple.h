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
#ifndef TRIPLE_H
#define TRIPLE_H

struct Triple {
	int from;
	char sym;
	int to;

	Triple(){}
	Triple(int a, char c, int b) : from(a), sym(c), to(b){}

};

#endif // !TRIPLE-H
