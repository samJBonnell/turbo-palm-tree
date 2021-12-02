#include <iostream>
#include <fstream>
#include <regex>
#include <memory>
#include <vector>

using namespace std;
void fileIO(vector<string>& inputVector, ifstream& in);

int main(void) {
	ifstream in;
	string fileName;
	vector<string> inputVector;
	cout << "Enter File Name\n";
	cin >> fileName;
	in.open(fileName.c_str());
	if (!in.is_open()) {
		cout << "Error - Exiting";
		exit(0);
	}
	fileIO(inputVector, in);

	int input = 1;
	int randomValue;
	srand(time(NULL));
	do {
		if (inputVector.size() == 0) {
			cout << "Reached the end - Exiting\n";
			exit(0);
		}
		cout << "There are " << inputVector.size() - 1 << " Minerals to learn\n\n";
		randomValue = rand() % inputVector.size();
		cout << "\n" << inputVector[randomValue] << "\nWould you like another mineral?\n";
		cin >> input;
		inputVector.erase(inputVector.begin() + randomValue);
		system("CLS");

	} while (input);

	in.close();
}

void fileIO(vector<string>& inputVector, ifstream& in) {
	string IO;
	int i = 0;
	while (getline(in, IO)) {
		inputVector.push_back(IO);
	}
}
