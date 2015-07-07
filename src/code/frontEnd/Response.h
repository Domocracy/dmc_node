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
		Response(const std::string& _content);
		// Default responses
		static Response ok();
		/// The received request's url doesn't meet the format expected by the message processor
		static Response invalidRequestUrl();
		static Response deviceNotFound(unsigned _devId);
		static Response failedToParseRequestBody();
		static Response commandExecutionError(const std::string& _info);

		void serialize (std::ostream&) const;
		const std::string& serialize() const { return mContent; }

	private:
		enum class ErrorCode {
			invalidRequestUrl = 1,
			deviceNotFound,
			failedToParseRequestBody,
			commandExecutionError
		};

	private:
		static Response error(ErrorCode, const std::string& _message);

		std::string mContent;
	};

}	//	namespace dmc

#endif	// _DMCNODE_CODE_FRONTEND_RESPONSE_H_
