#ifndef TTM_H
#define TTM_H

#include <iostream>
#include <fstream>
#include <istream>
#include <ostream>
#include <string>
#include "Parcer.h"

using std::string;
using std::fstream;
using std::cout;
using std::cin;
using std::endl;

struct transition;
struct state
{
	string name;
	transition* list;
};

struct transition
{
	char read;
	state* nextState;
	char write;
	int dir; //0- left   1-right *in input file*
	transition* nextTrans;
};


class TTM
{
public:
	TTM();
	TTM(string inFile);

	bool Run(string& tape);

	//~TTM();

private:
	state* Q;   //array of states
	string L;	//language
	state* q;	//starting state
	transition* d;	//array of transtion functions

	string name;
	int stateCnt; //count of number of states
	int transCnt; //count of number of transitions

	void Render(std::istream& fin, bool manual);
	void addTransition(state* list, int numStates, state* current, string* parts);
};
#endif

/*
Turing machine is a 4-tuple (Q,/\,q_0,d)
Q: a finite set of states
/\: (capital lamba) an alphabet including a blank character '#'
q_0: the start state
d: (lowercase delta) transition function- (current state ,input, next state ,output, direction)
*/