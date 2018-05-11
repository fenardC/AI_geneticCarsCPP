#pragma once

#include <QColor>

class DrawParameterNeuralNetwork {

    public:
        DrawParameterNeuralNetwork()
            : DrawParameterNeuralNetwork(2) {
        }

    public:
        DrawParameterNeuralNetwork(int scaler) {
            this->scaler = scaler;
        }

    public:
        static int getColorActivated() {
            QColor color(QColor(Qt::blue));
            return color.rgba();
        }

    public:
        static int getColorDesactivated() {
            QColor color(QColor(Qt::cyan));
            return color.rgba();
        }

    public:
        QColor getColorLink() const {
            return QColor(Qt::magenta);
        }

    public:
        int getRatioNeuron() const {
            return 1 * scaler;
        }

    public:
        int getRatioX() const {
            return 1 * scaler;
        }

    public:
        int getRatioY() const {
            return 1 * scaler;
        }

    private:
        int scaler = 1;
};
