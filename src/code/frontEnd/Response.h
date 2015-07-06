///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Dmc Node
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _DMCNODE_CODE_FRONTEND_RESPONSE_H_
#define _DMCNODE_CODE_FRONTEND_RESPONSE_H_

#include <string>

namespace dmc {

	class Response {
	public:
		static Response ok();
		static Response ok(const std::string& _body);
		static Response internalError();

		const std::string& serialize() const;

	private:
		enum class ErrorCode {
			invalidHttpRequest = 1
		};

	private:
		Response(bool _ok);
		Response(const std::string& _errorMsg);

		std::string mContent;
	};

}	//	namespace dmc

#endif	// _DMCNODE_CODE_FRONTEND_RESPONSE_H_
