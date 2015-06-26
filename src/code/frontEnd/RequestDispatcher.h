///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Dmc Node
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//

#ifndef _DMCNODE_CODE_FRONTEND_REQUEST_DISPATCHER_H_
#define _DMCNODE_CODE_FRONTEND_REQUEST_DISPATCHER_H_

#include <string>

// Forward declarations
namespace Poco { namespace Net { class HTTPRequest; } }

namespace dmc {
	class RequestProcessor;

	class RequestDispatcher {
	public:
		/// \brief Parse given request and return the proper request processor.
		/// \param _request Recived Requesto to be parsed
		/// \param _parsedUrl Output string that contains results of parsing the url of the request.
		RequestProcessor& dispatch(const Poco::Net::HTTPRequest &_request, std::string &_parsedUrl);

	};	// class RequestDispatcher
}	//	namespace dmc

#endif	//	_DMCNODE_CODE_FRONTEND_REQUEST_DISPATCHER_H_