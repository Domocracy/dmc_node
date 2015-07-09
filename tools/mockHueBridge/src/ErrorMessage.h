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
	void serialize(std::ostream&);

	static ErrorMessage unauthorizedUser();
	static ErrorMessage invalidJson();
	static ErrorMessage resourceNotAvailable();
	static ErrorMessage methodNotAvailable();
	static ErrorMessage missingBodyParameters();
	static ErrorMessage parameterNotAvailable();
};

#endif // _MOCKHUEBRIDGE_ERRORMESSAGE_H_