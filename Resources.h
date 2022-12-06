
/** $VER: Resources.cpp (2022.12.05) P. Stuer **/

#pragma once

#define TOSTRING_IMPL(x) #x
#define TOSTRING(x) TOSTRING_IMPL(x)

/** Component specific **/

#define STR_COMPONENT_NAME      "Preview"
#define STR_COMPONENT_VERSION   TOSTRING(NUM_FILE_MAJOR) "." TOSTRING(NUM_FILE_MINOR) "." TOSTRING(NUM_FILE_PATCH)
#define STR_COMPONENT_FILENAME  "foo_preview.dll"

/** Generic **/

#define STR_COMPANY_NAME        TEXT("LionTech")
#define STR_INTERNAL_NAME       TEXT(STR_COMPONENT_NAME)
#define STR_COMMENTS            TEXT("Written by P. Stuer")
#define STR_COPYRIGHT           TEXT("Copyright � 2022 ") STR_COMPANY_NAME TEXT(". All rights reserved.")

#define NUM_FILE_MAJOR          1
#define NUM_FILE_MINOR          0
#define NUM_FILE_PATCH          0
#define NUM_FILE_PRERELEASE     0

#define STR_FILE_NAME           TEXT(STR_COMPONENT_FILENAME)
#define STR_FILE_VERSION        TOSTRING(NUM_FILE_MAJOR) TEXT(".") TOSTRING(NUM_FILE_MINOR) TEXT(".") TOSTRING(NUM_FILE_PATCH)) TEXT(".") TOSTRING(NUM_FILE_PRERELEASE))
#define STR_FILE_DESCRIPTION    TEXT("Adds a Preview command to a track")

#define NUM_PRODUCT_MAJOR       1
#define NUM_PRODUCT_MINOR       0
#define NUM_PRODUCT_PATCH       0
#define NUM_PRODUCT_PRERELEASE  0

#define STR_PRODUCT_NAME        STR_COMPANY_NAME TEXT(" ") STR_INTERNAL_NAME
#define STR_PRODUCT_VERSION     TOSTRING(NUM_PRODUCT_MAJOR) TEXT(".") TOSTRING(NUM_PRODUCT_MINOR) TEXT(".") TOSTRING(NUM_PRODUCT_PATCH) TEXT(".") TOSTRING(NUM_PRODUCT_PRERELEASE)

#define STR_ABOUT_NAME          STR_INTERNAL_NAME
#define STR_ABOUT_WEB           TEXT("https://github.com/stuerp/foo_preview")
#define STR_ABOUT_EMAIL         TEXT("mailto:peter.stuer@outlook.com")

static constexpr GUID GUID_MENU_ITEM       = { 0x97ac4048, 0x0d76, 0x4646, { 0xb9, 0xcc, 0x50, 0x7a, 0x18, 0x94, 0xf9, 0x35 } }; // {97AC4048-0D76-4646-B9CC-507A1894F935}
static constexpr GUID GUID_PREVIEW_COMMAND = { 0xec19f550, 0x9ff2, 0x4a0c, { 0x8a, 0x61, 0x17, 0xcc, 0xcb, 0xa5, 0x26, 0xa2 } }; // {EC19F550-9FF2-4A0C-8A61-17CCCBA526A2}

#define IDD_PREFERENCES         101
#define IDC_START_TIME_TYPE     1001
#define IDC_START_TIME          1002
#define IDC_START_TIME_UNIT     1003
