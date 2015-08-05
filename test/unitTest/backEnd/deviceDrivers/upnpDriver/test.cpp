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

	driver->discover();
	std::list<Json> messages = driver->messages();
	std::cout << "Received " << messages.size() << std::endl;

	for (Json json : messages) {
		std::cout << "----------------" << std::endl;
		std::cout << json.serialize() << std::endl;
	}

	system("PAUSE");

	for (Json msg : messages) {
		string xml = driver->description(msg["headers"]["location"]);//msg["headers"]["location"]);
		std::cout << xml << std::endl;
	}
	system("PAUSE");
}
