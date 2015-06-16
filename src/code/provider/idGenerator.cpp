////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Project: DMC Server
// Date:	2015/Mar/03
// Author:	Carmelo J. Fdez-Agüera Tortosa
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "idGenerator.h"
#include <cassert>
#include <ctime>
#include <cstdlib>
#include "persistence.h"

namespace dmc {

	//------------------------------------------------------------------------------------------------------------------
	// Static data definition
	//------------------------------------------------------------------------------------------------------------------
	IdGenerator* IdGenerator::sInstance = nullptr;

	//------------------------------------------------------------------------------------------------------------------
	void IdGenerator::init() {
		assert(!sInstance);
		sInstance = new IdGenerator();
	}

	//------------------------------------------------------------------------------------------------------------------
	IdGenerator* IdGenerator::get() {
		return sInstance;
	}

	//------------------------------------------------------------------------------------------------------------------
	void IdGenerator::end() {
		assert(sInstance);
		delete sInstance;
		sInstance = nullptr;
	}

	//------------------------------------------------------------------------------------------------------------------
	uint32_t IdGenerator::newId() {
		for(;;) {
			uint32_t id = (uint32_t)rand();
			if(mGeneratedIds.find(id) == mGeneratedIds.end()) { // New key, not found
				mGeneratedIds.insert(id);
				save();
				return id;
			}
		}
	}

	//------------------------------------------------------------------------------------------------------------------
	IdGenerator::IdGenerator() {
		// Set random seed
		srand((uint32_t)time(0));
		// Load previous data
		cjson::Json storedIds = Persistence::get()->getData("randomIds");
		if(storedIds.isNull())
			return;
		for (unsigned i = 0; i < storedIds.size(); i++){
			mGeneratedIds.insert(storedIds(i));
		}
	}

	//------------------------------------------------------------------------------------------------------------------
	IdGenerator::~IdGenerator() {
		
	}

	//------------------------------------------------------------------------------------------------------------------
	void IdGenerator::save() {
		// Save generated ids
		cjson::Json ids("[]");
		for(auto id : mGeneratedIds) {
			cjson::Json *idJson = new cjson::Json();
			ids.push_back(id);
			//idJson->setInt(id);
			//ids.asList().push_back(idJson);
		}
		Persistence::get()->saveData("randomIds", ids);
	}

}	// namespace dmc
