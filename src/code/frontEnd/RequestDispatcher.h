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
		/// Parse given request and return the proper request processor.
		/// For every new request, the RequestProcessor that most specifically fits the url will be returned.
		/// For example, if A is suscribed to "/a" and B is suscribed to "/a/b", A will be retrieved for "/a/foo"
		/// but B will be retrieved for "/a/b/bar". For the same level of specialization, however, first suscribers
		/// have preferece.
		/// \param _request Received Request to be parsed
		/// \paramblock _parsedUrl
		/// Output string that contains results of parsing the url of the request.
		/// It corresponds to the whole url comming after the host, not including the first '/'
		/// \return The request processor associated to the Request or nullptr if no good candidate was found
		RequestProcessor*	dispatch(const Poco::Net::HTTPRequest &_request, std::string &_parsedUrl) const;
		/// Register a request processor to be retrieved for all requests to _localUrl
		void				subscribe(RequestProcessor*, const std::string& _localUrl);

	};
}	//	namespace dmc

#endif	//	_DMCNODE_CODE_FRONTEND_REQUEST_DISPATCHER_H_