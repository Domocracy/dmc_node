////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Dmc Node
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <cassert>
#include "DeviceManager.h"
#include "DeviceFactory.h"
#include "Device.h"

namespace dmc {
	//------------------------------------------------------------------------------------------------------------------
	Device* DeviceManager::device(unsigned _id) {
		auto i = mDevices.find(_id);
		if (i == mDevices.end()) // Not found
		{
			DeviceFactory* factory = DeviceFactory::get();
			assert(factory);
			Device* d = factory->load(_id);
			if(d)
				add(d);
			return d;
			// Load from device factory
		} else
			return i->second;
	}

	//------------------------------------------------------------------------------------------------------------------
	void DeviceManager::add(Device* _d) {
		assert(_d != nullptr);
		mDevices.insert(std::make_pair(_d->id(), _d));
	}

}	// namespace dmc