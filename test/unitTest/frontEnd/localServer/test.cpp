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

	Response Response::internalError() {
		Response error(false);
		error.mContent = "int";
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
		if(_request.url() == "/b")
			return false;
		if (_request.url() == "/c")
		{
			assert(false); // Bad requests don't get dispatched
		}
		if (_request.url() == "/d") // internal error
		{
			_server.respond(_request, Response::internalError()); // To alert mock translator
		}
		return true;
	}

	// --- Mock http translator
	bool HTTPTranslator::translate(const Poco::Net::HTTPRequest& _http, Request& _dmc) {
		if(_http.getURI() == "/c")
			return false; // Bad request test
		_dmc.url() = _http.getURI();
		return true;
	}

	bool HTTPTranslator::translate(const Response& _dmc, Poco::Net::HTTPResponse& _http) {
		if(_dmc.serialize() == "ok")
			_http.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_OK, "Ok");
		if(_dmc.serialize() == "int") // Simulate internal server error
			return false; 
		return true;
	}
}	// namespace dmc

using namespace dmc;
using namespace Poco::Net;
using namespace std;

void testUri(const string& _uri, const string& _expected) {
	SocketAddress localHost("localHost:5028");
	char buffer[1024];
	StreamSocket client(localHost);
	std::string req = 
		"Get " + _uri + " HTTP/1.1\n"
		"Host: localhost\r\n\r\n";
	client.sendBytes(req.c_str(), req.size());
	client.receiveBytes(buffer, 1023);
	assert(string(buffer).substr(0, _expected.size()) == _expected);
}

int main(int, const char**) {
	// --- Test setup ---
	RequestDispatcher dispatcher;
	LocalServer server(dispatcher, 5028);
	// --- Actual tests ---
	testUri("/a", "HTTP/1.1 200 Ok");// Test adequate behavior
	testUri("/b", "HTTP/1.1 404"); // Url not found
	testUri("/c", "HTTP/1.1 400"); // Bad request
	testUri("/d", "HTTP/1.1 500"); // Internal server error
	return 0;
}





