////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// DMC_NODE
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <backEnd/DeviceFactory.h>
#include <backEnd/Device.h>

#include <cassert>
#include <cjson/json.h>
#include <fstream>
#include <unordered_map>

// Mocks
namespace dmc {
	class DummyDevice: public Device {
	public:
		DummyDevice(unsigned _id) :Device(_id) {};
		CmdResult process(const std::string& command, std::ostream& info) {
			return CmdResult::Ok;
		}
	};

	class DummyCreator {
	public:
		Device* operator()(unsigned _id, const cjson::Json &_data) {
			if(_data.isObject() && _data.contains("state"))
				return new DummyDevice(_id);
			else
				return nullptr;
		}
		
	};
}

using namespace dmc;

void testSingletonCycle();
void testLoad();
void testCreation();

void createDeviceFile(unsigned _id, std::string _type);

int main(int, const char**) {
	testSingletonCycle();

	testLoad();

	testCreation();
}

//---------------------------------------------------------------------------------------------------------------------
void testSingletonCycle() {
	DeviceFactory::init();
	DeviceFactory *factory = DeviceFactory::get();
	assert(factory != nullptr);

	DeviceFactory::end();
	factory = DeviceFactory::get();
	assert(factory == nullptr);
}

//---------------------------------------------------------------------------------------------------------------------
void testLoad() {
	// --- Init Factory ---
	DeviceFactory::init();
	DeviceFactory *factory = DeviceFactory::get();
	
	// --- Dummy DeviceCreator for testing ---
	const std::string cDummyType = "dummy";
	DummyCreator creator;
	factory->subscribe(cDummyType, creator);

	// --- Create file to be load ---
	createDeviceFile(64, cDummyType);

	// --- Test ---
	assert(factory->load(64));	// Existing device.
	assert(!factory->load(32));	// Non Existing Device.

	DeviceFactory::end();
}

//---------------------------------------------------------------------------------------------------------------------
void testCreation() {
	DeviceFactory::init();
	DeviceFactory *factory = DeviceFactory::get();
	// --- Dummy DeviceCreator for testing ---
	const std::string cDummyType = "dummy";
	DummyCreator creator;
	factory->subscribe(cDummyType, creator);

	cjson::Json validData;
	validData.parse(R"({"state":true})");
	assert(factory->createDevice("dummy", 64, validData));		// Valid creation.
	assert(!factory->createDevice("dummy", 64, ""));			// Invalid Data.
	assert(!factory->createDevice("NoExist", 64, validData));	// Unexisting device creator.

	DeviceFactory::end();
}

//---------------------------------------------------------------------------------------------------------------------
void createDeviceFile(unsigned _id, std::string _type) {
	std::ofstream file("device_"+std::to_string(_id));
	file << R"({"type":")" << _type << R"(", "data":{"state":true}})";
	file.close();
}