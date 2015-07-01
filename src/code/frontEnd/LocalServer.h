///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Dmc Node
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _DMCNODE_CODE_FRONTEND_LOCALSERVER_H_
#define _DMCNODE_CODE_FRONTEND_LOCALSERVER_H_

namespace dmc {

	class RequestDispatcher;
	class Request;
	class Response;

	class LocalServer {
	public:
		/// \param dispatcher Local server will use this to retrieve the proper RequestProcessor for each incomming Request
		/// \param port the server will try to listen on
		LocalServer(RequestDispatcher& dispatcher, unsigned port);
		// Listening interface
		bool startListening	();
		bool stopListening	();

		// Ongoing connections
		/// Respond to a pending request
		///\ param request the request to which you intend to respond
		///\ param response the response you want to send
		///\ return \c true on success, \c false otherwise
		bool respond(const Request& request, const Response& response);

	private:
		RequestDispatcher& mDispatcher;
	};

}	//	namespace dmc

#endif	// _DMCNODE_CODE_FRONTEND_LOCALSERVER_H_
