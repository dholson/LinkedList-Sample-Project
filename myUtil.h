#ifndef MY_UTIL_H
#define MY_UTIL_H

bool yesOrNo();											// requires std input = 'y', 'Y', 'n', or 'N'
bool inRange(int ichk, int min, int max = 999999);		// compares parameter "ichk" with parameters "min" and "max"
int strcmpIgnoreCase(const char a[], const char b[]);	// compares two char arrays ignores upper or lower case
void getString(char str[]);								// returns string value from std input
int getInt();											// returns integer value from std input
void pause();											// prompts and pauses for std input

#endif
