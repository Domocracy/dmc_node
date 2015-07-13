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
	bool HueDriver::init(cjson::Json& _config) {
		assert(!sHueDriver);
		sHueDriver = new HueDriver(_config);
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
		string msgPiece;
		stringstream ss;
		std::istream& respBody = session.receiveResponse(resp);
		while(!respBody.eof()) {
			respBody >> msgPiece;
			ss << msgPiece;
		}
		cout << ss.str();
		if(!_data.parse(ss)){
			_errorInfo << "Error parsing bridge response\n";
			return false;
		}
		if (_data.contains("error")) {
			_errorInfo << std::string(_data["error"].serialize());
			return false;
		}
		return true;
	}

	//------------------------------------------------------------------------------------------------------------------
	bool HueDriver::putData(const std::string& _url, const cjson::Json& _request, std::ostream& _errorInfo) {
		HTTPClientSession session(mBridgeIp);
		HTTPRequest req;
		req.setMethod("GET");
		req.setURI(_url);
		//req.setHost(mBridgeIp.host().toString());
		_request.serialize(session.sendRequest(req));
		HTTPResponse resp;
		Json respData;
		if(!respData.parse(session.receiveResponse(resp))){
			_errorInfo << "Error parsing bridge response\n";
			return false;
		}
		if (respData.contains("error")) {
			_errorInfo << std::string(respData["error"].serialize());
			return false;
		}
		return true;
	}

	//------------------------------------------------------------------------------------------------------------------
	HueDriver::HueDriver(const cjson::Json& _config) {
		mBridgeIp = SocketAddress(string(_config["host"]), 80);
	}

}}	// namespace dmc::hue