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
	std::string outUrlA;
	RequestDispatcher a;
	assert(nullptr == a.dispatch({""}, outUrlA));
	assert(outUrlA.empty());
	assert(nullptr == a.dispatch({"/"}, outUrlA));
	assert(outUrlA.empty());
	assert(nullptr == a.dispatch({"/suscribe"}, outUrlA));
	assert(outUrlA.empty());
	for(auto base : urlBases) {
		assert(nullptr == a.dispatch({"GET",base+"suscribe"}, outUrlA));
	}

	// Top level suscriber
	std::string outUrlB;
	RequestDispatcher b;
	RequestProcessor foo;
	b.subscribe(&foo, "/");
	assert(nullptr == b.dispatch({"GET",""}, outUrlB)); // Ill-formed
	assert(outUrlB.empty());
	assert(nullptr == b.dispatch({"GET","/"}, outUrlB)); // Ill-formed
	assert(outUrlB.empty());
	assert(nullptr == b.dispatch({"GET","/suscribe"}, outUrlB)); // Ill-formed
	assert(outUrlB.empty());
	for(auto base : urlBases) {
		assert(&foo == b.dispatch({"GET",base}, outUrlB));
	}
	for(auto base : urlBases) {
		assert(&foo == b.dispatch({"GET",base+"hello"}, outUrlB));
	}

	// Test invalid host and invalid protocol
	std::string outUrlC;
	RequestDispatcher c;
	RequestProcessor bar;
	c.subscribe(&bar, "/hello/dolly");
	assert(nullptr == c.dispatch({"GET", "ftp://localhost/hello/dolly"}, outUrlC));	// Invalid protocol
	assert(nullptr == c.dispatch({"GET", "https://www.@invalid@.com/hello/dolly"}, outUrlC));	// Invalid Host

	// Two suscribers
	std::string outUrlD;
	RequestDispatcher d;
	RequestProcessor topLevel, specific;
	d.subscribe(&topLevel, "/top");
	d.subscribe(&specific, "/top/spec");
	assert(nullptr == d.dispatch({"GET","/x"}, outUrlD)); // No one suscribed here
	assert(outUrlD.empty());
	assert(d.dispatch({"GET",urlBases[0] + "top/spec/what"}, outUrlD) == &specific);
	assert(outUrlD == "/what");

	// Test first subscriber have preference for equal specializations
	std::string outUrlE;
	RequestDispatcher e;
	RequestProcessor specificA, specificB;
	e.subscribe(&specificA, "/top/spec");
	e.subscribe(&specificB, "/top/spec");
	assert(e.dispatch({"GET",urlBases[0] + "top/spec/what"}, outUrlE) == &specificB);
	assert(outUrlE == "/what");
}
