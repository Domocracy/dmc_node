///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Dmc Node
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
#include "RequestDispatcher.h"

#include <Poco/Net/HTTPRequest.h>
#include <regex>

namespace dmc {
	//-----------------------------------------------------------------------------------------------------------------
	RequestProcessor * RequestDispatcher::dispatch(const Poco::Net::HTTPRequest & _request, std::string & _parsedUrl) const {
		std::string url = _request.getURI();

		if(extractHost(url)) {
			std::string key = url[0] == '/' ? url : (std::string("/") + url); // Add slash at the begining.

			while (!key.empty()) {
				// Try key
				auto iter = mSubscriptions.find(key);
				if (iter != mSubscriptions.end()) {
					return (*iter).second;
				}
				// Not found, keep decomposing the url
				unsigned lastSlash = key.find_last_of('/');
				key = key.substr(0, lastSlash);
			}

			// Check if exist default subscription "/"
			auto iter = mSubscriptions.find("/");
			if (iter != mSubscriptions.end()) {
				return (*iter).second;
			}
		}

		return nullptr;
	}
	
	//-----------------------------------------------------------------------------------------------------------------
	void RequestDispatcher::subscribe(RequestProcessor * _requestProcessor, const std::string & _localUrl) {
		mSubscriptions[_localUrl] = _requestProcessor;
	}

	//-----------------------------------------------------------------------------------------------------------------
	bool RequestDispatcher::extractHost(std::string &_url) const{
		std::regex hostRegex(cValidHostExpression);
		std::smatch matches; 

		if (std::regex_search(_url, matches, hostRegex)) {
			std::string host = matches[0];
			_url = _url.substr(host.size() - 1, _url.size());
			return true;	// Has valid host.
		}
		return false;	// No host or invalid host.
	}

}
