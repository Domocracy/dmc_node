////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Project: DMC Server
// Date:	2015/Feb/19
// Author:	Carmelo J. Fdez-Agüera Tortosa
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "kodi.h"
#include <iostream>
#include <core/comm/json/rpc/jsonRpc.h>

using namespace std;

using cjson::Json;

namespace dmc { namespace kodi {

	//------------------------------------------------------------------------------------------------------------------
	Kodi::Kodi(unsigned _id, const cjson::Json& _data)
		:Actuator(_id, string(_data["name"]))
	{
		mIp = _data["ip"];
		mTcpConnection = new Socket();
	}

	//------------------------------------------------------------------------------------------------------------------
	Kodi::~Kodi() {
		delete mTcpConnection;
	}

	//------------------------------------------------------------------------------------------------------------------
	cjson::Json Kodi::runCommand(const cjson::Json& _cmd) {
		string command = std::string(_cmd["cmd"]);
		if(command == "lastEpisode") {
			if(playLastEpisode(_cmd["tvshowid"])) {
				return Json(R"({"result": "ok"})");
			} 
			else 
				return Json(R"({"result":"fail", "error":"unable to play show"})");
		}
		else if(command == "movie") {
			if(PlayMovie(_cmd["movieid"])) {
				return Json(R"({"result": "ok"})");
			}
			else 
				return Json(R"({"result":"fail", "error":"unable to play movie"})");
		} else if(command == "setVolume") {
			unsigned volume = _cmd["volume"];
			Json finalVol = setVolume(volume);
			Json result = Json(R"({"result": "ok"})");
			result["volume"] = finalVol;
			return result;
		} else if(command == "pause" || command == "resume") {
			Json result(R"({"result": "ok"})");
			result["state"] = pauseResume();
			return result;
		} else if(command == "stop") {
			stop();
			return Json(R"({"result": "ok"})");
		}
		return Json(R"({"result":"fail", "error":"unknown command"})");
	}

	//------------------------------------------------------------------------------------------------------------------
	cjson::Json Kodi::read(const cjson::Json& _request) const {
		string command = std::string(_request["cmd"]);
		if(command == "tvshows") {
			Json response(R"({})");
			Json shows = getTvShows();
			if(shows.isNull())
				return Json(R"({"result":"fail", "error":"Kodi not available"})");
			else
				response["tvshows"] = shows;
			response["result"] = Json("\"ok\"");
			return response;
		} 
		return Json(R"({"result":"fail", "error":"unknown request"})");
	}

	//------------------------------------------------------------------------------------------------------------------
	cjson::Json* Kodi::serialize() const {
		cjson::Json *base = Actuator::serialize();
		(*base)["ip"] = mIp;
		(*base)["type"] = "Kodi";
		return base;
	}

	//------------------------------------------------------------------------------------------------------------------
	void Kodi::sendRequest(const cjson::Json& _cmd) const {
		mTcpConnection->open(mIp, mPort);
		mTcpConnection->write(_cmd.serialize());
	}

	//------------------------------------------------------------------------------------------------------------------
	cjson::Json Kodi::readResponse() const {
		if(!mTcpConnection->isOpen()) {
			return cjson::Json();
		}
		const unsigned bufferSize = 64*1024;
		char buffer[bufferSize+1];
		bool match = false;
		cjson::Json kodiResponse;
		while(!match) { // Discard notifications
			int nBytes = mTcpConnection->read(buffer, bufferSize);
			buffer[nBytes] = '\0';
			kodiResponse = cjson::Json(string(buffer));
			cjson::Json responseId = kodiResponse["id"];
			if(!responseId.isNull() && responseId == (mLastReqId-1))
				match = true;
		}
		mTcpConnection->close();
		return cjson::Json(string(buffer));
	}

	//------------------------------------------------------------------------------------------------------------------
	bool Kodi::isIdValid(const cjson::Json &_id) const {
		if (_id == -1)
			return false;
		else
			return true;
	}

	//------------------------------------------------------------------------------------------------------------------
	cjson::Json Kodi::getPlayers() const{
		JsonRpcRequest request("Player.GetActivePlayers", cjson::Json("{}"), mLastReqId++);
		sendRequest(request);
		return readResponse();
	}

	//------------------------------------------------------------------------------------------------------------------
	cjson::Json Kodi::getMovies() const {
		JsonRpcRequest request("VideoLibrary.GetMovies", 
			cjson::Json(R"({"properties": ["file"]})"), mLastReqId++);
		sendRequest(request);
		cjson::Json response = readResponse();
		if(response.isNull())
			return response;
		cjson::Json cmdResult = response["result"];
		if(cmdResult["movies"].isNull())
			return cjson::Json("[]"); // Empty list
		return cmdResult["movies"];
	}

