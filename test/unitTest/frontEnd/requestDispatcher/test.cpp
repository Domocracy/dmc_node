///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//

#include <frontEnd/RequestDispatcher.h>
#include <frontEnd/Request.h>

#include <assert.h>
#include <cjson/json.h>
#include <Poco/Net/HTTPRequest.h>
#include <vector>

// Mock classes
namespace dmc {
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
			mCounter++;
			Response response;
			_localServer.respond(_request, response);
		}

		unsigned mCounter = 0;
	};
} // namespace dmc

using namespace Poco::Net;
using namespace dmc;
using namespace std;

void standardResponse(const Request &_req);
void validRequests();
void specificDispatch();

int main(int, const char**) {
	
	// Standard response.
	Request reqA(64);
	reqA.url() = "";
	reqA.body() = "";
	standardResponse(reqA);

	Request reqB(64);
	reqB.url() = "/";
	reqB.body() = "";
	standardResponse(reqB);

	// Valid requests.
	validRequests();
	
	// Top vs Specific dispatching.
	specificDispatch();
}


void standardResponse(const Request &_req) {
	RequestProcessor proc;
	RequestDispatcher disp;
	disp.subscribe(&proc, "/");	// Standard Responder.

	LocalServer server;
	assert(disp.dispatch(server, _req));
	assert(proc.mCounter == 1);
}

void validRequests() {
	RequestDispatcher disp;
	RequestProcessor procA;
	disp.subscribe(&procA, "/");	// Standard Responder.
	RequestProcessor procB;
	disp.subscribe(&procB, "/subscribe");

	LocalServer server;
	Request reqA(64);
	reqA.url() = "subscribe";
	reqA.body() = "";
	assert(disp.dispatch(server, reqA));
	assert(procA.mCounter == 0);
	assert(procB.mCounter == 1);

	Request reqB(64);
	reqB.url() = "/subscribe";
	reqB.body() = "";
	assert(disp.dispatch(server, reqB));
	assert(procA.mCounter == 0);
	assert(procB.mCounter == 2);

	Request reqC(64);
	reqC.url() = "/noexist";
	reqC.body() = "";
	assert(disp.dispatch(server, reqC));
	assert(procA.mCounter == 1);
	assert(procB.mCounter == 2);
}


void specificDispatch() {
	RequestDispatcher disp;
	RequestProcessor procA;
	disp.subscribe(&procA, "/subscribe");
	RequestProcessor procB;
	disp.subscribe(&procB, "/subscribe/dev");

	LocalServer server;
	Request reqA(64);
	reqA.url() = "/subscribe";
	reqA.body() = "";
	assert(disp.dispatch(server, reqA));
	assert(procA.mCounter == 1);
	assert(procB.mCounter == 0);

	Request reqB(64);
	reqB.url() = "/subscribe/dev";
	reqB.body() = "";
	assert(disp.dispatch(server, reqB));
	assert(procA.mCounter == 1);
	assert(procB.mCounter == 1);
}