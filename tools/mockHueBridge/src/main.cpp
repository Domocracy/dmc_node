//----------------------------------------------------------------------------------------------------------------------
// dmc_node
//----------------------------------------------------------------------------------------------------------------------
#include "MockHueBridge.h"
#include <iostream>
#include <string>

using namespace std;

int main(int, const char**) {
	MockHueBridge bridge;
	bridge.listen(5023);
	std::string s;
	cin >> s;
}