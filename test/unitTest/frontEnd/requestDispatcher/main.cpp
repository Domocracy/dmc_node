///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
#define Net_HTTPRequest_INCLUDED // Deactivate inclusion of POCO HTTP Requests
#include "frontEnd/RequestDispatcher.h"
#include <assert.h>
#include <vector>

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
	class RequestProcessor {};
} // namespace dmc

using namespace Poco::Net;
using namespace dmc;
using namespace std;

int main(int, const char**) {
	vector<string>	protocols = { "http", "https" };
	vector<string>	hosts = { "localhost", "192.168.0.64" };
	vector<string>	urlBases;
	for(auto host : hosts)
		for(auto protocol : protocols)
			urlBases.push_back(protocol + "://"+ host + "/");

	// Empty dispatcher should never retrieve anything
	std::string outUrl;
	RequestDispatcher a;
	assert(nullptr == a.dispatch({""}, outUrl));
	assert(outUrl.empty());
	assert(nullptr == a.dispatch({"/"}, outUrl));
	assert(outUrl.empty());
	assert(nullptr == a.dispatch({"/suscribe"}, outUrl));
	assert(outUrl.empty());
	for(auto base : urlBases) {
		assert(nullptr == a.dispatch({base+"suscribe"}, outUrl));
	}

	// Top level suscriber
	RequestDispatcher b;
	RequestProcessor foo;
	b.subscribe(&foo, "/");
	assert(nullptr == b.dispatch({""}, outUrl)); // Ill-formed
	assert(outUrl.empty());
	assert(nullptr == b.dispatch({"/"}, outUrl)); // Ill-formed
	assert(outUrl.empty());
	assert(nullptr == b.dispatch({"/suscribe"}, outUrl)); // Ill-formed
	assert(outUrl.empty());
	for(auto base : urlBases) {
		assert(&foo == b.dispatch({base}, outUrl));
	}
	for(auto base : urlBases) {
		assert(&foo == b.dispatch({base+"hello"}, outUrl));
	}

	// Two suscribers
	RequestDispatcher c;
	RequestProcessor topLevel, specific;
	c.subscribe(&topLevel, "/top");
	c.subscribe(&specific, "/top/spec");
	assert(nullptr == c.dispatch({"/x"}, outUrl)); // No one suscribed here
	assert(outUrl.empty());
	assert(c.dispatch({urlBases[0] + "top/spec/what"}, outUrl) == &specific);
	assert(outUrl == "top/spec/what");

	// Test first subscriber have preference for equal specializations
	RequestDispatcher c;
	RequestProcessor specificA, specificB;
	c.subscribe(&specificA, "/top/spec");
	c.subscribe(&specificB, "/top/spec");
	assert(c.dispatch({urlBases[0] + "top/spec/what"}, outUrl) == &specificA);
	assert(outUrl.empty());

}





