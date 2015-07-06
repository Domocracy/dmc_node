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
		/// Translate and incomming HTTPRequest into a dmc::Request.
		/// If the incomming request is ill-formed (for example with an incomplete Json as a body)
		/// Translation will fail, the function will return false, and the contents of
		/// the destination request will be undefined
		/// \param _id this will be the id assigned to the resulting request
		bool translate(const Poco::Net::HTTPServerRequest&, Request&);
		/// Translate a dmc response into an adequate  HTTPServerResponse
		/// \return \c false if the response is ill-formad, and can not be translated into HTTP. \c true otherwise.
		bool translate(const Response&, Poco::Net::HTTPServerResponse&);
	};

}	//	namespace dmc

#endif	// _DMCNODE_CODE_FRONTEND_HTTPTRANSLATOR_H_
