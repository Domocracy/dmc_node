////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// DMC_NODE
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <cjson/json.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPClientSession.h>
#include <backEnd/deviceDrivers/HueDriver.h>

using namespace Poco::Net;
using namespace cjson;
using namespace std;
using namespace dmc::hue;

Json config;
HueDriver* gDriver = nullptr;

bool isHueVulnerable() {
	Json bridgeData;
	gDriver->getData("/config/", bridgeData, cout);
	Json whitelist = bridgeData["whitelist"];
	for (auto& i = whitelist.begin(); i != whitelist.end(); ++i) {
		if(i.key() == "newdeveloper")
			continue;
		if (i.key().size() < 32) // Old hash names
		{
			cout << "Weak user token\n";
			i->serialize(cout);
		}
	}

	// Bridge sw version
	cout << "Bridge version 01016441 with known vulnerabilities\nSoftware update available\n";

	return true;
}

int main(int, const char**) {
	config.parse(fstream("config.json"));
	HueDriver::init(config["bridge"]);
	gDriver = HueDriver::get();

	// Detect vulnerabilities: -Vulnerable software version & vulnerable users.
	if(isHueVulnerable()) {
		// Delete attacker Id.
		Json bridgeData;
		gDriver->getData("/config/", bridgeData, cout);
		Json whitelist = bridgeData["whitelist"];
		cout << " --- Clean up users white list ---\n";
		for (auto& i = whitelist.begin(); i != whitelist.end(); ++i) {
			if(i.key() == "newdeveloper")
				continue;
			if (i.key().size() < 32) // Old hash names
			{
				cout << "Remove vulnerable user token " << i.key() << "\n";
				gDriver->deleteData(string("/config/whitelist/")+i.key(), Json(), cout);
			}
		}
		cout << " --- Update software version ... \n"
			<< "Success\nNew software version: 01024156\n";
		// Update bridge software.
	}
}