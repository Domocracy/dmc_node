////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Project: DMC Server
// Date:	2015/Feb/11
// Author:	Carmelo J. Fdez-Agüera Tortosa
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _DMCSERVER_HOME_DEVICE_H_
#define _DMCSERVER_HOME_DEVICE_H_

#include <string>
#include <cjson/json.h>

namespace dmc {

	class Device {
	public:
		virtual ~Device() = default;

		unsigned				id			() const { return mId; }
		const std::string		name		() const { return mName; }
		virtual cjson::Json		read		(const cjson::Json& _request) const { return cjson::Json(); }
		virtual cjson::Json*	serialize	() const;

	protected:
		Device(unsigned _id, const std::string& _name) : mId(_id), mName(_name) {}

	private:
		unsigned	mId;
		std::string	mName;
	};

	//------------------------------------------------------------------------------------------------------------------
	inline cjson::Json* Device::serialize() const {
		cjson::Json * devData = new cjson::Json();
		(*devData)["id"] = mId;
		(*devData)["name"] = mName;
		return devData;
	}

}	// namespace dmc

#endif // _DMCSERVER_HOME_DEVICE_H_