////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Project: DMC Server
// Date:	2015/Feb/19
// Author:	Carmelo J. Fdez-Ag�era Tortosa
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _DMCSERVER_SERVICE_USER_DEVICE_H_
#define _DMCSERVER_SERVICE_USER_DEVICE_H_

#include <home/device/actuator.h>
#include <cjson/json.h>
#include <unordered_map>

namespace dmc {

	class Json;

	class Scene final : public Actuator {
	public:
		Scene	(unsigned _id, const cjson::Json& _data);
		~Scene	() = default;

		cjson::Json		runCommand	(const cjson::Json& _cmd) override;
		cjson::Json*	serialize	() const override;

	private:
		std::unordered_map<unsigned, cjson::Json>	mChildren;
		cjson::Json							mPanels;
	};
}

#endif // _DMCSERVER_SERVICE_USER_DEVICE_H_