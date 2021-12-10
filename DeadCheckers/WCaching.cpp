#include "WCaching.h"

void WCaching::StartTrack()
{
	_isTracking = true;
}

void WCaching::EndTrack()
{
	_cache = _used;
}

HBITMAP WCaching::GetCached(void* key)
{
	HBITMAP val = _cache[key];
	if (_isTracking && (val != nullptr)) {
		_used[key] = val;
	}
	return val;
}

RECT WCaching::GetClientRect()
{
	return _clientRect;
}

void WCaching::SetClientRect(RECT clientRect)
{
	_cache.clear();
	_clientRect = clientRect;
}

