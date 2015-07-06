///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//

#include "backEnd/requestProcessors/CommandDispatcher.h"

#include <string>
#include <unordered_map>

// Forward declarations
namespace dmc {
	class Request {};
	class Response {};
	class DeviceManager {};

	class RequestDispatcher {
	public:
		void subscribe(RequestProcessor*, const std::string& _localUrl) {};
	};
	
	class LocalServer {
		bool respond(const Request &_request, const Response &_response) {
			return true;
		}
	};
}	//	namespace dmc

using namespace dmc;

int main(int, const char**) {
	
	// Test construction and subscription.
	DeviceManager devMgr;
	RequestDispatcher reqDispatcher;

	CommandDispatcher cmdDispatcher(devMgr, reqDispatcher);

	// Test request processing.
	LocalServer server;
	Request req;
	cmdDispatcher.process(req, &server);
}
