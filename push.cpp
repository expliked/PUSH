#include <iostream>
#include <fstream>
#include <string>
#include <list>

using namespace std;



/*
* excuse the messy code, please.
* 
* i'm not really expecting anyone to work on this alongside me
* so i'm just gonna throw down code and make it work.
*
* (im also only a beginner/intermediate C++ user. My main language is Python.)
*
* "PUSH" made by expliked.
*/



bool is_number(const std::string& s) {
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}


int ExecuteCode(string code, string filename) {
	list<int> memory;
	char c;
	string token = "";
	int statementNumber = 1;
	bool comment = false;
	bool whileStatement = false;
	int whileLocation = 0;
	for (int i = 0; i < code.length(); i++) {
		c = code[i];
		token += c;
		if (c == '[') {
			comment = true;
			//cout << "Comment started" << endl;
		}
		if (c == ']') {
			comment = false;
			token = "";
			//cout << "Comment end" << endl;
		}
		if (comment == true) {
			token = "";
			continue;
		}
		if (token == "PUSH:") {
			statementNumber += 1;
			//cout << "Found PUSH" << endl;
			token = "";
			while (c != ';') {
				i++;
				if (c == ' ') {
					continue;
				}
				c = code[i];
				if (c != ';') {
					token += code[i];
				}
				
			}
			if (is_number(token)) {
				memory.push_back(stoi(token));
				//cout << "Pushed " << token << " into memory." << endl;
				token = "";
			}

			else {
				cout << "Invalid value (" << token << ") located at statement " << statementNumber << ". (" << filename << ")" << endl;
				cout << "EXITING." << endl;
				return 0;
			}
		}
		if (token == "ADD:") {
			statementNumber += 1;
			//cout << "Found PUSH" << endl;
			token = "";
			while (c != ';') {
				i++;
				if (c == ' ') {
					continue;
				}
				c = code[i];
				if (c != ';') {
					token += code[i];
				}
				
			}
			if (is_number(token)) {
				int savedValue = memory.back();
				memory.pop_back();
				memory.push_back(savedValue + stoi(token));
				token = "";
			}

			else {
				cout << "Invalid value (" << token << ") located at statement " << statementNumber << ". (" << filename << ")" << endl;
				cout << "EXITING." << endl;
				return 0;
			}
		}
		if (token == "SUBTRACT:") {
			statementNumber += 1;
			//cout << "Found PUSH" << endl;
			token = "";
			while (c != ';') {
				i++;
				if (c == ' ') {
					continue;
				}
				c = code[i];
				if (c != ';') {
					token += code[i];
				}
				
			}
			if (is_number(token)) {
				int savedValue = memory.back();
				memory.pop_back();
				memory.push_back(savedValue - stoi(token));
				token = "";
			}

			else {
				cout << "Invalid value (" << token << ") located at statement " << statementNumber << ". (" << filename << ")" << endl;
				cout << "EXITING." << endl;
				return 0;
			}
		}
		if (token == "PULL;") {
			statementNumber += 1;
			if (memory.empty() == true) {
				cout << "Cannot PULL with an empty memory tape." << endl;
				cout << "EXITING." << endl;
				return 0;
			}
			cout << (char)memory.front();
			memory.pop_front();
			token = "";
		}
		if (token == "INPUT;") {
			statementNumber += 1;
			string USERINPUT;
			getline(cin, USERINPUT);
			for (int II = 0; II < USERINPUT.length(); II++) {
				memory.push_back((int)USERINPUT[II]);
			}
			token = "";
		}
		if (token == "DO;") {
			statementNumber += 1;
			whileLocation = i;
			token = "";

		}
		if (token == "WHILE;") {
			statementNumber += 1;
			token = "";
			if (memory.back()) {
				i = whileLocation;
			}
		}
		if (token == "CLEAR;") {
			statementNumber += 1;
			memory.clear();
			token = "";
		}
	}
	return 1;
}

bool FileExists(string FILENAME) {
	ifstream FILE(FILENAME);
	return FILE.good();
}

string ReadFile(string FILENAME) {
	ifstream INFILE(FILENAME);
	char C;
	string RESULT = "";
	while (INFILE >> C) {
		RESULT += C;
	}
	return RESULT;
}

int main(int argc, char * argv[]) {
	if (argc != 2) {
		cout << "Not enough arguments." << endl;
		return 0;
	}
	string filename = argv[1];
	if (FileExists(filename) != true) {
		cout << "The given file does not exist in the current directory." << endl;
		return 0;
	}
	string text = ReadFile(filename);
	ExecuteCode(text, filename);
	return 0;
}
