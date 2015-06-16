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
	const int cHttpPort = 80;

	class DmcNode{
	public:
		DmcNode(int _argc, char** _argv);
		
		bool update();

	private:
		dmc::http::Server mServer;

	};


}	//	namespace dmc



#endif	//	_DMC_NODE_DMC_NODE_H_