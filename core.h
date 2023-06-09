
// SAFE-GUARD: 
// It is good practice to apply safe-guards to header files
// Safe-guard's ensures only 1 copy of the header file is used in the project build
// The macro name should be mirroring the file name with _ for spaces, dots, etc.

#ifndef CORE_H
#define CORE_H

//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

// Clear the standard input buffer
void clearInputBuffer(void);

// Wait for user to input the "enter" key to continue
void suspend(void);


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// return an integer value and receives no arguments
int inputInt();

// return a positive integer value and receives no arguments
int inputIntPositive();

// return an integer value and receives two arguments
int  inputIntRange(int, int);

// return a single character value and receives one argument(string)
char inputCharOption(char str[]);

// this function obtain input for a string value with number of characters in the range
void  inputCString(char*, int, int);

// this function is to display an array of 10-character digits as a formatted phone number
void  displayFormattedPhone(const char*);

// !!! DO NOT DELETE THE BELOW LINE !!!
#endif // !CORE_H