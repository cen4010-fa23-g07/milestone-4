// sysofequation.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;
vector<string> find_tokens(vector<string>, string);

int main()
{
    string equation = "5x +7y +7z = 20";
    vector<string> labels;
    find_tokens(labels, equation);

    for (int i = 0; i < labels.size(); i++) {
        cout << labels[i] << endl;
    }
}

vector<string> find_tokens(vector<string>label, string s)
{
    vector<string> equation_labels;
    char delim = ' ';
    stringstream ss(s);
    vector<string> token_eq;
    while (getline(ss, s, delim)) {
        token_eq.push_back(s);
    }

    for (int i = 0; i < token_eq.size(); i++) {
        if (token_eq[i] == "+")
        {
            equation_labels[i] = "+op";
        }
        else if (token_eq[i] == "-") {
            equation_labels[i] = "-op";

        }
        else if (token_eq[i] == "x" || token_eq[i] == "y") {
            equation_labels[i] = "var";
        }
        else if (token_eq[i]== "=") {
            equation_labels[i] = "=op";

        }
      
    }
    for (int i = 0; i < equation_labels.size(); i++) {
        label[i] = equation_labels[i];
    }
    return label;

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
