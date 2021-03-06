// testbed.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include<string>
#include <map>

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

void substringPermutation(string smaller, string larger) 
{
	//Format: Permutation of string found at position x of larger string: print smaller.length characters from it. 

	if (smaller.length() == 0)
	{
		std::cout << "No substring found!";
		return;
	}
		

	if (smaller.length() > larger.length()) 
	{
		std::cout << "\'smaller\' string " << smaller << " is longer than \'larger\' string " << larger; 
		return;
	}

	bool everFoundSubString = false;

	for (int i = 0; i < larger.length() - smaller.length() + 1; ++i)  //TODO: Check terminal value of loop! 
	{
		//First fill the bufferofCharacters
		std::map< char, int > bufferOfCharacters;			
		for (int j = i; j < i + smaller.length(); ++j)  //TODO Optimization: Instead of making buffer anew all the time, just chuck out the oldest character and insert the newest character
		{
			if ( bufferOfCharacters.count( larger[ j ] ) > 0  ) //i.e. this is not the first time we've seen this character
			{
				++bufferOfCharacters[larger[j]];
			}
			else 
			{
				bufferOfCharacters.insert(make_pair(larger[j], 1));
			}

		}

		bool containsSubstring = true;

		for (int k = 0; k < smaller.length(); ++k) 
		{
			int countInBuffer = bufferOfCharacters.count(smaller[k]);
			if (countInBuffer == 0)  //Just exit out from this loop, go on to next buffer. 
			{
				containsSubstring = false;
				break;
			}

			if (bufferOfCharacters[smaller[k] ] == 0)  //This means that there are more instances of this character in smaller than there are in the buffer, e.g. smaller == "aaa" and larger == "abbbbb". 
			{
				containsSubstring = false;
				break;
			}

			--bufferOfCharacters[smaller[k]];
		}

		if (containsSubstring) 
		{
			std::cout << "Permutation of string found at position " << i << " :";
			for (int j = i; j < i + smaller.length(); ++j) 
			{
				std::cout << larger[j];
			}
			std::cout << std::endl;
			everFoundSubString = true; 
		}
	}

	if (!everFoundSubString) 
	{
		std::cout << "No substring found!";
	}
}

// "abc de f    ", 12
char * URLify(char * inputStr, int length) 
{
	int firstNotSpaceCharIndex = length - 1; 
	int currentCharToCopyIndex = firstNotSpaceCharIndex;
	
	for (int i = firstNotSpaceCharIndex; i >= 0; --i) 
	{
		if (inputStr[i] != ' ')
		{
			firstNotSpaceCharIndex = i;
			break;
		}		
	}	

	//Now traverse until we hit the start of the string, or we find another space. 
	
	for (int j = firstNotSpaceCharIndex; j >= 0; --j) 
	{
		if ( inputStr[j] == ' ' )
		{			
			inputStr[currentCharToCopyIndex--] = '0';
			inputStr[currentCharToCopyIndex--] = '2';
			inputStr[currentCharToCopyIndex--] = '%';
						
		}
		else 
		{
			inputStr[currentCharToCopyIndex--] = inputStr[j];			
		}		
	}	

	return inputStr;
}

