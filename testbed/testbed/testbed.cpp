// testbed.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include<string>

std::string s;

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

int main()
{
	int input = 0;

	std::cin >> input;

	char * strRep = chin_itoa(input);

	std::cout << strRep;

	delete[] strRep;

	std::cin >> input;
	std::cin.ignore();
	return 0;

	//Making comment in master branch from home desktop, think this is the workflow to go. 
}

