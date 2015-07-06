//----------------------------------------------------------------------------------------------------------------------
// local server unit test
//----------------------------------------------------------------------------------------------------------------------
#include <cassert>
#include <string>
#include <frontEnd/LocalServer.h>
#include <frontEnd/HttpTranslator.h>
#include <frontEnd/Request.h>
#include <frontEnd/RequestDispatcher.h>
#include <frontEnd/Response.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
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

	Response Response::ok() {
		Response error(false);
		error.mContent = "ok";
		return error;
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
		if(_request.url() == "/a") {
			_server.respond(_request, Response::ok());
		}
		return true;
	}

	// --- Mock http translator
	bool HTTPTranslator::translate(const Poco::Net::HTTPServerRequest& _http, Request& _dmc) {
		_dmc.url() = _http.getURI();
		return true;
	}

	bool HTTPTranslator::translate(const Response& _dmc, Poco::Net::HTTPServerResponse& _http) {
		if(_dmc.serialize() == "ok")
			_http.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_OK, "ok");
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
		"Get /a HTTP/1.1\n"
		"Host: localhost\r\n\r\n";
	clientA.sendBytes(reqA.c_str(), reqA.size());
	char buffer[1024];
	clientA.receiveBytes(buffer, 1023);
	assert(string(buffer) == "HTTP/1.1 200 ok\r\n\r\n");
	// Test translator failure
	// Test dispatcher failure
	return 0;
}





