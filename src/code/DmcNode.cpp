////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Project: DMC Server
//		Date:	2015-06-16
//		Author:	Pablo R.S.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//

#include "DmcNode.h"

namespace dmc{
	//---------------------------------------------------------------------------------------------------------------------
	DmcNode::DmcNode(int _argc, char** _argv){
		processArguments(_argc, _argv);

		initServer();

	}

	//---------------------------------------------------------------------------------------------------------------------
	void DmcNode::processArguments(int _argc, char** _argv){
		for (int i = 0; i < _argc; ++i) {
			std::string argument(_argv[i]);
			if (argument.substr(0, 9) == "-httpPort=") {
				mHttpPort = atoi(argument.substr(9).c_str());
			}
		}
	}

	//---------------------------------------------------------------------------------------------------------------------
	void DmcNode::initServer(){
		mServer = new http::Server(mHttpPort);

		// New subscription url.
		mServer->setResponder(cSubscriptionUrl, [this](http::Server* _s, unsigned _conId, const http::Request& _req) {
			_s->respond(_conId, this->newSubscription(_req));
		});

		// Request info url.
		mServer->setResponder(cRequestInfoUrl, [this](http::Server* _s, unsigned _conId, const http::Request& _req) {
			_s->respond(_conId, this->infoRequest(_req));
		});

		// Device related url.
		mServer->setResponder(cDeviceUrl, [this](http::Server* _s, unsigned _conId, const http::Request& _req) {
			_s->respond(_conId, this->execCmd(_req));
		});

	}

	//---------------------------------------------------------------------------------------------------------------------
	http::Response DmcNode::infoRequest(http::Request _request){
		// 666 Currently not implemented
		return http::Response::response404();
		// Decode request
		// Find information
		// Returninformation

	}
	
	//---------------------------------------------------------------------------------------------------------------------
	http::Response DmcNode::newSubscription(http::Request _request){
		// 666 Currently not implemented
		return http::Response::response404();
		// Decode request
		// Create a subscriptor
		// Save subscriptor into list
		// Return OK
	}

	//---------------------------------------------------------------------------------------------------------------------
	http::Response DmcNode::execCmd(http::Request _request){
		// 666 Currently not implemented
		return http::Response::response404();
		/// Extract command
		/// Check user permisions
		/// Execute command and response OK.
		
	}


}