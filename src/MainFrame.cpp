#include "MainFrame.h"

#include <fstream>
#include <regex>
#include <thread>
#include <sstream>

#include <boost/bind.hpp>
#include <boost/locale.hpp>

#include <wx/wx.h>

#include "RapidformatApp.h"
#include "PreferencesFrame.h"
#include "Preferences.h"
#include "ProgressDialog.h"

wxDEFINE_EVENT(MY_NEW_TYPE, wxCommandEvent);

ExtractedQuote::ExtractedQuote(size_t position, size_t length, const wstring& text)
{
    mPosition = position;
    mLength = length;
    mText = text.substr(position, length);
}

MainFrame::MainFrame(wxWindow* parent) : MainFrame_(parent)
{
}

MainFrame::~MainFrame()
{
}

void MainFrame::MainFrame_OnActivate(wxActivateEvent& event)
{
    if(!mInitialized)
    {
        mInitialized = true;
        onInit();
    }
}

void MainFrame::mFilepInputOnFileChanged(wxFileDirPickerEvent& event)
{
    load();
}

void MainFrame::mToolbarReloadOnToolClicked(wxCommandEvent& event)
{
    load();
}

void MainFrame::mToolbarFormatOnToolClicked(wxCommandEvent& event)
{
    auto data = make_shared<FormatThreadData>();

    for(int i = 0; i != mTxtctrlInput->GetNumberOfLines(); ++i)
    {
		data->input.emplace_back(mTxtctrlInput->GetLineText(i));
    }

    data->keywords = mKeywords;
	if (Preferences::getInstance().getUseTabs())
	{
		data->indentationString = L"\t";
	}
	else
	{
		data->indentationString = wstring(Preferences::getInstance().getSpaceCount(), L' ');
	}

	mProgressDialog = new ProgressDialog(this);
	mProgressDialog->SetTitle("Formatting. Please Wait...");
	disableControls();

	thread t(format, data, this);
    t.detach();

	mProgressDialog->Show();
}

void MainFrame::mToolbarSaveOnToolClicked(wxCommandEvent& event)
{
    save();
}

void MainFrame::onInit()
{
    if(!Preferences::getInstance().readFromDisk())
    {
        wxMessageBox("Failed to load Config\nCreating new Config File", "Warning");
        Preferences::getInstance().saveToDisk();
    }

    mKeywords.clear();

    ifstream ifs("keywords.txt");

    if(!ifs.is_open())
    {
        wxMessageBox("Failed to open keywords.txt", "Error");
        Close();
        return;
    }

    string line;

    while(getline(ifs, line))
    {
        if(line.size() > 0 && line[0] != '#')
        {
            mKeywords.emplace_back(line.begin(), line.end());
        }
    }

    ifs.close();
}

void MainFrame::load()
{
    string inPath = mFilepInput->GetPath();

    if(inPath == "")
    {
        wxMessageBox("No input File specified", "Error");
        return;
    }

    #ifdef __LINUX__
        ifstream ifs(inPath);
    #else
        wifstream ifs(inPath);
    #endif // __LINUX__

    if(!ifs.is_open())
    {
        wxMessageBox("Failed to open input File " + inPath, "Error");
        return;
    }

    mTxtctrlInput->Clear();

    #ifdef __LINUX__
        string line;
    #else
        wstring line;
    #endif // __LINUX__

	wstring input;

	bool firstLine = true;
    while(getline(ifs, line))
    {
		if (!firstLine)
		{
			input += L"\n";
		}

		#ifdef __LINUX__
            for(unsigned char c : line)
            {
                input += c;
            }
		#else
            input += line;
		#endif // __LINUX__

		firstLine = false;
    }

	mTxtctrlInput->SetValue(input);

    /* Show Top of Text */
    mTxtctrlInput->ShowPosition(0);
}

void MainFrame::save()
{
    if(mTxtctrlOutput->GetLastPosition() == 0)
    {
        wxMessageBox("Nothing to Save", "Error");
        return;
    }

    string outPath = mFilepOutput->GetPath();

    if(outPath == "")
    {
        wxMessageBox("No output File specified", "Error");
        return;
    }

    #ifdef __LINUX__
        ofstream ofs(outPath);
    #else
        wofstream ofs(outPath);
    #endif // __LINUX__

    if(!ofs.is_open())
    {
        wxMessageBox("Failed to open output File " + outPath, "Error");
        return;
    }

    bool firstLine = true;
    for(int i = 0; i != mTxtctrlOutput->GetNumberOfLines(); ++i)
    {
        if(!firstLine)
        {
            ofs << endl;
        }
        #ifdef __LINUX__
            ofs << boost::locale::conv::from_utf<wchar_t>(mTxtctrlOutput->GetLineText(i), "Latin1");
        #else
            ofs << mTxtctrlOutput->GetLineText(i);
        #endif // __LINUX__
        firstLine = false;
    }
}

