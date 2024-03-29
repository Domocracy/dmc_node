////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// DMC_NODE
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <cassert>
#include <backEnd/DeviceManager.h>
#include <backEnd/DeviceFactory.h>
#include <backEnd/Device.h>

namespace dmc {
	// --- Mock classes ---
	class TestDevice : public Device {
	public:
		TestDevice(unsigned _id) : Device(_id) {}

		CmdResult process(const std::string& command, std::ostream& info) {
			return CmdResult::CommandError; // Whatever
		}
	};

	TestDevice gD0(0);

	// Mock Device factory
	DeviceFactory* gFactory;
	DeviceFactory::DeviceFactory() {}
	void DeviceFactory::init() { gFactory = new DeviceFactory; }
	DeviceFactory* DeviceFactory::get() { return gFactory; }
	Device* DeviceFactory::load(unsigned _id) {
		if(_id == 0)
			return & gD0;
		else
			return nullptr;
	}

}	//	namespace dmc

using namespace dmc;

int main(int, const char**) {
	// All tests
	DeviceFactory::init();
	DeviceManager mgr;
	Device* d0 = mgr.device(0); // This one exists
	assert(d0 == &gD0);
	Device* d1 = mgr.device(1); // This one doesn't exist
	assert(d1 == nullptr);
	TestDevice dev2(2);
	mgr.add(&dev2);
	assert(&dev2  == mgr.device(2));
}
