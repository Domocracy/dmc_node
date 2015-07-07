////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// DMC_NODE
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <backEnd/requestProcessors/CommandDispatcher.h>
#include <backEnd/DeviceManager.h>
#include <backEnd/Device.h>
#include <frontEnd/LocalServer.h>
#include <frontEnd/Request.h>
#include <cassert>
#include <string>

namespace dmc {
	// --- Mock classes ---
	class Response {
	public:
		std::string mContent;

		static Response invalidRequestUrl() { return Response { "urlError" }; }
		static Response deviceNotFound(unsigned _devId) { 
			assert(_devId == 0);
			return Response { "devNotFound: 0" }; 
		}
		static Response failedToParseRequestBody() {
			return Response { "parse" }; 
		}
		static Response commandExecutionError(const std::string& _info) {
			return Response { std::string("run")+_info };
		}
	};


	std::string gResponse;

	LocalServer::LocalServer(RequestDispatcher& _rd, unsigned _port) :mDispatcher(_rd) {}

	bool LocalServer::respond(const Request& request, const Response& _response) {
		gResponse = _response.mContent;
		return true;
	}

	class TestDevice : public Device {
		
		Device::CmdResult process(const std::string& _command, std::ostream& _info) override{
			if(_command == "ok")
				return CmdResult::Ok;
			else if(_command == "parse") {
				_info << "Info";
				return CmdResult::CommandError;
			}
			else if(_command == "execution") {
				_info << "Info";
				return CmdResult::ExecutionError;
			}
			else {
				assert(false);
				return CmdResult::Ok;
			}
		}
	};

	TestDevice dev;
	Device*	DeviceManager::device(unsigned _id) const {
		if(_id == 1)
			return &dev;
		return nullptr;
	}

	class RequestDispatcher {
	public:
		void subscribe(RequestProcessor*, const std::string& _localUrl) {
			assert(_localUrl == "/command");
			assert(!suscribed);
			suscribed = true;
		}
		bool suscribed = false;
	};
}	//	namespace dmc

using namespace dmc;

void test(const std::string& url, const std::string& body, const std::string& expect) {
	Request req(0);
	req.url() = url;
	req.body() = body;
	DeviceManager mgr;
	RequestDispatcher rd;
	LocalServer server(rd, 0);
	CommandDispatcher cmdDisp(mgr, rd);
	assert(rd.suscribed);
	cmdDisp.process(req, server);
	assert(gResponse == expect);
}

int main(int, const char**) {
	// All tests
	test("/command/1", "ok", "ok"); // Test with everything ok
	// Test Device fails to run request
	test("/command/1", "parse", "parse");
	test("/command/1", "execution", "runError");
	// Test Device not found
	test("/command/0", "", "devNotFound: 0");
	// Test url error
	test("/comm", "", "urlError");
	test("/command/asd", "", "urlError");
	test("/command/023/what", "", "urlError");
}
