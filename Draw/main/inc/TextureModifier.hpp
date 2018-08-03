#pragma once

#include <QColor>

class TextureModifier {
    public:
        static const int ANTIALIASING_HIGH;

    public:
        TextureModifier();

    public:
        double getAngle() const {
            return angle;
        }

    public:
        int getAntialiasing() const {
            return antialiasing;
        }

    public:
        QColor getColor() const {
            return color;
        }

    public:
        int getH() const {
            return h;
        }

    public:
        double getRatio() const {
            return ratio;
        }

    public:
        int getW() const {
            return w;
        }

    public:
        void setAngle(const double angle) {
            this->angle = angle;
        }

    public:
        void setAntialiasing(const int antialiasing) {
            this->antialiasing = antialiasing;
        }

    public:
        void setCenter(const int width, const int height) {
            w = width;
            h = height;
        }

    public:
        void setColor(const QColor color) {
            this->color = color;
        }

    public:
        void setRatio(const double ratio) {
            this->ratio = ratio;
        }

    private:
        double angle;

    private:
        int antialiasing;

    private:
        QColor color;

    private:
        int h;

    private:
        double ratio;

    private:
        int w;
};
