///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Dmc Node
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//

#ifndef _DMC_NODE_BACKEND_DEVICECREATOR_H_
#define _DMC_NODE_BACKEND_DEVICECREATOR_H_

// Forward Declarations
namespace cjson{ class Json; }

namespace dmc {
	class Device;

	class DeviceCreator {
	public:
		/// Load existing device from persistent memory.
		/// \param _id identification number to search the device
		/// \return \c null pointer if device does not exist, \c pointer to device if exist.
		virtual Device* load(unsigned _id) = 0;

		/// Create a new device that have never been registered on the system.
		/// \param _id identification number to be assigned to the device
		/// \param _data necessary data to build/create the device
		/// \return \c null pointer if device could not be created, \c pointer to new created device.
		virtual Device* createDevice(unsigned _id, const cjson::Json &_data) = 0;
		
	};	//	 class DeviceCreator
}	//	namespace dmc

#endif	//	_DMC_NODE_BACKEND_DEVICECREATOR_H_