void oneOrZeroEdits(string a, string b)  //Strings to test against: blank string, abc abc, cat at, cat bat, blank string a, cat, twodogs
{
	size_t lengthA = a.length();
	size_t lengthB = b.length();

	size_t absDifference = abs(int(lengthA - lengthB));

	if (absDifference > 2)
	{
		std::cout << "Difference in length of strings is greater than 2. Strings are not One or Zero Edits away";
		return;
	}

	int numEdits = 0; 

	if (absDifference == 0) //Check strings are matching, get up to one miss. 
	{
		for (size_t i = 0; i < lengthA; ++i) 
		{
			if (a[i] != b[i]) 
			{
				++numEdits; 
				if (numEdits > 1) 
				{
					std::cout << "More than 2 differences found, Strings are not One or Zero Edits away";
					return;
				}
			}
		}

		if (numEdits == 0) 
		{
			std::cout << "0 differences found, Strings are zero Edits away";
			return;
		}
		else if (numEdits == 1) 
		{
			std::cout << "1 difference found, Strings are not One Edit away";
			return;
		}
	}

	//Only case remaining is difference of string length is one. 

	string* shorterStringPtr = &a; 
	string* longerStringPtr = &b;

	if (lengthA > lengthB) 
	{
		string* temp = shorterStringPtr;
		shorterStringPtr = longerStringPtr;
		longerStringPtr = temp;
	}

	string& shorterString = *shorterStringPtr; 
	string& longerString = *longerStringPtr;

	
	size_t shorterStringCurrentIndex = 0; 
	size_t longerStringCurrentIndex = 0; 

	while (shorterStringCurrentIndex < shorterString.length() && longerStringCurrentIndex < longerString.length()) 
	{
		if (shorterString[shorterStringCurrentIndex] != longerString[longerStringCurrentIndex]) 
		{
			++numEdits; 
			if (numEdits > 1)
			{
				std::cout << "More than 2 differences found, Strings are not One or Zero Edits away";
				return;
			}

			//We've found our first edit. Since we know the difference between the string lengths is exactly one, the only way for the strings to still be one edit away is for the shorter string to have the same character as the longer string in the current index. Thus, just increment the longerStringCurrentIndex;
			++longerStringCurrentIndex; 
			continue; 
		}

		++shorterStringCurrentIndex;
		++longerStringCurrentIndex;
	}

	//Exiting the while loop, numEdits is 0 or 1. 0 means everything but the final character of the longerString is in the shorter string. 
	if (numEdits == 0) 
	{
		std::cout << "1 difference found at end of shorter string, Strings are One Edit away";
		return;
	}

	if (numEdits == 1) 
	{
		//First check to see if we have reached the end of both strings. If not, that
		_ASSERT((shorterStringCurrentIndex == shorterString.length() ) && (longerStringCurrentIndex == longerString.length() ));
		std::cout << "1 difference found, Strings are One Edit away";
		return;
	}	
}

void rotateMatrix() 
{
	const int size = 3;
	char matrix[size][size] =
	{
		{ 'a', 'b','c' },
		{ 'd', 'e', 'f'},
		{ 'g', 'h', 'i' }
	};

	for (int i = 0; i < size; ++i) 
	{
		for (int j = 0; j < size; ++j) 
		{
			std::cout << matrix[i][j] << " ";
		}

		std::cout << std::endl;
	}

	for (int layer = 0; layer < size / 2; ++layer) 
	{
		int first = layer; 
		int last = size - layer -1;

		for (int i = layer; i < last; ++i) 
		{
			int offset = i - first; 
			char savedTopChar = matrix[ first ][ i ];

			matrix[first][i] = matrix[last - i][first]; //Bottom Left -> Top Left 
			matrix[i][first] = matrix[ last ][i] //Bottom Left -> 
			matrix[last - i][first] = 


			matrix[last][last - i] = ; //Bottom Right -> Bottom Left 
			matrix[ i ][ last ] = matrix[ last ][ last - i ] //Top right -> Bottom left
			matrix[  ]
		}
	}
}


int main()
{
	int test;
/*	int input = 0;

	std::cin >> input;

	char * strRep = chin_itoa(input);

	std::cout << strRep;

	delete[] strRep;
*/

	/*
	string s = "";
	std:cin >> s;
	permutation(s);

	std::cin >> s;
	
	

	string smaller, larger; 
	std::cin >> smaller;
	std::cin >> larger;
	substringPermutation(smaller, larger);	
	std::cin >> smaller;

	*/

	/*
	char inputStr[] = "abc de fhag blah      "; //"abc%20de"
	int inputStrLen = 22;
	std::cout << URLify(inputStr, inputStrLen);
	*/

	/*string a, b;
	std::cin >> a; 
	std::cin >> b; 
	oneOrZeroEdits(a, b);*/

	rotateMatrix();

	

	std::cin >> test;
	return 0;

	//And now, just to make sure this is correct: this is me overwriting the comment from my laptop. Still in master branch. 
}

