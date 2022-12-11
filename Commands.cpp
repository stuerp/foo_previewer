
/** $VER: Commands.cpp (2022.12.11) P. Stuer **/

#include "framework.h"

#pragma hdrstop

#pragma comment(lib, "shlwapi") // StrCmpLogicalW

constexpr GUID PreviewCommandGUID = GUID_PREVIEW_COMMAND;
constexpr char PreviewCommandName[] = "Preview";
constexpr char PreviewCommandDescription[] = "Starts preview playback mode.";

bool _IsPreviewing = false;

/// <summary>
/// Enables or disables Preview playback mode (Command called from the context menu)
/// </summary>
void PreviewCommand(metadb_handle_list_cref)
{
    static_api_ptr_t<playlist_manager> _PlaylistManager;

    t_size PlaylistIndex = _PlaylistManager->get_active_playlist();

    if (PlaylistIndex == pfc_infinite)
        return;

    t_size FocusedIndex = _PlaylistManager->playlist_get_focus_item(PlaylistIndex);

    if (FocusedIndex == pfc_infinite)
        return;

    // Queues the item that has the focus.
    _PlaylistManager->queue_add_item_playlist(PlaylistIndex, FocusedIndex);

    PreviewCommand();
}

/// <summary>
/// Enables or disables Preview playback mode (Command called from the main menu)
/// </summary>
void PreviewCommand()
{
    static_api_ptr_t<playback_control>()->stop();

    _IsPreviewing = !_IsPreviewing;

    if (_IsPreviewing)
    {
        double PreviewLength = GetPreviewLength();

        FB2K_console_formatter() << "Previewing track for " << PreviewLength << "s.";

        static_api_ptr_t<playback_control>()->start(playback_control::track_command_play, false);
    }
}
