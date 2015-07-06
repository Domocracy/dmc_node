///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Dmc Node
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _DMCNODE_CODE_FRONTEND_LOCALSERVER_H_
#define _DMCNODE_CODE_FRONTEND_LOCALSERVER_H_

#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/ServerSocket.h>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <map>

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
		virtual Poco::Net::HTTPRequestHandler * createRequestHandler(const Poco::Net::HTTPServerRequest & request) override;

		class RequestHandler : public Poco::Net::HTTPRequestHandler {
		public:
			RequestHandler(unsigned _reqId, LocalServer& _server, RequestDispatcher& _dispatcher);

			void lock	()		 { mFree = false;}
			void release()		 { mFree = true; }
			bool isFree	() const { return mFree; }

			unsigned id	() const { return mReqId; }

			void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
			Poco::Net::HTTPServerResponse& response() { return *mResponse; }
			void sendResponse();
			LocalServer&		mServer;
			RequestDispatcher&	mDispatcher;

		private:
			void send404(Poco::Net::HTTPServerResponse& response);

			Poco::Net::HTTPServerResponse* mResponse;
			bool			mFree = true;
			volatile bool	mWaiting = false;
			unsigned		mReqId;
		};

	private:
		RequestDispatcher&					mDispatcher;
		Poco::Net::HTTPServer*				mHTTPServer;
		std::map<unsigned,RequestHandler*>	mHandlers;
	};

}	//	namespace dmc

#endif	// _DMCNODE_CODE_FRONTEND_LOCALSERVER_H_
