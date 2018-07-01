#pragma once

#include <string>

#include "AppLearning/main/inc/AppLearningUi.h"
#include "AppLearning/main/inc/CarsLearningWorker.hpp"
#include "Draw/main/inc/Drawer.hpp"

class AppLearning final {

    public:
        AppLearning(AppLearningUi * mainUi);

    public:
        void doWork(Drawer & drawer);

    public:
        void startWorker();

    private:
        static const std::string FONT_VERDANA;

    private:
        CarsLearningWorker * worker;

    private:
        void initialize();
};
