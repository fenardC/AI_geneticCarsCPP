#include "DemoMisc/test/inc/AppTestDemoMisc.h"
#include <QtWidgets/QApplication>

int main(int argc, char * argv[]) {
    QApplication a(argc, argv);
    AppTestDemoMisc w;
    w.show();
    return a.exec();
}
