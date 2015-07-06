///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Dmc Node
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _DMCNODE_CODE_FRONTEND_REQUEST_H_
#define _DMCNODE_CODE_FRONTEND_REQUEST_H_

#include <cjson/json.h>

namespace dmc {
	class Request {
	public:
		unsigned	id	() const { return mId;	}
		std::string url	() const { return mUrl;	}
		cjson::Json body() const { return mJson;}

	private:
		unsigned	mId;
		std::string mUrl;
		cjson::Json mJson;

	};

}	//	namespace dmc

#endif	// _DMCNODE_CODE_FRONTEND_HTTPTRANSLATOR_H_
