//----------------------------------------------------------------------------------------------------------------------
// local server unit test
//----------------------------------------------------------------------------------------------------------------------
#include <string>
#include <frontEnd/LocalServer.h>
#include <frontEnd/HttpTranslator.h>
#include <frontEnd/RequestDispatcher.h>

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

int main(int, const char**) {
	// --- Test setup ---
	RequestDispatcher dispatcher;
	LocalServer server(dispatcher, 5028);
	// --- Test listening ---
	// Test translator failure
	// Test dispatcher failure
	return 0;
}





