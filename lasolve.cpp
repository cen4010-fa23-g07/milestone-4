// lasolve.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

vector<string> step(vector < string>, vector<string>);
vector<string> create_new_eq(vector<string>, int, string, string);
vector<string> create_new_labels(vector<string>);

vector<string> step(vector<string> token_eq, vector<string> label_eq) {
	//cout << "size is " << token_eq.size() << endl;
	int step_position;
	string step_type;
	string step_result;

	bool step_completed = false;
	while (!step_completed) {
		for (int i = 0; i < token_eq.size(); i++) {
			//cout << "got to for " << endl;
			//cout << "i is " << i << endl;
			//cout << "label eq size is " << label_eq.size() << endl;
			//cout << "label is " << label_eq[i] << endl;
			if (label_eq[i].find("+") != string::npos || label_eq[i].find("-") != string::npos) {
				//cout << "entered +" << endl;
				// if const + const or var + var
				if (label_eq[i - 1] == label_eq[i + 1]) {
					float el1 = stof(token_eq[i - 1]);
					float el2 = stof(token_eq[i + 1]);
					float result;
					if (label_eq[i].find("+") != string::npos) {
						result = el1 + el2;
						step_type = "+op";
					}
					else {
						result = el1 - el2;
						step_type = "-op";
					}
					step_result = to_string(result);
					// if var, append variable to end of result
					if (label_eq[i - 1] == "var") {
						step_result += "x";
					}
					step_position = i;
					
					step_completed = true;
					break;
				}
				
			} // end of +op
			//cout << "after +" << endl;
			
			// only need to solve now
			if (label_eq.size() == 3) {
				//cout << "entered final" << endl;
				float var_el;
				float const_el;
				if (label_eq[0] == "var") {
					//cout << "entered if" << endl;
					//cout << "token_eq[0] is " << token_eq[0] << endl;
					var_el = stof(token_eq[0]);
					
					const_el = stof(token_eq[2]);
					//cout << "const el is " << const_el << endl;
				}
				else {
					var_el = stof(token_eq[2]);
					const_el = stof(token_eq[0]);
				}

				//cout << "finished assignment" << endl;

				const_el /= var_el;
				//cout << "const el is " << const_el << endl;

				//string final_var = "x";
				step_result = to_string(const_el);
				//cout << "step result is " << step_result << endl;
				step_type = "solve";
				step_position = -1;
				step_completed = true;
				break;
			}
			//cout << "ended for " << endl;
		} // end of token_eq for

	} // end of while !step_completed

	vector<string> new_token_eq = create_new_eq(token_eq, step_position, step_type, step_result);
	return new_token_eq;
	//vector<string> new_labels_eq = create_new_labels(new_token_eq);
}

vector<string> create_new_eq(vector<string> orig_token_eq, int pos, string type, string result) {
	//cout << "result is " << result << endl;
	if (type == "+op" || type == "-op") {
		orig_token_eq.erase(orig_token_eq.begin() + (pos - 1));
		orig_token_eq.erase(orig_token_eq.begin() + (pos - 1));
		orig_token_eq.erase(orig_token_eq.begin() + (pos - 1));
		orig_token_eq.insert(orig_token_eq.begin() + (pos - 1), result);
	}
	else if (type == "solve") {
		vector<string> final_eq(3);
		final_eq[0] = "x";
		final_eq[1] = "=";
		final_eq[2] = result;
		//cout << "result is " << result << endl;
		return final_eq;
	}

	return orig_token_eq;
}

vector<string> create_new_labels(vector<string> token_eq) {
	vector<string> labels(token_eq.size());

	for (int i = 0; i < token_eq.size(); i++) {
		if (token_eq[i] == "+") {
			labels[i] = "+op";
		}
		else if (token_eq[i] == "-") {
			labels[i] = "-op";
		}
		else if (token_eq[i] == "=") {
			labels[i] = "=op";
		}
		else if (token_eq[i].find("x") != string::npos) {
			labels[i] = "var";
		}
		else {
			labels[i] = "const";
		}
	}

	return labels;
}

int main()
{
	
	string orig_eq = "12x - 16x = 15 + 15";
	char delim = ' ';
	stringstream ss(orig_eq);

	// holds separated equation
	vector<string> token_eq;
	while (getline(ss, orig_eq, delim)) {
		token_eq.push_back(orig_eq);
	}

	for (int i = 0; i < token_eq.size(); i++) {
		cout << token_eq[i] << " ";
	}
	cout << endl;

	// holds labels for each element in separated equation
	vector<string> orig_labels = create_new_labels(token_eq);

	for (int i = 0; i < orig_labels.size(); i++) {
		cout << orig_labels[i] << " ";
	}
	cout << endl;

	//// will hold updated eq
	//vector<string> step1 = step(token_eq, orig_labels);
	//vector<string> step1labels = create_new_labels(step1);

	//for (int i = 0; i < step1.size(); i++) {
	//	cout << step1[i] << " ";
	//}
	//cout << endl;

	//for (int i = 0; i < step1labels.size(); i++) {
	//	cout << step1labels[i] << " ";
	//}
	//cout << endl;

	bool more_steps = true;
	bool last = false;
	bool first = true;
	vector<string> step_eq;
	vector<string> label_step_eq;
	while (more_steps) {
		//cout << "entered while" << endl;
		if (first) {
			//cout << "entered first" << endl;
			step_eq = step(token_eq, orig_labels);
			//cout << "finished step" << endl;
			first = false;
		}
		else {
			step_eq = step(step_eq, label_step_eq);
		}

		for (int i = 0; i < step_eq.size(); i++) {
			cout << step_eq[i] << " ";
		}
		cout << endl;

		label_step_eq = create_new_labels(step_eq);

		//cout << "step_eq.size() is " << step_eq.size() << endl;
		if (step_eq.size() == 3 && last == false) {
			last = true;
		}
		else if (step_eq.size() == 3 && last) {
			more_steps = false;
		}


	}
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
