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
				url = url.substr(key.size(), url.size());
				iter->second->process(_request, _server);
			}
			// Not found, keep decomposing the url
			unsigned lastSlash = key.find_last_of('/');
			key = key.substr(0, lastSlash);
		}

		// Check if exist default subscription "/"
		auto iter = mSubscriptions.find("/");
		if (iter != mSubscriptions.end()) {
			iter->second->process(_request, _server);
		}
	}
	
	//-----------------------------------------------------------------------------------------------------------------
	void RequestDispatcher::subscribe(RequestProcessor * _requestProcessor, const std::string & _localUrl) {
		mSubscriptions[_localUrl] = _requestProcessor;
	}
}
