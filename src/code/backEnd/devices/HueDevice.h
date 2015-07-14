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
			/// Hue Device constructor.
			/// \param _id Device id (dmc id).
			/// \param _data necesary data to instance HueDevice (666 not defined yet)
			HueDevice(unsigned _id, const cjson::Json &_data);
			/// Process command received.
			/// \param _command Json as string that contains "method", "command" and "urlAp" (Appendix to be added to url).
			///			For example: {"method":"PUT","command":{"on":true},"urlAp":"/state"}.
			/// \param _info additional information
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