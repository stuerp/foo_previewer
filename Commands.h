
/** $VER: Commands.h (2022.12.11) P. Stuer **/

#pragma once

#include "framework.h"

extern bool _IsPreviewing;

extern const GUID PreviewCommandGUID;
extern const char PreviewCommandName[];
extern const char PreviewCommandDescription[];
extern void       PreviewCommand(metadb_handle_list_cref list);
extern void       PreviewCommand();
