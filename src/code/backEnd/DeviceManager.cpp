////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Dmc Node
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "DeviceManager.h"
#include "DeviceFactory.h"
#include "Device.h"

namespace dmc {
	//------------------------------------------------------------------------------------------------------------------
	Device* DeviceManager::device(unsigned _id) {
		auto i = mDevices.find(_id);
		if (i == mDevices.end()) // Not found
		{
			// Load from device factory
		} else
			return i->second;
	}

	//------------------------------------------------------------------------------------------------------------------
	void DeviceManager::add(Device* _d) {
		mDevices.insert(std::make_pair(_d->id(), _d));
	}

}	// namespace dmc