///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Dmc Node
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//

#ifndef _DMCNODE_CODE_FRONTEND_HUEDEVICE_H_
#define _DMCNODE_CODE_FRONTEND_HUEDEVICE_H_

#include "backEnd/Device.h"
#include "cjson/json.h"

namespace dmc{
	namespace hue{
			
		class HueDevice : public Device {
		public:
			HueDevice(unsigned _id, const cjson::Json &_data);
			CmdResult process(const std::string& command, std::ostream& info);
		private:
			bool parseCommand(const std::string& command);
		private:
			cjson::Json mCurrentCmd;
			std::string mUrl;
		};
	
	} //namespace hue
} //namespace dmc
#endif // _DMC_NODE_BACKEND_HUEDEVICE_H_