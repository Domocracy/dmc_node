///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Dmc Node
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//

#ifndef _DMCNODE_CODE_FRONTEND_DEVICEFACTORY_H_
#define _DMCNODE_CODE_FRONTEND_DEVICEFACTORY_H_

#include <string>
#include <functional>
#include <unordered_map>

// Forward declarations
namespace cjson { class Json; };

namespace dmc {
	class Device;

	class DeviceFactory {
	public:
		/// Interface of device creators/loaders
		typedef std::function<Device* (unsigned _id, const cjson::Json &_data)> DeviceCreator;

		/// Static initialization of DeviceFactory. 
		static void init();
		/// Get instance of DeviceFactory.
		static DeviceFactory* get();
		/// Static deinitialization of DeviceFactory.
		static void end();

		/// Add new device creator to the factory.
		/// \param _devCreator pointer to a DeviceCreator.
		void subscribe(std::string _key, DeviceCreator _devCreator);

		/// Load existing device from persistent memory.
		/// \param _id identification number to search the device
		/// \return \c null pointer if device does not exist, \c pointer to device if exist.
		Device* load(unsigned _id);

		/// Create a new device that have never been registered on the system.
		/// \param _type string containing information about the type of device to be created.
		/// \param _id identification number to be assigned to the device
		/// \param _data necessary data to build/create the device
		/// \return \c null pointer if device could not be created, \c pointer to new created device.
		Device* createDevice(const std::string &_type, unsigned _id, const cjson::Json &_data);

	private:
		DeviceFactory();

		static DeviceFactory *mInstance;

		std::unordered_map<std::string, DeviceCreator> mCreators;
	};	//	class DeviceFactory
}	//	namespace dmc

#endif	//	_DMCNODE_CODE_FRONTEND_DEVICEFACTORY_H_