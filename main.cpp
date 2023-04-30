
/** $VER: main.cpp (2023.04.30) P. Stuer **/

#include "framework.h"

#pragma hdrstop

namespace
{
    #pragma warning(push)
    #pragma warning(disable: 4265 4625 4626 5026 5027)
    DECLARE_COMPONENT_VERSION
    (
        _ComponentName,
        STR_COMPONENT_VERSION,
        STR_COMPONENT_FILENAME " " STR_COMPONENT_VERSION "\n"
            "Copyright (c) 2022-2023 LionTech. All rights reserved.\n"
            "Written by P. Stuer\n"
            "\n"
            "Adds a Preview playback mode.\n"
            "\n"
            "Built with foobar2000 SDK " TOSTRING(FOOBAR2000_SDK_VERSION) "\n"
            "on " __DATE__ " " __TIME__ "."
    );
    #pragma warning(pop)

    VALIDATE_COMPONENT_FILENAME(STR_COMPONENT_FILENAME);
}
