////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// DMC_NODE
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <backEnd/DeviceFactory.h>
#include <backEnd/DeviceCreator.h>
#include <backEnd/Device.h>

#include <cassert>
#include <cjson/json.h>
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

	class DummyCreator : public DeviceCreator {
	public:
		Device* load(unsigned _id) {
			auto iter = mDevices.find(_id);
			if(iter != mDevices.end())
				return iter->second;
			else
				return nullptr;
		}
		Device* createDevice(unsigned _id, const cjson::Json &_data) {
			auto iter = mDevices.find(_id);
			if(iter != mDevices.end())
				return iter->second;
			else
				return nullptr;
		}

		std::unordered_map<unsigned, Device*> mDevices;
	};
}

using namespace dmc;

void testSingletonCycle();
void testSubscription();

int main(int, const char**) {
	testSingletonCycle();
	testSubscription();
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
void testSubscription() {
	DeviceFactory::init();
	DeviceFactory *factory = DeviceFactory::get();
	
	const std::string cDummyTypeKey = "Dummy";
	DummyCreator dummyCreator;
	dummyCreator.mDevices[64] = new DummyDevice(64);	// Added to internal list in order to simulate loading.

	// Test existing DeviceCreator
	factory->subscribe(cDummyTypeKey, &dummyCreator);
	assert(nullptr != factory->load(cDummyTypeKey, 64));
	assert(nullptr == factory->load(cDummyTypeKey, 32));

	assert(nullptr != factory->createDevice(cDummyTypeKey,64, ""));
	assert(nullptr == factory->createDevice(cDummyTypeKey,32, ""));

	// Test non-subscribed DeviceCreator
	assert(nullptr == factory->load("noExist", 64));
	assert(nullptr == factory->createDevice("noExist",64, ""));

	DeviceFactory::end();
}

//---------------------------------------------------------------------------------------------------------------------