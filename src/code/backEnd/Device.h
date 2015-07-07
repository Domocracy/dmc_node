////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Dmc Node
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _DMC_NODE_BACKEND_DEVICE_H_
#define _DMC_NODE_BACKEND_DEVICE_H_

#include <string>
#include <ostream>

namespace dmc {
	
	/// Common interface for device classes. Each devices represents either a physical or logical device that can
	/// be accessed by a dmc_node. Physical devices may be appliances, lights, switches, media players,sensors, etc.
	/// Logical devices are abstract constructions that act like a device (e.g. scenes, triggers, ...).
	class Device {
	public:
		enum class CmdResult {
			Ok, ///< Command properly executed
			CommandError, ///< The received command is ill-formed and could not be processed by this device.
			ExecutionError, ///< The command is well-formed but the command could not be successfully executed.
		};

		/// Runs a command.
		/// \param command The command that will be executed by the device.
		/// \param info The device will save all extra information resulting from the execution of the command into
		/// this string. In case of error, the error message will be stored here. If the command requested some
		/// information and there was no error, the information will be saved here.
		virtual CmdResult process(const std::string& command, std::ostream& info) = 0;
	};

}	// namespace dmc

#endif // _DMC_NODE_BACKEND_DEVICE_H_
