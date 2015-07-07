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
	std::stringstream mStream;
	Poco::Net::SocketAddress mAddress;
	Poco::Net::HTTPServerParams *mParams;
	Poco::Net::HTTPServerResponse* mResponse;
	// Inherited via HTTPServerRequest
	virtual std::istream & stream() override { return mStream; }
	virtual bool expectContinue() const override { return false; }
	virtual const Poco::Net::SocketAddress & clientAddress() const override { return mAddress; }
	virtual const Poco::Net::SocketAddress & serverAddress() const override { return mAddress;	}
	virtual const Poco::Net::HTTPServerParams & serverParams() const override { return *mParams; }
	virtual Poco::Net::HTTPServerResponse & response() const override { return *mResponse; }

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
	Response Response::ok() {
		return Response(std::string());
	}

	void Response::serialize(std::ostream& _os) const {
		_os << mContent;
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
	TestHttpResponse resp;
	assert(t1.translate(empty, resp));
	assert(resp.getStatus() == HTTPResponse::HTTP_OK);
	assert(resp.getReason() == HTTPResponse::HTTP_REASON_OK);
	assert(resp.mSS.str().empty());
	// Response with body
	Response ok = Response(std::string("a")); // Simple answer
	HTTPTranslator t2;
	TestHttpResponse resp2;
	assert(t2.translate(ok, resp2));
	assert(resp2.getStatus() == HTTPResponse::HTTP_OK);
	assert(resp2.getReason() == HTTPResponse::HTTP_REASON_OK);
	assert(resp2.mSS.str() == "a");
	// --- http -> dmc
	// Complete request
	TestHttpRequest req;
	req.setURI("/a");
	req.mStream << "3";
	req.setContentLength(1);
	HTTPTranslator a;
	Request dmcReq(1);
	assert(a.translate(req, dmcReq));
	assert(dmcReq.url() == "/a");
	assert(int(dmcReq.body()) == 3);
	// Complete request except for content-length (must fail)
	TestHttpRequest req5;
	req5.setURI("/a");
	req5.mStream << "3";
	HTTPTranslator f;
	Request dmcReq5(1);
	assert(!f.translate(req5, dmcReq5));
	// Ill-formed request with no url HTTPRequest req;
	TestHttpRequest req2;
	req2.setURI("");
	HTTPTranslator b;
	Request dmcReq2(2);
	assert(!b.translate(req2, dmcReq2)); // Il-formed request must fail to translate
	// Ill-formed request with invalid json;
	TestHttpRequest req3;
	req3.setURI("/b");
	req3.mStream << "meh!";
	req3.setContentLength(4);
	HTTPTranslator c;
	Request dmcReq3(3);
	assert(!c.translate(req3, dmcReq3)); // Il-formed request must fail to translate
	return 0;
}





