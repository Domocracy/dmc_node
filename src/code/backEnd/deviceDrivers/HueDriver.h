///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Dmc Node
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//

#ifndef _DMCNODE_CODE_FRONTEND_HUEDRIVER_H_
#define _DMCNODE_CODE_FRONTEND_HUEDRIVER_H_

#include <ostream>
#include "cjson/json.h"

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

			static HueDriver*	get();
			static void			init();

			State state() const	{ return mState; }

			bool putData		(const std::string& _url, const cjson::Json& _data, std::ostream& _errorInfo);
			bool getData		(const std::string& _url, cjson::Json& _data, std::ostream& _errorInfo);
			bool postData		(const std::string& _url, const cjson::Json& _data, std::ostream& _errorInfo);
			bool deleteData		(const std::string& _url, const cjson::Json& _data, std::ostream& _errorInfo);

			bool			autoConnect		();
			cjson::Json		scanBridges		();
			bool			registerBridge	(const cjson::Json& _bridgeToConnect);
		private:

			State mState;
			HueDriver(const cjson::Json&);

			static HueDriver* sHueDriver;


		};
	
	} //namespace hue
} //namespace dmc


#endif // _DMC_NODE_BACKEND_HUEDRIVER_H_

