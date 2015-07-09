//----------------------------------------------------------------------------------------------------------------------
// Mock Hue Bridge
//----------------------------------------------------------------------------------------------------------------------
#include "MockHueBridge.h"
#include "ErrorMessage.h"
#include <frontEnd/LocalServer.h>
#include <frontEnd/Response.h>
#include <frontEnd/Request.h>
#include <frontEnd/RequestDispatcher.h>
#include <Poco/Net/HTTPServer.h>
#include <cjson/json.h>
#include <sstream>

using namespace Poco::Net;
using namespace cjson;
using namespace dmc;
using namespace std;

//----------------------------------------------------------------------------------------------------------------------
MockHueBridge::MockHueBridge(unsigned _port)
	:mServer(mDispatcher, _port)
{
	mDispatcher.subscribe(&mReqProcessor, "/");
}

//----------------------------------------------------------------------------------------------------------------------
void MockHueBridge::HueReqProcessor::generateResponse(const dmc::Request & _request, std::ostream& _responseBody) {
	ErrorMessage::resourceNotAvailable(_request.url()).serialize(_responseBody);
}

//----------------------------------------------------------------------------------------------------------------------
void MockHueBridge::HueReqProcessor::process(const Request & _request, LocalServer & _localServer)
{
	stringstream responseBody;
	generateResponse(_request, responseBody);
	Response resp(responseBody.str());
	_localServer.respond(_request, resp);
}
