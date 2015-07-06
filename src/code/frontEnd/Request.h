///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Dmc Node
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _DMCNODE_CODE_FRONTEND_REQUEST_H_
#define _DMCNODE_CODE_FRONTEND_REQUEST_H_

#include <cjson/json.h>

namespace dmc {
	class Request {
	public:
		// Accessors
		unsigned			id	() const { return mId;	}
		const std::string&	url	() const { return mUrl;	}
		const cjson::Json&	body() const { return mJson;}
		std::string&		url	() { return mUrl;	}
		cjson::Json&		body() { return mJson;	}

	private:
		unsigned	mId;
		std::string mUrl;
		cjson::Json mJson;

	};

}	//	namespace dmc

#endif	// _DMCNODE_CODE_FRONTEND_HTTPTRANSLATOR_H_
