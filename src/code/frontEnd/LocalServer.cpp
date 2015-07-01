///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Dmc Node
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "LocalServer.h"

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

		class DmcRequestHandlerFactory: public HTTPRequestHandlerFactory
		{
		public:
			DmcRequestHandlerFactory(LocalServer& _server)
				: mSever(_server) {}

			HTTPRequestHandler* createRequestHandler(const HTTPServerRequest& request)
			{
				return new DmcRequestHandler(mSever);
			}

		private:
			LocalServer& mSever;
		};

	}	// unnamed namespace

	//-----------------------------------------------------------------------------------------------------------------
	LocalServer::LocalServer(RequestDispatcher& _dispatcher, unsigned _port)
		:mDispatcher(_dispatcher)
	{

		// set-up a server socket
		mSrvSocket = new ServerSocket(_port);
		// set-up a HTTPServer instance
		mHTTPServer = new HTTPServer()
		HTTPServer srv(new TimeRequestHandlerFactory(format), svs, new HTTPServerParams);
		// start the HTTPServer
		srv.start();
		// wait for CTRL-C or kill
		waitForTerminationRequest();
		// Stop the HTTPServer
		srv.stop();
	}

}