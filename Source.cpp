#include<iostream>
#include<cmath>
#include<cstring>
#include<string>
#include<stack>
using namespace std;
class truth_table {
private:
	int total_inputs;//number of col
	char** total_inputs_table;
	int num_row_input;//num of rows
	int lenght;
	char* result_table;
	int count;

public:
	truth_table() {
		count = 0;
		result_table = nullptr;
		total_inputs = 0;//number of col
		total_inputs_table = NULL;
		num_row_input = 0;//num of rows
		lenght = 0;
	}
	void make_input_table(string element) {
		stack<char >obj;
		stack<char >obj1;
		char val;

		lenght = element.length();

		for (int i = 0; i < lenght; i++) {
			if (element[i] <= 'z' && element[i] >= 'a') {
				obj.push(element[i]);
				total_inputs++;
			}
		}
		num_row_input = pow(2, total_inputs);
		total_inputs_table = new char* [num_row_input + 1];
		for (int i = 0; i < num_row_input + 1; i++) {
			total_inputs_table[i] = new char[total_inputs];
		}
		int  x = 0;// to input the variable name in the first row
		while (obj.empty() == false)
		{
			val = obj.top();
			obj.pop();
			obj1.push(val);
			count++;

		}
		while (obj1.empty() == false)
		{
			val = obj1.top();
			obj1.pop();

			total_inputs_table[0][x] = val;
			x++;
		}
		x = 0;//
		int num_of_zero = 0, index = 0, num_lop;
		for (int i = total_inputs - 1; i >= 0; i--) {//in each col
			num_of_zero = pow(2, x);
			index = 1;
			x++;
			num_lop = pow(2, x);
			for (int j = 1; j < (num_row_input + 1); j += num_lop) {

				for (int y = 0; y < num_of_zero; y++) {
					total_inputs_table[index][i] = '0';
					index++;
				}
				for (int y = 0; y < num_of_zero; y++) {
					total_inputs_table[index][i] = '1';
					index++;
				}

			}
		}


	}



