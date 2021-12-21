#include "PreparedTracks.h"


PreparedTracks::PreparedTracks(const std::vector<std::wstring>& tracks)
{
	_tracks = tracks;
}

void PreparedTracks::PlayNext()
{
	_current++;
	PlaySound(_tracks[_current].c_str(), NULL, SND_ASYNC);
}
