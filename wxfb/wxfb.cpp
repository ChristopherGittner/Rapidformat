///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Feb 26 2014)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "wxfb.h"

///////////////////////////////////////////////////////////////////////////

MainFrame_::MainFrame_( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxHORIZONTAL );
	
	m_panel2 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxVERTICAL );
	
	mFilepInput = new wxFilePickerCtrl( m_panel2, idFilepInput, wxEmptyString, wxT("Select the input File"), wxT("*"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE );
	bSizer7->Add( mFilepInput, 0, wxALL|wxEXPAND, 5 );
	
	mTxtctrlInput = new wxTextCtrl( m_panel2, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_DONTWRAP|wxTE_MULTILINE|wxTE_READONLY );
	mTxtctrlInput->SetFont( wxFont( 10, 76, 90, 90, false, wxT("Monospace") ) );
	
	bSizer7->Add( mTxtctrlInput, 1, wxALL|wxEXPAND, 5 );
	
	
	bSizer13->Add( bSizer7, 1, wxEXPAND, 0 );
	
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxVERTICAL );
	
	mFilepOutput = new wxFilePickerCtrl( m_panel2, idFilepInput, wxEmptyString, wxT("Select the output File"), wxT("*"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE );
	bSizer8->Add( mFilepOutput, 0, wxALL|wxEXPAND, 5 );
	
	mTxtctrlOutput = new wxTextCtrl( m_panel2, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_DONTWRAP|wxTE_MULTILINE );
	mTxtctrlOutput->SetFont( wxFont( 10, 76, 90, 90, false, wxT("Monospace") ) );
	
	bSizer8->Add( mTxtctrlOutput, 1, wxALL|wxEXPAND, 5 );
	
	
	bSizer13->Add( bSizer8, 1, wxEXPAND, 0 );
	
	
	m_panel2->SetSizer( bSizer13 );
	m_panel2->Layout();
	bSizer13->Fit( m_panel2 );
	bSizer1->Add( m_panel2, 1, wxEXPAND | wxALL, 0 );
	
	
	this->SetSizer( bSizer1 );
	this->Layout();
	mToolbar = this->CreateToolBar( wxTB_HORIZONTAL, wxID_ANY ); 
	mToolbar->AddTool( idToolbarReload, wxT("Reload"), wxArtProvider::GetBitmap( wxART_REDO, wxART_TOOLBAR ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxT("Reload input File"), NULL ); 
	
	mToolbar->AddTool( idToolbarEvaluate, wxT("Evaluate"), wxArtProvider::GetBitmap( wxART_EXECUTABLE_FILE, wxART_TOOLBAR ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxT("Format"), NULL ); 
	
	mToolbar->AddTool( idToolbarSave, wxT("Save"), wxArtProvider::GetBitmap( wxART_FILE_SAVE, wxART_TOOLBAR ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxT("Save output to File"), NULL ); 
	
	mToolbar->Realize(); 
	
	mStatusBar = this->CreateStatusBar( 1, wxST_SIZEGRIP, wxID_ANY );
	mMenubar = new wxMenuBar( 0 );
	mMenubarFile = new wxMenu();
	wxMenuItem* mMenubarFileExit;
	mMenubarFileExit = new wxMenuItem( mMenubarFile, wxID_ANY, wxString( wxT("Exit") ) , wxEmptyString, wxITEM_NORMAL );
	mMenubarFile->Append( mMenubarFileExit );
	
	mMenubar->Append( mMenubarFile, wxT("File") ); 
	
	mMenubarEdit = new wxMenu();
	wxMenuItem* mMenubarEditPreferences;
	mMenubarEditPreferences = new wxMenuItem( mMenubarEdit, wxID_ANY, wxString( wxT("Preferences") ) , wxEmptyString, wxITEM_NORMAL );
	mMenubarEdit->Append( mMenubarEditPreferences );
	
	mMenubar->Append( mMenubarEdit, wxT("Edit") ); 
	
	mMenubarHelp = new wxMenu();
	wxMenuItem* mMenubarHelpAbout;
	mMenubarHelpAbout = new wxMenuItem( mMenubarHelp, wxID_ANY, wxString( wxT("About") ) , wxEmptyString, wxITEM_NORMAL );
	mMenubarHelp->Append( mMenubarHelpAbout );
	
	mMenubar->Append( mMenubarHelp, wxT("Help") ); 
	
	this->SetMenuBar( mMenubar );
	
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_ACTIVATE, wxActivateEventHandler( MainFrame_::MainFrame_OnActivate ) );
	mFilepInput->Connect( wxEVT_COMMAND_FILEPICKER_CHANGED, wxFileDirPickerEventHandler( MainFrame_::mFilepInputOnFileChanged ), NULL, this );
	this->Connect( idToolbarReload, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainFrame_::mToolbarReloadOnToolClicked ) );
	this->Connect( idToolbarEvaluate, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainFrame_::mToolbarFormatOnToolClicked ) );
	this->Connect( idToolbarSave, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainFrame_::mToolbarSaveOnToolClicked ) );
	this->Connect( mMenubarFileExit->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame_::mMenubarFileExitOnMenuSelection ) );
	this->Connect( mMenubarEditPreferences->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame_::mMenubarEditPreferencesOnMenuSelection ) );
	this->Connect( mMenubarHelpAbout->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame_::mMenubarHelpAboutOnMenuSelection ) );
}

