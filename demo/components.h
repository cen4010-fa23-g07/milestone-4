#pragma once

// 3rd party microsoft & and cpp headers
#include <windows.h> // windows.h required for windows app
#include <tchar.h> // defines TCHAR macro whe unicode is not enabled || consider getting rid of tchar for string. research says tchar is outdated, as non unicode compiles will not occur.
#include <new> // required for using the new operator
#include <commctrl.h> // user control intefaces
#include <windowsx.h> // windows such as buttons and input boxes
#include <math.h> // this will help with the calculator functions.
#include <vector> // for linear algebra and sys eq solvers.
#include <string> // not stupid like tchar

// custom compenents

// la_step solves one step of a given solution vector<string>.
void la_step(std::vector<std::string>* solution); 
