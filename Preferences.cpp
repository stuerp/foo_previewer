
/** $VER: Preferences.cpp (2022.12.11) P. Stuer **/

#include "framework.h"

#include "Support.h"

#pragma hdrstop

#pragma region("Preferences")
static constexpr GUID StartTimeTypeSettingGUID = {0xde897f39,0x305a,0x480a,{0xb3,0xf0,0xcc,0x0b,0xb7,0xdc,0x43,0x73}}; // {de897f39-305a-480a-b3f0-cc0bb7dc4373}
static constexpr GUID StartTimeSettingInSecGUID = {0x599f7ea8,0xa066,0x4882,{0x9a,0x0f,0x99,0xfe,0xe7,0xe4,0x7c,0x82}}; // {599f7ea8-a066-4882-9a0f-99fee7e47c82}
static constexpr GUID StartTimeSettingAsPercentageGUID = {0xd0e04101,0xeec2,0x43f8,{0xb8,0x8b,0x2f,0xa4,0xf8,0x8f,0x3a,0x02}}; // {d0e04101-eec2-43f8-b88b-2fa4f88f3a02}
static constexpr GUID PreviewLengthInSecGUID = {0x53c995f8,0x7496,0x418b,{0xbc,0x13,0xbb,0x07,0xe1,0x7e,0x98,0x28}}; // {53c995f8-7496-418b-bc13-bb07e17e9828}

static constexpr UINT StartTimeTypeDefaultValue = (UINT)StartTimeTypes::Seconds;
static constexpr const char StartTimeInSecDefaultValue[] = "0.0";
static constexpr const char StartTimeAsPercentageDefaultValue[] = "50.0";
static constexpr const char PreviewLengthInSecDefaultValue[] = "61.0";

cfg_uint StartTimeTypeSetting(StartTimeTypeSettingGUID, StartTimeTypeDefaultValue);
cfg_string StartTimeInSecSetting(StartTimeSettingInSecGUID, StartTimeInSecDefaultValue);
cfg_string StartTimeAsPercentageSetting(StartTimeSettingAsPercentageGUID, StartTimeAsPercentageDefaultValue);
cfg_string PreviewLengthInSecSetting(PreviewLengthInSecGUID, PreviewLengthInSecDefaultValue);
#pragma endregion

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
        StartTimeTypeSetting = _StartTimeTypeList.GetCurSel();

        pfc::string8 Text;

        {
            ::uGetDlgItemText(m_hWnd, IDC_START_TIME, Text);

            if (StartTimeTypeSetting == StartTimeTypes::Seconds)
                StartTimeInSecSetting = pfc::format_float(::atof(Text), 0, 1);
            else
            if (StartTimeTypeSetting == StartTimeTypes::Percentage)
                StartTimeAsPercentageSetting = pfc::format_float(::atof(Text), 0, 1);
        }

        {
            ::uGetDlgItemText(m_hWnd, IDC_PREVIEW_LENGTH, Text);

            PreviewLengthInSecSetting = pfc::format_float(::atof(Text), 0, 1);
        }

        OnChanged();
    }

    /// <summary>
    /// Resets this page's content to the default values. Does not apply any changes - lets user preview the changes before hitting "apply".
    /// </summary>
    virtual void reset() final
    {
        _StartTimeTypeList.SetCurSel(StartTimeTypes::Seconds);

        ::uSetDlgItemText(m_hWnd, IDC_START_TIME, StartTimeInSecDefaultValue);
        ::uSetDlgItemText(m_hWnd, IDC_START_TIME_UNIT, "s");

        ::uSetDlgItemText(m_hWnd, IDC_PREVIEW_LENGTH, PreviewLengthInSecDefaultValue);

        OnChanged();
    }
#pragma endregion

    //WTL message map
    BEGIN_MSG_MAP_EX(Preferences)
        MSG_WM_INITDIALOG(OnInitDialog)
//      MSG_WM_CTLCOLORDLG(OnDrawBackground)
        COMMAND_HANDLER_EX(IDC_START_TIME_TYPE, CBN_SELCHANGE, OnSelectionChanged)
        COMMAND_HANDLER_EX(IDC_START_TIME, EN_CHANGE, OnEditChange)
    END_MSG_MAP()

