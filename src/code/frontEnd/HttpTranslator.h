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
		/// \param _id this will be the id assigned to the resulting request
		bool translate(const Poco::Net::HTTPServerRequest&, Request&, unsigned _id);
		bool translate(const Response&, Poco::Net::HTTPServerResponse&);
	};

}	//	namespace dmc

#endif	// _DMCNODE_CODE_FRONTEND_HTTPTRANSLATOR_H_
