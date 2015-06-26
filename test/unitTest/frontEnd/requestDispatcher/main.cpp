///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
#define Net_HTTPRequest_INCLUDED // Deactivate inclusion of POCO HTTP Requests
#include "frontEnd/RequestDispatcher.h"
#include <assert.h>

// Mock classes
namespace Poco {
	namespace Net {
		class HTTPRequest {
		public:
			const std::string& getURI() const { return url; }

			std::string url;
		};
	}
} // namespace Poco

namespace dmc {
	class RequestProcessor {
	public:
		enum class Type {
			eEventPublisher,
			eCommandDispatcher
		};

		virtual Type iAm() const = 0;
	};

	class EventPublisher : public RequestProcessor {
		Type iAm() const { return Type::eEventPublisher; }
	};

	class CommandDispatcher : public RequestProcessor {
		Type iAm() const { return Type::eCommandDispatcher; }
	};
} // namespace dmc

using namespace Poco::Net;
using namespace dmc;

int main(int, const char**) {
	RequestDispatcher dispatcher;

	std::string outUrl;
	RequestProcessor& a = dispatcher.dispatch(HTTPRequest{"/suscribe/a"}, outUrl);
	assert(a.iAm() == RequestProcessor::Type::eEventPublisher);
	assert(outUrl == "a");

	RequestProcessor& b = dispatcher.dispatch(HTTPRequest{"/command/b/c/d?=e"}, outUrl);
	assert(b.iAm() == RequestProcessor::Type::eCommandDispatcher);
	assert(outUrl == "b/c/d?=e");
}