MainFrame_::~MainFrame_()
{
	// Disconnect Events
	this->Disconnect( wxEVT_ACTIVATE, wxActivateEventHandler( MainFrame_::MainFrame_OnActivate ) );
	mFilepInput->Disconnect( wxEVT_COMMAND_FILEPICKER_CHANGED, wxFileDirPickerEventHandler( MainFrame_::mFilepInputOnFileChanged ), NULL, this );
	this->Disconnect( idToolbarReload, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainFrame_::mToolbarReloadOnToolClicked ) );
	this->Disconnect( idToolbarEvaluate, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainFrame_::mToolbarFormatOnToolClicked ) );
	this->Disconnect( idToolbarSave, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainFrame_::mToolbarSaveOnToolClicked ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame_::mMenubarFileExitOnMenuSelection ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame_::mMenubarEditPreferencesOnMenuSelection ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame_::mMenubarHelpAboutOnMenuSelection ) );
	
}

PreferencesFrame_::PreferencesFrame_( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxVERTICAL );
	
	m_panel1 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxVERTICAL );
	
	mChkbUseTabs = new wxCheckBox( m_panel1, wxID_ANY, wxT("Use Tabs"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer7->Add( mChkbUseTabs, 0, wxALL, 5 );
	
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxHORIZONTAL );
	
	mStattxtSpaces = new wxStaticText( m_panel1, wxID_ANY, wxT("Spaces"), wxDefaultPosition, wxDefaultSize, 0 );
	mStattxtSpaces->Wrap( -1 );
	bSizer8->Add( mStattxtSpaces, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	mTxtctrlSpaceCount = new wxTextCtrl( m_panel1, wxID_ANY, wxT("2"), wxDefaultPosition, wxSize( 30,-1 ), 0 );
	bSizer8->Add( mTxtctrlSpaceCount, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer7->Add( bSizer8, 1, wxEXPAND, 5 );
	
	
	bSizer11->Add( bSizer7, 0, 0, 5 );
	
	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxHORIZONTAL );
	
	mBtnSave = new wxButton( m_panel1, wxID_ANY, wxT("Save"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer9->Add( mBtnSave, 0, wxALL, 5 );
	
	mBtnCancel = new wxButton( m_panel1, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer9->Add( mBtnCancel, 0, wxALL, 5 );
	
	
	bSizer11->Add( bSizer9, 1, wxEXPAND, 5 );
	
	
	m_panel1->SetSizer( bSizer11 );
	m_panel1->Layout();
	bSizer11->Fit( m_panel1 );
	bSizer6->Add( m_panel1, 1, wxEXPAND | wxALL, 0 );
	
	
	this->SetSizer( bSizer6 );
	this->Layout();
	bSizer6->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_ACTIVATE, wxActivateEventHandler( PreferencesFrame_::Settingsframe_OnActivate ) );
	mChkbUseTabs->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( PreferencesFrame_::mChkbUseTabsOnCheckBox ), NULL, this );
	mBtnSave->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PreferencesFrame_::mBtnSaveOnButtonClick ), NULL, this );
	mBtnCancel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PreferencesFrame_::mBtnCancelOnButtonClick ), NULL, this );
}

PreferencesFrame_::~PreferencesFrame_()
{
	// Disconnect Events
	this->Disconnect( wxEVT_ACTIVATE, wxActivateEventHandler( PreferencesFrame_::Settingsframe_OnActivate ) );
	mChkbUseTabs->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( PreferencesFrame_::mChkbUseTabsOnCheckBox ), NULL, this );
	mBtnSave->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PreferencesFrame_::mBtnSaveOnButtonClick ), NULL, this );
	mBtnCancel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PreferencesFrame_::mBtnCancelOnButtonClick ), NULL, this );
	
}

ProgressDialog_::ProgressDialog_( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxVERTICAL );
	
	mGauge = new wxGauge( this, wxID_ANY, 100, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL|wxGA_SMOOTH );
	mGauge->SetValue( 0 ); 
	bSizer9->Add( mGauge, 0, wxALL, 5 );
	
	
	this->SetSizer( bSizer9 );
	this->Layout();
	bSizer9->Fit( this );
	
	this->Centre( wxBOTH );
}

ProgressDialog_::~ProgressDialog_()
{
}

AboutDialog_::AboutDialog_( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText2 = new wxStaticText( this, wxID_ANY, wxT("RapidFormat\n\nChristopher Gittner"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
	m_staticText2->Wrap( -1 );
	bSizer5->Add( m_staticText2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	this->SetSizer( bSizer5 );
	this->Layout();
	bSizer5->Fit( this );
	
	this->Centre( wxBOTH );
}

AboutDialog_::~AboutDialog_()
{
}
