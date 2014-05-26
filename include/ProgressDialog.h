#ifndef PROGRESSDIALOG_H
#define PROGRESSDIALOG_H

#include "wxfb.h"

#include <wx/wx.h>

class ProgressDialog : public ProgressDialog_
{
public:
	ProgressDialog(wxWindow* parent);
	~ProgressDialog();

	void setProgress(int progress);

protected:
private:
};

#endif // PROGRESSDIALOG_H
