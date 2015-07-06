///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Dmc Node
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "Request.h"
#include "HttpTranslator.h"
#include <cassert>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/HTTPRequest.h>
#include <sstream>

using namespace Poco::Net;
using std::stringstream;

namespace dmc {

	//-----------------------------------------------------------------------------------------------------------------
	bool HTTPTranslator::translate(const Poco::Net::HTTPRequest& _http, Request& _dmc) {
		_dmc.url() = _http.getURI();
		if(_dmc.url().empty())
			return false;
		stringstream ss;
		_http.write(ss);
		return _dmc.body().parse(ss);
	}
}