///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Dmc Node
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _DMCNODE_CODE_BACKEND_UPNPDRIVER_H_
#define _DMCNODE_CODE_BACKEND_UPNPDRIVER_H_

#include <vector>

namespace dmc {
	class UpnpEntity {	// Service or Device

	};

	class UpnpDriver {
	public:
		/// Get instance of UpnpDriver.
		static UpnpDriver* get();

		/// Initialize Upnp driver.
		static void init();

		/// Deinitialize upnp driver.
		static void end();

	public:
		// Implementation of SSDP (Simple Service Discovery Protocol) for discovering devices on network.
		/// Look for all devices and services availables on network.
		std::vector<> discoverAll();

		/// Look for an especific device.
		/// \param _uuid: unique id of device.
		std::vector<> discover(std::string _uuid);

		/// Look for devices of an especific type and version
		/// \param _type: device type
		/// \param _version: highest version supported
		std::vector<> discover(std::string _type, std::string _version);

	private:
		static UpnpDriver * mInstance;

		const std::string	cMulticastAddr = "239.255.255.250";
		const unsigned		cMulticastPort = 1900;

	};	//	 class UpnpDriver
}	//	namespace dmc

#endif	//	_DMCNODE_CODE_BACKEND_UPNPDRIVER_H_