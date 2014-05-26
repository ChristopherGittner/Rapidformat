#include "Preferences.h"

#include <wx/wx.h>

#include <fstream>

using namespace std;

Preferences::Preferences()
{
    readFromDisk();
}

Preferences::~Preferences()
{
}

bool Preferences::readFromDisk()
{
    ifstream ifs("config.cfg");

    if(!ifs.is_open())
    {
        return false;
    }

    ifs >> mUseTabs;
    ifs >> mSpaceCount;

    return true;
}

bool Preferences::saveToDisk()
{
    ofstream ofs("config.cfg");

    if(!ofs.is_open())
    {
        return false;
    }

    ofs << mUseTabs << endl;
    ofs << mSpaceCount << endl;

    return true;
}

bool Preferences::getUseTabs()
{
    return mUseTabs;
}

void Preferences::setUseTabs(bool useTabs)
{
    mUseTabs = useTabs;
}

int Preferences::getSpaceCount()
{
    return mSpaceCount;
}

void Preferences::setSpaceCount(int spaceCount)
{
    mSpaceCount = spaceCount;
}
