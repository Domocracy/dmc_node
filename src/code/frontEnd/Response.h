///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Dmc Node
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _DMCNODE_CODE_FRONTEND_RESPONSE_H_
#define _DMCNODE_CODE_FRONTEND_RESPONSE_H_

#include <cjson/json.h>
#include <string>
#include <iostream>

namespace dmc {

	class Response {
	public:
		Response(const cjson::Json& _content);
		// Default responses
		static Response ok();
		/// The received request's format doesn't meet the requirements. There might be missing content in the Json.
		static Response invalidRequest();

		void serialize (std::ostream&) const;
		const std::string& serialize() const { return mContent; }

	private:
		enum class ErrorCode {
			invalidRequest = 1
		};

	private:
		static Response error(ErrorCode, const std::string& _message);
		Response(const std::string& _content);

		std::string mContent;
	};

}	//	namespace dmc

#endif	// _DMCNODE_CODE_FRONTEND_RESPONSE_H_
