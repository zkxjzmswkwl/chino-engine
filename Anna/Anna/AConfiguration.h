#pragma once
#include "pch.h"

struct AResolution
{
	int		nWidth;
	int		nHeight;
};

class AConfiguration
{
private:
	bool			bFullScreen;
	uint			nRefreshRate;
	AResolution		csResolution;

public:
	bool Load();
	bool LoadConfig(string configPath);
};

#define A_CONFIG_WINDOW					"WINDOW"
#define A_CONFIG_WINDOW_RESOLUTION		"RESOLUTION"
#define A_CONFIG_WINDOW_FULLSCREEN		"FULLSCREEN"
#define A_CONFIG_WINDOW_REFRESH_RATE	"REFRESH_RATE"

