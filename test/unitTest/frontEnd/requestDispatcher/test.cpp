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
	class Request {};
	class Response {};
	class LocalServer {
	public:
		bool respond(const Request &_request, const Response &_response) {
			return true;
		}
	};

	class RequestProcessor {
	public:
		void process(const Request &_request, LocalServer *_localServer) {
			Response response;
			_localServer->respond(_request, response);
		}
	};

} // namespace dmc

using namespace Poco::Net;
using namespace dmc;
using namespace std;

int main(int, const char**) {
	
}
