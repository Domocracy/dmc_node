//----------------------------------------------------------------------------------------------------------------------
// Mock Hue Bridge
//----------------------------------------------------------------------------------------------------------------------
#ifndef _MOCKHUEBRIDGE_MOCKHUEBRIDGE_H_
#define _MOCKHUEBRIDGE_MOCKHUEBRIDGE_H_

#include <frontEnd/LocalServer.h>
#include <frontEnd/RequestDispatcher.h>
#include <backEnd/RequestProcessor.h>

class MockHueBridge {
public:
	MockHueBridge(unsigned _port);

private:
	class HueReqProcessor : public dmc::RequestProcessor {
		// Inherited via RequestProcessor
		void process(const dmc::Request & _request, dmc::LocalServer & _localServer) override;
		virtual void generateResponse(const dmc::Request & _request, std::ostream& _responseBody) = 0;
	};

	class NoUser : public HueReqProcessor {
		void generateResponse(const dmc::Request & _request, std::ostream& _responseBody) override;
	};

private:
	NoUser					mNoUser;
	dmc::RequestDispatcher	mDispatcher;
	dmc::LocalServer		mServer;
};

#endif // _MOCKHUEBRIDGE_MOCKHUEBRIDGE_H_
