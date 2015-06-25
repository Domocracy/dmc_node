///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Dmc Node
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//

#ifndef _DMCNODE_CODE_FRONTEND_REQUEST_DISPATCHER_H_
#define _DMCNODE_CODE_FRONTEND_REQUEST_DISPATCHER_H_

#include <Poco/Net/HTTPRequest.h>

namespace dmc {
	class RequestProcessor;

	class RequestDispatcher {
	public:
		RequestProcessor& dispatch(Poco::Net::HTTPRequest _request);

	};	// class RequestDispatcher
}	//	namespace dmc

#endif	//	_DMCNODE_CODE_FRONTEND_REQUEST_DISPATCHER_H_