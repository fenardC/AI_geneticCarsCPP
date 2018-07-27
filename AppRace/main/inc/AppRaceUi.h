#ifndef APPRACEUI_H
#define APPRACEUI_H

#include <QMainWindow>
#include <QTimer>

class AppRace;

namespace Ui {
class AppRaceUi;
}

class AppRaceUi : public QMainWindow
{
    Q_OBJECT

public:
    explicit AppRaceUi(QWidget *parent = 0);
    ~AppRaceUi();

    void paintEvent(QPaintEvent*) override;

private:
    Ui::AppRaceUi *ui;
    AppRace * racer;
};

#endif /* APPRACEUI_H */
