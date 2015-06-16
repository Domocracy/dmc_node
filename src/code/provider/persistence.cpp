////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Project: DMC Server
// Date:	2015/Feb/19
// Author:	Carmelo J. Fdez-Agüera Tortosa
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "persistence.h"
#include <cassert>
#include <core/platfrom/file/file.h>

namespace dmc {

	//------------------------------------------------------------------------------------------------------------------
	Persistence* Persistence::sInstance = nullptr;

	//------------------------------------------------------------------------------------------------------------------
	void Persistence::init() {
		assert(!sInstance);
		sInstance = new Persistence();
	}

	//------------------------------------------------------------------------------------------------------------------
	void Persistence::saveData(const std::string& _dataId, const cjson::Json& _data) {
		File dataFile(_dataId + ".json");
		std::string data = _data.serialize();
		dataFile.setContent(data.c_str(), data.size());
		
		//666 TODO : _data.saveToFile(_dataId + ".json");
	}

	//------------------------------------------------------------------------------------------------------------------
	cjson::Json Persistence::getData(const std::string& _dataId) {
		std::string fileName = _dataId + ".json";
		File * dataFile = File::openExisting(fileName);
		if(!dataFile) {
			return cjson::Json();
		}
		dataFile->readAll();
		cjson::Json loadedData(dataFile->bufferAsText());
		delete dataFile;
		return loadedData;
	}

}	// namespace dmc