	void make_result_table(string element) {
		stack<char>obj;
		result_table = new char[num_row_input + 1];
		result_table[0] = '?';
		string value = post_fix(element);
		lenght = value.length();
		int mark = 0, mark2 = 0;
		char oprand1 = 'a', oprand2 = 'a';
		char index = 'a';
		for (int i = 0; i < lenght; i++)
		{
			index = value[i];
			if (index == '~' || index == '{' || index == '*' || index == '$' || index == '+' || index == '>') {
				if (index == '~') {
					oprand1 = obj.top();
					obj.pop();
					if (oprand1 == '?') {
						for (int i = 0; i < num_row_input + 1; i++) {
							if (result_table[i] == '0') {
								result_table[i] = '1';
							}
							else if (result_table[i] == '1')
							{
								result_table[i] = '0';
							}
						}
						obj.push(result_table[0]);
						continue;
					}
					else {
						for (int i = 0; i < count; i++) {
							if (total_inputs_table[0][i] == oprand1)
							{
								mark = i;
								break;
							}
						}
						for (int i = 1; i < num_row_input + 1; i++) {
							result_table[i] = total_inputs_table[i][mark];
						}
						for (int i = 1; i < num_row_input + 1; i++) {
							if (result_table[i] == '0') {
								result_table[i] = '1';
							}
							else if (result_table[i] == '1')
							{
								result_table[i] = '0';
							}
						}
						obj.push(result_table[0]);
					}


				}
				else if (index == '+') {
					oprand1 = obj.top();
					obj.pop();
					oprand2 = obj.top();
					obj.pop();
					if (oprand1 == '?') {
						for (int i = 0; i < count; i++) {
							if (total_inputs_table[0][i] == oprand2)
							{
								mark = i;
								break;
							}

						}
						for (int i = 1; i < num_row_input + 1; i++) {
							if (total_inputs_table[i][mark] == '0') {
								continue;
							}
							else if (total_inputs_table[i][mark] == '1') {
								result_table[i] = '1';
								continue;
							}
						}
						obj.push(result_table[0]);
					}
					else 	if (oprand2 == '?') {
						for (int i = 0; i < count; i++) {
							if (total_inputs_table[0][i] == oprand1)
							{
								mark = i;
								break;
							}

						}
						for (int i = 1; i < num_row_input + 1; i++) {
							if (total_inputs_table[i][mark] == '0') {
								continue;
							}
							else if (total_inputs_table[i][mark] == '1') {
								result_table[i] = '1';
								continue;
							}
						}
						obj.push(result_table[0]);
					}
					else {
						for (int i = 0; i < count; i++) {
							if (total_inputs_table[0][i] == oprand2)
							{
								mark2 = i;
								break;
							}

						}
						for (int i = 0; i < count; i++) {
							if (total_inputs_table[0][i] == oprand1)
							{
								mark = i;
								break;
							}

						}
						for (int i = 1; i < num_row_input + 1; i++) {
							if (total_inputs_table[i][mark] == '1' || total_inputs_table[i][mark2] == '1') {
								result_table[i] = '1';
							}
							else if (total_inputs_table[i][mark] == '0' || total_inputs_table[i][mark2] == '0')
							{
								result_table[i] = '0';
							}
						}
						obj.push(result_table[0]);

					}

				}
				else if (index == '*') {
					oprand1 = obj.top();
					obj.pop();
					oprand2 = obj.top();
					obj.pop();
					if (oprand1 == '?') {
						for (int i = 0; i < count; i++) {
							if (total_inputs_table[0][i] == oprand2)
							{
								mark = i;
								break;
							}

						}
						for (int i = 1; i < num_row_input + 1; i++) {
							if (total_inputs_table[i][mark] == '0' || (result_table[i] == '0')) {
								result_table[i] = '0';
								continue;
							}
							else if ((total_inputs_table[i][mark] == '1') && (result_table[i] == '1')) {
								result_table[i] = '1';

								continue;
							}

						}

						obj.push(result_table[0]);
					}
					else 	if (oprand2 == '?') {
						for (int i = 0; i < count; i++) {
							if (total_inputs_table[0][i] == oprand1)
							{
								mark = i;
								break;
							}

						}
						for (int i = 1; i < num_row_input + 1; i++) {
							if (total_inputs_table[i][mark] == '0') {
								result_table[i] = '0';
								continue;
							}
							else if (total_inputs_table[i][mark] == '1' && result_table[i] == '1') {
								result_table[i] == '1';
								continue;
							}
							else {
								result_table[i] = '0';

							}
						}
						obj.push(result_table[0]);

					}
					else {
						for (int i = 0; i < count; i++) {
							if (total_inputs_table[0][i] == oprand2)
							{
								mark2 = i;
								break;
							}

						}
						for (int i = 0; i < count; i++) {
							if (total_inputs_table[0][i] == oprand1)
							{
								mark = i;
								break;
							}

						}
						for (int i = 1; i < num_row_input + 1; i++) {
							if ((total_inputs_table[i][mark] == '0' || total_inputs_table[i][mark2] == '0')) {
								result_table[i] = '0';
							}
							else {
								result_table[i] = '1';
							}
						}

						obj.push(result_table[0]);
					}

				}
				else if (index == '>') {


					oprand1 = obj.top();
					obj.pop();
					oprand2 = obj.top();
					obj.pop();
					if (oprand1 == '?') {
						for (int i = 0; i < count; i++) {
							if (total_inputs_table[0][i] == oprand2)
							{
								mark = i;
								break;
							}

						}
						for (int i = 1; i < num_row_input + 1; i++) {
							if ((total_inputs_table[i][mark] == '1' && result_table[i] == '0') || (total_inputs_table[i][mark] == '0' && result_table[i] == '1')) {
								result_table[i] = '1';
								continue;
							}
							else {
								result_table[i] = '0';
							}
						}


					}
					else 	if (oprand2 == '?') {
						for (int i = 0; i < count; i++) {
							if (total_inputs_table[0][i] == oprand1)
							{
								mark = i;
								break;
							}

						}
						for (int i = 1; i < num_row_input + 1; i++) {
							if ((total_inputs_table[1][mark] == '1' && result_table[i] == '0') || (total_inputs_table[1][mark] == '0' && result_table[i] == '1')) {
								result_table[i] = '1';
								continue;
							}
							else {
								result_table[i] = '0';
							}
						}

					}
					else {
						for (int i = 0; i < count; i++) {
							if (total_inputs_table[0][i] == oprand2)
							{
								mark2 = i;
								break;
							}

						}
						for (int i = 0; i < count; i++) {
							if (total_inputs_table[0][i] == oprand1)
							{
								mark = i;
								break;
							}

						}
						for (int i = 1; i < num_row_input + 1; i++) {
							if ((total_inputs_table[i][mark] == '0' && total_inputs_table[0][mark2] == '0') || (total_inputs_table[0][mark] == '1' && total_inputs_table[i][mark2] == '1')) {
								result_table[i] = '0';
							}
							else {
								result_table[i] = '1';
							}
						}


					}
					obj.push(result_table[0]);



				}

				else if (index == '{') {

					oprand1 = obj.top();
					obj.pop();
					oprand2 = obj.top();
					obj.pop();
					if (oprand1 == '?') {
						for (int i = 0; i < count; i++) {
							if (total_inputs_table[0][i] == oprand2)
							{
								mark = i;
								break;
							}

						}
						for (int i = 1; i < num_row_input + 1; i++) {
							if (result_table[i] = '0') {
								result_table[i] = '0';
								continue;
							}
							else if ((result_table[i] = '1') && (total_inputs_table[i][mark] == '0'))
							{
								result_table[i] = '0';
							}
							else if ((result_table[i] = '1') && (total_inputs_table[i][mark] == '1'))
							{
								result_table[i] = '1';
							}

						}


					}
					else 	if (oprand2 == '?') {
						for (int i = 0; i < count; i++) {
							if (total_inputs_table[0][i] == oprand1)
							{
								mark = i;
								break;
							}

						}
						for (int i = 1; i < num_row_input + 1; i++) {
							if (result_table[i] = '0') {
								result_table[i] = '0';
								continue;
							}
							else if ((result_table[i] = '1') && (total_inputs_table[i][mark] == '0'))
							{
								result_table[i] = '0';
							}
							else if ((result_table[i] = '1') && (total_inputs_table[i][mark] == '1'))
							{
								result_table[i] = '1';
							}

						}

					}
					else {
						for (int i = 0; i < count; i++) {
							if (total_inputs_table[0][i] == oprand2)
							{
								mark2 = i;
								break;
							}

						}
						for (int i = 0; i < count; i++) {
							if (total_inputs_table[0][i] == oprand1)
							{
								mark = i;
								break;
							}

						}
						for (int i = 1; i < num_row_input + 1; i++) {
							if (total_inputs_table[i][mark] == '0') {
								result_table[i] = '1';
							}
							else if (total_inputs_table[i][mark] == '1' && total_inputs_table[i][mark2] == '1')
							{
								result_table[i] = '1';
							}
							else if (total_inputs_table[i][mark] == '1' && total_inputs_table[i][mark2] == '0') {
								result_table[i] = '0';

							}
						}


					}
					obj.push(result_table[0]);


				}

				else if (index == '$') {



					oprand1 = obj.top();
					obj.pop();
					oprand2 = obj.top();
					obj.pop();
					if (oprand1 == '?') {
						for (int i = 0; i < count; i++) {
							if (total_inputs_table[0][i] == oprand2)
							{
								mark = i;
								break;
							}

						}
						for (int i = 1; i < num_row_input + 1; i++) {
							if ((result_table[i] = '1' && total_inputs_table[i][mark] == '1') || (result_table[i] = '0' && total_inputs_table[i][mark] == '0'))
							{
								result_table[i] = '1';
							}
							else
							{
								result_table[i] = '0';
							}

						}


					}
					else 	if (oprand2 == '?') {
						for (int i = 0; i < count; i++) {
							if (total_inputs_table[0][i] == oprand1)
							{
								mark = i;
								break;
							}

						}
						for (int i = 1; i < num_row_input + 1; i++) {
							if ((result_table[i] = '1' && total_inputs_table[i][mark] == '1') || (result_table[i] = '0' && total_inputs_table[i][mark] == '0'))
							{
								result_table[i] = '1';
							}
							else
							{
								result_table[i] = '0';
							}
						}

					}
					else {
						for (int i = 0; i < count; i++) {
							if (total_inputs_table[0][i] == oprand2)
							{
								mark2 = i;
								break;
							}

						}
						for (int i = 0; i < count; i++) {
							if (total_inputs_table[0][i] == oprand1)
							{
								mark = i;
								break;
							}

						}
						for (int i = 1; i < num_row_input + 1; i++) {
							if ((total_inputs_table[i][mark] == '1' && total_inputs_table[i][mark2] == '1') || (total_inputs_table[i][mark] == '0' && total_inputs_table[i][mark2] == '0'))
							{
								result_table[i] = '1';
							}
							else {
								result_table[i] = '0';

							}
						}


					}
					obj.push(result_table[0]);



				}


			}
			else {
				obj.push(index);
			}
		}


	}

