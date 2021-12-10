#pragma once

#include <Windows.h>
#include <vector>
#include <map>

class WCaching {
private:
	bool _isTracking;
	RECT _clientRect;
	std::map<void*, HBITMAP> _used;
	std::map<void*, HBITMAP> _cache;

public:
	void StartTrack();
	void EndTrack();
	HBITMAP GetCached(void* key);
	RECT GetClientRect();
	void SetClientRect(RECT clientRect);
};