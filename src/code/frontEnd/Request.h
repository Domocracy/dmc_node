///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Dmc Node
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _DMCNODE_CODE_FRONTEND_REQUEST_H_
#define _DMCNODE_CODE_FRONTEND_REQUEST_H_

#include <string>

namespace dmc {
	class Request {
	public:
		Request(unsigned _id) : mId(_id) {}
		// Accessors
		unsigned			id		() const { return mId;	}
		const std::string&	url		() const { return mUrl;	}
		const std::string&	method	() const { return mMethod;	}
		const std::string&	body	() const { return mJson;}
		std::string&		url		() { return mUrl;	}
		std::string&		method	() { return mMethod;	}
		std::string&		body	() { return mJson;	}

	private:
		unsigned	mId;
		std::string mUrl;
		std::string mJson;
		std::string mMethod;

	};

}	//	namespace dmc

#endif	// _DMCNODE_CODE_FRONTEND_HTTPTRANSLATOR_H_
