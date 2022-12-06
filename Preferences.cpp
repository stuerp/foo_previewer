
/** $VER: Preferences.cpp (2022.12.05) P. Stuer **/

#include "framework.h"

#pragma hdrstop

static constexpr GUID StartTimeTypeSettingGUID = {0xde897f39,0x305a,0x480a,{0xb3,0xf0,0xcc,0x0b,0xb7,0xdc,0x43,0x73}}; // {de897f39-305a-480a-b3f0-cc0bb7dc4373}
static constexpr GUID StartTimeSettingInSecGUID = {0x599f7ea8,0xa066,0x4882,{0x9a,0x0f,0x99,0xfe,0xe7,0xe4,0x7c,0x82}}; // {599f7ea8-a066-4882-9a0f-99fee7e47c82}
static constexpr GUID StartTimeSettingPercentageGUID = {0xd0e04101,0xeec2,0x43f8,{0xb8,0x8b,0x2f,0xa4,0xf8,0x8f,0x3a,0x02}}; // {d0e04101-eec2-43f8-b88b-2fa4f88f3a02}

static constexpr UINT StartTimeTypeDefaultValue = 0;
static constexpr const char StartTimeInSecDefaultValue[] = "61.0";
static constexpr const char StartTimePercentageDefaultValue[] = "50.0";

static cfg_uint StartTimeTypeSetting(StartTimeTypeSettingGUID, StartTimeTypeDefaultValue);
static cfg_string StartTimeInSecSetting(StartTimeSettingInSecGUID, StartTimeInSecDefaultValue);
static cfg_string StartTimePercentageSetting(StartTimeSettingInSecGUID, StartTimePercentageDefaultValue);

/// <summary>
/// Implements the preferences page for the component.
/// </summary>
class Preferences : public CDialogImpl<Preferences>, public preferences_page_instance
{
public:
    Preferences(preferences_page_callback::ptr callback) : _Callback(callback), m_bMsgHandled(FALSE) { }

    enum
    {
        IDD = IDD_PREFERENCES
    };

#pragma region("preferences_page_instance")
    /// <summary>
    /// Returns a combination of preferences_state constants.
    /// </summary>
    virtual t_uint32 get_state() final
    {
        t_uint32 State = preferences_state::resettable | preferences_state::dark_mode_supported;

        if (HasChanged())
            State |= preferences_state::changed;

        return State;
    }

    /// <summary>
    /// Applies the changes to the preferences.
    /// </summary>
    virtual void apply() final
    {
        auto StartTimeTypeList = (CComboBox)GetDlgItem(IDC_START_TIME_TYPE);

        int StartTimeType = StartTimeTypeList.GetCurSel();

        pfc::string8 StartTime;

        ::uGetDlgItemText(m_hWnd, IDC_START_TIME, StartTime);

        if (StartTimeType == 1)
            StartTimeInSecSetting = StartTime;
        else
        if (StartTimeType == 2)
            StartTimePercentageSetting = StartTime;

        OnChanged();
    }

    /// <summary>
    /// Resets this page's content to the default values. Does not apply any changes - lets user preview the changes before hitting "apply".
    /// </summary>
    virtual void reset() final
    {
        auto StartTimeTypeList = (CComboBox)GetDlgItem(IDC_START_TIME_TYPE);

        OnChanged();
    }
#pragma endregion

    //WTL message map
    BEGIN_MSG_MAP_EX(Preferences)
        MSG_WM_INITDIALOG(OnInitDialog)
//      MSG_WM_CTLCOLORDLG(OnDrawBackground)
        COMMAND_HANDLER_EX(IDC_START_TIME_TYPE, CBN_SELCHANGE, OnStartTimeTypeChange)
        COMMAND_HANDLER_EX(IDC_START_TIME, EN_CHANGE, OnEditChange)
    END_MSG_MAP()

