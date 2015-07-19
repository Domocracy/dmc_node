//----------------------------------------------------------------------------------------------------------------------
// Upnp testing tool
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <Poco/Net/MulticastSocket.h>

using namespace std;
using namespace Poco::Net;
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
	SocketAddress multicastAddress("239.255.255.250", 1900);
	MulticastSocket udpSock(multicastAddress);
	/*processArguments(_argc, _argv);
	MockHueBridge bridge(gPort);
	std::string s;
	cin >> s;*/
}