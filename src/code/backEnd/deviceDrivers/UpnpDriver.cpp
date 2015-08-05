///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Dmc Node
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "UpnpDriver.h"
#include <cassert>

using namespace cjson;
using namespace std;
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
	void UpnpDriver::discoverAll() {
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
	// Private members
	UpnpDriver::UpnpDriver(): mMulticastGroup("239.255.255.250", 1900) {

	}

	//-----------------------------------------------------------------------------------------------------------------
	UpnpDriver::~UpnpDriver() {

	}

	//-----------------------------------------------------------------------------------------------------------------
	Json UpnpDriver::parseResponse(string _response) {
		UpnpParser parser;
		return parser.parse(_response);
	}

	//-----------------------------------------------------------------------------------------------------------------
	// ResponseParser.

	Json UpnpParser::parse(string _message) {
		switch (decodeType(extractLine(_message))){
		case eMessageType::M_SEARCH:
			return decodeMSearch(_message);
			break;
		case eMessageType::NOTIFY:
			return decodeNotify(_message);
			break;
		case eMessageType::RESPONSE:
			return decodeResponse(_message);
			break;
		case eMessageType::ERR_TYPE:
			Json error;
			error["type"] = "Un-spected type of message";
			return error;
			break;
		}
	}

	//-----------------------------------------------------------------------------------------------------------------
	UpnpParser::eMessageType UpnpParser::decodeType(const std::string & _line) {
		if (_line.find("M-SEARCH") != string::npos) {
				return eMessageType::M_SEARCH;
		} else if (_line.find("NOTIFY") != string::npos) {
			return eMessageType::NOTIFY;
		} else if (_line.find("200 OK") != string::npos) {
			return eMessageType::RESPONSE;
		} else {
			return eMessageType::ERR_TYPE;
		}
	}

	//-----------------------------------------------------------------------------------------------------------------
	cjson::Json UpnpParser::decodeMSearch(std::string & _message) {
		Json search;
		search["type"] = "M-SEARCH";
		search["headers"] = decodeHeaders(_message);
		search["body"] = decodeBody(_message);
		return search;
	}

	//-----------------------------------------------------------------------------------------------------------------
	Json UpnpParser::decodeNotify(std::string & _message) {
		Json notification;
		notification["type"] = "NOTIFY";
		notification["headers"] = decodeHeaders(_message);
		notification["body"] = decodeBody(_message);
		return notification;
	}

	//-----------------------------------------------------------------------------------------------------------------
	Json UpnpParser::decodeResponse(std::string & _message) {
		Json response;
		response["type"] = "RESPONSE";
		response["headers"] = decodeHeaders(_message);
		response["body"] = decodeBody(_message);
		return response;
	}

	//-----------------------------------------------------------------------------------------------------------------
	Json UpnpParser::decodeHeaders(string & _message) {
		Json headers;
		string line;
		while ( (line = extractLine(_message)) != "") {
			string lowerCaseLine = line;
			std::transform(lowerCaseLine.begin(), lowerCaseLine.end(), lowerCaseLine.begin(), ::tolower);
			if (lowerCaseLine.find("cache-control") != string::npos) {
				headers["cache_control"] = cache_control(line);
			} else if (lowerCaseLine.find("date") != string::npos) {
				headers["date"] = date(line);
			} else if (lowerCaseLine.find("ext") != string::npos) {
				headers["ext"] = "";	// Required for backward compatibility with UPnP 1.0
			} else if (lowerCaseLine.find("location") != string::npos) {
				headers["location"] = location(line);
			} else if (lowerCaseLine.find("server") != string::npos) {
				headers["server"] = server(line);
			} else if (lowerCaseLine.find("st") != string::npos) {
				headers["st"] = st(line);
			} else if (lowerCaseLine.find("usn") != string::npos) {
				headers["usn"] = usn(line);
			} else {	// End of headers
				headers["headers"] = headers;
			}
		}	
		return headers;
	}

	//-----------------------------------------------------------------------------------------------------------------
	cjson::Json UpnpParser::decodeBody(std::string & _message) {
		int index = _message.find_first_not_of(char(-52)+char(-52)+char(-52)+char(-52));
		return _message.substr(0,index);
	}

	//-----------------------------------------------------------------------------------------------------------------
	std::string UpnpParser::extractLine(std::string & _message) {
		string line = _message.substr(0, _message.find_first_of("\r\n"));
		_message	= _message.substr(_message.find_first_of("\r\n")+2, _message.size());
		return line;
	}

	//-----------------------------------------------------------------------------------------------------------------
	Json UpnpParser::cache_control(const string &_line){
		Json cache("{}");
		// Cache-control has only one element: max-age = SMTG. 666 improve
		int max_age = atoi(_line.substr(_line.find("=")+1, _line.size()).c_str());
		cache["max-age"] = max_age;
		return cache;
	}

	//-----------------------------------------------------------------------------------------------------------------
	Json UpnpParser::location(const string &_line){
		return _line.substr(_line.find_first_of(":")+1, _line.size());
	}

	//-----------------------------------------------------------------------------------------------------------------
	Json UpnpParser::date(const string &_line){
		return _line.substr(_line.find_first_of(":")+1, _line.size());
	}

	//-----------------------------------------------------------------------------------------------------------------
	Json UpnpParser::server(const string &_line){
		return _line.substr(_line.find_first_of(":")+1, _line.size());
	}

	//-----------------------------------------------------------------------------------------------------------------
	Json UpnpParser::st(const string &_line){
		return _line.substr(_line.find_first_of(":")+1, _line.size());
	}

	//-----------------------------------------------------------------------------------------------------------------
	Json UpnpParser::usn(const string &_line){
		return _line.substr(_line.find_first_of(":")+1, _line.size());
	}

	//-----------------------------------------------------------------------------------------------------------------
	Json UpnpParser::uuid(const string &_line){
		return Json();	// 666 not implemented yet
	}

	//-----------------------------------------------------------------------------------------------------------------
	Json UpnpParser::searchPorts(const string &_line){
		return Json(); // 666 not implemented yet
	}

}	//	namespace dmc