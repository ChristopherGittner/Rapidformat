#ifndef RAPIDFORMATAPP_H
#define RAPIDFORMATAPP_H

#include <wx/app.h>

#include <string>

using namespace std;

class RapidformatApp : public wxApp
{
    public:
        RapidformatApp();
        virtual ~RapidformatApp();

    protected:

        virtual bool OnInit() override;

    private:
};

#endif // RAPIDFORMATAPP_H
