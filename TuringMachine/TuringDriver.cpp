#include <iostream>
#include "TTM.h"
#include "Parcer.h"

using std::cout;
using std::endl;

int main()
{
	//misc variables
	Parcer p;
 
	//menu variables
	string ans = "";
	string fileName;

	//TM variable
	TTM* machine = NULL;
	string tape = "";
	int result = 0;

	cout << p.wrap("Would you like to load a file or manually create a machine? \n\n1.load existing file \n\n2.manually create machine",80) << endl;

	while (ans[0] != '1' && ans[0] != '2')
	{
		cin >> ans;
		if (ans[0] == '1')
		{
			cout << p.wrap("Enter the file name, including any extension. The format of the file should be as follows: \n\n(Q0,Q1,..,Qn)  //list of states \n\nS0  //starting state \n\n#ABCD..etc  //accepted language of the machine \n\n{(Sc,R,Sn,W,D),..}  //List of transitions in the order (current state, read character, next state, write character, direction)", 80) << endl;
			cout << '>';
			cin >> fileName;
			try
			{
				machine = new TTM(fileName);
			}
			catch (const std::exception&)
			{
				cout << p.wrap("Something seems to be seriously wrong with that text file, please fix the file to fit the correct format or try a different file", 80) << endl;
			}
		}
		else if (ans[0] == '2')
		{
			machine = new TTM;
		}
		else
		{
			cout << "Enter a valid option (1 or 2)" << endl;
		}
	}

	cout << p.wrap("Enter an input string for the machine.", 80) << endl;
	cin >> tape;
	result = machine->Run(tape);
	ans = "";

	while (ans[0] != '3')
	{
		cout << p.wrap("Select one of the following options: \n1.Run machine again \n2.Discard machine and create a new one \n3.Exit", 80) << endl;
		cin >> ans;

		if (ans[0] == '1')
		{
			cout << p.wrap("Enter an input string for the machine.", 80) << endl;
			cin >> tape;
			result = machine->Run(tape);
			ans = "1";
		}//end option 1
		else if (ans[0] == '2')
		{
			//delete machine //broken?
			delete machine;

			cout << p.wrap("Would you like to load a file or manually create a machine? \n1.load existing file \n2.manually create machine", 80) << endl;
			ans = "";

			while (ans[0] != '1' && ans[0] != '2')
			{
				cin >> ans;
				if (ans[0] == '1')
				{
					cout << p.wrap("Enter the file name, including any extension. The format of the file should be as follows: \n\n(Q0,Q1,..,Qn)  //list of states \n\nS0  //starting state \n\n#ABCD..etc  //accepted language of the machine \n\n{(Sc,R,Sn,W,D),..}  //List of transitions in the order (current state, read character, next state, write character, direction)", 80) << endl;
					cin >> fileName;
					try
					{
						machine = new TTM(fileName);

						cout << p.wrap("Enter an input string for the machine.", 80) << endl;
						cin >> tape;
						result = machine->Run(tape);
					}
					catch (const std::exception&)
					{
						cout << p.wrap("Something seems to be seriously wrong with that text file, please fix the file to fit the correct format or try a different file", 80) << endl;
					}
				}
				else if (ans[0] == '2')
				{
					machine = new TTM;
				}
				else
				{
					cout << "Enter a valid option (1 or 2)" << endl;
					cin >> ans;
				}
			}
		}//end option 2
		else if(ans[0] != '3')
		{
			cout << p.wrap("You have entered an invalid menu option", 80) << endl;
		}//end invalid option
	}//end menu loop

	return result;
}