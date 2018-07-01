#ifndef APPTESTDEMOMISC_H
#define APPTESTDEMOMISC_H

#include <QMainWindow>
#include <QTimer>
#include "DemoMisc/test/inc/DemoCar.hpp"

namespace Ui {
class AppTestDemoMisc;
}

class AppTestDemoMisc : public QMainWindow
{
    Q_OBJECT

public:
    explicit AppTestDemoMisc(QWidget *parent = 0);

public:
    ~AppTestDemoMisc();

public:
    void paintEvent(QPaintEvent*) override;

private:
    Ui::AppTestDemoMisc *ui;

private:
    QTimer *timer;

private:
    DemoCar * demo;
};

#endif /* APPTESTDEMOMISC_H */
