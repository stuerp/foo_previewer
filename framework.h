
/** $VER: framework.h (2022.12.05) P. Stuer **/

#pragma once

#define TOSTRING_IMPL(x) #x
#define TOSTRING(x) TOSTRING_IMPL(x)

#include <SDKDDKVer.h>

#include <sdk/foobar2000.h>

#include <helpers/foobar2000+atl.h>
#include <helpers/atl-misc.h>
#include <helpers/advconfig_impl.h>
#include <helpers/DarkMode.h>

#include <stdlib.h>

#include <random>

#include "Commands.h"
#include "Settings.h"

#include "Resources.h"
