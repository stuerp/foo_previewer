
/** $VER: ContextMenuHandler.cpp (2022.12.05) P. Stuer **/

#include "framework.h"

#pragma hdrstop

namespace
{
// 
    // Identifier of our context menu group.
    static constexpr GUID MenuItemGUID = GUID_MENU_ITEM;

    // Embed the command in the root of the context menu but separated from other commands.
    static contextmenu_group_factory _ContextMenuGroup(MenuItemGUID, contextmenu_groups::root, 0);

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

    //! Instantiates a context menu item (including sub-node tree for items that contain dynamically-generated sub-items).
    //virtual contextmenu_item_node_root * instantiate_item(unsigned p_index, metadb_handle_list_cref p_data, const GUID & p_caller) = 0;

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
    /// Retrieves human-readable name of the context menu item.
    /// </summary>
    virtual void get_item_name(unsigned index, pfc::string_base & itemName) final
    {
        if (index == 0)
            itemName = PreviewCommandName;
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

    //! Controls default state of context menu preferences for this item: \n
    //! Return DEFAULT_ON to show this item in the context menu by default - useful for most cases. \n
    //! Return DEFAULT_OFF to hide this item in the context menu by default - useful for rarely used utility commands. \n
    //! Return FORCE_OFF to hide this item by default and prevent the user from making it visible (very rarely used). \n
    //! foobar2000 v1.6 and newer: FORCE_OFF items are meant for being shown only in the keyboard shortcut list, not anywhere else. \n
    //! Values returned by this method should be constant for this context menu item and not change later. Do not use this to conditionally hide the item - return false from get_display_data() instead.
    //virtual t_enabled_state get_enabled_state(unsigned p_index) = 0;

    //! Executes the menu item command without going thru the instantiate_item path. For items with dynamically-generated sub-items, p_node is identifies of the sub-item command to execute.
    //virtual void item_execute_simple(unsigned p_index, const GUID & p_node, metadb_handle_list_cref p_data, const GUID & p_caller) = 0;
#pragma endregion

#pragma region("contextmenu_item_v2 interface")
    //virtual double get_sort_priority();

    /// <summary>
    /// Gets the parent of all our menu items.
    /// </summary>
    virtual GUID get_parent() final
    {
        return MenuItemGUID;
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

    //virtual bool context_get_display(unsigned index, metadb_handle_list_cref list, pfc::string_base& text, unsigned& displayFlags, const GUID& caller);
#pragma endregion
    };

    static contextmenu_item_factory_t<ContextMenuHandler> _ContextMenuHandler;
}
