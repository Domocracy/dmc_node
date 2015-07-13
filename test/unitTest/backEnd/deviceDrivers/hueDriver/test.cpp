////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// DMC_NODE
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <backEnd/deviceDrivers/HueDriver.h>
#include <cjson/json.h>
#include <iostream>
#include <sstream>

namespace dmc {
}

using namespace cjson;
using namespace dmc;
using namespace dmc::hue;
using namespace std;

int main(int, const char**) {
	Json serverConfig;
	serverConfig["host"] = "10.100.3.211";
	HueDriver::init(serverConfig);
	HueDriver* driver = HueDriver::get();
	Json response;
	if (driver->getData("/api/1234", response, cout))
	{
		cout << "\nResponse is ok\n";
	}
	else {
		cout << "\nError response\n";
	}
}
