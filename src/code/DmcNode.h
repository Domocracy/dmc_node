////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Project: DMC Server
//		Date:	2015-06-16
//		Author:	Pablo R.S.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//



#ifndef _DMC_NODE_DMC_NODE_H_
#define _DMC_NODE_DMC_NODE_H_

#include <string>

#include <http/httpServer.h>

namespace dmc{
	const std::string cDeviceUrl = "dev/";
	const std::string cSubscriptionUrl = "subscription/";

	class DmcNode{
	public:	// Public interface
		DmcNode(int _argc, char** _argv);
		
		http::Response execCmd(http::Request);

	private:	// Private methods
		void processArguments(int _argc, char **_argv);
		void initServer();

	private:	// Members
		int mHttpPort = 80;
		dmc::http::Server *mServer;


	};


}	//	namespace dmc



#endif	//	_DMC_NODE_DMC_NODE_H_