////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// DMC_NODE
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "backEnd/requestProcessors/CommandDispatcher.h"
#include "backEnd/Device.h"
#include "frontEnd/Request.h"
#include <cassert>
#include <string>

namespace dmc {
	// --- Mock classes ---
	class Response {
	public:
		std::string mContent;
	};

	class LocalServer {
	public:
		bool respond(const Request& request, const Response& _response) {
			assert(!responded);
			responded = true;
			response = _response.mContent;
			return true;
		}

		bool responded = false;
		std::string response;
	};

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

	class DeviceManager {
	public:
		TestDevice dev;
		Device* devPtr;

		DeviceManager() { devPtr = &dev; }

		Device*	device(unsigned _id) const {
			if(_id == 1)
				return devPtr;
			return nullptr;
		}
	};

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

void testEverythingOk() {
	LocalServer server;
	Request req(0);
	req.url() = "/command/1";
	req.body() = "ok";
	DeviceManager mgr;
	RequestDispatcher rd;
	CommandDispatcher cmdDisp(mgr, rd);
	assert(rd.suscribed);
	cmdDisp.process(req, server);
	assert(server.responded);
	assert(server.response == "ok");
}

void testDeviceFailsParse() {
	LocalServer server;
	Request req(0);
	req.url() = "/command/1";
	req.body() = "parse";
	DeviceManager mgr;
	RequestDispatcher rd;
	CommandDispatcher cmdDisp(mgr, rd);
	assert(rd.suscribed);
	cmdDisp.process(req, server);
	assert(server.responded);
	assert(server.response == "parseInfo");
}

void testDeviceFailsExecution() {
	LocalServer server;
	Request req(0);
	req.url() = "/command/1";
	req.body() = "execution";
	DeviceManager mgr;
	RequestDispatcher rd;
	CommandDispatcher cmdDisp(mgr, rd);
	assert(rd.suscribed);
	cmdDisp.process(req, server);
	assert(server.responded);
	assert(server.response == "runError");
}

void testDeviceNotFound() {
	LocalServer server;
	Request req(0);
	req.url() = "/command/0";
	DeviceManager mgr;
	RequestDispatcher rd;
	CommandDispatcher cmdDisp(mgr, rd);
	assert(rd.suscribed);
	cmdDisp.process(req, server);
	assert(server.responded);
	assert(server.response == "devNotFound");
}

void testUrlError(const std::string& _url) {
	LocalServer server;
	Request req(0);
	req.url() = _url;
	DeviceManager mgr;
	RequestDispatcher rd;
	CommandDispatcher cmdDisp(mgr, rd);
	assert(rd.suscribed);
	cmdDisp.process(req, server);
	assert(server.responded);
	assert(server.response == "urlError");
}

int main(int, const char**) {
	// All tests
	testEverythingOk();
	// Test Device fails to run request
	testDeviceFailsParse();
	testDeviceFailsExecution();
	// Test Device not found
	testDeviceNotFound();
	// Test url error
	testUrlError("/comm");
	testUrlError("/command/asd");
	testUrlError("/command/023/what");
}
