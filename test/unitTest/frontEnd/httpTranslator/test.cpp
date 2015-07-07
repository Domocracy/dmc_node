//----------------------------------------------------------------------------------------------------------------------
// http translator unit test
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

class TestHttpRequest : public Poco::Net::HTTPServerRequest {
public:
	stringstream mStream;
	SocketAddress mAddress;
	HTTPServerParams *mParams;
	HTTPServerResponse* mResponse;
	// Inherited via HTTPServerRequest
	virtual std::istream & stream() override { return mStream; }
	virtual bool expectContinue() const override { return false; }
	virtual const SocketAddress & clientAddress() const override { return mAddress; }
	virtual const SocketAddress & serverAddress() const override { return mAddress;	}
	virtual const HTTPServerParams & serverParams() const override { return *mParams; }
	virtual HTTPServerResponse & response() const override { return *mResponse; }

};

class TestHttpResponse : public Poco::Net::HTTPServerResponse {
public:
	unsigned mSent = 0;
	std::stringstream mSS;
	// Inherited via HTTPServerResponse
	virtual void sendContinue() override {return;}

	// Possible ways to send
	virtual std::ostream & send() override
	{
		assert(!sent());
		mSent++;
		return mSS;
	}

	virtual void sendBuffer(const void * pBuffer, std::size_t length) override 
	{ 
		assert(!sent());
		mSent++;
		mSS << reinterpret_cast<const char*>(pBuffer);
		return;
	}

	virtual void sendFile(const std::string & path, const std::string & mediaType) override { assert(false); return;}
	virtual void redirect(const std::string & uri, HTTPStatus status = HTTP_FOUND) override { assert(false); return;}
	virtual void requireAuthentication(const std::string & realm) override { assert(false); return;}

	virtual bool sent() const override
	{
		return mSent > 0;
	}

};

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
	TestHttpResponse resp;
	assert(t1.translate(empty, resp));
	ostringstream oss;
	resp.write(oss);
	assert(oss.str() == "HTTP/1.1 200 Ok\r\n\r\n");
	assert(resp.getStatus() == HTTPResponse::HTTP_OK);
	// Response with body
	Response ok = Response::ok("a"); // Simple answer
	HTTPTranslator t2;
	TestHttpResponse resp2;
	assert(t2.translate(ok, resp2));
	ostringstream oss2;
	resp2.write(oss2);
	assert(oss2.str() == "HTTP/1.1 200 Ok\r\n\r\na");
	assert(resp.getStatus() == HTTPResponse::HTTP_OK);
	// --- http -> dmc
	// Complete request
	TestHttpRequest req;
	req.setURI("/a");
	req.read(stringstream(string("{3}")));
	HTTPTranslator a;
	Request dmcReq(1);
	assert(a.translate(req, dmcReq));
	assert(dmcReq.url() == "/a");
	assert(int(dmcReq.body()) == 3);
	// Ill-formed request with no url HTTPRequest req;
	TestHttpRequest req2;
	req2.setURI("");
	HTTPTranslator b;
	Request dmcReq2(2);
	assert(!b.translate(req2, dmcReq2)); // Il-formed request must fail to translate
	// Ill-formed request with invalid json;
	TestHttpRequest req3;
	req3.setURI("/b");
	req3.read(stringstream(string("meh!")));
	HTTPTranslator c;
	Request dmcReq3(3);
	assert(!c.translate(req3, dmcReq3)); // Il-formed request must fail to translate
	return 0;
}





