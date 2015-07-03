///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Dmc Node
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "LocalServer.h"
#include "HttpTranslator.h"

#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>

using namespace Poco::Net;

namespace dmc {

	//-----------------------------------------------------------------------------------------------------------------
	// Local classes for handles and factories
	//-----------------------------------------------------------------------------------------------------------------
	namespace {

		class DmcRequestHandler : public HTTPRequestHandler{
		public:
			void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
			{
				//
			}
		}

	}	// unnamed namespace

	//-----------------------------------------------------------------------------------------------------------------
	LocalServer::LocalServer(RequestDispatcher& _dispatcher, unsigned _port)
		:mDispatcher(_dispatcher)
	{
		// set-up a HTTPServer instance
		mHTTPServer = new HTTPServer(static_cast<HTTPRequestHandlerFactory*>(this), _port);
		// start the HTTPServer
		mHTTPServer->start();
	}

	//-----------------------------------------------------------------------------------------------------------------
	LocalServer::~LocalServer() {
		mHTTPServer->stop();
	}

	//-----------------------------------------------------------------------------------------------------------------
	void LocalServer::respond(const Request& _id, Response& _response) {
		// Get the adequate handler
		// Translate response
		HTTPServerResponse response;
		HTTPTranslator(_response, response);
		// send
	}

	//-----------------------------------------------------------------------------------------------------------------
	HTTPRequestHandler * LocalServer::createRequestHandler(const HTTPServerRequest & request)
	{
		RequestHandler* handler = reuseHandler();
		if(handler)
			return handler;
		else
			return getNewHandler();
	}

	//-----------------------------------------------------------------------------------------------------------------

}