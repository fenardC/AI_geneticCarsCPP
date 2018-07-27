#ifndef APPLEARNINGUI_H
#define APPLEARNINGUI_H

#include <QMainWindow>

namespace Ui {
class AppLearningUi;
}

class AppLearning;

class AppLearningUi : public QMainWindow
{
public:
    explicit AppLearningUi(QWidget *parent = 0);

    ~AppLearningUi();

    void paintEvent(QPaintEvent*) override;

private:
    Ui::AppLearningUi *ui;

    AppLearning * learner;
};

#endif /* APPLEARNINGUI_H */
