#include "RapidformatApp.h"

#include "MainFrame.h"

RapidformatApp::RapidformatApp()
{
}

RapidformatApp::~RapidformatApp()
{
}

bool RapidformatApp::OnInit()
{
    return (new MainFrame())->Show();
}
