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

	Response Response::ok() {
		Response r(true);
		return r;
	}

	Response Response::ok(const std::string& _body) {
		Response r(true);
		r.mContent = _body;
		return r;
	}

	const std::string& Response::serialize() const { return mContent; }
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
	assert(oss.str() == "HTTP/1.1 200 Ok\r\n\r\n");
	assert(resp.getStatus() == HTTPResponse::HTTP_OK);
	// Response with body
	Response ok = Response::ok("a"); // Simple answer
	HTTPTranslator t2;
	HTTPResponse resp2;
	assert(t2.translate(ok, resp2));
	ostringstream oss2;
	resp2.write(oss2);
	assert(oss2.str() == "HTTP/1.1 200 Ok\r\n\r\na");
	assert(resp.getStatus() == HTTPResponse::HTTP_OK);
	// --- http -> dmc
	// Complete request
	HTTPRequest req;
	req.setURI("/a");
	req.read(stringstream(string("{3}")));
	HTTPTranslator a;
	Request dmcReq(1);
	assert(a.translate(req, dmcReq));
	assert(dmcReq.url() == "/a");
	assert(int(dmcReq.body()) == 3);
	// Ill-formed request with no url HTTPRequest req;
	HTTPRequest req2;
	req2.setURI("");
	HTTPTranslator b;
	Request dmcReq2(2);
	assert(!b.translate(req2, dmcReq2)); // Il-formed request must fail to translate
	// Ill-formed request with invalid json;
	HTTPRequest req3;
	req3.setURI("/b");
	req3.read(stringstream(string("meh!")));
	HTTPTranslator c;
	Request dmcReq3(3);
	assert(!c.translate(req3, dmcReq3)); // Il-formed request must fail to translate
	return 0;
}





