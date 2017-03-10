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

// SearchTextByRegex.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Stack.h"
#include "InfixToPostfix.h"
#include "RegexToNfa.h"
#include "NFAtoDFA.h"
#include <io.h>
#include <iostream>
#include <fstream>
#include "dirent.h"

void DisplayFile(const char* name) {
	fstream file(name);
	char* line = new char[2000];
	int cnt = 1;
	if (file.is_open()) {
		while (file.getline(line, 2000)) {
			printf("%s:%d:%s\n", name, cnt, line);
			cnt++;
		}
	}
	else {
		printf("Can not open file\n");
	}
	delete[] line;
	file.close();
}

void ScanFile(const char* name, DFA& dfa) { 
	fstream file(name);
	char* line = new char[2000];
	int cnt = 1;
	if (file.is_open()) {
		while (file.getline(line, 2000)) {
			if (dfa.MatchString(line)) {
				//<fileName>:<lineNo.>:<text> 
				printf("%s:%d:%s\n", name, cnt, line);
			}
			cnt++;
		}
	}
	else {
		printf("Can not open file\n");
	}
	delete[] line;
	file.close();
}

const int PATH_MAX = 300;

static int find_directory(const char* dirname, DFA* dfa)
{
	DIR *dir;
	char buffer[PATH_MAX + 2];
	char *p = buffer;
	const char* src;
	char *end = &buffer[PATH_MAX]; 
	int ok;

	// Copy directory name to buffer 
	src = dirname;
	while (p < end  &&  *src != '\0') {
		*p++ = *src++;
	}
	*p = '\0';

	//Open directory stream 
	dir = opendir(dirname);
	if (dir != NULL) {
		printf("Opens directory %s\n", dirname);
		struct dirent *ent;

		// Print all files and directories within the directory 
		while ((ent = readdir(dir)) != NULL) {
			char *q = p;
			char c;

			// Get final character of directory name
			if (buffer < q) {
				c = q[-1];      //a[i] = (*(a+i))
			}
			else {
				c = ':';
			}

			// Append directory separator if not already there
			if (c != ':'  &&  c != '/'  &&  c != '\\') {
				*q++ = '/';
			}

			//Append file name
			src = ent->d_name;
			while (q < end  &&  *src != '\0') {
				*q++ = *src++;
			}
			*q = '\0';

			if (strcmp(ent->d_name, ".") != 0
				&& strcmp(ent->d_name, "..") != 0) {
				find_directory(buffer,dfa);
			}
		}

		closedir(dir);
		ok = 1;

	}
	else {
		//Cannot open directory ->it is a file or there is no such directory
		if (dfa == nullptr)
			DisplayFile(dirname);
		else
			ScanFile( dirname,*dfa);
		ok = 0;
	}

	return ok;
}


using namespace std;
int main()
{
	cout << "Enter a directory/file name:" << endl;
	char* fileName = new char[PATH_MAX];
	cin.getline(fileName, PATH_MAX);
	cout << "Enter a regular expression:" << endl;
	char* regex = new char [200];
	cin.getline(regex, 200);
	
	String* s = CstringToString(regex);
	AddConcatSym(*s);
	
	if (*regex == *"") {
		int ok = find_directory(fileName, nullptr);
		if (!ok) {
			exit(EXIT_FAILURE);
		}
	}
	else try {
		//turn expression in postfix notation
		InfixToPostfix(*s);
		//create NFA from the expression
		NFA nfa = ReToNFA(*s);
		//create DFA from the NFA
		DFA dfa = nfa_to_dfa(nfa);
		int ok = find_directory(fileName,&dfa);
		if (!ok) {
			exit(EXIT_FAILURE);
		}

	}
	catch (BracketsException& e) {
		cout << e.what() << '\n';
	}
	catch (BackSlashException& e) {
		cout << e.what() << '\n';
	}
	catch (StackException& e) {
		cout << e.what() << '\n';
	}
	
	
	delete[] fileName;
	delete[] regex;
	
    return 0;
}

