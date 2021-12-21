#pragma once

#include <Windows.h>
#include <string>
#include <vector>


class PreparedTracks {
private:
	int _current = -1;
	std::vector<std::wstring> _tracks;

public:
	PreparedTracks(const std::vector<std::wstring>& tracks);
	void PlayNext();
};