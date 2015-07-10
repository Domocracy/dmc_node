//----------------------------------------------------------------------------------------------------------------------
// Mock Hue Bridge
//----------------------------------------------------------------------------------------------------------------------
#include "ErrorMessage.h"
#include <sstream>

using namespace std;

//----------------------------------------------------------------------------------------------------------------------
ErrorMessage::ErrorMessage(unsigned _id, const std::string& _uri, const std::string& _message) {
	stringstream ss;
	ss << R"({
	"error" : { "type":)" << _id << ",\n"
		<< R"(	"address":")" << _uri << "\",\n"
		<< R"(	"description":")" << _message << "\"}\n}\n";
	mContent = ss.str();
}

//----------------------------------------------------------------------------------------------------------------------
ErrorMessage ErrorMessage::unauthorizedUser(const std::string& _uri) {
	return ErrorMessage(1, _uri, "unauthorized user");
}

//----------------------------------------------------------------------------------------------------------------------
ErrorMessage ErrorMessage::resourceNotAvailable(const std::string& _uri) {
	return ErrorMessage(3, _uri, "resource, " + _uri + ", not available");
}

//----------------------------------------------------------------------------------------------------------------------
ErrorMessage ErrorMessage::methodNotAvailable(const std::string& _uri, const std::string& _method) {
	return ErrorMessage(4, _uri, "method, " + _method+ ", not available for resource, " + _uri);
}