///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Dmc Node
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//

#include "HueDevice.h"
#include "backEnd\deviceDrivers\HueDriver.h"
namespace dmc {
	namespace hue {
		//------------------------------------------------------------------------------------------------------------------
		HueDevice::CmdResult HueDevice::process(const std::string & _command, std::ostream & _info) {
			assert(mJson.parse(_command.c_str()));
			std::string method = mJson["method"];
			HueDriver* hubDriver = HueDriver::get();

			if (method == "GET") {
				hubDriver->getData(mJson["url"], mJson["command"], _info);
				return HueDevice::CmdResult::Ok;
			}
			else if (method == "POST") {
				hubDriver->postData(mJson["url"], mJson["command"], _info);
				return HueDevice::CmdResult::Ok;
			}
			else if (method == "DELETE") {
				hubDriver->deleteData(mJson["url"], mJson["command"], _info);
				return HueDevice::CmdResult::Ok;
			}
			else if (method == "PUT") {
				hubDriver->putData(mJson["url"], mJson["command"], _info);
				return HueDevice::CmdResult::Ok;
			}
			return HueDevice::CmdResult::CommandError;
		};

	} //namespace hue
} //namespace dmc