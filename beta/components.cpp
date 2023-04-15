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



std::vector<std::string> step(std::vector<std::string> token_eq, std::vector<std::string> label_eq)
{
	//cout << "size is " << token_eq.size() << endl;
	int step_position;
	std::string step_type;
	std::string step_result;
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
					if (label_eq[i].find("+") != std::string::npos) {
						result = el1 + el2;
						step_type = "+op";
					}
					else {
						result = el1 - el2;
						step_type = "-op";
					}
					step_result = std::to_string(result);
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
				//cout << "entered if " << endl;
				second_round = true;
			}

			if (second_round) {
				//cout << "second round" << endl;
				int next_match;
				int current_match;
				std::string current_match_type;
				std::string next_match_type;
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
							//cout << current_match_type << " vs " << next_match_type << endl;
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
							std::string el2_str = std::to_string(el2);
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
							std::string el1_str = std::to_string(el1);
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
				step_result = std::to_string(const_el);
				//cout << "step result is " << step_result << endl;
				step_type = "solve";
				step_position = -1;
				step_completed = true;
				break;
			}
			//cout << "ended for " << endl;
		} // end of token_eq for

	} // end of while !step_completed

	std::vector<std::string> new_token_eq = create_new_eq(token_eq, step_position, step_type, step_result);
	return new_token_eq;
	//vector<string> new_labels_eq = create_new_labels(new_token_eq);
}


std::vector<std::string> create_new_eq(std::vector<std::string> orig_token_eq, int pos, std::string type, std::string result) {
	//cout << "result is " << result << endl;
	if (type == "+op" || type == "-op") {
		orig_token_eq.erase(orig_token_eq.begin() + (pos - 1));
		orig_token_eq.erase(orig_token_eq.begin() + (pos - 1));
		orig_token_eq.erase(orig_token_eq.begin() + (pos - 1));
		orig_token_eq.insert(orig_token_eq.begin() + (pos - 1), result);
	}
	else if (type == "solve") {
		std::vector<std::string> final_eq(3);
		final_eq[0] = "x";
		final_eq[1] = "=";
		final_eq[2] = result;
		//cout << "result is " << result << endl;
		return final_eq;
	}

	return orig_token_eq;
}

std::vector<std::string> create_new_labels(std::vector<std::string> token_eq) {
	std::vector<std::string> labels(token_eq.size());

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
		else if (token_eq[i].find("x") != std::string::npos) {
			labels[i] = "var";
		}
		else {
			labels[i] = "const";
		}
	}

	return labels;
}





// solves one step of linear algebra problem
bool laStep(std::vector<std::string>* solution)
{
	// TODO: actually make this solve for the next step in a solution.

	// for example (TODO: remove this when the function is actually implemented)
	//solution->push_back("Successful laStep() call! Thanks for using the beta.");
	char delim = ' ';
	std::string orig_eq = solution->back();
	std::stringstream ss(orig_eq);

	// holds separated equation
	std::vector<std::string> token_eq;
	while (std::getline(ss, orig_eq, delim)) {
		token_eq.push_back(orig_eq);
	}

	// holds labels for each element in separated equation
	std::vector<std::string> orig_labels(token_eq.size()); 

	for (int i = 0; i < token_eq.size(); i++) {
		if (token_eq[i] == "+") {
			orig_labels[i] = "+op";
		}
		else if (token_eq[i] == "-") {
			orig_labels[i] = "-op";
		}
		else if (token_eq[i] == "=") {
			orig_labels[i] = "=op";
		}
		else if (token_eq[i].find("x") != std::string::npos) {
			orig_labels[i] = "var";
		}
		else {
			orig_labels[i] = "const";
		}
	}

	std::vector<std::string> step1 = step(token_eq, orig_labels);
	std::vector<std::string> step1labels = create_new_labels(step1);
	std::string result = "";

	for (int i = 0; i < step1.size(); i++)
	{
		result = result + step1.at(i);
	}
	solution->push_back(result);


	return false;
}
