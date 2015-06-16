////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Project: DMC Server
// Date:	2015/Feb/11
// Author:	Carmelo J. Fdez-Agüera Tortosa
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "hueLight.h"
#include <iostream>
#include <string>
#include <core/comm/http/httpClient.h>

using namespace std;

namespace dmc { namespace hue {

	// Statid data definition
	Bridge* Light::sBridge = nullptr;

	//------------------------------------------------------------------------------------------------------------------
	Light::Light(unsigned _id, const std::string& _name, const std::string& _hueId)
		:Actuator(_id,_name)
		, mHueId(_hueId)
	{
		if(!sBridge)
			sBridge = Bridge::get();
	}

	//------------------------------------------------------------------------------------------------------------------
	cjson::Json * Light::serialize() const {
		cjson::Json * base = Actuator::serialize();
		(*base)["type"] = "HueLight";
		cjson::Json& data = (*base)["data"]["data"]["id"] = mHueId;
		return base;
	}

	//------------------------------------------------------------------------------------------------------------------
	cjson::Json Light::runCommand(const cjson::Json& _cmd) {
		cjson::Json r;
		if(!sBridge) {
			r["result"] = "fail";
			return r;
		}
		std::cout << "Hue light received a command\n";
		string commandUrl = string("/lights/") + mHueId + "/state";
		r["result"] = sBridge->putData(commandUrl, _cmd)?"ok":"fail";
		return r;
	}

	//------------------------------------------------------------------------------------------------------------------
	cjson::Json Light::read(const cjson::Json& _request) const {
		return cjson::Json(); // TODO
	}

}}	// namespace dmc::hue