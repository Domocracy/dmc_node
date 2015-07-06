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
	class RequestProcessor;
	class LocalServer;

	class RequestDispatcher {
	public:
		/// Parse given request and return the proper request processor.
		/// For every new request, the RequestProcessor that most specifically fits the url will be returned.
		/// For example, if A is suscribed to "/a" and B is suscribed to "/a/b", A will be retrieved for "/a/foo"
		/// but B will be retrieved for "/a/b/bar". For the same level of specialization, however, last suscriber
		/// has preferece.
		/// \param _request Received Request to be parsed
		void dispatch(const Poco::Net::HTTPRequest &_request, const LocalServer *_localServer) const;
		/// Register a request processor to be retrieved for all requests to _localUrl
		void				subscribe(RequestProcessor*, const std::string& _localUrl);

	private:
		const std::string cValidHostExpression = "(http|https):\/\/[a-zA-Z0-9\-\.]+\/";
		bool extractHost(std::string &_url) const;

	private:
		std::unordered_map<std::string, RequestProcessor*>	mSubscriptions;
	};
}	//	namespace dmc

#endif	//	_DMCNODE_CODE_FRONTEND_REQUESTDISPATCHER_H_