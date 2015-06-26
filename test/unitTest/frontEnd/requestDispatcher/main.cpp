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
	// Test invalid requests
	assert(nullptr == dispatcher.dispatch(HTTPRequest{""}, outUrl));
	assert(nullptr == dispatcher.dispatch(HTTPRequest{"/suscribe/a"}, outUrl));
	assert(nullptr == dispatcher.dispatch(HTTPRequest{"/command/b/c/d?=e"}, outUrl));

	// Test valid requests
	RequestProcessor* a = dispatcher.dispatch(HTTPRequest{"http://some.host/suscribe/"}, outUrl);
	assert(a->iAm() == RequestProcessor::Type::eEventPublisher);
	assert(outUrl == "");
}





