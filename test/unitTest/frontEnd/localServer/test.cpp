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
	// --- Mock response
	class Response {
	public:
	};

	// --- Mock request processor
	class RequestProcessor {
	public:
		void processRequest(const Request& _req, const std::string& _parsedUrl, LocalServer& _server) {
			while(!mRespond)
			{}
			_server.respond(_req, response);
			mRespond = false;
		}

		bool mRespond = false;
		Response response;
	};

	RequestProcessor gA;

	// --- Mock request dispatcher
	class RequestDispatcher {
	public:
		RequestProcessor* dispatch(const Poco::Net::HTTPRequest &_request, std::string &_parsedUrl) const {
			return &gA;
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





