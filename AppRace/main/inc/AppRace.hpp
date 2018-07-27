#pragma once

#include <string>

#include "Draw/main/inc/Drawer.hpp"
#include "AppRace/main/inc/CarRacingWorker.hpp"


class AppRace final {
    public:
        AppRace(AppRaceUi * mainUi);

    public:
        ~AppRace();

    public:
        void doWork(Drawer & drawer);

    public:
        void startWorker();

    public:
        void stopWorker();

    private:
        static const std::string FONT_VERDANA;

    private:
        CarRacingWorker * const worker;

    private:
        void initialize();
};
