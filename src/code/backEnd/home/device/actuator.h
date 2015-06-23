////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Project: DMC Server
// Date:	2015/Feb/11
// Author:	Carmelo J. Fdez-Ag�era Tortosa
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _DMCSERVER_HOME_DEVICE_ACTUATOR_H_
#define _DMCSERVER_HOME_DEVICE_ACTUATOR_H_

#include "../device.h"

namespace cjson {	class Json; }

namespace dmc {

	class Actuator : public Device {
	public:
		Actuator(unsigned _id, const std::string& _name) : Device(_id, _name) {}
		virtual ~Actuator() = default;
		virtual cjson::Json runCommand(const cjson::Json& _cmd) = 0;
	};
}

#endif // _DMCSERVER_HOME_DEVICE_ACTUATOR_H_