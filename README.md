# TuringMachineSimulator
A small c++ program that is able to simulate (at least small) Turing Machines

{Note: this wasn't originally made to be used by other people, so its currently not very user friendly}
This Turing Machine simulator reads in a file or lets the user define some automata 
	with an "infinite" tape. The tape is an input of a string of characters which have
	'#' characters on the ends to signify the end of the tape. The tape will extend if
	the machine moves "off" the tape.

There are 4 main parts to an automata for this TM simulator definition:
1.) A set of states for the machine to be in
	>Each state is a string of characters. My examples have short state names, but 
	they can be any length as long as it doesnt go over the standard string length max
2.) A state designated as the starting state
3.) An alphabet
	>currently this is setup where each element of the alphabet is a single character
4.) A set of transition functions
	>Each transition function is formatted as:
	([current state],[read character on tape],[next state],[write character to tape],[direction to move along tape: 'R'/'L'])

There are some example files if you need something to reference.
-bitFLip: 
	takes a binary string as input and will flip all the bits
-mod4: 
	takes a string of 1's as input, where the (amount of digits - 1) represents a decimal
	number. The resulting string will be reduced to whatever the input number mod 4 is
	ex.) input -> 111111 //this is 5
	     output-> 11     //this is 1
-subtract:
	this uses the same way of representing numbers as mod4. It takes two numbers
	separated by a '-' and will output the resulting subtraction
	ex.) input -> 111111111-1111 // 8-3
	     output-> 111111	     // 5