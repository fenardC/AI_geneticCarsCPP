#pragma once
#include "Draw/main/inc/Drawer.hpp"
#include <string>

class AppRaceUi;
class CarRacingWorker;


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
