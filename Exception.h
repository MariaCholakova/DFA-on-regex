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
#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>

using namespace std;

struct StackException : public exception {
	const char* what() const throw ()
	{
		return "Error! ";
	}
};

struct BracketsException : public exception {
	const char* what() const throw ()
	{
		return "Error! More brackets than needed!";
	}
}brex;

struct BackSlashException: public exception {
	const char* what() const throw ()
	{
		return "Error! More backslashes than needed!";
	}
}bslex;


#endif // !EXCEPTION_H
