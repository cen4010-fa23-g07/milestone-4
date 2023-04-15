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
	bool second_round = false;

	bool step_completed = false;
	while (!step_completed) {
		for (int i = 0; i < token_eq.size(); i++) {
			if (label_eq[i] == "+op" || label_eq[i] == "-op") {
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
				
			} // end of +/-op

			if (i == token_eq.size() - 1 && label_eq.size() != 3 && second_round == false) {
				cout << "entered if " << endl;
				second_round = true;
			}

			if (second_round) {
				//cout << "second round" << endl;
				int next_match;
				int current_match;
				string current_match_type;
				string next_match_type;
				bool wrap_around = false;
				bool wrap_around2 = false;

				/*cout << "token eq is ";
				for (int k = 0; k < token_eq.size(); k++) {
					cout << token_eq[k] << " ";
				}
				cout << endl;*/

				for (int k = 0; k < token_eq.size(); k++) {
					//cout << "size is " << token_eq.size() << endl;
					// if var +/- const or vice versa
					if (label_eq[k] == "+op" || label_eq[k] == "-op") {
					
						//cout << "i is " << k << endl;
						current_match = k - 1;
						//cout << "current match " << current_match << " " << token_eq[current_match] << endl;

						current_match_type = label_eq[k - 1];
						next_match_type = label_eq[k + 1];
						int j = k + 1;
						while (current_match_type != next_match_type && j < token_eq.size()) {
							
							/*if (current_match == j) {
								cout << "current match vs j " << current_match << " vs " << j << endl;
								j++;
								next_match_type = label_eq[j];
								continue;
							}*/


							//cout << "current match " << current_match << " " << token_eq[current_match] << endl;
							cout << current_match_type << " vs " << next_match_type << endl;
							//cout << "next match " << next_match << " " << token_eq[next_match] << endl;

							//cout << "j is " << j << endl;
							
							
							
							next_match_type = label_eq[j];
							j++;

							if (j >= token_eq.size() - 1 && wrap_around == false) {
								// test end value
								if (current_match_type == label_eq[token_eq.size() - 1]) {
									//cout << "end match type is " << label_eq[j] << endl;
									next_match_type = label_eq[j];
									continue;
								}
								// wrap around
								//cout << "wrapped" << endl;
								if (current_match != 0) {
									j = 0;
								}
								else {
									current_match = k + 1;
									current_match_type = label_eq[k + 1];
									wrap_around2 = true;
									j = 0;
									next_match_type = label_eq[j];
									continue;
								}
								
								wrap_around = true;
								next_match_type = label_eq[j];
								//cout << "end wrap" << endl;
								continue;
							}
							else if (j == current_match && wrap_around == true && !wrap_around2) {
								//cout << "inc" << endl;
								current_match = k + 1;
								current_match_type = label_eq[k + 1];
								wrap_around2 = true;
								wrap_around = false;
								j = 0;
								next_match_type = label_eq[j];
								break;
							}

							
							if (current_match == j) {
								//cout << "current match vs j " << current_match << " vs " << j << endl;
								j++;
								next_match_type = label_eq[j];
								continue;
							}
							
						}

						//j++;
						next_match = j;

						//cout << "current match " << current_match << " " << token_eq[current_match] << endl;
						//cout << "next match " << next_match << endl;

						float el1 = stof(token_eq[current_match]);
						float el2 = stof(token_eq[next_match]);
						if (next_match == token_eq.size() - 1 || current_match > next_match) {
							//cout << "current > next" << endl;
							el2 -= el1;
							// replace el2
							string el2_str = to_string(el2);
							if (label_eq[current_match] == "var") {
								el2_str += "x";
							}
							token_eq[next_match] = el2_str;
							//cout << "going to erase" << endl;
							// erase el1 and the op to the left of it
							if (next_match == token_eq.size() - 1) {
								token_eq.erase(token_eq.begin() + current_match);
								token_eq.erase(token_eq.begin() + current_match);
							}
							else {
								token_eq.erase(token_eq.begin() + current_match - 1);
								token_eq.erase(token_eq.begin() + current_match - 1);
							}
							// not permanent
							if (token_eq.size() == 3) {
								token_eq[1] = "=";
							}
							return token_eq;
						}
						else {
							//cout << "el1 is " << el1 << endl;
							//cout << "el2 is " << el2 << endl;
							el1 -= el2;
							//cout << "el1 is " << el1 << endl;
							// replace el1
							string el1_str = to_string(el1);
							if (label_eq[next_match] == "var") {
								el1_str += "x";
							}
							token_eq[current_match] = el1_str;
							token_eq.erase(token_eq.begin() + next_match);
							token_eq.erase(token_eq.begin() + next_match);
							// not permanent
							if (token_eq.size() == 3) {
								token_eq[1] = "=";
							}
							return token_eq;
						}
						
					}
				}
			} // end of second round
			
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
	
	string orig_eq = "3 + 2x = 5x";
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