    LRESULT OnDrawBackground(HDC, HWND)
    {
        return (LRESULT) ::CreateSolidBrush(RGB(0, 0, 255));
    }

    void OnStartTimeTypeChange(UINT, int, CWindow)
    {
        Adjust();
    }

private:
    BOOL OnInitDialog(CWindow, LPARAM);
    void OnEditChange(UINT, int, CWindow);
    bool HasChanged() const;
    void OnChanged() const;

    void Adjust();

private:
    const preferences_page_callback::ptr _Callback;

    fb2k::CDarkModeHooks _DarkModeHooks;
};

/// <summary>
/// Initializes the dialog.
/// </summary>
BOOL Preferences::OnInitDialog(CWindow, LPARAM)
{
    _DarkModeHooks.AddDialogWithControls(*this);

    int StartTimeType = StartTimeTypeSetting;

    {
        auto StartTimeTypeList = (CComboBox)GetDlgItem(IDC_START_TIME_TYPE);

        StartTimeTypeList.AddString(L"In seconds");
        StartTimeTypeList.AddString(L"As percentage of track length");
        StartTimeTypeList.AddString(L"Random");

        StartTimeTypeList.SetCurSel(StartTimeType);
    }

    Adjust();

    return FALSE;
}

void Preferences::Adjust()
{
    int StartTimeType = SendDlgItemMessage(IDC_START_TIME_TYPE, CB_GETCURSEL);

    {
        auto hStartTime = GetDlgItem(IDC_START_TIME);
        auto hStartTimeUnit = GetDlgItem(IDC_START_TIME_UNIT);

        switch (StartTimeType)
        {
            case 0:
            {
                ::uSetDlgItemText(m_hWnd, IDC_START_TIME, StartTimeInSecSetting);
                ::uSetWindowText(hStartTimeUnit, "s");

                ::uEnableWindow(hStartTime, TRUE);
                ::uEnableWindow(hStartTimeUnit, TRUE);
                break;
            }

            case 1:
            {
                ::uSetDlgItemText(m_hWnd, IDC_START_TIME, StartTimePercentageSetting);
                ::uSetWindowText(hStartTimeUnit, "%");

                ::uEnableWindow(hStartTime, TRUE);
                ::uEnableWindow(hStartTimeUnit, TRUE);
                break;
            }

            case 2:
            {
                ::uEnableWindow(hStartTime, FALSE);
                ::uEnableWindow(hStartTimeUnit, FALSE);
                break;
            }
        }
    }
}

/// <summary>
/// 
/// </summary>
void Preferences::OnEditChange(UINT, int, CWindow)
{
    OnChanged();
}

/// <summary>
/// Returns whether our dialog content is different from the current configuration (whether the apply button should be enabled or not)
/// </summary>
bool Preferences::HasChanged() const
{
    pfc::string8 StartTime;

    ::uGetDlgItemText(m_hWnd, IDC_START_TIME, StartTime);

    return (StartTime != StartTimeInSecSetting);
}

/// <summary>
/// Tells the host that our state has changed to enable/disable the apply button appropriately.
/// </summary>
void Preferences::OnChanged() const
{
    _Callback->on_state_changed();
}

#pragma region("PreferencesPage")
/// <summary>
/// preferences_page_impl<> helper deals with instantiation of our dialog; inherits from preferences_page_v3.
/// </summary>
class PreferencesPage : public preferences_page_impl<Preferences>
{
public:
    const char * get_name()
    {
        return "Preview";
    }

    GUID get_guid()
    {
        static constexpr GUID _GUID = {0xaa630707,0x1fca,0x4672,{0x98,0x2c,0x88,0xe3,0x71,0xcb,0xb8,0xfc}}; // {aa630707-1fca-4672-982c-88e371cbb8fc}

        return _GUID;
    }

    GUID get_parent_guid()
    {
        return guid_playback;
    }
};

static preferences_page_factory_t<PreferencesPage> _PreferencesPageFactory;
#pragma endregion
