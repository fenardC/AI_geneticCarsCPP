
#include "AppRace/main/inc/AppRaceUi.h"
#include <QtWidgets/QApplication>

int main(int argc, char * argv[]) {
    QApplication a(argc, argv);
    AppRaceUi w;
    w.show();
    return a.exec();
}
