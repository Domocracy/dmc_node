cmake_minimum_required (VERSION 2.6)

# Front End tests
add_subdirectory(requestProcessors)
add_subdirectory(deviceFactory)
add_subdirectory(deviceManager)
add_subdirectory(deviceDrivers/hueDriver)
add_subdirectory(deviceDrivers/upnpDriver)
add_subdirectory(hueDevice)
