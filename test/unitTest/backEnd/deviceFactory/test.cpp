////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// DMC_NODE
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <backEnd/DeviceFactory.h>
#include <backEnd/DeviceCreator.h>
#include <backEnd/Device.h>

#include <cassert>
#include <unordered_map>

// Mocks
namespace dmc {
	class DummyDevice: public Device {
	public:
		DummyDevice(unsigned _id) :mId(_id) {};
		unsigned id(){return mId;};

		CmdResult process(const std::string& command, std::ostream& info) {

		}

		unsigned mId;
	};

	class DummyCreator : public DeviceCreator {
	public:
		Device* load(unsigned _id) {

		}
		Device* createDevice(unsigned _id, const cjson::Json &_data) {

		}

		std::unordered_map<unsigned, Device*> mDevices;
	};
}

using namespace dmc;

void testSingletonCycle();
void testSubscription();

int main(int, const char**) {
	testSingletonCycle();
}

//---------------------------------------------------------------------------------------------------------------------
void testSingletonCycle() {
	DeviceFactory::init();
	DeviceFactory *factory = DeviceFactory::get();
	assert(factory != nullptr);

	DeviceFactory::end();
	DeviceFactory *factory = DeviceFactory::get();
	assert(factory == nullptr);
}

//---------------------------------------------------------------------------------------------------------------------
void testSubscription() {
	DeviceFactory::init();
	DeviceFactory *factory = DeviceFactory::get();
	
	const std::string cDummyTypeKey = "Dummy";
	factory->subscribe(cDummyTypeKey, new DummyCreator());

	Device* dev = factory->load(64);

	DeviceFactory::end();
}

//---------------------------------------------------------------------------------------------------------------------