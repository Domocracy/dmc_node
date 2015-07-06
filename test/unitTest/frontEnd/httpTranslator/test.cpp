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
	// --- Test setup ---
	Response empty = Response::ok();
	Response ok = Response::ok("a"); // Simple answer
	// --- http -> dmc
	HTTPRequest req;
	req.setURI("/a");
	req.read(stringstream(string("body")));
	HTTPTranslator a;
	Request dmcReq(1);
	a.translate(req, dmcReq);
	return 0;
}