void MainFrame::disableControls()
{
	mToolbar->Disable();
}

void MainFrame::enableControls()
{
	mToolbar->Enable();
}

void MainFrame::format(shared_ptr<FormatThreadData> data, MainFrame* frame)
{
    data->output = L"";
	data->indentation = 0;
    data->indentationBelowZero = false;

    wregex trimWhitespace(L"^[ \\t]+|[ \\t]+$");
    wregex indentingExpression(L"\\b(CASE|DEFAULT|DO|ELSE|ERROR|FUNC|MODULE|PROC|SYSMODULE|TEST|THEN|TRAP)\\b");
    wregex dedentingExpression(L"\\b(CASE|DEFAULT|ELSE|ELSEIF|ENDFOR|ENDFUNC|ENDIF|ENDMODULE|ENDPROC|ENDTEST|ENDTRAP|ENDWHILE|ERROR)\\b");
    wregex stripQuotes(L"\"[^\"]*\"");
    vector<shared_ptr<wregex>> knownKeywordsExpressions;

    for(auto keyword : data->keywords)
    {
        knownKeywordsExpressions.push_back(make_shared<wregex>(L"\\b(" + keyword + L")\\b", regex_constants::icase));
    }

    for(size_t lineNumber = 0; lineNumber != data->input.size(); ++lineNumber)
    {
        wstring line = data->input[lineNumber];

        /* Remove Whitespace */
        line = regex_replace(line, trimWhitespace, L"");

        /* Extract Comment */
        wsmatch match;
        vector<ExtractedQuote> quotes;
        wstring strippedLine = line;

        while(regex_search(strippedLine, match, stripQuotes))
        {
            strippedLine.replace(match.position(0), match.length(0), match.length(0), ' ');
        }

        size_t commentStart = strippedLine.find('!');
        wstring comment = L"";

        if(commentStart != string::npos)
        {
            comment = line.substr(commentStart);
            line = line.substr(0, commentStart);
        }

        /* Extract Quotes */
        while(regex_search(line, match, stripQuotes))
        {
            quotes.emplace_back(match.position(0), match.length(0), line);
            line.erase(match.position(0), match.length(0));
        }

        /* Correct known Keywords */
        for(size_t i = 0; i != knownKeywordsExpressions.size(); ++i)
        {
            line = regex_replace(line, *(knownKeywordsExpressions[i]), data->keywords[i]);
        }

        /* Insert Quotes */
        for(auto quote = quotes.rbegin(); quote != quotes.rend(); ++quote)
        {
            line.insert(quote->getPosition(), quote->getText());
        }

        /* Apply Indentation */
        if(regex_search(line, dedentingExpression))
        {
            if(data->indentation > 0)
            {
                --data->indentation;
            }
            else
            {
                data->indentationBelowZero = true;
            }
        }

        for(size_t i = 0; i != data->indentation; ++i)
        {
            line = data->indentationString + line;
        }

        if(regex_search(line, indentingExpression))
        {
            ++data->indentation;
        }

		/* Attach Comment */
		line += comment;

		if (lineNumber != data->input.size() - 1)
        {
            data->output += line + "\n";
        }
        else
        {
            data->output += line;
        }

		int progress = ((double)lineNumber / (double)data->input.size()) * 100;
		wxTheApp->GetTopWindow()->GetEventHandler()->CallAfter(boost::bind(&MainFrame::onProgressUpdate, frame, progress));
    }

    wxTheApp->GetTopWindow()->GetEventHandler()->CallAfter(boost::bind(&MainFrame::onFormatDone, frame, data));
}

void MainFrame::onProgressUpdate(int progress)
{
	mProgressDialog->setProgress(progress);
}

void MainFrame::onFormatDone(shared_ptr<FormatThreadData> data)
{
    mTxtctrlOutput->Clear();

	mProgressDialog->Close();
	delete mProgressDialog;

	enableControls();

	mTxtctrlOutput->SetValue(data->output);

    /* Show Top of Text */
    mTxtctrlOutput->ShowPosition(0);

	if (data->indentation)
	{
		wxMessageBox("Indentation not 0 at EOF", "Warning");
	}

	if (data->indentationBelowZero)
	{
		wxMessageBox("Indentation went Below 0 while formatting", "Warning");
	}
}

void MainFrame::mMenubarFileExitOnMenuSelection(wxCommandEvent& event)
{
    Close();
}

void MainFrame::mMenubarEditPreferencesOnMenuSelection(wxCommandEvent& event)
{
    (new PreferencesFrame(this))->Show();
}

void MainFrame::mMenubarHelpAboutOnMenuSelection(wxCommandEvent& event)
{
    (new AboutDialog_(this))->ShowModal();
}
