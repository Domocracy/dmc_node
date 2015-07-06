//----------------------------------------------------------------------------------------------------------------------
// local server unit test
//----------------------------------------------------------------------------------------------------------------------
#include <cassert>
#include <string>
#include <frontEnd/LocalServer.h>
#include <frontEnd/HttpTranslator.h>
#include <frontEnd/RequestDispatcher.h>
#include <frontEnd/Response.h>
#include <Poco/Net/SocketAddress.h>
#include <Poco/Net/StreamSocket.h>

// Call counter
unsigned gCallCount = 0;
unsigned callCount() { return ++gCallCount; }

// Mock classes
namespace Poco {
	namespace Net {
		class HTTPRequest;
	}
}

namespace dmc {

	class Request;

	// --- Mock dmc::Response
	Response::Response(bool) {
	}

	Response Response::errorInvalidHttpRequest() {
		Response error(false);
		error.mContent = "invalidHttpRequest";
		return error;
	}

	const std::string& Response::serialize() const {
		return mContent;
	}
	
	// --- Mock request dispatcher
	bool RequestDispatcher::dispatch(LocalServer& _server, const Request &_request) const{
		return true;
	}

	// --- Mock http translator
	bool HTTPTranslator::translate(const Poco::Net::HTTPServerRequest&, Request&, unsigned _id) {
		return true;
	}
}	// namespace dmc

using namespace dmc;
using namespace Poco::Net;
using namespace std;

int main(int, const char**) {
	// --- Test setup ---
	RequestDispatcher dispatcher;
	LocalServer server(dispatcher, 5028);
	// --- Common test data---
	SocketAddress localHost("localHost:5028");
	// Test adequate behavior
	StreamSocket clientA(localHost);
	std::string reqA = 
		"Get /a HTTP/1.1"
		"Host: localhost\r\n\r\n";
	clientA.sendBytes(reqA.c_str(), reqA.size());
	char buffer[1024];
	clientA.receiveBytes(buffer, 1023);
	assert(string(buffer) == "200 Ok");
	// Test translator failure
	// Test dispatcher failure
	return 0;
}





