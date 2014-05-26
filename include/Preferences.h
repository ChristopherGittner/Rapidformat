#ifndef PREFERENCES_H
#define PREFERENCES_H


class Preferences
{
    public:
        virtual ~Preferences();

        static Preferences& getInstance() { static Preferences instance; return instance; };

        bool readFromDisk();
        bool saveToDisk();

        bool getUseTabs();
        void setUseTabs(bool useTabs);

        int getSpaceCount();
        void setSpaceCount(int spaceCount);

    protected:

    private:
        Preferences();
        Preferences(const Preferences& rhs);
        void operator = (const Preferences& rhs);

        bool mUseTabs = false;
        int mSpaceCount = 2;
};

#endif // PREFERENCES_H
