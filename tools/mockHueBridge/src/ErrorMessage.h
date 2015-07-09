//----------------------------------------------------------------------------------------------------------------------
// Mock Hue Bridge
//----------------------------------------------------------------------------------------------------------------------
#ifndef _MOCKHUEBRIDGE_ERRORMESSAGE_H_
#define _MOCKHUEBRIDGE_ERRORMESSAGE_H_

#include <string>
#include <ostream>

class ErrorMessage {
public:
	ErrorMessage(unsigned _id, const std::string& _uri, const std::string& _message);
	void serialize(std::ostream& _os) { _os << mContent; }

	static ErrorMessage unauthorizedUser(const std::string& _uri);
	static ErrorMessage invalidJson(const std::string& _uri);
	static ErrorMessage resourceNotAvailable(const std::string& _uri);
	static ErrorMessage methodNotAvailable(const std::string& _uri);
	static ErrorMessage missingBodyParameters(const std::string& _uri);
	static ErrorMessage parameterNotAvailable(const std::string& _uri);
	static ErrorMessage invalidValue(const std::string& _uri);
	static ErrorMessage parameterNotModifiable(const std::string& _uri);
	static ErrorMessage tooManyItems(const std::string& _uri);
	static ErrorMessage portalConnRequired(const std::string& _uri);
	static ErrorMessage internalError(const std::string& _uri);

private:
	std::string mContent;
};

#endif // _MOCKHUEBRIDGE_ERRORMESSAGE_H_