	//------------------------------------------------------------------------------------------------------------------
	cjson::Json Kodi::getTvShows() const {
		JsonRpcRequest request("VideoLibrary.GetTVShows", 
			cjson::Json("{}"), mLastReqId++);
		sendRequest(request);
		cjson::Json response = readResponse();
		if(response.isNull())
			return response;
		cjson::Json cmdResult = response["result"];
		if(cmdResult["tvshows"].isNull())
			return cjson::Json("[]"); // Empty list
		return cmdResult["tvshows"];
	}

	//------------------------------------------------------------------------------------------------------------------
	cjson::Json Kodi::getEpisodes(const cjson::Json& _showId)
	{
		cjson::Json command = cjson::Json(R"({"filter": {"field": "playcount", "operator": "is", "value": "0"}, "sort":{"order": "ascending", "method": "dateadded"}})");
		command["tvshowid"] = _showId;
		JsonRpcRequest request("VideoLibrary.GetEpisodes",
				command, mLastReqId++);
		sendRequest(request);
		cjson::Json response = readResponse();
		if(response.isNull())
			return response;
		return response["result"]["episodes"];
	}

	//------------------------------------------------------------------------------------------------------------------
	cjson::Json Kodi::getPlayer() const {
		cjson::Json command = cjson::Json("{}");
		JsonRpcRequest request("Player.GetActivePlayers", command, mLastReqId++);
		sendRequest(request);
		cjson::Json response = readResponse();
		if(response.isNull() || response["result"].size() == 0)
			return cjson::Json();
		int playerId = response["result"][0]["playerid"];
		cjson::Json playerJson("{}");
		playerJson["playerid"] = playerId;
		return playerJson;
	}

	//------------------------------------------------------------------------------------------------------------------
	cjson::Json Kodi::pauseResume() {
		cjson::Json player = getPlayer();
		if(player.isNull()) {
			cjson::Json error;
			error = "Error";
			return error;
		}
		JsonRpcRequest request("Player.PlayPause", player, mLastReqId++);
		sendRequest(request);
		cjson::Json response = readResponse();
		if(response.isNull())
			return response;
		return response["result"];
	}

	//------------------------------------------------------------------------------------------------------------------
	cjson::Json Kodi::stop() {
		cjson::Json player = getPlayer();
		if(player.isNull()) {
			cjson::Json error;
			error = "Error";
			return error;
		}
		JsonRpcRequest request("Player.Stop", player, mLastReqId++);
		sendRequest(request);
		cjson::Json response = readResponse();
		if(response.isNull())
			return response;
		return response["result"];
	}

	//------------------------------------------------------------------------------------------------------------------
	cjson::Json Kodi::setVolume(unsigned _volume) {
		cjson::Json volumeCmd("{}");
		volumeCmd["volume"] = ((int)_volume);
		JsonRpcRequest request("Application.SetVolume", volumeCmd, mLastReqId++);
		sendRequest(request);
		cjson::Json response = readResponse();
		if(response.isNull())
			return response;
		return response["result"];
	}

	//------------------------------------------------------------------------------------------------------------------
	bool Kodi::playLastEpisode(const Json& _show) {
		if (!isIdValid(_show))
			return false;

		cjson::Json episodes = getEpisodes(_show);
		if(episodes.isNull()) {
			return true;
		}
		cjson::Json params(R"({"item":{}})");
		params["item"]["episodeid"] = episodes[0]["episodeid"];
		JsonRpcRequest request ("Player.Open", params, mLastReqId++);
		sendRequest(request);
		readResponse(); // Prevent return string to stack on read buffer.
		return true;
	}

	//------------------------------------------------------------------------------------------------------------------
	bool Kodi::PlayMovie(const Json& _movie) {
		cjson::Json params(R"({"item":{}})");
		params["item"]["movieid"] = _movie["movieid"];
		JsonRpcRequest request ("Player.Open", params, mLastReqId++);
		sendRequest(request);
		readResponse(); // Prevent return string to stack on read buffer.
		return true;
	}

	//------------------------------------------------------------------------------------------------------------------
	cjson::Json Kodi::scanLibrary() {
		JsonRpcRequest request("VideoLibrary.Scan", Json("{}"), mLastReqId++);
		sendRequest(request);
		readResponse();
		return cjson::Json();
	}

}}	// namespace dmc::kodi