#ifndef MAINFRAME_H
#define MAINFRAME_H

#include "wxfb.h"

#include <string>
#include <vector>
#include <memory>

class ProgressDialog;

using namespace std;

class ExtractedQuote
{
    public:
        ExtractedQuote(size_t position, size_t length, const wstring& text);

        size_t getPosition() { return mPosition; }
        size_t getLength() { return mLength; }
        wstring getText() { return mText; }

    protected:
    private:
        size_t mPosition;
        size_t mLength;
        wstring mText;
};

struct FormatThreadData
{
    vector<wstring> input;
    wstring output;
    vector<wstring> keywords;
    size_t indentation;
	string indentationString;
	bool indentationBelowZero;
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

		void disableControls();
		void enableControls();

        static void format(shared_ptr<FormatThreadData> data, MainFrame* frame);
		void onProgressUpdate(int progress);
		void onFormatDone(shared_ptr<FormatThreadData> data);

        bool mInitialized = false;

        vector<wstring> mKeywords;

		ProgressDialog* mProgressDialog = nullptr;
};

#endif // MAINFRAME_H
