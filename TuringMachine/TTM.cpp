#include "TTM.h"

TTM::TTM()
{
	Q = nullptr;
	d = nullptr;
	Render(cin, true);
}

TTM::TTM(string inFile)
{
	Q = nullptr;
	d = nullptr;

	fstream reader;
	reader.open(inFile);

	if (!reader.fail())
	{
		name = inFile;
		Render(reader, false);
	}
	else
	{
		cout << endl;
		cout << "Error 404: File not found" << endl;
		cout << endl;
	}
}

bool TTM::Run(string& tape)
{
	Parcer p;
	cout << p.wrap("The Machine is now running.", 80) << endl;
	cout << endl;

	int loc = 0;
	char in;
	bool found;
	bool halted = false;
	state* current = q;
	transition* temp = NULL;

	//finding first non blank character
	while (tape[loc] == '#')
	{
		loc++;
	}

	while (!halted)
	{
		in = tape[loc];
		found = false;

		//resetting temp back to current State
		if (current->list != NULL)
		{
			temp = current->list;
		}

		//looking for transition
		while (temp != NULL && !found)
		{
			if (temp->read == in)
			{
				tape[loc] = temp->write;
				current = temp->nextState;
				loc += (2 * temp->dir) - 1;

				//checking if the TM is trying to move 'off' the tape
				if (loc == -1)
				{
					tape = '#' + tape;
					loc++;
				}
				else if (loc == tape.length())
				{
					tape += '#';
				}
				
				found = true;
			}
			else
			{
				temp = temp->nextTrans;
			}
		}

		if (current->list == NULL && found)
		{
			halted = true;
			p.trim(tape, '#');
			cout << p.wrap("This machine has succesfully halted, input string accepted.", 80) << endl;
			cout << "Resulting String is: " << tape << endl;
			cout << endl;
			return 1;
			
		}
		else if (temp == NULL)
		{
			p.cutOut(tape, '#');
			cout << p.wrap("Unsuccesful halt, input string not accepted.", 80) << endl;
			return 0;
		}
	}

	/*
	-need tape
	-need location integer to keep track of where on the tape it is
	-read character
		>find transition with inputChar == read character
		>if none exist, but there are transitions from current state, halt & indicate input string is not accepted
		>if no transitions exist for a state, halt and indicate the input string was accepted
	-when at the start and moving L or at the end and moving R
		>for beginning moving L
			~append a '#' to the front
		>for end moving R
			~append a '#' to the end and increment the location integer
	-when moving
		>dir(x) = 2x - 1
		>add result to location integer
	*/

	return -1;
}

