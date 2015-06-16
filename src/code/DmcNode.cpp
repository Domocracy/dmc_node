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

		// Parse urls
		mServer->setResponder(cSubscriptionUrl, http::Response::response404);

		mServer->setResponder(cDeviceUrl, [this](http::Server* _s, unsigned _conId, const http::Request& _req) {
			_s->respond(_conId, this->execCmd(_req));
		});

	}

	//---------------------------------------------------------------------------------------------------------------------
	http::Response DmcNode::execCmd(http::Request _request){
		// 666 Currently not implemented

		return http::Response::response404();
	}
}