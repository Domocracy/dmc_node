//----------------------------------------------------------------------------------------------------------------------
// dmc_node
//----------------------------------------------------------------------------------------------------------------------
#include "MockHueBridge.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
unsigned gPort = 5023;

void processArguments(int _argc, const char** _argv) {
	vector<string> args;
	for (int i = 0; i < _argc; ++i) {
		args.push_back(_argv[i]);
	}
	for (auto arg : args) {
		if (arg.substr(0, 5) == "port=") {
			stringstream ss(arg.substr(5));
			ss >> gPort;
		}
	}
}

int main(int _argc, const char** _argv) {
	processArguments(_argc, _argv);
	MockHueBridge bridge(gPort);
	std::string s;
	cin >> s;
}