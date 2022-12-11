
/** $VER: Preferences.h (2022.12.11) P. Stuer **/

#pragma once

#include "framework.h"

enum StartTimeTypes
{
    Seconds = 0,
    Percentage,
    Random
};

extern StartTimeTypes GetStartTimeType();
extern double GetPreviewLength();
extern double GetPreviewStartTimeInSec();
extern double GetPreviewStartTimeAsPercentage();
