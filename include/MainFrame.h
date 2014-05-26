#ifndef MAINFRAME_H
#define MAINFRAME_H

#include "wxfb.h"

#include <string>
#include <vector>

using namespace std;

class ExtractedQuote
{
    public:
        ExtractedQuote(size_t position, size_t length, const string& text);

        size_t getPosition() { return mPosition; }
        size_t getLength() { return mLength; }
        string getText() { return mText; }

    protected:
    private:
        size_t mPosition;
        size_t mLength;
        string mText;
};

class MainFrame : public MainFrame_
{
    public:
        MainFrame(wxWindow* parent = nullptr);
        virtual ~MainFrame();

    protected:
        virtual void MainFrame_OnActivate(wxActivateEvent& event) override;
        virtual void mFilepInputOnFileChanged(wxFileDirPickerEvent& event) override;
		virtual void mToolbarReloadOnToolClicked(wxCommandEvent& event) override;
		virtual void mToolbarFormatOnToolClicked(wxCommandEvent& event) override;
		virtual void mToolbarSaveOnToolClicked(wxCommandEvent& event) override;
        virtual void mMenubarFileExitOnMenuSelection(wxCommandEvent& event) override;
		virtual void mMenubarEditPreferencesOnMenuSelection(wxCommandEvent& event) override;
		virtual void mMenubarHelpAboutOnMenuSelection(wxCommandEvent& event) override;

    private:
        void onInit();
        void load();
        void save();
        void format();

        bool mInitialized = false;

        vector<string> mKeywords;
};

#endif // MAINFRAME_H
