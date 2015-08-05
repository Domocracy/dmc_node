///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Dmc Node
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "UpnpDriver.h"
#include "upnp/SddpParser.h"
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/SocketAddress.h>
#include <Poco/URI.h>
#include <sstream>
#include <cassert>


using namespace cjson;
using namespace std;
using namespace Poco;
using namespace Poco::Net;

namespace dmc {
	UpnpDriver * UpnpDriver::mInstance = nullptr;

	//-----------------------------------------------------------------------------------------------------------------
	// Static methods
	UpnpDriver * UpnpDriver::get() {
		assert(mInstance);
		return mInstance;
	}

	//-----------------------------------------------------------------------------------------------------------------
	void UpnpDriver::init() {
		assert(!mInstance);
		mInstance = new UpnpDriver();
	}

	//-----------------------------------------------------------------------------------------------------------------
	void UpnpDriver::end() {
		assert(mInstance);
		delete mInstance;

	}

	//-----------------------------------------------------------------------------------------------------------------
	// Non-static methods
	void UpnpDriver::discover() {
		std::string searchAll = "M-SEARCH * HTTP/1.1\r\n" + 
								string("HOST: 239.255.255.250:1900\r\n") +
								"MAN: \"ssdp:discover\"\r\n" +
								"MX: 1\r\n" +
								"ST: ssdp:all\r\n\r\n";
		Poco::Net::MulticastSocket	socket;
		socket.sendTo(searchAll.c_str(), searchAll.length(), mMulticastGroup);

		char buffer[1024];
		int len = 0;
		socket.setReceiveTimeout(Poco::Timespan(5, 0));
		try {
			while ((len = socket.receiveBytes(buffer, 1024)) != -1) {
				mMessages.push_back(parseResponse(buffer));
			}
		}
		catch (Poco::TimeoutException _err) {
			std::cout << "Timout!" << std::endl;
		}

	}

	//-----------------------------------------------------------------------------------------------------------------
	void UpnpDriver::discover(string _uuid) {
		std::string searchAll = "M-SEARCH * HTTP/1.1\r\n" + 
								string("HOST: 239.255.255.250:1900\r\n") +
								"MAN: \"ssdp:discover\"\r\n" +
								"MX: 1\r\n" +
								"ST: uuid:" + _uuid + "\r\n\r\n";
		Poco::Net::MulticastSocket	socket;
		socket.sendTo(searchAll.c_str(), searchAll.length(), mMulticastGroup);
	}

	//-----------------------------------------------------------------------------------------------------------------
	void UpnpDriver::discover(string _type, string _version, bool _isDevice) {
		std::string searchAll = "M-SEARCH * HTTP/1.1\r\n" + 
								string("HOST: 239.255.255.250:1900\r\n") +
								"MAN: \"ssdp:discover\"\r\n" +
								"MX: 1\r\n" +
								"ST: urn:schemas-upnp-org:" + (_isDevice? "device:":"service:") + _type + ":" + _version + "\r\n\r\n";
		Poco::Net::MulticastSocket	socket;
		socket.sendTo(searchAll.c_str(), searchAll.length(), mMulticastGroup);
	}

	//-----------------------------------------------------------------------------------------------------------------
	std::string UpnpDriver::description(const std::string &_uri) {
		// Parse uri
		URI uri(_uri);

		// Send Request
		SocketAddress addr(uri.getHost(), uri.getPort());
		HTTPClientSession session(addr);
		HTTPRequest req;
		req.setMethod("GET");
		req.setURI(uri.getPath());
		session.sendRequest(req);
		
		// Parse response
		stringstream ss;
		HTTPResponse response;
		string fragmentMsg;
		std::istream& body = session.receiveResponse(response);
		while(!body.eof()) {
			body >> fragmentMsg;
			ss << fragmentMsg;
		}

		return ss.str();
	}

	//-----------------------------------------------------------------------------------------------------------------
	// Private members
	UpnpDriver::UpnpDriver(): mMulticastGroup("239.255.255.250", 1900) {

	}

	//-----------------------------------------------------------------------------------------------------------------
	UpnpDriver::~UpnpDriver() {

	}

	//-----------------------------------------------------------------------------------------------------------------
	Json UpnpDriver::parseResponse(string _response) {
		SddpParser parser;
		return parser.parse(_response);
	}

}	//	namespace dmc