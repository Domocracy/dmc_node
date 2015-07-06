///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Dmc Node
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//


#include "CommandDispatcher.h"

namespace dmc {
	//--------------------------------------------------------------------------------------------------------------------
	CommandDispatcher::CommandDispatcher(DeviceManager &_devMgr, RequestDispatcher &_requestDispatcher): mDevMgr(_devMgr) {

	}

	//--------------------------------------------------------------------------------------------------------------------
	void CommandDispatcher::process(const Request &_request, LocalServer &_server) {
		// Decode request.
		// Get device id.
		// Get Device.
		// Exec command.
		// Create OK response.
		// Respond to local server.
	}

	//--------------------------------------------------------------------------------------------------------------------
}	//	namespace dmc