#include "Parcer.h"

Parcer::Parcer() {}

/*
	Cout a single string that will wrap given a buffer width.
	Use the cout << function and call the parcer.wrap() within

	@param input string and int buffer width
	@return the last line (this is passed into the cout << function)
*/
string Parcer::wrap(string input, int width)
{
	string temp = "";
	int counter = 1; //init. at 1 so a string "hello there" will be associated with 2 words for the one space

	//finding out how many words there will be
	for (int x = 0; x < input.length(); x++)
	{
		if (input[x] == ' ')
		{
			counter++;
		}
	}

	//creating a  dynamic array of words
	string* words = new string[counter];

	//splitting the input up into the above created array
	split(input, ' ', words);

	for (int x = 0; x < counter; x++)
	{
		if (((temp + words[x]).length() <= width) && (words[x][0] != '\n'))
		{
			//if adding the next word doesnt make it longer than the buffer width, then add it to the current line
			temp += words[x] + ' ';
		}
		else
		{
			//adding the next word exceded the buffer width, so commit the current line and start a new one
			cout << temp << endl;
			temp = words[x] + ' ';
		}
	}

	return temp;
}

/*
	splits a string into an array of strings (or "words")
	@param string to be split, a char to split by, a string pointer
	@return "returns" an arrary of strings
*/
void Parcer::split(string toSplit, char splitBy, string words[])
{
	string temps = "";
	int count = 0;

	for (int x = 0; x < toSplit.length(); x++)
	{
		if (toSplit[x] != splitBy)
		{
			temps = temps + toSplit[x];
		}
		else
		{
			/*
			temp = new string[count + 1];
			for (int i = 0; i < count; i++)
			{
				temp[i] = words[i];
			}
			temp[count] = temps;
			*/
			//delete words;
			words[count] = temps;

			temps = "";
			count++;
		}

	}
	words[count] = temps;
}

/*
	splitting a string into 'words' separated by an opening and closing character
	ex.)    "{(AB),(BC)}" would be split into "AB" & "BC" with '(' as OpenChar and ')' as CloseChar
	If there are an unequal amount of openChars and closeChars, the function will do nothing

	@param string to be split, opening character, closing character, integer pointer
	@return a string pointer
*/
string* Parcer::split(string toSplit, char openChar, char closeChar, int& numWords)
{
	

	int numOp = 0;
	int numCl = 0;
	string* words = NULL;

	//counting all opening and closing chars
	for (int i = 0; i < toSplit.length(); i++)
	{
		if (toSplit[i] == openChar)
		{
			numOp++;
		}
		else if (toSplit[i] == closeChar)
		{
			numCl++;
		}
	}

	//rest done in here
	if (numOp == numCl)
	{
		numWords = numOp;
		words = new string[numOp];
		string temp = "";
		int i = 0;
		int c = 0;
		
		//looping through all characters in toSplit
		while (i < toSplit.length())
		{
			//if its an open character
			if (toSplit[i] == openChar)
			{
				//putting all chars up to next close char into one string
				while (toSplit[i] != closeChar)
				{
					temp += toSplit[i];
					i++;
				}//end close while
				temp += toSplit[i];
				i++;

				//putting that string into the split array
				words[c] = temp;
				c++;
				temp = "";
			}//end open if
			else
			{
				i++;
			}
		}//end main while
	}
	else
	{
		numWords = -1;
	}
	return words;
}

/*
	removes spaces from a string
	@param string pointer
	@return [void]
*/
void Parcer::cutOut(string& input)
{
	//change the string to no longer have spaces
	string temp = "";

	for (int i = 0; i < input.length(); i++)
	{
		if (input[i] != ' ')
		{
			temp += input[i];
		}
	}

	input = temp;
}

/*
	removes all instances of a specific character from a string
	@param string pointer, char to take out
	@return [void]
*/
void Parcer::cutOut(string& input, char toTrim)
{
	//change the string to no longer have toTrim chars
	string temp = "";

	for (int i = 0; i < input.length(); i++)
	{
		if (input[i] != toTrim)
		{
			temp += input[i];
		}
	}

	input = temp;
}

/*
	removes spaces at the ends of a string
	@param string pointer
	@return [void]
*/
void Parcer::trim(string& input) 
{
	//removes spaces at the ends of a string
	string temp = "";

	while (input[0] != ' ' || input[input.length() - 1] != ' ')
	{
		if (input[0] == ' ')
		{
			for (int i = 1; i < input.length(); i++)
			{
				temp += input[i];
			}
			input = temp;
		}
		if (input[input.length() - 1] == ' ')
		{
			for (int i = 0; i < input.length() - 1; i++)
			{
				temp += input[i];
			}
			input = temp;
		}
	}
	
}

