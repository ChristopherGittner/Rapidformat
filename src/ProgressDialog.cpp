#include "ProgressDialog.h"

ProgressDialog::ProgressDialog(wxWindow* parent) : ProgressDialog_(parent)
{
}

ProgressDialog::~ProgressDialog()
{
}

void ProgressDialog::setProgress(int progress)
{
	mGauge->SetValue(progress);
}