///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Dmc Node
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "SddpParser.h"
#include <cjson/json.h>
#include <string>

using namespace cjson;
using namespace std;

namespace dmc {
	Json SddpParser::parse(string _message) {
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

		return Json();
	}

	//-----------------------------------------------------------------------------------------------------------------
	SddpParser::eMessageType SddpParser::decodeType(const std::string & _line) {
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
	cjson::Json SddpParser::decodeMSearch(std::string & _message) {
		Json search;
		search["type"] = "M-SEARCH";
		search["headers"] = decodeHeaders(_message);
		search["body"] = decodeBody(_message);
		return search;
	}

	//-----------------------------------------------------------------------------------------------------------------
	Json SddpParser::decodeNotify(std::string & _message) {
		Json notification;
		notification["type"] = "NOTIFY";
		notification["headers"] = decodeHeaders(_message);
		notification["body"] = decodeBody(_message);
		return notification;
	}

	//-----------------------------------------------------------------------------------------------------------------
	Json SddpParser::decodeResponse(std::string & _message) {
		Json response;
		response["type"] = "RESPONSE";
		response["headers"] = decodeHeaders(_message);
		response["body"] = decodeBody(_message);
		return response;
	}

	//-----------------------------------------------------------------------------------------------------------------
	Json SddpParser::decodeHeaders(string & _message) {
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
	cjson::Json SddpParser::decodeBody(std::string & _message) {
		int index = _message.find_first_not_of("ออออ");
		return _message.substr(0,index);
	}

	//-----------------------------------------------------------------------------------------------------------------
	std::string SddpParser::extractLine(std::string & _message) {
		string line = _message.substr(0, _message.find_first_of("\r\n"));
		_message	= _message.substr(_message.find_first_of("\r\n")+2, _message.size());
		return line;
	}

	//-----------------------------------------------------------------------------------------------------------------
	Json SddpParser::cache_control(const string &_line){
		Json cache("{}");
		// Cache-control has only one element: max-age = SMTG. 666 improve
		int max_age = atoi(_line.substr(_line.find("=")+1, _line.size()).c_str());
		cache["max-age"] = max_age;
		return cache;
	}

	//-----------------------------------------------------------------------------------------------------------------
	Json SddpParser::location(const string &_line){
		return _line.substr(_line.find_first_of(":")+1, _line.size());
	}

	//-----------------------------------------------------------------------------------------------------------------
	Json SddpParser::date(const string &_line){
		return _line.substr(_line.find_first_of(":")+1, _line.size());
	}

	//-----------------------------------------------------------------------------------------------------------------
	Json SddpParser::server(const string &_line){
		return _line.substr(_line.find_first_of(":")+1, _line.size());
	}

	//-----------------------------------------------------------------------------------------------------------------
	Json SddpParser::st(const string &_line){
		return _line.substr(_line.find_first_of(":")+1, _line.size());
	}

	//-----------------------------------------------------------------------------------------------------------------
	Json SddpParser::usn(const string &_line){
		return _line.substr(_line.find_first_of(":")+1, _line.size());
	}

	//-----------------------------------------------------------------------------------------------------------------
	Json SddpParser::uuid(const string &_line){
		return Json();	// 666 not implemented yet
	}

	//-----------------------------------------------------------------------------------------------------------------
	Json SddpParser::searchPorts(const string &_line){
		return Json(); // 666 not implemented yet
	}

}	//	namespace dmc