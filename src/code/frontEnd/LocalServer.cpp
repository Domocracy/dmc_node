///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Dmc Node
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "LocalServer.h"
#include "Request.h"
#include "HttpTranslator.h"

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
		RequestHandler* handler = reuseHandler();
		if(handler)
			return handler;
		else
			return getNewHandler();
	}

	//-----------------------------------------------------------------------------------------------------------------
	LocalServer::RequestHandler* LocalServer::reuseHandler() {
		assert(mPoolTip <= mHandlerPool.size());
		if(mPoolTip == mHandlerPool.size()) // Exhausted pool
			return nullptr;
		unsigned slot = mPoolTip;
		do {
			assert(mHandlerPool[slot]); // No slot should be empty
			if (mHandlerPool[slot]->isFree())
			{
				// Set tip for next time
				mPoolTip = slot+1;
				mPoolTip %= mHandlerPool.size();
				return mHandlerPool[slot];
			}
		} while(mPoolTip != slot);
		// No slot available, pool exhausted
		mPoolTip = mHandlerPool.size();
		return nullptr;
	}
}