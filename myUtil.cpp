//  Useful functions:
//					  int strcmpIgnoreCase(const char a[], const char b[])
//                    bool yesOrNo();
//                    bool inRange(int ichk, int min, int max);
//                    void getString(char str[]);
//                    int getInt();
//                    void pause();
//
#include <iostream>
#include <algorithm>
#include <cstring>
#include "Song.h"
#include "myUtil.h"

using namespace std;

int strcmpIgnoreCase(const char a[], const char b[])
{
	/* This function compares two char arrays (elements converted to lower case) and returns an integer value
	return = <0  when a[i] < b[i]; or a[i...] = b[i...] and strlen(a) < strlen(b)
	return =  0  when a[i] = b[i] and strlen(a) = strlen(b)
	return = >0  when a[i] > b[i]; or a[i...] = b[i...] and strlen(a) > strlen(b)
	*/
	int minLength;

	minLength = min(strlen(a), strlen(b)) - 1;
	for (int i = 0; i <= minLength; i++)
	{
		if (tolower(a[i]) > tolower(b[i]))
		{
			return 1;
		}
		else if (tolower(a[i]) < tolower(b[i]))
		{
			return -1;
		}
	}
	return (strlen(a) - strlen(b));
}
bool yesOrNo()
{
	/* This function reads char from std input. Requires user to enter 'y' or 'n' and returns a boolean value
	return = true  when reply is 'y' or 'Y'
	return = false  when reply is 'n' or 'N'
	*/
	char reply;

	while (true) {
		cin >> reply;
		while (!cin) {
			cin.clear();
			cin.ignore(MAX_CHAR, '\n');
			cout << "Please answer 'y' or 'n'. ";
			cin >> reply;
		}
		cin.ignore(MAX_CHAR, '\n');

		switch (reply) {
		case 'y':
		case 'Y':
			return true;           //  user replied yes, return true
			break;
		case 'n':
		case 'N':
			return false;         //  user replied no, return false
			break;
		default:
			cout << "Please answer 'y' or 'n'. ";
			continue;
			break;
		}
	}
}
bool inRange(int ichk, int min, int max)
{
	/* This function compares parameter "ichk" with parameters "min" and "max" and returns a boolean value
	return = true  when ichk >= min and ichk <= max
	return = false when ichk <  min or  ichk >  max
	*/
	if (ichk >= min && ichk <= max) {
		return true;
	}
	else {
		cout << ichk << " is out of range (" << min << "-" << max << "). Try again." << endl;
		return false;
	}
}
/* The following 3 functions were taken from examples written by instructor Li Liang for PCC CS162  */
void getString(char str[])
{
	cin.get(str, MAX_CHAR, '\n');
	while (!cin) {
		cin.clear();
		cin.ignore(MAX_CHAR, '\n');
		cout << "Please try again: ";
		cin.get(str, MAX_CHAR, '\n');
	}
	cin.ignore(MAX_CHAR, '\n');
	return;
}
int getInt()
{
	int n;
	cin >> n;
	while (!cin) {
		cin.clear();
		cin.ignore(MAX_CHAR, '\n');
		cout << "Illegal integer. Please try again: ";
		cin >> n;
	}
	cin.ignore(MAX_CHAR, '\n');
	return n;
}
void pause()
{
	char ch[MAX_CHAR];

	cout << "Press any key to continue ...";
	cin.get(ch, MAX_CHAR, '\n');
	cin.clear();
	cin.ignore(MAX_CHAR, '\n');
}
