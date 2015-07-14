////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Project: DMC Server
//		Date:	2015-06-16
//		Author:	Pablo R.S.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//

#include "DmcNode.h"
#include <backEnd/deviceDrivers/HueDriver.h>
#include <backEnd/DeviceFactory.h>

using namespace cjson;
using namespace dmc::hue;

namespace dmc{
	//---------------------------------------------------------------------------------------------------------------------
	DmcNode::DmcNode(): mServer(mRequestDispatcher, cHttpPort), mCmdDispatcher(mDevMgr, mRequestDispatcher){
		initDrivers();
	}

	//---------------------------------------------------------------------------------------------------------------------
	void DmcNode::initDrivers() {
		DeviceFactory::init();

		Json serverConfig;
		serverConfig["host"] = "10.100.3.211";	// 666 TODO: Look for hue bridge.
		HueDriver::init(serverConfig);
	}
}