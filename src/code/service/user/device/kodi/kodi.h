////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Project: DMC Server
// Date:	2015/Feb/19
// Author:	Carmelo J. Fdez-Agüera Tortosa
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _DMCSERVER_SERVICE_USER_DEVICE_KODI_KODI_H_
#define _DMCSERVER_SERVICE_USER_DEVICE_KODI_KODI_H_

#include <string>
#include <cjson/json.h>
#include <core/comm/socket/socket.h>
#include <home/device/actuator.h>

namespace dmc { namespace kodi {

	class Kodi final : public Actuator{
	public:
		Kodi(unsigned _id, const cjson::Json&);
		~Kodi();

		cjson::Json	runCommand	(const cjson::Json& _cmd) override;
		cjson::Json	read		(const cjson::Json& _request) const override;
		cjson::Json*	serialize	() const override;

	private:
		void		sendRequest		(const cjson::Json&) const;
		cjson::Json readResponse	() const;

		bool		isIdValid		(const cjson::Json&) const;

		cjson::Json getPlayers		() const;
		cjson::Json getMovies		() const;
		cjson::Json getTvShows		() const;
		cjson::Json getEpisodes		(const cjson::Json& _show);
		cjson::Json getPlayer		() const;
		cjson::Json pauseResume		();
		cjson::Json stop			();
		cjson::Json setVolume		(unsigned _volume); // 0 to 100
		bool		playLastEpisode(const cjson::Json& _show);
		bool		PlayMovie		(const cjson::Json& _movie);
		cjson::Json scanLibrary		();

		std::string mIp;
		unsigned	mPort = 9090;
		Socket*		mTcpConnection;

		mutable unsigned	mLastReqId = 1;
	};

}}	// namespace dmc::kodi

#endif // _DMCSERVER_SERVICE_USER_DEVICE_KODI_KODI_H_