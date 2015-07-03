///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Dmc Node
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "LocalServer.h"
#include "Request.h"
#include "HttpTranslator.h"
#include "RequestDispatcher.h"

#include <cassert>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>

using namespace Poco::Net;

namespace dmc {

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
	bool LocalServer::respond(const Request& _request, const Response& _response) {
		// Get the adequate handler
		if(mHandlerPool.size() < _request.id())
			return false;
		RequestHandler* handler = mHandlerPool[_request.id()];
		if(handler->isFree())
			return false;
		// Translate response
		HTTPTranslator t;
		t.translate(_response, handler->response());
		// send
		handler->sendResponse();
		return true;
	}

	//-----------------------------------------------------------------------------------------------------------------
	HTTPRequestHandler * LocalServer::createRequestHandler(const HTTPServerRequest & request)
	{
		return new RequestHandler(*this, mDispatcher);
	}

	//-----------------------------------------------------------------------------------------------------------------
	LocalServer::RequestHandler::RequestHandler(LocalServer& _server, RequestDispatcher& _dispatcher)
		: mServer(_server)
		, mDispatcher(_dispatcher)
	{
	}

	//-----------------------------------------------------------------------------------------------------------------
	void LocalServer::RequestHandler::handleRequest(HTTPServerRequest& _request, HTTPServerResponse& _response) {
		// Translate incomming message
		HTTPTranslator t;
		Request request;
		// Dispatch the message
		mWaiting = true; // This flag must be set before dispatching, because some component may be able to respond even before the dispatcher returns
		mDispatcher.dispatch(request);
		// Wait for someone to answer
		while(mWaiting)
		{}
		return;
	}
}