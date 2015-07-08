///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Dmc Node
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//

#include <cassert>

#include "DeviceFactory.h"
#include "DeviceCreator.h"

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
	void DeviceFactory::subscribe(std::string _key, DeviceCreator *_devCreator){
		mCreators[_key] = _devCreator;
	}

	//-----------------------------------------------------------------------------------------------------------------
	Device* DeviceFactory::load(const std::string &_type, unsigned _id){
		auto iter = mCreators.find(_type);
		if (iter != mCreators.end())
			return iter->second->load(_id);	// Found device creator
		else
			return nullptr;	// Not found device creator
	}

	//-----------------------------------------------------------------------------------------------------------------
	Device* DeviceFactory::createDevice(const std::string &_type, unsigned _id, const cjson::Json &_data){
		auto iter = mCreators.find(_type);
		if (iter != mCreators.end())
			return iter->second->createDevice(_id, _data);	// Found device creator
		else
			return nullptr;	// Not found device creator
	}

	//-----------------------------------------------------------------------------------------------------------------
	DeviceFactory::DeviceFactory() {

	};

}	//	namespace dmc
