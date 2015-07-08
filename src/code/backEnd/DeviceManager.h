////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Dmc Node
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _DMC_NODE_BACKEND_DEVICEMANAGER_H_
#define _DMC_NODE_BACKEND_DEVICEMANAGER_H_

namespace dmc {

	class Device;

	class DeviceManager {
	public:
		/// Retrieve a device with the given id. If the device isn't already loaded, it asks DeviceFactory to load it.
		/// \param id Id of the requested device.
		/// \return A pointer to the requested device, or \nullptr if the device was not found.
		Device*	device	(unsigned _id);
		/// Register a new device into the device manager.
		void	add		(Device* _dev);
	};

}	// namespace dmc

#endif // _DMC_NODE_BACKEND_DEVICEMANAGER_H_