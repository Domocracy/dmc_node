//----------------------------------------------------------------------------------------------------------------------
// local server unit test
//----------------------------------------------------------------------------------------------------------------------
#include <cassert>
#include <string>
#include <frontEnd/HttpTranslator.h>
#include <frontEnd/Request.h>
#include <frontEnd/Response.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <sstream>

namespace dmc {
	// --- Mock
	Response::Response(bool) {
	}

	Response Response::ok(const std::string& _body) {
		Response r(true);
		r.mContent = _body;
		return r;
	}
}	// namespace dmc

using namespace dmc;
using namespace Poco::Net;
using namespace std;

int main(int, const char**) {
	// --- dmc -> http
	// Empty response
	Response empty = Response::ok();
	HTTPTranslator t1;
	HTTPResponse resp;
	assert(t1.translate(empty, resp));
	assert()
	Response ok = Response::ok("a"); // Simple answer
	// --- http -> dmc
	HTTPRequest req;
	req.setURI("/a");
	req.read(stringstream(string("body")));
	HTTPTranslator a;
	Request dmcReq(1);
	assert(a.translate(req, dmcReq));
	assert(dmcReq.url() == "/a");
	assert(dmcReq.body() == "body");
	return 0;
}





