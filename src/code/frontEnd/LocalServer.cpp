///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Dmc Node
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "LocalServer.h"
#include "Request.h"
#include "HttpTranslator.h"
#include "RequestDispatcher.h"

#include <cassert>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPServerRequest.h>
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
		auto it = mHandlers.find(_request.id());
		if(it == mHandlers.end())
			return false;
		RequestHandler* handler = it->second;
		// Translate response
		HTTPTranslator t;
		if (!t.translate(_response, handler->response()))
		{
			handler->response().setStatusAndReason(HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
			handler->response().send();
		}
		// send
		handler->sendResponse();
		return true;
	}

	//-----------------------------------------------------------------------------------------------------------------
	HTTPRequestHandler * LocalServer::createRequestHandler(const HTTPServerRequest & request)
	{
		unsigned id = 0;
		while(mHandlers.find(id) != mHandlers.end())
			++id;
		RequestHandler* h = new RequestHandler(id, *this, mDispatcher);
		mHandlers.insert(std::make_pair(id, h));
		return h;
	}

	//-----------------------------------------------------------------------------------------------------------------
	LocalServer::RequestHandler::RequestHandler(unsigned _reqId, LocalServer& _server, RequestDispatcher& _dispatcher)
		: mServer(_server)
		, mDispatcher(_dispatcher)
		, mReqId(_reqId)
	{
	}

	//-----------------------------------------------------------------------------------------------------------------
	void LocalServer::RequestHandler::handleRequest(HTTPServerRequest& _request, HTTPServerResponse& _response) {
		mResponse = &_response; // Answer to this response
		// Translate incomming message
		HTTPTranslator t;
		Request request(mReqId);
		if (!t.translate(_request, request)) {
			// Unable to translate, bad request
			_response.setStatusAndReason(HTTPResponse::HTTP_BAD_REQUEST);
			_response.send();
			return;
		}
		// Dispatch the message
		mWaiting = true; // This flag must be set before dispatching, because some component may be able to respond even before the dispatcher returns
		if (!mDispatcher.dispatch(mServer, request))
		{
			// On dispatch error, return 404
			send404(_response);
			return;
		}
		// Wait for someone to answer
		while(mWaiting)
		{}
		return;
	}

	//-----------------------------------------------------------------------------------------------------------------
	void LocalServer::RequestHandler::send404(HTTPServerResponse& _response) {
		_response.setStatusAndReason(HTTPResponse::HTTP_NOT_FOUND);
		_response.send();
	}

	//-----------------------------------------------------------------------------------------------------------------
	void LocalServer::RequestHandler::sendResponse() {
		mWaiting = false;
	}
}