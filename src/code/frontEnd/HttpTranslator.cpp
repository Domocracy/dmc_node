///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Dmc Node
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "Request.h"
#include "Response.h"
#include "HttpTranslator.h"
#include <cassert>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <sstream>
#include <string>

using namespace Poco::Net;
using std::stringstream;

namespace dmc {

	//-----------------------------------------------------------------------------------------------------------------
	bool HTTPTranslator::translate(Poco::Net::HTTPServerRequest& _http, Request& _dmc) {
		_dmc.url() = _http.getURI();
		if(_dmc.url().empty())
			return false;
		if(!_http.hasContentLength())
			return true; // Skip body
		if(_http.getContentLength() > 0)
			return _dmc.body().parse(_http.stream());
		else return true;
	}

	//-----------------------------------------------------------------------------------------------------------------
	bool HTTPTranslator::translate(const Response& _dmc, Poco::Net::HTTPServerResponse& _http) {
		_http.setStatusAndReason(HTTPResponse::HTTP_OK);
		_dmc.serialize(_http.send());
		 return true;
	}
}