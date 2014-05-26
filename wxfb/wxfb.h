///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Feb 26 2014)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __WXFB_H__
#define __WXFB_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/filepicker.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/toolbar.h>
#include <wx/statusbr.h>
#include <wx/menu.h>
#include <wx/frame.h>
#include <wx/checkbox.h>
#include <wx/stattext.h>
#include <wx/button.h>
#include <wx/gauge.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////

#define idMainFrame 1000
#define idFilepInput 1001
#define idToolbarReload 1002
#define idToolbarEvaluate 1003
#define idToolbarSave 1004
#define idPreferencesFrame 1005
#define idAboutDialog 1006

///////////////////////////////////////////////////////////////////////////////
/// Class MainFrame_
///////////////////////////////////////////////////////////////////////////////
class MainFrame_ : public wxFrame 
{
	private:
	
	protected:
		wxPanel* m_panel2;
		wxFilePickerCtrl* mFilepInput;
		wxTextCtrl* mTxtctrlInput;
		wxFilePickerCtrl* mFilepOutput;
		wxTextCtrl* mTxtctrlOutput;
		wxToolBar* mToolbar;
		wxStatusBar* mStatusBar;
		wxMenuBar* mMenubar;
		wxMenu* mMenubarFile;
		wxMenu* mMenubarEdit;
		wxMenu* mMenubarHelp;
		
		// Virtual event handlers, overide them in your derived class
		virtual void MainFrame_OnActivate( wxActivateEvent& event ) { event.Skip(); }
		virtual void mFilepInputOnFileChanged( wxFileDirPickerEvent& event ) { event.Skip(); }
		virtual void mToolbarReloadOnToolClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void mToolbarFormatOnToolClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void mToolbarSaveOnToolClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void mMenubarFileExitOnMenuSelection( wxCommandEvent& event ) { event.Skip(); }
		virtual void mMenubarEditPreferencesOnMenuSelection( wxCommandEvent& event ) { event.Skip(); }
		virtual void mMenubarHelpAboutOnMenuSelection( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		MainFrame_( wxWindow* parent, wxWindowID id = idMainFrame, const wxString& title = wxT("Rapidformat"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 800,600 ), long style = wxCLOSE_BOX|wxDEFAULT_FRAME_STYLE|wxMAXIMIZE|wxMAXIMIZE_BOX|wxMINIMIZE_BOX|wxTAB_TRAVERSAL );
		
		~MainFrame_();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class PreferencesFrame_
///////////////////////////////////////////////////////////////////////////////
class PreferencesFrame_ : public wxFrame 
{
	private:
	
	protected:
		wxPanel* m_panel1;
		wxCheckBox* mChkbUseTabs;
		wxStaticText* mStattxtSpaces;
		wxTextCtrl* mTxtctrlSpaceCount;
		wxButton* mBtnSave;
		wxButton* mBtnCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void Settingsframe_OnActivate( wxActivateEvent& event ) { event.Skip(); }
		virtual void mChkbUseTabsOnCheckBox( wxCommandEvent& event ) { event.Skip(); }
		virtual void mBtnSaveOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void mBtnCancelOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		PreferencesFrame_( wxWindow* parent, wxWindowID id = idPreferencesFrame, const wxString& title = wxT("Preferences"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		
		~PreferencesFrame_();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class ProgressDialog_
///////////////////////////////////////////////////////////////////////////////
class ProgressDialog_ : public wxDialog 
{
	private:
	
	protected:
		wxGauge* mGauge;
	
	public:
		
		ProgressDialog_( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0 ); 
		~ProgressDialog_();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class AboutDialog_
///////////////////////////////////////////////////////////////////////////////
class AboutDialog_ : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText2;
	
	public:
		
		AboutDialog_( wxWindow* parent, wxWindowID id = idAboutDialog, const wxString& title = wxT("About"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE ); 
		~AboutDialog_();
	
};

#endif //__WXFB_H__
