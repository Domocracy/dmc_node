//----------------------------------------------------------------------------------------------------------------------
// local server unit test
//----------------------------------------------------------------------------------------------------------------------
#include <string>
#include <frontEnd/LocalServer.h>
#include <frontEnd/RequestDispatcher.h>

// Mock classes
namespace Poco {
	namespace Net {
		class HTTPRequest;
	}
}

namespace dmc {
	class Request;

	// --- Mock request dispatcher
	bool RequestDispatcher::dispatch(LocalServer& _server, const Request &_request) const{
		return true;
		}
	};
}	// namespace dmc

using namespace dmc;

int main(int, const char**) {
	// --- Test setup ---
	RequestDispatcher dispatcher;
	LocalServer server(dispatcher, 5028);
	// Test POCO systems were properly called during configuration
	// --- Test listening ---
	server.startListening();
	// Test a request
	// --- Test stop ---
	server.stopListening();
	return 0;

	// Todo: Test responding to inexisting or free requests fails.
}