private:
    /// <summary>
    /// Initializes the dialog.
    /// </summary>
    BOOL OnInitDialog(CWindow, LPARAM) noexcept
    {
        _DarkModeHooks.AddDialogWithControls(*this);

        {
            _StartTimeTypeList = (CComboBox)GetDlgItem(IDC_START_TIME_TYPE);

            _StartTimeTypeList.AddString(L"In seconds");
            _StartTimeTypeList.AddString(L"As percentage of track length");
            _StartTimeTypeList.AddString(L"Random");

            _StartTimeTypeList.SetCurSel(StartTimeTypeSetting);
        }

        _StartTimeInSec = StartTimeInSecSetting;
        _StartTimeAsPercentage = StartTimeAsPercentageSetting;
        _PreviewLengthInSec = PreviewLengthInSecSetting;

        UpdateDialog();

        return FALSE;
    }

    LRESULT OnDrawBackground(HDC, HWND) const noexcept
    {
        return (LRESULT) ::CreateSolidBrush(RGB(0, 0, 255));
    }

    /// <summary>
    /// Handles a combobox change.
    /// </summary>
    void OnSelectionChanged(UINT, int, CWindow) noexcept
    {
        UpdateDialog();

        OnChanged();
    }

    /// <summary>
    /// Handles a textbox change.
    /// </summary>
    void OnEditChange(UINT, int, CWindow) noexcept
    {
        OnChanged();
    }

    /// <summary>
    /// Returns whether our dialog content is different from the current configuration (whether the apply button should be enabled or not)
    /// </summary>
    bool HasChanged() noexcept
    {
        int StartTimeType = _StartTimeTypeList.GetCurSel();

        {
            if (StartTimeType != (int)StartTimeTypeSetting)
                return true;
        }

        pfc::string8 Text;

        {
            ::uGetDlgItemText(m_hWnd, IDC_START_TIME, Text);

            if (!IsNumber<double>(Text.c_str()))
                return false;

            double Value = ::strtod(Text.c_str(), nullptr);

            if (StartTimeType == StartTimeTypes::Seconds)
            {
                if (Value < 0.0)
                    return false;

                _StartTimeInSec = Text;
            }
            else
            if (StartTimeType == StartTimeTypes::Percentage)
            {
                if ((Value < 0.0) || (Value > 100.0))
                    return false;

                _StartTimeAsPercentage = Text;
            }
        }

        {
            ::uGetDlgItemText(m_hWnd, IDC_PREVIEW_LENGTH, Text);

            if (!IsNumber<double>(Text.c_str()))
                return false;

            double Value = ::strtod(Text.c_str(), nullptr);

            if (Value < 0.0)
                return false;

            _PreviewLengthInSec = Text;
        }

        return (_StartTimeInSec != StartTimeInSecSetting) || (_StartTimeAsPercentage != StartTimeAsPercentageSetting) || (_PreviewLengthInSec != PreviewLengthInSecSetting);
    }

    /// <summary>
    /// Tells the host that our state has changed to enable/disable the apply button appropriately.
    /// </summary>
    void OnChanged() const noexcept
    {
        _Callback->on_state_changed();
    }

    /// <summary>
    /// Updates the appearance of the dialog according to the values of the settings.
    /// </summary>
    void UpdateDialog() const noexcept
    {
        StartTimeTypes StartTimeType = (StartTimeTypes)_StartTimeTypeList.GetCurSel();

        {
            auto hStartTime = GetDlgItem(IDC_START_TIME);
            auto hStartTimeUnit = GetDlgItem(IDC_START_TIME_UNIT);

            switch (StartTimeType)
            {
                case StartTimeTypes::Seconds:
                {
                    ::uSetWindowText(hStartTime, _StartTimeInSec);
                    ::uSetWindowText(hStartTimeUnit, "s");

                    ::uEnableWindow(hStartTime, TRUE);
                    ::uEnableWindow(hStartTimeUnit, TRUE);
                    break;
                }

                case StartTimeTypes::Percentage:
                {
                    ::uSetWindowText(hStartTime, _StartTimeAsPercentage);
                    ::uSetWindowText(hStartTimeUnit, "%");

                    ::uEnableWindow(hStartTime, TRUE);
                    ::uEnableWindow(hStartTimeUnit, TRUE);
                    break;
                }

                case StartTimeTypes::Random:
                {
                    ::uEnableWindow(hStartTime, FALSE);
                    ::uEnableWindow(hStartTimeUnit, FALSE);
                    break;
                }
            }
        }

        {
            ::uSetDlgItemText(m_hWnd, IDC_PREVIEW_LENGTH, _PreviewLengthInSec);
        }
    }

private:
    const preferences_page_callback::ptr _Callback;

    fb2k::CDarkModeHooks _DarkModeHooks;

    CComboBox _StartTimeTypeList;
    pfc::string8 _StartTimeInSec;
    pfc::string8 _StartTimeAsPercentage;
    pfc::string8 _PreviewLengthInSec;
};

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

/// <summary>
/// Gets the length of the preview period in sec.
/// </summary>
double GetPreviewLength()
{
    return ::atof(PreviewLengthInSecSetting);
}

/// <summary>
/// Gets the start time type of the preview period.
/// </summary>
StartTimeTypes GetStartTimeType()
{
    return (StartTimeTypes)(t_uint)StartTimeTypeSetting;
}

/// <summary>
/// Gets the start time of the preview period in sec.
/// </summary>
double GetPreviewStartTimeInSec()
{
    return ::atof(StartTimeInSecSetting);
}

/// <summary>
/// Gets the start time of the preview period as percentage of the track length.
/// </summary>
double GetPreviewStartTimeAsPercentage()
{
    return ::atof(StartTimeAsPercentageSetting);
}
