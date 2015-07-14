///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Dmc Node
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
#include "Request.h"
#include "RequestDispatcher.h"
#include "backEnd/RequestProcessor.h"

#include <Poco/Net/HTTPRequest.h>
#include <regex>

namespace dmc {
	//-----------------------------------------------------------------------------------------------------------------
	bool RequestDispatcher::dispatch(LocalServer& _server, const Request &_request) const {
		std::string url = _request.url();

		std::string key = url[0] == '/' ? url : (std::string("/") + url); // Add slash at the begining.

		while (!key.empty()) {
			// Try key
			auto iter = mSubscriptions.find(key);
			if (iter != mSubscriptions.end()) {
				iter->second->process(_request, _server);
				return true;
			}
			// Not found, keep decomposing the url
			unsigned lastSlash = key.find_last_of('/');
			key = key.substr(0, lastSlash);
		}

		// Check if exist default subscription "/"
		auto iter = mSubscriptions.find("/");
		if (iter != mSubscriptions.end()) {
			iter->second->process(_request, _server);
			return true;
		}
		return false;
	}
	
	//-----------------------------------------------------------------------------------------------------------------
	void RequestDispatcher::subscribe(RequestProcessor * _requestProcessor, const std::string & _localUrl) {
		std::string url;
		size_t urlSize = _localUrl.size();
		if(urlSize > 1 && _localUrl[urlSize-1] == '/')
			url = _localUrl.substr(0, urlSize-1); // Skip trailing slash
		else
			url = _localUrl;
		mSubscriptions[url] = _requestProcessor;
	}
}
