//----------------------------------------------------------------------------------------------------------------------
// local server unit test
//----------------------------------------------------------------------------------------------------------------------
#include <string>
#include <frontEnd/LocalServer.h>

// Mock classes
namespace Poco {
	namespace Net {
		class HTTPRequest;
	}
}

namespace dmc {
	class Request;

	// --- Mock request dispatcher
	class RequestDispatcher {
	public:
		void dispatch(const Request &_request, std::string &_parsedUrl) const {
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
}





