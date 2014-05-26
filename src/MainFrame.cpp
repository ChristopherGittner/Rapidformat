#include "MainFrame.h"

#include <fstream>
#include <regex>
#include <thread>
#include <sstream>

#include <boost/bind.hpp>

#include <wx/wx.h>

#include "RapidformatApp.h"
#include "PreferencesFrame.h"
#include "Preferences.h"
#include "ProgressDialog.h"

wxDEFINE_EVENT(MY_NEW_TYPE, wxCommandEvent);

ExtractedQuote::ExtractedQuote(size_t position, size_t length, const string& text)
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
		data->indentationString = "\t";
	}
	else
	{
		data->indentationString = string(Preferences::getInstance().getSpaceCount(), ' ');
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
            mKeywords.emplace_back(line);
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

    ifstream ifs(inPath);

    if(!ifs.is_open())
    {
        wxMessageBox("Failed to open input File " + inPath, "Error");
        return;
    }

    mTxtctrlInput->Clear();

    string line;
	string input;

	bool firstLine = true;
    while(getline(ifs, line))
    {
		if (!firstLine)
		{
			input += "\n";
		}
		input += line;
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

    ofstream ofs(outPath);

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
        ofs << mTxtctrlOutput->GetLineText(i);
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
    data->output.clear();
	data->indentation = 0;
    data->indentationBelowZero = false;

    regex trimWhitespace("^[ \\t]+|[ \\t]+$");
    regex indentingExpression("\\b(CASE|DEFAULT|DO|ELSE|ERROR|FUNC|MODULE|PROC|SYSMODULE|TEST|THEN|TRAP)\\b");
    regex dedentingExpression("\\b(CASE|DEFAULT|ELSE|ELSEIF|ENDFOR|ENDFUNC|ENDIF|ENDMODULE|ENDPROC|ENDTEST|ENDTRAP|ENDWHILE|ERROR)\\b");
    regex stripQuotes("\"[^\"]*\"");
    vector<shared_ptr<regex>> knownKeywordsExpressions;

    for(auto keyword : data->keywords)
    {
        knownKeywordsExpressions.push_back(make_shared<regex>("\\b(" + keyword + ")\\b", regex_constants::icase));
    }

    for(size_t lineNumber = 0; lineNumber != data->input.size(); ++lineNumber)
    {
        string line = data->input[lineNumber];

        /* Remove Whitespace */
        line = regex_replace(line, trimWhitespace, "");

        /* Extract Comment */
        smatch match;
        vector<ExtractedQuote> quotes;
        string strippedLine = line;

        while(regex_search(strippedLine, match, stripQuotes))
        {
            strippedLine.replace(match.position(0), match.length(0), match.length(0), ' ');
        }

        size_t commentStart = strippedLine.find('!');
        string comment = "";

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
            data->output.emplace_back(line + "\n");
        }
        else
        {
            data->output.emplace_back(line);
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

	string output;
	for (string line : data->output)
	{
		output += line;
	}

	mProgressDialog->Close();
	delete mProgressDialog;

	enableControls();

	mTxtctrlOutput->SetValue(output);

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
