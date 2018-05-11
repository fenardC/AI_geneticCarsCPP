#include "Draw/test/inc/AppTestDraw.h"
#include <QtWidgets/QApplication>

int main(int argc, char * argv[]) {
    QApplication a(argc, argv);
    AppTestDraw w;
    w.show();
    return a.exec();
}
