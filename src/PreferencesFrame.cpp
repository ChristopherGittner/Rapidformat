#include "PreferencesFrame.h"

#include <wx/wx.h>

#include <boost/lexical_cast.hpp>

#include "Preferences.h"

PreferencesFrame::PreferencesFrame(wxWindow* parent) : PreferencesFrame_(parent)
{
}

PreferencesFrame::~PreferencesFrame()
{
}

void PreferencesFrame::Settingsframe_OnActivate( wxActivateEvent& event )
{
    Preferences& preferences = Preferences::getInstance();

    mChkbUseTabs->SetValue(preferences.getUseTabs());
    mStattxtSpaces->Enable(!preferences.getUseTabs());
    mTxtctrlSpaceCount->Enable(!preferences.getUseTabs());
    mTxtctrlSpaceCount->SetValue(wxString::Format("%i", preferences.getSpaceCount()));
}

void PreferencesFrame::mChkbUseTabsOnCheckBox( wxCommandEvent& event )
{
    bool setVal = !mChkbUseTabs->GetValue();
    mStattxtSpaces->Enable(setVal);
    mTxtctrlSpaceCount->Enable(setVal);
}

void PreferencesFrame::mBtnSaveOnButtonClick( wxCommandEvent& event )
{
    Preferences& preferences = Preferences::getInstance();

    preferences.setUseTabs(mChkbUseTabs->GetValue());
    if(mTxtctrlSpaceCount->GetValue() != "")
    {
        preferences.setSpaceCount(boost::lexical_cast<int>(mTxtctrlSpaceCount->GetValue()));
    }

    if(preferences.saveToDisk())
    {
        Close();
    }
    else
    {
        wxMessageBox("Failed to save Preferences to Disk", "Error");
    }
}

void PreferencesFrame::mBtnCancelOnButtonClick( wxCommandEvent& event )
{
    Close();
}
