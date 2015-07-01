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
		assert(nullptr == a.dispatch({"GET",base+"suscribe"}, outUrl));
	}

	// Top level suscriber
	RequestDispatcher b;
	RequestProcessor foo;
	b.subscribe(&foo, "/");
	assert(nullptr == b.dispatch({"GET",""}, outUrl)); // Ill-formed
	assert(outUrl.empty());
	assert(nullptr == b.dispatch({"GET","/"}, outUrl)); // Ill-formed
	assert(outUrl.empty());
	assert(nullptr == b.dispatch({"GET","/suscribe"}, outUrl)); // Ill-formed
	assert(outUrl.empty());
	for(auto base : urlBases) {
		assert(&foo == b.dispatch({"GET",base}, outUrl));
	}
	for(auto base : urlBases) {
		assert(&foo == b.dispatch({"GET",base+"hello"}, outUrl));
	}

	// Test invalid host and invalid protocol
	RequestDispatcher e;
	RequestProcessor bar;
	e.subscribe(&bar, "/hello/dolly");
	assert(nullptr == e.dispatch({"GET", "ftp://localhost/hello/dolly"}, outUrl));	// Invalid protocol
	assert(nullptr == e.dispatch({"GET", "https://www.@invalid@.com/hello/dolly"}, outUrl));	// Invalid Host

	// Two suscribers
	RequestDispatcher c;
	RequestProcessor topLevel, specific;
	c.subscribe(&topLevel, "/top");
	c.subscribe(&specific, "/top/spec");
	assert(nullptr == c.dispatch({"GET","/x"}, outUrl)); // No one suscribed here
	assert(outUrl.empty());
	assert(c.dispatch({"GET",urlBases[0] + "top/spec/what"}, outUrl) == &specific);
	assert(outUrl == "top/spec/what");

	// Test first subscriber have preference for equal specializations
	RequestDispatcher d;
	RequestProcessor specificA, specificB;
	d.subscribe(&specificA, "/top/spec");
	d.subscribe(&specificB, "/top/spec");
	assert(d.dispatch({"GET",urlBases[0] + "top/spec/what"}, outUrl) == &specificB);
	assert(outUrl.empty());
}
