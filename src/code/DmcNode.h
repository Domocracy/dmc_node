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
#include <frontEnd/RequestDispatcher.h>
#include <frontEnd/LocalServer.h>
#include <backEnd/DeviceManager.h>
#include <backEnd/requestProcessors/CommandDispatcher.h>

namespace dmc{

	/// Main process of Domocracy. Initialize application.
	class DmcNode{
	public:	// Public interface
		const int cHttpPort = 5028;

		/// Initialize main components of the application
		DmcNode	();

	private:	// Private methods
		

	private:	// Members
		RequestDispatcher	mRequestDispatcher;
		LocalServer			mServer;
		DeviceManager		mDevMgr;

		// Request processors.
		CommandDispatcher	mCmdDispatcher;
	};


}	//	namespace dmc



#endif	//	_DMC_NODE_DMC_NODE_H_