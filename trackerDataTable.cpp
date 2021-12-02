#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

void getData(vector<vector<double>>& dataLines, ifstream& in, int FILE_NUM);
void outputData(vector<vector<double>>& dataLines, ofstream& out);

int main(void) {
	ifstream in;
	ofstream out;
	string fileName;
	int FILE_NUM;

	out.open("output.txt");

	cout << "Enter the number of columns to be parsed." << endl;
	cin >> FILE_NUM;
	if (!FILE_NUM) {
		cout << "Error allocating file memory" << endl;
		exit(2);
	}
	vector<vector<double>> dataLines(FILE_NUM, vector<double>());
	cout << "Enter file name.\n";
	cin >> fileName;
	in.open(fileName.c_str());
	if (!in.is_open()) {
		cout << "File Error";
		exit(1);
	}
	getData(dataLines, in, FILE_NUM);
	outputData(dataLines, out);
	
	return 0;
}

void getData(vector<vector<double>>& dataLines, ifstream& in, int FILE_NUM) {
	string IO;
	while (getline(in, IO)) {
		for (int i = 0; i < FILE_NUM; i++) {
			dataLines[i].push_back(stod(IO.substr(0, IO.find("\t"))));
			IO.erase(0, IO.find("\t") + 1);
		}
	}

}

void outputData(vector<vector<double>>& dataLines, ofstream& out) {
	for (const auto& ptr : dataLines) {
		for (const auto& ptr2 : ptr) {
			out << ptr2 << endl;
		}
		out << endl << endl;
	}
}