	void display() {
		for (int i = 0; i < num_row_input + 1; i++) {
			for (int j = 0; j < total_inputs; j++) {
				cout << total_inputs_table[i][j] << " ";
			}
			if (result_table[i] == '?') {
				cout << "final output";
			}
			else {
				cout << " : " << result_table[i] << " ";
			}

			cout << endl;
		}
	}




	string post_fix(string value) {
		string final = "";
		int size;
		char* ptr;
		char index = 'a';
		size = value.length();
		/ ptr = new char[size]; /
			stack<char >obj;
		for (int i = 0; i < size; i++) {
			index = value[i];
			if (index == '(') {
				obj.push('(');
			}
			else if (index == ')') {
				while (obj.top() != '(') {
					final += obj.top();
					obj.pop();
				}
				obj.pop();
			}
			else if (index == '~' || index == '{' || index == '*' || index == '$' || index == '+' || index == '>') {
				if (index == '~') {
					if (obj.empty() == true) {
						obj.push(index);
					}
					else if (obj.top() != '~') {
						obj.push(index);
					}
					else {
						while (!obj.empty() && (obj.top() == '~')) {
							if (obj.top() == '(')
								break;
							final += obj.top();
							obj.pop();
						}
						obj.push(index);
					}
				}
				else if (index == '>') {
					if (obj.empty() == true) {
						obj.push(index);
					}
					else if (obj.top() != '~' || obj.top() != '>') {
						obj.push(index);

					}
					else {
						while (!obj.empty() && ((obj.top() == '~') || (obj.top() == '>'))) {
							if (obj.top() == '(')
								break;
							final += obj.top();
							obj.pop();
						}
						obj.push(index);
					}

				}
				else if (index == '*') {
					if (obj.empty() == true) {
						obj.push(index);
					}
					else if (obj.top() != '~' || obj.top() != '>' || obj.top() != '*') {
						obj.push(index);

					}
					else {
						while (!obj.empty() && ((obj.top() == '~') || (obj.top() == '>') || (obj.top() == '*'))) {
							if (obj.top() == '(')
								break;
							final += obj.top();
							obj.pop();
						}
						obj.push(index);
					}

				}
				else if (index == '+') {
					if (obj.empty() == true) {
						obj.push(index);
					}
					else if (obj.top() != '~' || obj.top() != '>' || obj.top() != '*' || obj.top() != '+') {
						obj.push(index);

					}
					else {
						while (!obj.empty() && ((obj.top() == '~') || (obj.top() == '>') || (obj.top() == '*') || (obj.top() == '+'))) {
							if (obj.top() == '(')
								break;
							final += obj.top();
							obj.pop();
						}
						obj.push(index);
					}

				}

				else if (index == '{') {
					if (obj.empty() == true) {
						obj.push(index);
					}
					else if (obj.top() != '~' || obj.top() != '>' || obj.top() != '*' || obj.top() != '+' || obj.top() != '{') {
						obj.push(index);

					}
					else {
						while (!obj.empty() && ((obj.top() == '~') || (obj.top() == '>') || (obj.top() == '*') || (obj.top() == '+') || (obj.top() == '{'))) {
							if (obj.top() == '(')
								break;
							final += obj.top();
							obj.pop();
						}
						obj.push(index);
					}

				}
				else if (index == '$') {
					if (obj.empty() == true) {
						obj.push(index);
					}
					else if (obj.top() != '$' || obj.top() != '~' || obj.top() != '>' || obj.top() != '*' || obj.top() != '+' || obj.top() != '{') {
						obj.push(index);

					}
					else {
						while (!obj.empty() && ((obj.top() == '$') || (obj.top() == '~') || (obj.top() == '>') || (obj.top() == '*') || (obj.top() == '+') || (obj.top() == '{'))) {
							if (obj.top() == '(')
								break;
							final += obj.top();
							obj.pop();
						}
						obj.push(index);
					}

				}


			}
			else
			{
				final += index;
			}
		}
		char val;
		while (!obj.empty()) {
			val = obj.top();
			obj.pop();
			if (val == '(') {
			}
			else {
				final += val;
			}
		}
		return final;
	}
};
int main() {
	truth_table obj;
	string value;
	cout << "input the string " << endl;
	cin >> value;
	obj.make_input_table(value);

	obj.make_result_table(value);
	obj.display();
	system("pause");
	return 0;
}