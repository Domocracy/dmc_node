///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//

#include "frontEnd/RequestDispatcher.h"

#include <assert.h>
#include <Poco/Net/HTTPRequest.h>
#include <vector>

// Mock classes
namespace dmc {
	class Request {
	public:
		unsigned id() const { return mId; };
		std::string url() const { return mUrl; };

		unsigned mId = 0;
		std::string mUrl = "";
	};
	class Response {};
	class LocalServer {
	public:
		bool respond(const Request &_request, const Response &_response) {
			return true;
		}
	};

	class RequestProcessor {
	public:
		void process(const Request &_request, LocalServer &_localServer){
			Response response;
			_localServer.respond(_request, response);
		}
	};

} // namespace dmc

using namespace Poco::Net;
using namespace dmc;
using namespace std;


// Global tick counter.
unsigned gTickCounter = 0;

int main(int, const char**) {
	
	// Init mocks
	RequestProcessor proc;
	RequestDispatcher dispatcher;
	dispatcher.subscribe(&proc, "/subscribe");
	
	LocalServer server;

	// Test Valid subscription
	Request req({64, "/subscribe"});
	dispatcher.dispatch(server, req);

	Request req({64, "/subscribe"});

}
