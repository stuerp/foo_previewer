
/** $VER: Settings.h (2022.11.01) P. Stuer **/

#pragma once

#include "framework.h"

extern bool _IsPreviewing;

extern advconfig_string_factory _SettingsPreviewStartTime;
    extern advconfig_checkbox_factory _SettingsPreviewRandomStartTime;
extern advconfig_string_factory _SettingsPreviewLength;

extern advconfig_checkbox_factory _SettingsPreviewStartTimeAsPercentage;
    extern advconfig_string_factory _SettingsPreviewStartTimePercentage;

extern double GetPreviewLength();
extern double GetPreviewStartTime();
extern double GetPreviewStartTimePercentage();
