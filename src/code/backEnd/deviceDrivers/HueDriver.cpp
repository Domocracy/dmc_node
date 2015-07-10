///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Dmc Node
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "HueDriver.h"
#include <cjson/json.h>
#include <istream>

using cjson::Json;

namespace dmc { namespace hue {
	//------------------------------------------------------------------------------------------------------------------
	// Static data definition
	HueDriver* HueDriver::sHueDriver = nullptr;

	//------------------------------------------------------------------------------------------------------------------
	bool HueDriver::init(std::istream& _configStream) {
		assert(!sHueDriver);
		Json config;
		if(!config.parse(_configStream))
			return false;
		sHueDriver = new HueDriver(config);
		return sHueDriver != nullptr;
	}

}}	// namespace dmc::hue