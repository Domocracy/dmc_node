///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Dmc Node
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//

#include <cassert>
#include <cjson/json.h>
#include <fstream>

#include "DeviceFactory.h"
#include <iostream>

namespace dmc {
	// Static data initialization
	DeviceFactory* DeviceFactory::mInstance = nullptr;

	//-----------------------------------------------------------------------------------------------------------------
	void DeviceFactory::init(){
		assert(mInstance == nullptr);
		mInstance =  new DeviceFactory();
	}

	//-----------------------------------------------------------------------------------------------------------------
	DeviceFactory* DeviceFactory::get(){
		return mInstance;
	}
	
	//-----------------------------------------------------------------------------------------------------------------
	void DeviceFactory::end() {
		delete mInstance;
		mInstance = nullptr;
	}

	//-----------------------------------------------------------------------------------------------------------------
	void DeviceFactory::subscribe(std::string _key, DeviceCreator _devCreator){
		mCreators[_key] = _devCreator;
	}

	//-----------------------------------------------------------------------------------------------------------------
	Device* DeviceFactory::load(unsigned _id) {
		// Load dev file, 
		std::ifstream devFile("device_" + std::to_string(_id));
		if(!devFile.is_open())	// Check if device file exists.
			return nullptr;
		// Parse to Json,
		cjson::Json devData;
		devData.parse(devFile);
		devFile.close();
		// Extract device type,
		std::string devType = devData["type"];
		// Find device creator,
		auto iter = mCreators.find(devType);
		if (iter != mCreators.end()) 
			return iter->second(_id, devData);	// Found device creator	
		else
			return nullptr;	// Not found device creator
	}

	//-----------------------------------------------------------------------------------------------------------------
	Device* DeviceFactory::createDevice(const std::string &_type, unsigned _id, const cjson::Json &_data){
		auto iter = mCreators.find(_type);
		if (iter != mCreators.end())
			return iter->second(_id, _data);	// Found device creator
		else
			return nullptr;	// Not found device creator
	}

	//-----------------------------------------------------------------------------------------------------------------
	DeviceFactory::DeviceFactory() {

	};

}	//	namespace dmc
