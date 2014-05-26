#ifndef PREFERENCESFRAME_H
#define PREFERENCESFRAME_H

#include "wxfb.h"

class PreferencesFrame : public PreferencesFrame_
{
    public:
        PreferencesFrame(wxWindow* parent = nullptr);
        virtual ~PreferencesFrame();

    protected:
        void Settingsframe_OnActivate( wxActivateEvent& event ) override;
		void mChkbUseTabsOnCheckBox( wxCommandEvent& event ) override;
		void mBtnSaveOnButtonClick( wxCommandEvent& event ) override;
		void mBtnCancelOnButtonClick( wxCommandEvent& event ) override;

    private:
};

#endif // PREFERENCESFRAME_H