void TTM::Render(std::istream& fin, bool manual)
{
	bool valid = false;
	int numStates = 1;
	int numTrans = 1;
	Parcer p;

	string ans;
	string states;
	string start;
	string language;
	string trans;
	string* tempStates = NULL;
	string* tempTrans = NULL;

	//getting list of states
	cout << p.wrap("Enter the set of states for this machine, formatted: (Q0, Q1, Q2, Q3, ... , Qn) *note: the states do not have to be named Q1,Q2,etc*", 80) << endl;

	while (!valid)
	{
		fin >> states;

		for (int i = 0; i < states.length(); i++)
		{
			if (states[i] == ',')
			{
				numStates++;
			}
		}

		tempStates = new string[numStates];

		if ((states[0] == '(') && (states[states.length() - 1] == ')') && (numStates != 0))
		{
			p.cutOut(states, '(');
			p.cutOut(states, ')');

			p.split(states, ',', tempStates);
			p.removeCopy(tempStates, numStates);

			cout << "You've entered the states:" << endl;

			for (int i = 0; i < numStates; i++)
			{
				cout << tempStates[i] << endl;
			}
			cout << endl;
			valid = true;

		}
		else
		{
			cout << "You have entered an incorrect format, please enter a valid one." << endl;
		}
	}//end of states being entered

	//getting start state
	cout << p.wrap("Enter the starting state for this turing machine.", 80) << endl;

	valid = false;

	while (!valid)
	{
		fin >> start;
		if (p.searchArray(tempStates, start, numStates) != -1)
		{
			valid = true;
			cout << p.wrap(start + " will be the starting state for this machine.", 80) << endl;
			cout << endl;
		}
		else
		{
			cout << p.wrap("That state is not in the list of states previously entered. Would you like to add the state to the list? (Y/N)", 80) << endl;
			fin >> ans;
			if (ans == "Y" || ans == "y")
			{
				p.appendArray(tempStates, start, numStates);
			}
		}
	}

	//getting the machine's language
	cout << p.wrap("Enter the characters of the language to be used. (exlucde spaces unless a space character is valid in the language)", 80) << endl;
	cout << p.wrap("Note: The '#' character will automatically be included.", 80) << endl;
	cout << p.wrap("Ex.) \"ABCD\" would be a language that accepts the characters: #,A,B,C,D and nothing else", 80) << endl;

	fin >> language;
	//adding # to the beginning
	language = '#' + language;
	p.removeCopy(language);   //removing any repeated characters

	cout << p.wrap("This machine's accepted language will be: " + p.partition(language), 80) << endl;
	cout << endl;

	//getting list of transitions
	cout << p.wrap("Enter the transitions of the machine in the following format:", 80) << endl;
	cout << p.wrap("{(Sx,I,Sy,O,D),..,()}", 80) << endl;
	cout << p.wrap("Where Sx is the current state, Sy is the next state, I is the input char, O is the output char, and D is the direciton: L or R for Left or Right", 80) << endl;

	valid = false;

	while (!valid)
	{
		fin >> trans;
		tempTrans = p.split(trans, '(', ')', numTrans);

		string* parts = new string[5]; //for taking apart transition

		if (numTrans != -1)
		{
			p.removeCopy(tempTrans, numTrans);
			p.alphSort(tempTrans, numTrans);
			valid = true;

			for (int i = 0; i < numTrans; i++)
			{
				trans = tempTrans[i].substr(1, tempTrans[i].length());
				p.split(trans, ',', parts);

				if ((parts[4][0] != 'L') && (parts[4][0] != 'R'))
				{
					valid = false;
				}
				
				//making sure the read and write chars are in the language
				if (p.inStr(L, parts[1][0]) && p.inStr(L, parts[3][0]))
				{
					valid = false;
				}
			}
		}
		else
		{
			cout << p.wrap("You have entered an incorrect format for transitions. Enter the transitions in the correct format.", 80) << endl;
		}
	}

	cout << p.wrap("You have entered the transitions:", 80) << endl;
	for (int i = 0; i < numTrans; i++)
	{
		cout << tempTrans[i] << endl;
	}
	cout << endl;

	//begin actual building
	//language is a string of chars
	//states are a dyn arr of strings
	//transitions are a dyn arr of strings
	//start state is a string

	L = language;
	Q = new state[numStates];
	q = &Q[p.searchArray(tempStates, start, numStates)];
	q->name = start;

	int currentTrans = 0;
	string* parts = new string[5]; //for taking apart transition

	for (int i = 0; i < numStates; i++)
	{
		Q[i].name = tempStates[i];
		Q[i].list = NULL;
	}

	//loop through all states in Q arr
	for (int i = 0; i < numStates; i++)
	{
		//find transitions for state i
		for (int j = 0; j < numTrans; j++)
		{
			trans = tempTrans[j].substr(1, tempTrans[j].length());
			p.split(trans, ',', parts);

			if (Q[i].name == parts[0])
			{
				addTransition(Q, numStates, &Q[i], parts);
			}
		}
	}

	if (manual)
	{
		cout << p.wrap("Enter a file name for this machine, the '.txt' extension will not be added automatically", 80) << endl;
		
		do
		{
			cin >> ans;

			if (ans != "")
			{
				name = ans;
				std::ofstream fout;
				fout.open(ans);

				if (fout.bad())
				{
					cout << "Error in trying to create file." << endl;
				}

				fout << '(' << states << ')' << endl;
				fout << start << endl;
				fout << language << endl;

				fout << '{';
				for (int i = 0; i < numTrans; i++)
				{
					fout << tempTrans[i];
					if (i != 0 && i != (numTrans - 1))
					{
						fout << ',';
					}
				}
				fout << '}' << endl;
				fout.close();
			}
		} while (ans == "");
		/*
		string states;
		string start;
		string language;
		string tempTrans
		*/
	}
}

void TTM::addTransition(state* list, int numStates, state* current, string* parts)
{
	bool found = false;
	int i = 0;
	transition* temp = NULL;

	if (current->list != NULL)
	{
		temp = current->list;
	}

	while (!found && i < numStates)
	{
		if (list[i].name == parts[2])
		{
			found = true;
			
			if (temp != NULL)
			{
				while (temp->nextTrans != NULL)
				{
					temp = temp->nextTrans;
				}
				temp->nextTrans = new transition;
				temp = temp->nextTrans;
			}
			else
			{
				current->list = new transition;
				temp = current->list;
			}

			temp->nextTrans = NULL;
			temp->read = parts[1][0];
			temp->nextState = &list[i];
			temp->write = parts[3][0];
			
			if (parts[4][0] == 'L')
			{
				temp->dir = 0;
			}
			if (parts[4][0] == 'R')
			{
				temp->dir = 1;
			}
		}
		else
		{
			i++;
		}
	}
}

/*
TTM::~TTM()
{
	if (Q != NULL && d != NULL)
	{
		delete[] Q;
		delete[] d;
	}
}
*/