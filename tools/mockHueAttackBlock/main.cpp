////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// DMC_NODE
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPClientSession.h>

using namespace Poco::Net;

int main(int, const char**) {
	
	std::cout << "Scanning network" << std::endl;
	Sleep(3000);
	std::cout << "Detected intrusion in Hue Bridge" << std::endl;
	
	HTTPClientSession session("10.100.3.211");
	HTTPRequest delUsr;
	delUsr.setMethod("DELETE");
	delUsr.setURI("/api/newdeveloper/config/whitelist/attack");
	session.sendRequest(delUsr);

	Sleep(1000);
	std::cout << "Blocked intrusion" << std::endl;
}