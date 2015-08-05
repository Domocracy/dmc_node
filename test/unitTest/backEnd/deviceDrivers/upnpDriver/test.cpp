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

	driver->discoverAll();
	std::list<Json> messages = driver->messages();
	std::cout << "Received " << messages.size() << std::endl;

	for (Json json : messages) {
		std::cout << "----------------" << std::endl;
		std::cout << json.serialize() << std::endl;
	}

	system("PAUSE");
}
