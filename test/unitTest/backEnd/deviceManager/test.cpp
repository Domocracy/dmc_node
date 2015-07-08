////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// DMC_NODE
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <cassert>
#include <backEnd/DeviceManager.h>

namespace dmc {
	// --- Mock classes ---
	
}	//	namespace dmc

using namespace dmc;

int main(int, const char**) {
	// All tests
	DeviceManager mgr;
	Device* d0 = mgr.device(0); // This one exists
	assert(d0 == gD0);
	Device* d1 = mgr.device(1); // This one doesn't exist
	assert(d1 == nullptr);
	TestDevice dev2(2);
	mgr.add(&dev2);
	assert(&dev2  == mgr.device(2));
}
