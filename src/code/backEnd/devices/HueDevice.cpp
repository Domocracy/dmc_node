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
	
			std::string method = mCurrentCmd["method"];
			Json& commandData = mCurrentCmd["command"];
			HueDriver* hubDriver = HueDriver::get();

			bool res;
			if (method == "GET") {
				Json dst;
				res = hubDriver->getData(mUrl, dst, _info);
			} else if (method == "POST") {
				res = hubDriver->postData(mUrl, mCurrentCmd["command"], _info);
			} else if (method == "DELETE") {
				res = hubDriver->deleteData(mUrl, mCurrentCmd["command"], _info);
			} else if (method == "PUT") {
				res = hubDriver->putData(mUrl, mCurrentCmd["command"], _info);
			}
			return res? CmdResult::Ok : CmdResult::ExecutionError;
		};

		//------------------------------------------------------------------------------------------------------------------
		bool HueDevice::parseCommand(const std::string& _command) {
			if(!mCurrentCmd.parse(_command.c_str()))
				return false;
			if(!mCurrentCmd.contains("method"))
				return false;
			if(!mCurrentCmd["method"].isString())
				return false;
			if(!mCurrentCmd.contains("command"))
				return false;
			return true;
		}

	} //namespace hue
} //namespace dmc