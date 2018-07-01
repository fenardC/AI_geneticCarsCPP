
#include "AppLearning/main/inc/AppLearningUi.h"
#include <QtWidgets/QApplication>

int main(int argc, char * argv[]) {
    QApplication a(argc, argv);
    AppLearningUi w;
    w.show();
    return a.exec();
}
