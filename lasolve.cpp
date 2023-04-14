#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

vector<string> step(vector < string>, vector<string>);
vector<string> create_new_eq(vector<string>, int, string, string);
vector<string> create_new_labels(vector<string>);
vector<string> final_step(vector < string>, vector<string>);


vector<string> step(vector<string> token_eq, vector<string> label_eq) {
	int step_position;
	string step_type;
	string step_result;

	bool step_completed = false;
	while (!step_completed) {
		cout << "got to while" << endl;
		for (int i = 0; i < token_eq.size(); i++) {
			if (label_eq[i].find("+") != string::npos) {
				// if const + const or var + var
				if (label_eq[i - 1] == label_eq[i + 1]) {
					float el1 = stof(token_eq[i - 1]);
					float el2 = stof(token_eq[i + 1]);
					float result = el1 + el2;
					step_result = to_string(result);
					// if var, append variable to end of result
					if (label_eq[i - 1] == "var") {
						step_result += "x";
					}
					step_position = i;
					step_type = "+op";
					step_completed = true;
				}
			}
			else if (label_eq[i].find("-") != string::npos)
			{
				if (label_eq[i - 1] == label_eq[i + 1]) {
					float el1 = stof(token_eq[i - 1]);
					float el2 = stof(token_eq[i + 1]);
					float result = el1 - el2;
					step_result = to_string(result);
					// if var, append variable to end of result
					if (label_eq[i - 1] == "var") {
						step_result += "x";
					}
					step_position = i;
					step_type = "-op";
					step_completed = true;
				}
			}

		} // end of token_eq for
	} // end of while !step_completed

	cout << "finished while " << endl;

	vector<string> new_token_eq = create_new_eq(token_eq, step_position, step_type, step_result);
	return new_token_eq;
	//vector<string> new_labels_eq = create_new_labels(new_token_eq);
}

vector<string> create_new_eq(vector<string> orig_token_eq, int pos, string type, string result) {
	cout << "began creation" << endl;
	if (type == "+op") {
		orig_token_eq.erase(orig_token_eq.begin() + (pos - 1));
		orig_token_eq.erase(orig_token_eq.begin() + (pos - 1));
		orig_token_eq.erase(orig_token_eq.begin() + (pos - 1));
		orig_token_eq.insert(orig_token_eq.begin() + (pos - 1), result);
	}
	else if (type == "=op") {


		orig_token_eq.erase(orig_token_eq.begin() + (pos - 1));
		orig_token_eq.erase(orig_token_eq.begin() + pos);
		orig_token_eq.insert(orig_token_eq.begin(), "x");
		orig_token_eq.insert(orig_token_eq.end(), result);

	}
	else if (type == "-op") {
		orig_token_eq.erase(orig_token_eq.begin() + (pos - 1));
		orig_token_eq.erase(orig_token_eq.begin() + (pos - 1));
		orig_token_eq.erase(orig_token_eq.begin() + (pos - 1));
		orig_token_eq.insert(orig_token_eq.begin() + (pos - 1), result);
	}

	cout << "ended creation" << endl;
	return orig_token_eq;
}

vector<string> create_new_labels(vector<string> token_eq) {
	vector<string> labels(token_eq.size());
	cout << "created labels vector" << endl;

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

vector<string> final_step(vector < string>token_eq, vector<string>label_eq) {
	int step_position;
	string step_type;
	string step_result;
	bool step_completed = false;
	while (!step_completed) {
		cout << "got to while" << endl;
		for (int i = 0; i < token_eq.size(); i++) {
			if (label_eq[i].find("=") != string::npos) {
				// if const var = const  
				if (label_eq[i - 1] == "var" && label_eq[i + 1] == "const") {
					float el1 = stof(token_eq[i - 1]);
					float el2 = stof(token_eq[i + 1]);
					float result = el2 / el1;
					step_result = to_string(result);


					step_position = i;
					step_type = "=op";
					step_completed = true;
				}
			} // end of =op
		} // end of token_eq for
	}
	cout << "finished while" << endl;
	vector<string> new_token_eq = create_new_eq(token_eq, step_position, step_type, step_result);
	return new_token_eq;
}
int main()
{

	//string orig_eq = " 10x + 15x = 20 + 20 ";
	string orig_eq;
	getline(cin, orig_eq);
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
	vector<string> orig_labels(token_eq.size());

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
		else if (token_eq[i].find("x") != string::npos) {
			orig_labels[i] = "var";
		}
		else {
			orig_labels[i] = "const";
		}
	}

	for (int i = 0; i < orig_labels.size(); i++) {
		cout << orig_labels[i] << " ";
	}
	cout << endl;

	// will hold updated eq

	/* for (int i = 0; i < step1.size(); i++) {
		cout << step1[i] << " ";
	}
	cout << endl;

	for (int i = 0; i < step1labels.size(); i++) {
		cout << step1labels[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < step2.size(); i++) {
		cout << step2[i] << " ";
	}
	cout << endl;

	for (int i = 0; i < step2labels.size(); i++) {
		cout << step2labels[i] << " ";
	}
	cout << endl;

	for (int i = 0; i < step3.size(); i++) {
		cout << step3[i] << " ";
	}
	cout << endl;

	for (int i = 0; i < step3labels.size(); i++) {
		cout << step3labels[i] << " ";
	}
	cout << endl;
	*/
	int var = 0;
	int con = 0;
	for (int i = 0; i < orig_labels.size(); i++) {
		if (orig_labels[i] == "var") {
			var++;
		}
	}
	// need to work on the different cases of when there is (1 const and 1 var) or 2 var 1 const and so on etc...
	switch (var) { //switch statement based on if there is only one variable or two variables. ex 5x = 10 + 20 or 5x + 10x = 10 + 20
	case 1:
		cout << "hello"; // ignore this  just there to test when it counts 1 var 
		break;
	case 2:
		vector<string> step1 = step(token_eq, orig_labels);
		vector<string> step1labels = create_new_labels(step1);
		vector<string> step2 = step(step1, step1labels);
		vector<string> step2labels = create_new_labels(step2);
		vector<string> step3 = final_step(step2, step2labels);
		vector<string> step3labels = create_new_labels(step3);
		for (int i = 0; i < step1.size(); i++) {
			cout << step1[i] << " ";
		}
		cout << endl;

		for (int i = 0; i < step1labels.size(); i++) {
			cout << step1labels[i] << " ";
		}
		cout << endl;
		for (int i = 0; i < step2.size(); i++) {
			cout << step2[i] << " ";
		}
		cout << endl;

		for (int i = 0; i < step2labels.size(); i++) {
			cout << step2labels[i] << " ";
		}
		cout << endl;

		for (int i = 0; i < step3.size(); i++) {
			cout << step3[i] << " ";
		}
		cout << endl;

		for (int i = 0; i < step3labels.size(); i++) {
			cout << step3labels[i] << " ";
		}
		cout << endl;
		break;
	};

}