/*
	removes all instances of a specified character from the ends of a string
	@param string pointer, toTrim character
	@return [void]
*/
void Parcer::trim(string& input, char toTrim) 
{
	string temp = "";

	while (input[0] == toTrim || input[input.length() - 1] == toTrim)
	{
		if (input[0] == toTrim)
		{
			for (int i = 1; i < input.length(); i++)
			{
				temp += input[i];
			}
			input = temp;
		}
		temp.clear();

		if (input[input.length() - 1] == toTrim)
		{
			for (int i = 0; i < input.length() - 1; i++)
			{
				temp += input[i];
			}
			input = temp;
		}
		temp.clear();
	}
	
}

/*
	removes any repeating string instances from a string array
	@param string pointer to array, integer pointer to number of strings in array ("words")
	@return [void]
*/
void Parcer::removeCopy(string* words, int& numWords)
{
	string* temp = new string[numWords];
	for (int i = 0; i < numWords; i++)
	{
		temp[i] = "";
	}

	int count = 0;

	for (int x = 0; x < numWords; x++)
	{
		bool found = false;
		int y = 0;

		while (!found)
		{
			if (words[x] == temp[y])
			{
				found = true;
			}
			else if (temp[y] == "")
			{
				temp[y] = words[x];
				count++;
				found = true;
			}
			y++;
		}
	}

	words = temp;
	numWords = count;

	temp = new string[count];

	//copying over to shortened array
	for (int i = 0; i < count; i++)
	{
		temp[i] = words[i];
	}

	words = temp;
}

/*
	removes any repeating instances of a character from a string
	@param string pointer
	@return [void]
*/
void Parcer::removeCopy(string& word)
{
	string temp;

	for (int x = 0; x < word.length(); x++)
	{
		bool found = false;
		int y = 0;

		while (!found)
		{
			if (word[x] == temp[y])
			{
				found = true;
			}
			else if (temp[y] == '\0')
			{
				temp += word[x];
				found = true;
			}
			y++;
		}
	}

	word = temp;
}

/*
	inserts commas between all characters in a string
	@param string pointer
	@return resulting string
*/
string Parcer::partition(const string& word)
{
	string temp = "";

	for (int i = 0; i < word.length(); i++)
	{
		if (i == 0)
		{
			temp = word[0];
		}
		else
		{
			temp = temp + ',' + word[i];
		}
	}

	return temp;
}

/*
	finds a specified string within an array of strings
	@param string array pointer, string to find, array size integer
	@return array index integer
*/
int Parcer::searchArray(string* words, string toFind, const int& numWords) 
{
	for (int i = 0; i < numWords; i++)
	{
		if (words[i] == toFind)
		{
			return i;
		}
	}

	return -1;
}

/*
	adds a string to a string array (like with a vector)
	@param string pointer, string to add, integer pointer for number of words
	@return [void]
*/
void Parcer::appendArray(string* words, string toAdd, int& numWords)
{
	//add another string to the end of an array of strings (like a vector)
	string* temp = new string[numWords + 1];
	string* temp2 = words;

	for (int i = 0; i < numWords; i++)
	{
		temp[i] = words[i];
	}

	temp[numWords] = toAdd;
	words = temp;
	delete[] temp2;
	numWords++;
}

/*
	looks for a character within a string
	@param string, character to find
	@return bool if found
*/
bool Parcer::inStr(const string& word, char toFind)
{
	for (int i = 0; i < word.length(); i++)
	{
		if (word[i] == toFind)
		{
			return true;
		}
	}
	return false;
}

/*
	sorts an array of strings in alphabetical order
	@param string pointer, integer of array size
	@return [void]
*/
void Parcer::alphSort(string* words, const int& numWords)
{
	string temp;

	//bubble sort with strings
	for (int z = 0; z < numWords - 1; z++)
	{
		for (int x = 0; x < numWords - 1; x++)
		{
			bool greater = false; //char[x] > char[x+1]
			bool equal = true;
			int y = 0;
			while (equal)
			{
				if (words[x][y] < words[x + 1][y])
				{
					equal = 0;
				}
				else if (words[x][y] > words[x + 1][y])
				{
					greater = true;
					equal = 0;
				}
				y++;
			}

			if (greater)
			{
				temp = words[x];
				words[x] = words[x + 1];
				words[x + 1] = temp;
			}
		}
	}
}

/*
	sorts the characters of a string in alphabetical order
	@param "word" string
	@return [void]
*/
void Parcer::alphSort(string& word)
{
	//bubble sort a string
	char temp = '\0';

	for (int x = 0; x < word.length() - 1; x++)
	{
		for (int y = 0; y < word.length() - 1; y++)
		{
			if (word[y] > word[y + 1])
			{
				temp = word[y];
				word[y] = word[y + 1];
				word[y + 1] = temp;
			}
		}
	}
}

/*
	converts a string to it's pig latin equivalent
	@param input string
	@return pig latin string
*/
string Parcer::toPig(string input)
{
	//convert a string to it's Pig Latin equivalent
	string temp = "";

	for (int i = 1; i < input.size(); i++)
	{
		temp += input[i];
	}
	temp += input[0] + "ay";

	return temp;
}