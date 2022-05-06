#ifndef PARCER_H
#define PARCER_H

#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::endl;

class Parcer
{
public:
	Parcer();

	string wrap(string input, int width);
	void split(string toSplit, char splitBy, string words[]);
	string* split(string toSplit, char openChar, char closeChar, int& numWords);
	void cutOut(string& input);
	void cutOut(string& input, char toTrim);
	void trim(string& input);
	void trim(string& input, char toTrim);
	void removeCopy(string* words, int& numWords);
	void removeCopy(string& word);
	void appendArray(string* words, string toAdd, int& numWords);
	string partition(const string& word);
	int searchArray(string* words, string toFind, const int& numWords);
	bool inStr(const string& word, char toFind);
	void alphSort(string* words, const int& numWords);
	void alphSort(string& word);
	string toPig(string input);
};

#endif