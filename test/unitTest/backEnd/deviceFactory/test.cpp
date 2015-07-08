////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// DMC_NODE
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <backEnd/DeviceFactory.h>
#include <backEnd/DeviceCreator.h>
#include <backEnd/Device.h>

#include <cassert>

// Mocks
namespace dmc {
	class DummyDevice: public Device {
		CmdResult process(const std::string& command, std::ostream& info) {

		}
	};

	class DummyCreator : public DeviceCreator {
		Device* load(unsigned _id) {

		}
		Device* createDevice(unsigned _id, const cjson::Json &_data) {

		}
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



	DeviceFactory::end();
}

//---------------------------------------------------------------------------------------------------------------------