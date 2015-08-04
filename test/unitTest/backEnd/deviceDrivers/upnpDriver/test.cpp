////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// DMC_NODE
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <backEnd/deviceDrivers/UpnpDriver.h>

using namespace dmc;
using namespace std;
using namespace cjson;

int main(int, const char**) {
	UpnpDriver::init();
	UpnpDriver* driver = UpnpDriver::get();

	vector<Json> upnpEntities = driver->discoverAll();

}