///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Dmc Node
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _DMCNODE_CODE_FRONTEND_HTTPTRANSLATOR_H_
#define _DMCNODE_CODE_FRONTEND_HTTPTRANSLATOR_H_

namespace Poco {
	namespace Net {
		class HTTPServerRequest;
		class HTTPServerResponse;
	}
}

namespace dmc {

	class Request;
	class Response;

	class HTTPTranslator {
	public:
		bool translate(const Poco::Net::HTTPServerRequest&, Request&);
		bool translate(const Response&, Poco::Net::HTTPServerResponse&);
	};

}	//	namespace dmc

#endif	// _DMCNODE_CODE_FRONTEND_HTTPTRANSLATOR_H_
