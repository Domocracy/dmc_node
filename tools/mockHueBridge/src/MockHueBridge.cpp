//----------------------------------------------------------------------------------------------------------------------
// Mock Hue Bridge
//----------------------------------------------------------------------------------------------------------------------
#include "MockHueBridge.h"
#include "ErrorMessage.h"
#include <Poco/Net/HTTPServer.h>
#include <cjson/json.h>

using namespace Poco::Net;
using namespace cjson;

//----------------------------------------------------------------------------------------------------------------------
MockHueBridge::MockHueBridge(unsigned _port) {
	mHTTPServer = new HTTPServer(static_cast<HTTPRequestHandlerFactory*>(this), _port);
}

//----------------------------------------------------------------------------------------------------------------------
bool MockHueBridge::listen() {
	mHTTPServer->start();
}

//----------------------------------------------------------------------------------------------------------------------
HTTPRequestHandler * MockHueBridge::createRequestHandler(const HTTPServerRequest & request)
{
	return new HueRequestHandler;
}

//----------------------------------------------------------------------------------------------------------------------
void MockHueBridge::HueRequestHandler::handleRequest(HTTPServerRequest & request, HTTPServerResponse & response)
{
	Json req;
	if (req.parse(request.stream())) {
		//
	} // Valid request
	else {
		ErrorMessage error = ErrorMessage::invalidJson();
		error.serialize(response.send());
	}
}
