///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Dmc Node
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//

#ifndef _DMCNODE_CODE_FRONTEND_REQUESTPROCESSORS_COMMANDDISPATCHER_H_
#define _DMCNODE_CODE_FRONTEND_REQUESTPROCESSORS_COMMANDDISPATCHER_H_

#include "../RequestProcessor.h"

namespace dmc {
	// Forward Declarations.
	class DeviceManager;
	class RequestDispatcher;
	class Request;

	class CommandDispatcher : public RequestProcessor {
	public:
		/// Construct command dispatcher with the given manager of devices and subscribe itself to the request dispatcher.
		/// \param _devMgr instance to a DeviceManager in order to retreive devices afterwards-
		/// \param _requestDispatcher instance to RequestDispatcher to subscribe itself to inconming requests.
		CommandDispatcher(DeviceManager &_devMgr, RequestDispatcher &_requestDispatcher);

		/// Process received dmc request and response properly to the server.
		/// \param _request incoming request to be processed
		/// \param _server pointer to server to respond to.
		void process(const Request &_request, LocalServer &_server) override;

	private:
		DeviceManager		&mDevMgr;
	};	//	class CommandDispatcher
}	//	namespace dmc

#endif	//	_DMCNODE_CODE_FRONTEND_REQUESTPROCESSORS_COMMANDDISPATCHER_H_