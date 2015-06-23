////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Project: DMC Server
// Date:	2015/Feb/19
// Author:	Carmelo J. Fdez-Agüera Tortosa
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "scene.h"
#include <provider/deviceMgr.h>

namespace dmc {

	//------------------------------------------------------------------------------------------------------------------
	Scene::Scene(unsigned _id, const cjson::Json& _data)
		:Actuator(_id, std::string(_data["name"]))
	{
		cjson::Json childrenData = _data["children"];
		for (size_t i = 0; i < childrenData.size(); ++i) {
			unsigned childId = int(childrenData(i)["id"]);	///	777 Explicit cast
			cjson::Json childCmd = childrenData(i)["cmd"];
			mChildren.insert(std::make_pair(childId, childCmd));
		}
		mPanels = _data["panels"];
	}

	//------------------------------------------------------------------------------------------------------------------
	cjson::Json Scene::runCommand(const cjson::Json&) {
		DeviceMgr* mgr = DeviceMgr::get();
		bool ok = true;
		for(auto i : mChildren)
		{
			Actuator* act = dynamic_cast<Actuator*>(mgr->device(i.first));
			if(!act){
				ok = false;
				continue;
			}
			ok &= (std::string(act->runCommand(i.second)["result"]) == "ok");
		}
		return ok ? cjson::Json(R"("result":"ok")") : cjson::Json(R"("result":"fail")");
	}

	//------------------------------------------------------------------------------------------------------------------
	cjson::Json* Scene::serialize() const {
		cjson::Json& base = *Actuator::serialize();
		base["type"] = "Scene";
		cjson::Json children("[]"); // Serialize children commands
		for (auto child : mChildren) {
			cjson::Json& childData = *new cjson::Json("{}");
			childData["id"] = child.first;
			childData["cmd"] = child.second;
			children.push_back(&childData);
		}

		base["children"]	= children;
		base["panels"]		= mPanels;

		return &base;
	}
}
