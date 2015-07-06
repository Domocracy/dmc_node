///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Dmc Node
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//

#ifndef _DMCNODE_CODE_FRONTEND_REQUESTPROCESSOR_H_
#define _DMCNODE_CODE_FRONTEND_REQUESTPROCESSOR_H_

namespace dmc {
	// Forward Declarations
	class Request;
	class LocalServer;

	/// Base interface of backend request processors.
	class RequestProcessor {
	public:
		/// Process received dmc request and response properlly to the server.
		virtual void process(const Request &_request, LocalServer &_localServer) = 0;


	};	//	 class RequestProcessor
}	//	namespace RequestProcessor

#endif	//	_DMCNODE_CODE_FRONTEND_REQUESTPROCESSOR_H_
