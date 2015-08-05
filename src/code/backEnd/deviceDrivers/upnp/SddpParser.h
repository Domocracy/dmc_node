///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Dmc Node
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _DMCNODE_CODE_BACKEND_SDDPPARSER_H_
#define _DMCNODE_CODE_BACKEND_SDDPPARSER_H_

#include <cjson/json.h>
#include <list>
#include <Poco/Net/MulticastSocket.h>
#include <vector>


namespace dmc {
	class SddpParser {
	public:
		enum eMessageType {NOTIFY, M_SEARCH, RESPONSE, ERR_TYPE};

		cjson::Json parse(std::string _message);

	private:
		eMessageType decodeType(const std::string &_line);

		cjson::Json decodeMSearch	(std::string &_message);
		cjson::Json decodeNotify	(std::string &_message);
		cjson::Json decodeResponse	(std::string &_message);

		cjson::Json decodeHeaders	(std::string &_message);
		cjson::Json decodeBody		(std::string &_message);

		std::string extractLine		(std::string &_message);

		cjson::Json cache_control	(const std::string &_line);
		cjson::Json location		(const std::string &_line);
		cjson::Json date			(const std::string &_line);
		cjson::Json server			(const std::string &_line);
		cjson::Json st				(const std::string &_line);
		cjson::Json usn				(const std::string &_line);
		cjson::Json uuid			(const std::string &_line);
		cjson::Json searchPorts		(const std::string &_line);
	};
}	// namespace dmc

#endif	//	_DMCNODE_CODE_BACKEND_SDDPPARSER_H_