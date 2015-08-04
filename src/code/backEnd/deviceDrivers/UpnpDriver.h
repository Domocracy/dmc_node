///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Dmc Node
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _DMCNODE_CODE_BACKEND_UPNPDRIVER_H_
#define _DMCNODE_CODE_BACKEND_UPNPDRIVER_H_

#include <vector>
#include <cjson/json.h>

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
		// Implementation of SSDP (Simple Service Discovery Protocol) for discovering devices on network.
		/// Look for all devices and services availables on network.
		std::vector<cjson::Json> discoverAll();

		/// Look for an especific device.
		/// \param _uuid: unique id of device.
		std::vector<cjson::Json> discover(std::string _uuid);

		/// Look for devices of an especific type and version
		/// \param _type: device type
		/// \param _version: highest version supported
		std::vector<cjson::Json> discover(std::string _type, std::string _version);

	private:	// Private methods
		cjson::Json parseResponse(std::string _response);

	private:
		static UpnpDriver * mInstance;

		const std::string	cMulticastAddr = "239.255.255.250";
		const unsigned		cMulticastPort = 1900;

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