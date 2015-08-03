///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Dmc Node
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "UpnpDriver.h"
#include <cassert>
#include <Poco/Net/DatagramSocket.h>

using namespace std;
using namespace Poco::Net;

namespace dmc {
	UpnpDriver * UpnpDriver::mInstance = nullptr;

	//-----------------------------------------------------------------------------------------------------------------
	// Static methods
	UpnpDriver * UpnpDriver::get() {
		assert(mInstance);
		return mInstance;
	}

	//-----------------------------------------------------------------------------------------------------------------
	void UpnpDriver::init() {
		assert(!mInstance);
		mInstance = new UpnpDriver();
	}

	//-----------------------------------------------------------------------------------------------------------------
	void UpnpDriver::end() {
		assert(mInstance);
		delete mInstance;

	}

	//-----------------------------------------------------------------------------------------------------------------
	// Non-static methods
	vector<UpnpEntity> UpnpDriver::discoverAll() {
		SocketAddress multicastAddr(cMulticastAddr, cMulticastPort);
		DatagramSocket sdSocket;

		std::string searchAll = "M-SEARCH * HTTP/1.1\r\n" + 
								string("HOST: ") + cMulticastAddr + ":" + to_string(cMulticastPort) + "\r\n" +
								"MAN: \"ssdp:discover\"\r\n" +
								"MX: 3\r\n" +
								"ST: ssdp:all\r\n\r\n";
		
		sdSocket.connect(multicastAddr);
		sdSocket.sendBytes(searchAll.c_str(), searchAll.length());

		char responseBuffer[1024];
		int len = sdSocket.receiveBytes(responseBuffer, 1024);

		if (len == -1) {
			std::cout << "Error receiving M-SEARCH response" << std::endl;
		}
		else {

		}

		return vector<UpnpEntity>();
	}

	//-----------------------------------------------------------------------------------------------------------------
	vector<UpnpEntity> UpnpDriver::discover(std::string _uuid) {
		return vector<UpnpEntity>();
	}

	//-----------------------------------------------------------------------------------------------------------------
	vector<UpnpEntity> UpnpDriver::discover(std::string _type, std::string _version) {
		return vector<UpnpEntity>();
	}

}	//	namespace dmc