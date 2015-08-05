///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Dmc Node
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _DMCNODE_CODE_BACKEND_UPNPDRIVER_H_
#define _DMCNODE_CODE_BACKEND_UPNPDRIVER_H_

#include <cjson/json.h>
#include <list>
#include <Poco/Net/MulticastSocket.h>
#include <vector>

namespace dmc {
	class UpnpDriver {
	public:
		/// Get instance of UpnpDriver.
		static UpnpDriver* get();

		/// Initialize Upnp driver.
		static void init();

		/// Deinitialize upnp driver.
		static void end();

	public:
		// Addressing interface (Opcional)
		// 666 TODO

		// Implementation of SSDP (Simple Service Discovery Protocol) for discovering devices on network.
		/// Look for all devices and services availables on network.
		void discoverAll();

		/// Look for an especific device.
		/// \param _uuid: unique id of device.
		void discover(std::string _uuid);

		/// Look for devices or services of an especific type and version
		/// \param _type: device type
		/// \param _version: highest version supported
		/// \param _isDevice: true if looking for devices of type _type, false if looking for services.
		void discover(std::string _type, std::string _version, bool _isDevice);

		/// Return current messages
		std::list<cjson::Json> messages(){ return mMessages; };

		// Control interface
		// 666 TODO

		// Description interface
		// 666 TODO

		// Eventing interface
		// 666 TODO

	private:	// Private methods
		UpnpDriver();
		~UpnpDriver();

		cjson::Json parseResponse(std::string _response);

	private:
		static UpnpDriver			*mInstance;
		
		Poco::Net::SocketAddress	mMulticastGroup;

		std::list<cjson::Json>		mMessages;		

	};	//	 class UpnpDriver
}	//	namespace dmc

#endif	//	_DMCNODE_CODE_BACKEND_UPNPDRIVER_H_