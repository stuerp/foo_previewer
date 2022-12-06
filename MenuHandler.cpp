
/** $VER: MenuHandler.cpp (2022.12.05) P. Stuer **/

#include "framework.h"

#pragma hdrstop

namespace
{
    /// <summary>
    /// Provides the commands for the main menu.
    /// </summary>
    class MenuHandler : public mainmenu_commands
    {
    public:
        /// <summary>
        /// Retrieves number of implemented commands. Index parameter of other methods must be in 0....command_count-1 range.
        /// </summary>
        virtual t_uint32 get_command_count() final
        {
            return 1;
        }

        /// <summary>
        /// Retrieves the GUID of specified command.
        /// </summary>
        virtual GUID get_command(t_uint32 index) final
        {
            if (index == 0)
                return PreviewCommandGUID;

            return pfc::guid_null;
        }

        /// <summary>
        /// Retrieves the name of the menu item. For list of commands to assign keyboard shortcuts to etc.
        /// </summary>
        virtual void get_name(t_uint32 index, pfc::string_base & itemName) final
        {
            if (index == 0)
                itemName = PreviewCommandName;
        }

        /// <summary>
        /// Retrieves the description of the menu item for displaying in the statusbar for example.
        /// </summary>
        virtual bool get_description(t_uint32 index, pfc::string_base & itemDescription) final
        {
            if (index != 0)
                return false;

            itemDescription = PreviewCommandDescription;

            return true;
        }

        /// <summary>
        /// Retrieves the GUID of the menu these commands belong to.
        /// </summary>
        virtual GUID get_parent() final
        {
            return mainmenu_groups::playback;
        }

        /// <summary>
        /// Retrieves the sorting priority of the command; the lower the number, the higher in the menu your commands will appear.
        /// Third party components should use sorting_priority_base and up (values below are reserved for internal use). In case of equal priority, order is undefined.
        /// </summary>
        virtual t_uint32 get_sort_priority() final
        {
            return (t_uint32)sort_priority_dontcare;
        }

        /// <summary>
        /// Retrieves the display string and display flags to use when menu is about to be displayed.
        /// If returns false, menu item won't be displayed.
        /// You can create keyboard-shortcut-only commands by always returning false from get_display().
        /// </summary>
        virtual bool get_display(t_uint32 index, pfc::string_base & text, t_uint32 & flags) final
        {
            if (index == 0)
            {
                get_name(index, text);

                if (_IsPreviewing)
                    flags |= flag_checked;
                else
                    flags = 0;
            }

            return true;
        }

        /// <summary>
        /// Executes the command. callback parameter is reserved for future use and should be ignored / set to null pointer.
        /// </summary>
        virtual void execute(t_uint32 index, service_ptr_t<service_base>) final
        {
            if (index != 0)
                return;

            PreviewCommand();
        }
    };

    static mainmenu_commands_factory_t<MenuHandler> _MenuHandler;
}
