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
	ostringstream oss;
	resp.write(oss);
	assert(oss.str().empty());
	// Response with body
	Response ok = Response::ok("a"); // Simple answer
	HTTPTranslator t2;
	HTTPResponse resp2;
	assert(t2.translate(ok, resp2));
	ostringstream oss2;
	resp.write(oss2);
	assert(oss2.str() == "a");
	// --- http -> dmc
	// Complete request
	HTTPRequest req;
	req.setURI("/a");
	req.read(stringstream(string("body")));
	HTTPTranslator a;
	Request dmcReq(1);
	assert(a.translate(req, dmcReq));
	assert(dmcReq.url() == "/a");
	assert(dmcReq.body() == "body");
	// Ill-formed request with no urlHTTPRequest req;
	HTTPRequest req2;
	req.setURI("");
	HTTPTranslator b;
	Request dmcReq2(2);
	assert(!b.translate(req2, dmcReq2)); // Il-formed request must fail to translate
	return 0;
}





