///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Dmc Node
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//

#ifndef _DMCNODE_CODE_FRONTEND_REQUESTPROCESSORS_COMMANDDISPATCHER_H_
#define _DMCNODE_CODE_FRONTEND_REQUESTPROCESSORS_COMMANDDISPATCHER_H_

#include "../RequestProcessor.h"
#include <string>

namespace dmc {
	// Forward Declarations.
	class DeviceManager;
	class RequestDispatcher;
	class Request;

	class CommandDispatcher : public RequestProcessor {
	public:
		/// Construct command dispatcher with the given manager of devices and subscribe itself to the request dispatcher.
		/// This object will suscribe to the /command url.
		/// \param _devMgr instance to a DeviceManager in order to retreive devices afterwards-
		/// \param _requestDispatcher instance to RequestDispatcher to subscribe itself to inconming requests.
		CommandDispatcher(DeviceManager &_devMgr, RequestDispatcher &_requestDispatcher);

		/// Process received dmc request. This method alwais responds to the server's request.
		/// \param _request incoming request to be processed
		/// \param _server server to which the respond must be sent.
		void process(const Request &_request, LocalServer &_server) override;

	private:
		/// Parses the url and stores the decoded device id into _id.
		/// \return \c false if there was an error decoding the url, \true otherwise.
		bool parseUrl(const std::string& _url, unsigned& _id);

	private:
		DeviceManager		&mDevMgr;
		static const std::string cLabel;
	};	//	class CommandDispatcher
}	//	namespace dmc

#endif	//	_DMCNODE_CODE_FRONTEND_REQUESTPROCESSORS_COMMANDDISPATCHER_H_