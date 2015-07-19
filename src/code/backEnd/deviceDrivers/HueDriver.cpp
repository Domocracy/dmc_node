///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Dmc Node
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "HueDriver.h"
#include <cjson/json.h>
#include <istream>
#include <sstream>

#include <backEnd/DeviceFactory.h>
#include <backEnd/devices/HueDevice.h>

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
	void HueDriver::init(std::istream& _configStream) {
		assert(!sHueDriver);
		Json config;
		if(!config.parse(_configStream))
			return;
		sHueDriver = new HueDriver(config);
		registerDeviceCreators();
	}

	//------------------------------------------------------------------------------------------------------------------
	void HueDriver::init(cjson::Json& _config) {
		assert(!sHueDriver);
		sHueDriver = new HueDriver(_config);
		registerDeviceCreators();
	}

	//------------------------------------------------------------------------------------------------------------------
	bool HueDriver::sendRequest(const std::string& _method, const std::string& _uri, const cjson::Json& _body, cjson::Json& _dst, std::ostream& _errorInfo) {
		HTTPClientSession session(mBridgeIp);
		HTTPRequest req;
		req.setMethod(_method);
		req.setURI(mPrefix + _uri);
		std::ostream& reqStrm = session.sendRequest(req);
		if (!_body.isNull()) {
			_body.serialize(reqStrm);
		}
		stringstream ss;
		receiveResp(session, ss);
		if(!_dst.parse(ss)){
			_errorInfo << "Error parsing bridge response\n";
			return false;
		}
		return isSuccess(_dst, _errorInfo);
	}

	//------------------------------------------------------------------------------------------------------------------
	bool HueDriver::getData(const std::string& _url, cjson::Json& _data, std::ostream& _errorInfo) {
		return sendRequest("GET", _url, Json(), _data, _errorInfo);
	}

	//------------------------------------------------------------------------------------------------------------------
	bool HueDriver::putData(const std::string& _url, const cjson::Json& _request, std::ostream& _errorInfo) {
		Json respData;
		return sendRequest("PUT", _url, _request, respData, _errorInfo);
	}

	//------------------------------------------------------------------------------------------------------------------
	bool HueDriver::postData(const std::string& _url, const cjson::Json& _request, std::ostream& _errorInfo) {
		Json respData;
		return sendRequest("POST", _url, _request, respData, _errorInfo);
	}

	//------------------------------------------------------------------------------------------------------------------
	bool HueDriver::deleteData(const std::string& _url, const cjson::Json& _request, std::ostream& _errorInfo) {
		Json respData;
		return sendRequest("DELETE", _url, _request, respData, _errorInfo);
	}

	//------------------------------------------------------------------------------------------------------------------
	void HueDriver::registerDeviceCreators() {
		DeviceFactory *factory = DeviceFactory::get();
		factory->subscribe("HueDevice", [](unsigned _id, const cjson::Json &_data) { return new HueDevice(_id, _data);});
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
		mPrefix = string("/api/") + _config["user"];
	}

}}	// namespace dmc::hue