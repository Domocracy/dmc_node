////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Project: DMC Server
// Date:	2015/Feb/11
// Author:	Carmelo J. Fdez-Agüera Tortosa
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _DMCSERVER_HOME_DEVICE_HUE_HUELIGHT_H_
#define _DMCSERVER_HOME_DEVICE_HUE_HUELIGHT_H_

#include <home/device/actuator.h>
#include "hueBridge.h"

namespace dmc { namespace hue {

	class Light : public Actuator {
	public:
		Light(unsigned _id, const std::string& _name, const std::string& _hueId);
		cjson::Json*	serialize	() const override;

		// Device interface
		cjson::Json runCommand		(const cjson::Json& _cmd) override;
		cjson::Json read			(const cjson::Json& _request) const override;

	private:
		std::string mHueId;
		
		static Bridge* sBridge;
	};

}}	// namespace dmc::hue

#endif // _DMCSERVER_HOME_DEVICE_HUE_HUELIGHT_H_