
/** $VER: Settings.cpp (2022.12.05) P. Stuer **/

#include "framework.h"

#pragma hdrstop

static constexpr GUID SettingsBranchGUID                        = { 0x90073616, 0x61a0, 0x473d, { 0xa1, 0x72, 0x70, 0x39, 0x24, 0xfe, 0xb0, 0xa1 } }; // {90073616-61A0-473D-A172-703924FEB0A1}
static constexpr GUID SettingsPreviewLengthGUID                 = { 0x43009833, 0xd765, 0x4515, { 0x9c, 0x59, 0x7e, 0xed, 0x78, 0x2b, 0x62, 0x2b } }; // {43009833-D765-4515-9C59-7EED782B622B}
static constexpr GUID SettingsPreviewStartTimeGUID              = { 0x547e2382, 0x09cb, 0x4ec3, { 0xb3, 0x25, 0xc0, 0xff, 0xbf, 0xf3, 0xbd, 0xa6 } }; // {547E2382-09CB-4EC3-B325-C0FFBFF3BDA6}

static constexpr GUID SettingsPreviewRandomStartTimeGUID        = { 0xe0b5aa2a, 0x189e, 0x4f1c, { 0xb8, 0x95, 0x67, 0x20, 0xb2, 0x2f, 0xa4, 0xea } }; // {E0B5AA2A-189E-4F1C-B895-6720B22FA4EA}
static constexpr GUID SettingsPreviewStartTimeAsPercentageGUID  = { 0x7c8b7e19, 0x5ba9, 0x4391, { 0x92, 0x99, 0x20, 0xcc, 0xc6, 0x20, 0xf4, 0xe7 } }; // {7C8B7E19-5BA9-4391-9299-20CCC620F4E7}
static constexpr GUID SettingsPreviewStartTimePercentageGUID    = { 0x1d5d5c64, 0x18e6, 0x4ff5, { 0xb5, 0xde, 0x50, 0xce, 0xda, 0x4e, 0x97, 0x5d } }; // {1D5D5C64-18E6-4FF5-B5DE-50CEDA4E975D}

static advconfig_branch_factory _SettingsBranch("Preview track", SettingsBranchGUID, advconfig_entry::guid_branch_playback, 0);

    advconfig_string_factory _SettingsPreviewStartTime("Start time in seconds", SettingsPreviewStartTimeGUID, SettingsBranchGUID, 0, "0.0");
        advconfig_checkbox_factory _SettingsPreviewRandomStartTime("Random start time", SettingsPreviewRandomStartTimeGUID, SettingsPreviewStartTimeGUID, 0, false);

    advconfig_string_factory _SettingsPreviewLength("Preview length in seconds", SettingsPreviewLengthGUID, SettingsBranchGUID, 1, "5.0");

    advconfig_checkbox_factory _SettingsPreviewStartTimeAsPercentage("Start time as percentage of track length", SettingsPreviewStartTimeAsPercentageGUID, SettingsBranchGUID, 2, false);
        advconfig_string_factory _SettingsPreviewStartTimePercentage("Start time percentage", SettingsPreviewStartTimePercentageGUID, SettingsPreviewStartTimeAsPercentageGUID, 0, "50.0");

bool _IsPreviewing = false;

/// <summary>
/// Gets the length of the preview period.
/// </summary>
double GetPreviewLength()
{
    pfc::string8 Text;

    _SettingsPreviewLength.get(Text);

    return ::atof(Text);
}

/// <summary>
/// Gets the start time of the preview period.
/// </summary>
double GetPreviewStartTime()
{
    pfc::string8 PreviewStartTimeText;

    _SettingsPreviewStartTime.get(PreviewStartTimeText);

    return ::atof(PreviewStartTimeText);
}

/// <summary>
/// Gets the start time percentage of the preview period.
/// </summary>
double GetPreviewStartTimePercentage()
{
    pfc::string8 PreviewStartTimePercentageText;

    _SettingsPreviewStartTimePercentage.get(PreviewStartTimePercentageText);

    return ::atof(PreviewStartTimePercentageText);
}
