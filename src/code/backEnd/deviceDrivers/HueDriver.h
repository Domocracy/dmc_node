///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Dmc Node
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _DMCNODE_CODE_FRONTEND_HUEDRIVER_H_
#define _DMCNODE_CODE_FRONTEND_HUEDRIVER_H_

#include <ostream>
#include "cjson/json.h"

#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/SocketAddress.h>

namespace dmc{ 
	namespace hue {
	
		class HueDriver{
		public:
			enum class State{
				connected,
				connecting,
				disconnected
			};

			//Singleton

			static HueDriver*	get() { return sHueDriver; }
			/// Creates the singleton instance of HueDriver using the configuration read from the _config stream
			/// \param _config A stream containing a configuration for the driver. It must be in Json format.
			/// \return \c false if any issue prevented correct initialization of the driver. \c true if everything
			/// worked fine.
			static bool			init(std::istream& _config);
			static bool			init(cjson::Json& _config);

			State state() const	{ return mState; }

			/// Puts a get request to the current bridge
			/// It also processes the result in case of error.
			/// \param _url RESTfull API resource url.
			/// \param _response This Json will be filled with the bridge's response.
			/// \param _errorInfo In case of error, information about the error will be put to this stream
			/// \return \c true if everything went fine, \c false if an error was returned by the server or some
			/// other error happened
			bool getData		(const std::string& _url, cjson::Json& _response, std::ostream& _errorInfo);
			bool putData		(const std::string& _url, const cjson::Json& _request, std::ostream& _errorInfo);
			bool postData		(const std::string& _url, const cjson::Json& _request, std::ostream& _errorInfo);
			bool deleteData		(const std::string& _url, const cjson::Json& _request, std::ostream& _errorInfo);

			bool			autoConnect		();
			cjson::Json		scanBridges		();
			bool			registerBridge	(const cjson::Json& _bridgeToConnect);
		private:
			static void registerDeviceCreators();

			void receiveResp(Poco::Net::HTTPClientSession& _session, std::stringstream& _dst);
			bool isSuccess(const cjson::Json& _response, std::ostream& _errorInfo);

			State mState;
			HueDriver(const cjson::Json&);
			Poco::Net::SocketAddress mBridgeIp;

			static HueDriver* sHueDriver;
		};
	
	} //namespace hue
} //namespace dmc


#endif // _DMC_NODE_BACKEND_HUEDRIVER_H_

