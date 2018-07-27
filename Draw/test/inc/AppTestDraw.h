#ifndef APPTESTDRAW_H
#define APPTESTDRAW_H

#include <QMainWindow>

namespace Ui {
class AppTestDraw;
}

class AppTestDraw : public QMainWindow
{
    Q_OBJECT

public:
    explicit AppTestDraw(QWidget *parent = 0);
    ~AppTestDraw();

    void paintEvent(QPaintEvent*) override;


private:
    Ui::AppTestDraw *ui;
};

#endif /* APPTESTDRAW_H */
