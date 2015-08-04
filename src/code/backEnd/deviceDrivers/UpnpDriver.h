///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Dmc Node
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _DMCNODE_CODE_BACKEND_UPNPDRIVER_H_
#define _DMCNODE_CODE_BACKEND_UPNPDRIVER_H_

#include <cjson/json.h>
#include <list>
#include <mutex>
#include <Poco/Net/MulticastSocket.h>
#include <thread>
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

		/// Look for devices of an especific type and version
		/// \param _type: device type
		/// \param _version: highest version supported
		void discover(std::string _type, std::string _version);

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

		std::list<cjson::Json>	mMessages;		

	};	//	 class UpnpDriver

	class UpnpParser {
	public:
		enum eMessageType {NOTIFY, M_SEARCH, RESPONSE, ERR_TYPE};

		cjson::Json parse(std::string _message);

	private:
		eMessageType decodeType(const std::string &_line);

		cjson::Json decodeMSearch	(std::string &_message);
		cjson::Json decodeNotify	(std::string &_message);
		cjson::Json decodeResponse	(std::string &_message);

		cjson::Json decodeHeaders	(std::string &_message);
		cjson::Json decodeBody		(std::string &_message);

		std::string extractLine		(std::string &_message);

		cjson::Json cache_control	(const std::string &_line);
		cjson::Json location		(const std::string &_line);
		cjson::Json date			(const std::string &_line);
		cjson::Json server			(const std::string &_line);
		cjson::Json st				(const std::string &_line);
		cjson::Json usn				(const std::string &_line);
		cjson::Json uuid			(const std::string &_line);
		cjson::Json searchPorts		(const std::string &_line);
	};
}	//	namespace dmc

#endif	//	_DMCNODE_CODE_BACKEND_UPNPDRIVER_H_