///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Dmc Node
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _DMCNODE_CODE_FRONTEND_LOCALSERVER_H_
#define _DMCNODE_CODE_FRONTEND_LOCALSERVER_H_

#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/ServerSocket.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>

namespace dmc {

	class RequestDispatcher;
	class Request;
	class Response;

	class LocalServer : private Poco::Net::HTTPRequestHandlerFactory {
	public:
		/// \param dispatcher Local server will use this to retrieve the proper RequestProcessor for each incomming Request
		/// \param port the server will try to listen on
		LocalServer(RequestDispatcher& dispatcher, unsigned port);
		~LocalServer();

		// Ongoing connections
		/// Respond to a pending request. The method will fail if you try
		/// to respond to an inexisting request or to one that has already been responded.
		///\ param request the request to which you intend to respond
		///\ param response the response you want to send
		///\ return \c true on success, \c false otherwise.
		bool respond(const Request& request, const Response& response);

	private:
		// Inherited via HTTPRequestHandlerFactory
		virtual HTTPRequestHandler * createRequestHandler(const HTTPServerRequest & request) override;

		class RequestHandler : public HTTPRequestHandler {
		public:
			void lock	()		 { mFree = false;}
			void release()		 { mFree = true; }
			bool isFree	() const { return mFree; }

			void setId	(unsigned _id) { mId = _id; }
			unsigned id	() const { return mId; }

			void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response);
			HTTPServerResponse& response();
			void sendResponse();

		private:
			bool		mFree = true;
			unsigned	mId;
		};

		RequestHandler* reuseHandler();
		RequestHandler* getNewHandler();

	private:
		RequestDispatcher&				mDispatcher;
		Poco::Net::HTTPServer*			mHTTPServer;
		// The pool must be a vector of handler pointers so that realocation doesn't kill the actual handles
		// being used
		std::vector<RequestHandler*>	mHandlerPool;
		unsigned mHandlerTip = 0;
	};

}	//	namespace dmc

#endif	// _DMCNODE_CODE_FRONTEND_LOCALSERVER_H_
