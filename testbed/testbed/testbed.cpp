// testbed.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include<string>

using namespace std;
char* chin_itoa(int i)
{
	bool isNeg = i < 0;
	int posI = abs(i); //Take absolute of i to avoid having to deal with negative and positive cases all over the place. 

	int numDigits = 1;
	if (posI != 0)  // log of 0 is undefined, so handle an edge case here. 
	{
		numDigits = int ( floor(log10(posI)) )  + 1;
	}
	int alphaLength = numDigits + 1; //Add 1 at end for null char.
	if (isNeg)
	{
		++alphaLength;
	}

	char * returnCharArray = new char[alphaLength];
	returnCharArray[alphaLength - 1] = 0;

	int endingLoopIndex = 0;

	if (isNeg)
	{
		endingLoopIndex = 1;
		returnCharArray[0] = '-';
	}

	for (int loopIndex = alphaLength - 2; loopIndex >= endingLoopIndex; --loopIndex)
	{
		int remainder = posI % 10;
		returnCharArray[loopIndex] = '0' + remainder;
		posI /= 10;
	}

	return returnCharArray;
}

void permutation(string str, string prefix)
{
	if (str.length() == 0)
	{
		std:cout << "Terminal case, prefix is: " << prefix << std::endl;		

	}
	else
	{
		std::cout << "str: " << str << ", prefix: " << prefix << std::endl;
		for (int i = 0; i < str.length(); ++i)
		{
			std::cout << "iteration i: " << i << ", str is: " << str << ", prefix is:" << prefix << "" << std::endl;
			string rem = str.substr(0, i) + str.substr(i + 1);			
			std::cout << "str.substr(0, i):" << (str.substr(0, i)) << ", .substr(i + 1): " << (str.substr(i + 1)) << std::endl;
			permutation(rem, prefix + str[i]);
		}
	}
}

void permutation(string str) 
{
	permutation(str, "");
}


int main()
{
/*	int input = 0;

	std::cin >> input;

	char * strRep = chin_itoa(input);

	std::cout << strRep;

	delete[] strRep;
*/

	string s = "";
	std:cin >> s; 
	permutation(s);

	std::cin >> s;
	std::cin.ignore();

	return 0;

	//And now, just to make sure this is correct: this is me overwriting the comment from my laptop. Still in master branch. 
}

