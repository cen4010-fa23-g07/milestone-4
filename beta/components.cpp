#pragma once
#include "components.h"

// convert string to TCHAR
void string_2_TCHAR(std::string * input, TCHAR * output, const int SIZE) // SIZE of TCHAR
{
	// copies chars over
	for (int i = 0; i < input->length() && i < SIZE; i++) 
	{
		output[i] = input->at(i);
	}

	// insert null terminator
	if (SIZE > input->length())
	{
		output[input->length()] = '\0'; // if the input length is less than the TCHAR size, insernt the null terminator at the end of the copied string
	}
	else
	{
		output[SIZE - 1] = '\0'; // if the input was cut off, or filled the entire TCHAR, then insert the terminator at the end of the TCHAR
	}
}


// solves one step of linear algebra problem
void la_step(std::vector<std::string>* solution)
{
	// TODO: actually make this solve for the next step in a solution.

	// for example (TODO: remove this when the function is actually implemented)
	solution->push_back("y = mx + b");
}
