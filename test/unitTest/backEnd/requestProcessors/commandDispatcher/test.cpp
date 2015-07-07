////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// DMC_NODE
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "backEnd/requestProcessors/CommandDispatcher.h"
#include "frontEnd/Request.h"
#include <cassert>
#include <string>

namespace dmc {
	// --- Mock classes ---
	class Response {
	public:
		std::string mContent;
	};

	class LocalServer {
	public:
		bool respond(const Request& request, const Response& response) {
			//
		}

		bool responded = false;
		std::string response;
	};

	class DeviceManager {
	public:
	};

	class RequestDispatcher {
	public:
		void subscribe(RequestProcessor*, const std::string& _localUrl) {
			assert(_localUrl == "/command");
			assert(!suscribed);
			suscribed = true;
		}
		bool suscribed = false;
	};
}	//	namespace dmc

using namespace dmc;

void testEverythingOk() {
	LocalServer server;
	Request req(0);
	req.url() = "/command/ok";
	DeviceManager mgr;
	RequestDispatcher rd;
	CommandDispatcher cmdDisp(mgr, rd);
	assert(rd.suscribed);
	cmdDisp.process(req, server);
	assert(server.responded);
	assert(server.response == "ok");
}

int main(int, const char**) {
	// All tests
	testEverythingOk();
	// Test Device fails to run request
	// Test Device not found
	// Test url error



	// Test construction and subscription.
	DeviceManager devMgr;
	RequestDispatcher reqDispatcher;

	CommandDispatcher cmdDispatcher(devMgr, reqDispatcher);

	// Test request processing.
	LocalServer server;
	Request req;
	cmdDispatcher.process(req, &server);
}
