
/** $VER: Commands.h (2022.12.05) P. Stuer **/

#pragma once

#include "framework.h"

extern const GUID PreviewCommandGUID;
extern const char PreviewCommandName[];
extern const char PreviewCommandDescription[];
extern void       PreviewCommand(metadb_handle_list_cref list);
extern void       PreviewCommand();
