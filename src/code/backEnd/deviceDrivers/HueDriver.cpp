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
		session.sendRequest(req);
		stringstream ss;
		receiveResp(session, ss);
		if(!_data.parse(ss)){
			_errorInfo << "Error parsing bridge response\n";
			return false;
		}
		return isSuccess(_data, _errorInfo);
	}

	//------------------------------------------------------------------------------------------------------------------
	bool HueDriver::putData(const std::string& _url, const cjson::Json& _request, std::ostream& _errorInfo) {
		HTTPClientSession session(mBridgeIp);
		HTTPRequest req;
		req.setMethod("PUT");
		req.setURI(_url);
		_request.serialize(session.sendRequest(req));
		stringstream ss;
		receiveResp(session, ss);
		Json respData;
		if(!respData.parse(ss)){
			_errorInfo << "Error parsing bridge response\n";
			return false;
		}
		return isSuccess(respData, _errorInfo);
	}

	//------------------------------------------------------------------------------------------------------------------
	bool HueDriver::postData(const std::string& _url, const cjson::Json& _request, std::ostream& _errorInfo) {
		HTTPClientSession session(mBridgeIp);
		HTTPRequest req;
		req.setMethod("POST");
		req.setURI(_url);
		_request.serialize(session.sendRequest(req));
		stringstream ss;
		receiveResp(session, ss);
		Json respData;
		if(!respData.parse(ss)){
			_errorInfo << "Error parsing bridge response\n";
			return false;
		}
		return isSuccess(respData, _errorInfo);
	}

	//------------------------------------------------------------------------------------------------------------------
	bool HueDriver::deleteData(const std::string& _url, const cjson::Json& _request, std::ostream& _errorInfo) {
		HTTPClientSession session(mBridgeIp);
		HTTPRequest req;
		req.setMethod("DELETE");
		req.setURI(_url);
		_request.serialize(session.sendRequest(req));
		stringstream ss;
		receiveResp(session, ss);
		Json respData;
		if(!respData.parse(ss)){
			_errorInfo << "Error parsing bridge response\n";
			return false;
		}
		return isSuccess(respData, _errorInfo);
	}

	//------------------------------------------------------------------------------------------------------------------
	void HueDriver::receiveResp(HTTPClientSession& _session, std::stringstream& _dst) {
		HTTPResponse resp;
		string msgPiece;
		std::istream& respBody = _session.receiveResponse(resp);
		while(!respBody.eof()) {
			respBody >> msgPiece;
			_dst << msgPiece;
		}
	}

	//------------------------------------------------------------------------------------------------------------------
	bool HueDriver::isSuccess(const cjson::Json& _data, std::ostream& _errorInfo) {
		if (_data.isArray() && _data(0).contains("error")) {
			_data.serialize(_errorInfo);
			return false;
		}
		return true;
	}

	//------------------------------------------------------------------------------------------------------------------
	HueDriver::HueDriver(const cjson::Json& _config) {
		mBridgeIp = SocketAddress(string(_config["host"]), 80);
	}

}}	// namespace dmc::hue