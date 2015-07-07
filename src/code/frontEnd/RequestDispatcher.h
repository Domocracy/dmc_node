///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Dmc Node
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//

#ifndef _DMCNODE_CODE_FRONTEND_REQUESTDISPATCHER_H_
#define _DMCNODE_CODE_FRONTEND_REQUESTDISPATCHER_H_

#include <string>
#include <unordered_map>

// Forward declarations
namespace Poco { namespace Net { class HTTPRequest; } }

namespace dmc {
	class LocalServer;
	class Request;
	class RequestProcessor;

	class RequestDispatcher {
	public:
		/// Parse given request and send it to the best fitting request processor subscribed. Is assumed that requests 
		/// contains URLs not URIs. Requests which url does not start with / are assumed as with /, i.e., 
		/// "subscribe" == "/subscribe".
		/// \param _request Received Request to be dispatched
		/// \param _server where request processors should answer the requests
		/// \return \c false if no requestProcessor was found for the incomming request, \c true otherwise.
		bool dispatch(LocalServer& _server, const Request &_request) const;
		/// Register a request processor to listen for all requests to _localUrl
		/// For example, if A is suscribed to "/a" and B is suscribed to "/a/b", A will be called for "/a/foo"
		/// but B will be called for "/a/b/bar". For the same level of specialization, however, last suscriber
		/// has preferece. Indeed, any new suscriber erases old entries, which efectively means you can
		/// Unsuscribe to an url by calling suscribe with a nullptr as the request processor param
		void subscribe(RequestProcessor*, const std::string& _localUrl);

	private:
		std::unordered_map<std::string, RequestProcessor*>	mSubscriptions;
	};
}	//	namespace dmc

#endif	//	_DMCNODE_CODE_FRONTEND_REQUESTDISPATCHER_H_