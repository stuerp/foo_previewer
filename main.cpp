
/** $VER: main.cpp (2022.12.05) P. Stuer **/

#include "framework.h"

#pragma hdrstop

DECLARE_COMPONENT_VERSION
(
    "Preview",
    STR_COMPONENT_VERSION,
    STR_COMPONENT_FILENAME " " STR_COMPONENT_VERSION "\n"
        "Copyright (c) 2022 LionTech. All rights reserved.\n"
        "Written by P. Stuer\n"
        "\n"
        "Adds a Preview playback mode.\n"
        "\n"
        "Build with foobar2000 SDK " TOSTRING(FOOBAR2000_SDK_VERSION) ".\n"
        "Build: " __TIME__ ", " __DATE__
);

// This will prevent users from renaming your component around (important for proper troubleshooter behaviors) or loading multiple instances of it.
VALIDATE_COMPONENT_FILENAME(STR_COMPONENT_FILENAME);
