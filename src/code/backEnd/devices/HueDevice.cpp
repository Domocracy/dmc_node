///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Dmc Node
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//

#include "HueDevice.h"
#include "backEnd/deviceDrivers/HueDriver.h"
#include <cassert>

using namespace cjson;

namespace dmc {
	namespace hue {
		//------------------------------------------------------------------------------------------------------------------
		HueDevice::CmdResult HueDevice::process(const std::string & _command, std::ostream & _info) {
			// Validate command
			if (!parseCommand(_command))
				return HueDevice::CmdResult::CommandError;
	
			std::string method = mJson["method"];
			Json& commandData = mJson["command"];
			HueDriver* hubDriver = HueDriver::get();

			bool res;
			if (method == "GET") {
				Json dst;
				res = hubDriver->getData(mJson["url"], dst, _info);
			} else if (method == "POST") {
				res = hubDriver->postData(mJson["url"], mJson["command"], _info);
			} else if (method == "DELETE") {
				res = hubDriver->deleteData(mJson["url"], mJson["command"], _info);
			} else if (method == "PUT") {
				res = hubDriver->putData(mJson["url"], mJson["command"], _info);
			}
			return res? CmdResult::Ok : CmdResult::ExecutionError;
		};

		//------------------------------------------------------------------------------------------------------------------
		bool HueDevice::parseCommand(const std::string& _command) {
			if(!mJson.parse(_command.c_str()))
				return false;
			if(!mJson.contains("method"))
				return false;
			if(!mJson["method"].isString())
				return false;
			if(!mJson.contains("command"))
				return false;
			return true;
		}

	} //namespace hue
} //namespace dmc