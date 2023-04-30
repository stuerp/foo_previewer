
/** $VER: ContextMenuHandler.cpp (2022.12.11) P. Stuer **/

#include "framework.h"

#pragma hdrstop

namespace
{
#pragma region("GUIDs")
static constexpr GUID _ContextMenuGUID = { 0x97ac4048, 0x0d76, 0x4646, { 0xb9, 0xcc, 0x50, 0x7a, 0x18, 0x94, 0xf9, 0x35 } }; // {97AC4048-0D76-4646-B9CC-507A1894F935};
#pragma endregion

#pragma region("Context Menu")
/// <summary>
/// Simple context menu item class.
/// </summary>
class ContextMenuHandler : public contextmenu_item_simple
{
public:
#pragma region("contextmenu_item interface")
    /// <summary>
    /// Retrieves number of menu items provided by this contextmenu_item implementation.
    /// </summary>
    virtual unsigned int get_num_items() final
    {
        return 1;
    }

    /// <summary>
    /// Retrieves human-readable name of the context menu item.
    /// </summary>
    virtual void get_item_name(unsigned index, pfc::string_base & itemName) final
    {
        if (index == 0)
            itemName = PreviewCommandName;
    }

    /// <summary>
    /// Retrieves GUID of the context menu item.
    /// </summary>
    virtual GUID get_item_guid(unsigned int index) final
    {
        if (index == 0)
            return PreviewCommandGUID;

        return pfc::guid_null;
    }

    /// <summary>
    /// Retrieves item's description to show in the status bar. Set p_out to the string to be displayed and return true if you provide a description, return false otherwise.
    /// </summary>
    virtual bool get_item_description(unsigned index, pfc::string_base & itemDescription) final
    {
        if (index != 0)
            return false;

        itemDescription = PreviewCommandDescription;

        return true;
    }
#pragma endregion

#pragma region("contextmenu_item_v2 interface")
    /// <summary>
    /// Gets the parent of all our menu items.
    /// </summary>
    virtual GUID get_parent() final
    {
        return _ContextMenuGUID;
    }
#pragma endregion

#pragma region("contextmenu_item_simple interface")
    /// <summary>
    /// Executes the specified command
    /// </summary>
    virtual void context_command(unsigned index, metadb_handle_list_cref list, const GUID &) final
    {
        if (index != 0)
            FB2K_BugCheck();

        PreviewCommand(list);
    }
#pragma endregion
};

// Embed the command in the root of the context menu but separated from other commands.
static contextmenu_group_factory _ContextMenuGroup(_ContextMenuGUID, contextmenu_groups::root, 0);

FB2K_SERVICE_FACTORY(ContextMenuHandler);
#pragma endregion
}
