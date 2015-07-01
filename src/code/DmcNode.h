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
	const std::string cDeviceUrl		= "dev/";
	const std::string cSubscriptionUrl	= "subscription/";
	const std::string cRequestInfoUrl	= "request/";

	class DmcNode{
	public:	// Public interface
		DmcNode	(int _argc, char** _argv);

	private:	// Private methods
		void processArguments	(int _argc, char **_argv);
		void initServer			();

		http::Response infoRequest		(http::Request);
		http::Response newSubscription	(http::Request);
		http::Response execCmd			(http::Request);

	private:	// Members
		int mHttpPort = 80;
		dmc::http::Server *mServer;

		friend http::Server::UrlHandler;
	};


}	//	namespace dmc



#endif	//	_DMC_NODE_DMC_NODE_H_