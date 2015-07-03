///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Dmc Node
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "LocalServer.h"
#include "Request.h"
#include "HttpTranslator.h"

#include <Poco/Net/HTTPServerResponse.h>
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

			HTTPServerResponse& respondTo();
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
	void LocalServer::respond(const Request& _request, Response& _response) {
		// Get the adequate handler
		RequestHandler* handler = mHandlerPool[_request.id()];
		// Translate response
		HTTPTranslator t;
		t.translate(_response, response);
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