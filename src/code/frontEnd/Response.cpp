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
		return error(ErrorCode::invalidRequestUrl, "Invalid request url");
	}

	//------------------------------------------------------------------------------------------------------------------
	Response Response::deviceNotFound(unsigned _devId) {
		return error(ErrorCode::deviceNotFound, "Device Not Found");
	}

	//------------------------------------------------------------------------------------------------------------------
	Response Response::failedToParseRequestBody(const std::string& _info) {
		std::string message = "Failed to parse request body.\n" + _info;
		return error(ErrorCode::failedToParseRequestBody, message);
	}

	//------------------------------------------------------------------------------------------------------------------
	Response Response::commandExecutionError(const std::string& _info) {
		std::string message = "Error runninc command.\n" + _info;
		return error(ErrorCode::commandExecutionError, message);
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
