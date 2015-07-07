////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Dmc Node
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "Response.h"
#include <sstream>

using namespace std;

namespace dmc {

	//------------------------------------------------------------------------------------------------------------------
	Response::Response(const cjson::Json& _body) {
		mContent = _body.serialize();
	}

	//------------------------------------------------------------------------------------------------------------------
	Response Response::ok() {
		return Response(std::string(R"({"ok":true})"));
	}

	//------------------------------------------------------------------------------------------------------------------
	Response Response::invalidRequestUrl() {
		return error(ErrorCode::invalidRequest, "Invalid request url");
	}

	//------------------------------------------------------------------------------------------------------------------
	void Response::serialize(std::ostream& _os) const {
		_os << mContent;
	}

	//------------------------------------------------------------------------------------------------------------------
	Response Response::error(ErrorCode _code, const std::string& _message) {
		stringstream ss;
		ss << R"({"ok":false, "error"{
				"code":)" << unsigned(_code) << R"(,"message":")" << _message << "\"}}";
		return Response(ss.str());
	}



}	//	namespace dmc
