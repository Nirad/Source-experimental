#include "../common/graymul.h"
#include "CSectorEnviron.h"


CSectorEnviron::CSectorEnviron()
{
    m_Light = LIGHT_BRIGHT;	// set based on time later.
    m_Season = SEASON_Summer;
    m_Weather = WEATHER_DRY;
}

void CSectorEnviron::SetInvalid()
{
    // Force a resync of all this. we changed location by teleport etc.
    m_Light = UCHAR_MAX;	// set based on time later.
    m_Season = SEASON_QTY;
    m_Weather = WEATHER_DEFAULT;
}