#pragma once
#include "components.h"

// convert string to TCHAR
void string2TCHAR(std::string * pInput, TCHAR * output, const int SIZE) // SIZE of TCHAR
{
	// copies chars over
	for (int i = 0; i < pInput->length() && i < SIZE; i++) 
	{
		output[i] = pInput->at(i);
	}

	// insert null terminator
	if (SIZE > pInput->length())
	{
		output[pInput->length()] = '\0'; // if the input length is less than the TCHAR size, insernt the null terminator at the end of the copied string
	}
	else
	{
		output[SIZE - 1] = '\0'; // if the input was cut off, or filled the entire TCHAR, then insert the terminator at the end of the TCHAR
	}
}

// TCHAR to string
void TCHAR2String(TCHAR* input, const int SIZE, std::string* pOutput) // TCHAR, its size, and then output string
{
	// copies chars over
	for (int i = 0; i < SIZE && input[i] != '\0'; i++)
	{
		pOutput->push_back(input[i]);
	}
}


// solves one step of linear algebra problem
bool laStep(std::vector<std::string>* solution)
{
	// TODO: actually make this solve for the next step in a solution.

	// for example (TODO: remove this when the function is actually implemented)
	solution->push_back("Successful laStep() call! Thanks for using the beta.");
	return false;
}
