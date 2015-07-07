///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Dmc Node
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
#include "CommandDispatcher.h"
#include <frontEnd/LocalServer.h>
#include <frontEnd/RequestDispatcher.h>
#include <frontEnd/Request.h>
#include <frontEnd/Response.h>

namespace dmc {
	//--------------------------------------------------------------------------------------------------------------------
	// Static data definition
	const std::string CommandDispatcher::cLabel = "/command";

	//--------------------------------------------------------------------------------------------------------------------
	CommandDispatcher::CommandDispatcher(DeviceManager &_devMgr, RequestDispatcher &_requestDispatcher): mDevMgr(_devMgr) {
		_requestDispatcher.subscribe(this, cLabel);
	}

	//--------------------------------------------------------------------------------------------------------------------
	void CommandDispatcher::process(const Request &_request, LocalServer &_server) {
		// Decode request.
		unsigned devId;
		if (parseUrl(_request.url(), devId))
		{
			//
		}
		else { // Parsing error
			_server.respond(_request, Response::failedToParseRequestBody());
		}
	}

	bool CommandDispatcher::parseUrl(const std::string & _url, unsigned & _id)
	{
		if (_url.substr(0, cLabel.size()+1) == (cLabel+'/')) { // Url starts with /command/
			std::string devLabel = _url.substr(cLabel.size()+1);
			size_t size = devLabel.size();
			if(devLabel[size-1] == '/')
				--size; // Skip trailing slash
			if(devLabel.substr(0,size).find('/') != std::string::npos)
				return false; // Slashes in the middle of the url
			_id = unsigned(atol(devLabel.c_str()));
			return true;
		}
		return false;
	}

	//--------------------------------------------------------------------------------------------------------------------
}	//	namespace dmc