///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Dmc Node
//		Author: Pablo R.S.
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
#include "RequestDispatcher.h"
#include <regex>

namespace dmc {
	//-----------------------------------------------------------------------------------------------------------------
	RequestProcessor * RequestDispatcher::dispatch(const Poco::Net::HTTPRequest & _request, std::string & _parsedUrl) const {


		return nullptr;
	}
	
	//-----------------------------------------------------------------------------------------------------------------
	void RequestDispatcher::subscribe(RequestProcessor * _requestProcessor, const std::string & _localUrl) {
		mSubscriptions[_localUrl] = _requestProcessor;
	}
}
