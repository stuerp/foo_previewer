
/** $VER: Resources.cpp (2023.05.01) P. Stuer **/

#pragma once

#define TOSTRING_IMPL(x) #x
#define TOSTRING(x) TOSTRING_IMPL(x)

/** Component specific **/

#define STR_COMPONENT_NAME      "Previewer"
#define STR_COMPONENT_VERSION   TOSTRING(NUM_FILE_MAJOR) "." TOSTRING(NUM_FILE_MINOR) "." TOSTRING(NUM_FILE_PATCH) "." TOSTRING(NUM_FILE_PRERELEASE)
#define STR_COMPONENT_FILENAME  "foo_previewer.dll"

/** Generic **/

#define STR_COMPANY_NAME        TEXT("LionTech")
#define STR_INTERNAL_NAME       TEXT(STR_COMPONENT_NAME)
#define STR_COMMENTS            TEXT("Written by P. Stuer")
#define STR_COPYRIGHT           TEXT("Copyright (c) 2022-2023 ") STR_COMPANY_NAME TEXT(". All rights reserved.")

#define NUM_FILE_MAJOR          1
#define NUM_FILE_MINOR          1
#define NUM_FILE_PATCH          0
#define NUM_FILE_PRERELEASE     0

#define STR_FILE_NAME           TEXT(STR_COMPONENT_FILENAME)
#define STR_FILE_VERSION        TOSTRING(NUM_FILE_MAJOR) TEXT(".") TOSTRING(NUM_FILE_MINOR) TEXT(".") TOSTRING(NUM_FILE_PATCH) TEXT(".") TOSTRING(NUM_FILE_PRERELEASE)
#define STR_FILE_DESCRIPTION    TEXT("Adds a Preview command to a track")

#define NUM_PRODUCT_MAJOR       1
#define NUM_PRODUCT_MINOR       1
#define NUM_PRODUCT_PATCH       0
#define NUM_PRODUCT_PRERELEASE  0

#define STR_PRODUCT_NAME        STR_COMPANY_NAME TEXT(" ") STR_INTERNAL_NAME
#define STR_PRODUCT_VERSION     TOSTRING(NUM_PRODUCT_MAJOR) TEXT(".") TOSTRING(NUM_PRODUCT_MINOR) TEXT(".") TOSTRING(NUM_PRODUCT_PATCH) TEXT(".") TOSTRING(NUM_PRODUCT_PRERELEASE)

#define STR_ABOUT_NAME          STR_INTERNAL_NAME
#define STR_ABOUT_WEB           TEXT("https://github.com/stuerp/foo_previewer")
#define STR_ABOUT_EMAIL         TEXT("mailto:peter.stuer@outlook.com")

#define IDD_PREFERENCES         101
#define IDC_START_TIME_TYPE     1001
#define IDC_START_TIME          1002
#define IDC_START_TIME_UNIT     1003
#define IDC_PREVIEW_LENGTH      1004
