/*
	ffplay.h - Header file for the static Ffplay class.
	
	Revision 0
	
	Notes:
			- 
		
	2019/10/15 - Maya Posch
*/


#ifndef FFPLAY_H
#define FFPLAY_H


#include <iostream>
#include <atomic>
#include <queue>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mutex.h>


#include <Poco/Condition.h>
#include <Poco/Thread.h>
#include <Poco/Runnable.h>

#include "types.h"


struct FileMetaInfo {
	//std::atomic<uint32_t> filesize;		// bytes.
	std::atomic<uint64_t> duration;		// seconds
	std::atomic<double> position;		// seconds with remainder.
	std::atomic<uint32_t> width;		// pixels
	std::atomic<uint32_t> height;		// pixels
	std::atomic<uint32_t> video_rate;	// kilobits per second
	std::atomic<uint32_t> audio_rate;	// kilobits per second
	std::atomic<uint32_t> framrate;
	std::atomic<uint8_t> audio_channels;
	std::string title;
	std::string artist;
	std::string album;
	Poco::Mutex mutex;	// Use only with non-atomic entries.
};


// --- Globals ---
extern FileMetaInfo file_meta;
extern std::atomic<bool> playerStarted;
	
void finishPlayback(); // Defined in NymphCastServer.cpp

	
class Ffplay : public Poco::Runnable {
    VideoState* is = 0;
	
	static int media_read(void* opaque, uint8_t* buf, int buf_size);
	static int64_t media_seek(void* opaque, int64_t pos, int whence);
	
public:
	virtual void run();
	uint8_t getVolume();
	void setVolume(uint8_t volume);
	void quit();
};


#endif
