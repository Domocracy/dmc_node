///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Dmc Node
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "CommandDispatcher.h"
#include <backEnd/Device.h>
#include <backEnd/DeviceManager.h>
#include <frontEnd/LocalServer.h>
#include <frontEnd/RequestDispatcher.h>
#include <frontEnd/Request.h>
#include <frontEnd/Response.h>
#include <sstream>

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
			Device* dev = mDevMgr.device(devId);
			if (!dev)
			{
				_server.respond(_request, Response::deviceNotFound(devId));
				return;
			}
			std::ostringstream info;
			auto result = dev->process(_request.body(), info);
			switch (result)
			{
			case dmc::Device::CmdResult::Ok:
				_server.respond(_request, Response::ok());
				return;
			case dmc::Device::CmdResult::CommandError:
				_server.respond(_request, Response::failedToParseRequestBody(info.str()));
				return;
			case dmc::Device::CmdResult::ExecutionError:
				_server.respond(_request, Response::commandExecutionError(info.str()));
				return;
			default:
				assert(false); // Unexpected case
				return;
			}
		}
		else { // Parsing error
			_server.respond(_request, Response::invalidRequestUrl());
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