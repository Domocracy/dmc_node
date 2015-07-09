//----------------------------------------------------------------------------------------------------------------------
// Mock Hue Bridge
//----------------------------------------------------------------------------------------------------------------------
#ifndef _MOCKHUEBRIDGE_MOCKHUEBRIDGE_H_
#define _MOCKHUEBRIDGE_MOCKHUEBRIDGE_H_

#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>

class MockHueBridge : Poco::Net::HTTPRequestHandlerFactory {
public:
	MockHueBridge(unsigned _port);
	bool listen();

private:
	// Inherited via HTTPRequestHandlerFactory
	virtual Poco::Net::HTTPRequestHandler * createRequestHandler(const Poco::Net::HTTPServerRequest & request) override;

	class HueRequestHandler : public Poco::Net::HTTPRequestHandler {
	public:
		// Inherited via HTTPRequestHandler
		virtual void handleRequest(HTTPServerRequest & request, HTTPServerResponse & response) override;
	};

private:
	Poco::Net::HTTPServer*	mHTTPServer;
};

#endif // _MOCKHUEBRIDGE_MOCKHUEBRIDGE_H_
