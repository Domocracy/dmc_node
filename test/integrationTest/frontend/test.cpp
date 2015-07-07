///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//

#include <cassert>
#include <frontEnd/LocalServer.h>
#include <frontEnd/RequestDispatcher.h>
#include <frontEnd/Response.h>
#include <frontEnd/Request.h>
#include <backEnd/RequestProcessor.h>
#include <Poco/Net/SocketAddress.h>
#include <Poco/Net/StreamSocket.h>

// Mocks
namespace dmc {
	class Processor: public RequestProcessor {
	public:
		Processor(std::string _name) {
			mName = _name;
		}
		void process(const Request &_request, LocalServer &_localServer) override{
			if(_request.url() == mName)
				_localServer.respond(_request, Response::ok());
			else
				_localServer.respond(_request, Response::invalidRequest());
		}

		std::string mName = "";
	};
}	//	namespace dmc



using namespace dmc;
using namespace Poco::Net;
using namespace std;

void testUri(const string& _uri, const string& _expected) {
	// Setup server
	RequestDispatcher dispatcher;
	Processor procA("/subscribe");
	dispatcher.subscribe(&procA, "/subscribe");
	LocalServer server(dispatcher, 5028);

	// Test
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
	// --- Actual tests ---
	testUri("/subscribe", "HTTP/1.1 200 Ok");// Test adequate behavior
	testUri("/noexist", "HTTP/1.1 404"); // Url not found
	//testUri("/c", "HTTP/1.1 400"); // Bad request
	//testUri("/d", "HTTP/1.1 500"); // Internal server error
	return 0;
}
