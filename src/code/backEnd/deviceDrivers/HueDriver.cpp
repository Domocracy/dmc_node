///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Dmc Node
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "HueDriver.h"
#include <cjson/json.h>
#include <istream>
#include <sstream>

#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/SocketAddress.h>
#include <Poco/Net/StreamSocket.h>

using namespace Poco::Net;
using namespace std;
using cjson::Json;

namespace dmc { namespace hue {
	//------------------------------------------------------------------------------------------------------------------
	// Static data definition
	HueDriver* HueDriver::sHueDriver = nullptr;

	//------------------------------------------------------------------------------------------------------------------
	bool HueDriver::init(std::istream& _configStream) {
		assert(!sHueDriver);
		Json config;
		if(!config.parse(_configStream))
			return false;
		sHueDriver = new HueDriver(config);
		return sHueDriver != nullptr;
	}

	//------------------------------------------------------------------------------------------------------------------
	bool HueDriver::getData(const std::string& _url, cjson::Json& _data, std::ostream& _errorInfo) {
		HTTPClientSession session(mBridgeIp);
		HTTPRequest req;
		req.setMethod("GET");
		req.setURI(_url);
		//req.setHost(mBridgeIp.host().toString());
		session.sendRequest(req);
		HTTPResponse resp;
		if(!_data.parse(session.receiveResponse(resp))){
			_errorInfo << "Error parsing bridge response\n";
			return false;
		}
		return true;
	}

}}	// namespace dmc::hue