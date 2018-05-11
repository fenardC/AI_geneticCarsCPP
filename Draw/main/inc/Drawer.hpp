#pragma once

#include <QPainter>
#include <QColor>
#include <QBrush>
#include <QPen>

class Drawer {
    public:
        Drawer(QPaintDevice * device);

    public:
        ~Drawer();

    public:
        void clear() const;

    public:
        void drawArc(const double posX, const double posY, const int width, const int height,
                     const int startAngle, const int arcAngle) const;

    public:
        void drawDashedLine(const double posX1, const double posY1,
                            const double posX2, const double posY2) const;
#if 0
    public:
        void drawImage(const Image img, const double posX, const double posY);
#endif

    public:
        void drawLine(const double posX1, const double posY1, const double posX2, const double posY2) const;

    public:
        void drawPolygon(const int xPoints[], const int yPoints[], const int nPoints) const;

    public:
        void drawRect(const double posX, const double posY, const int width, const int height) const;

    public:
        void drawString(const std::string string, const int posX, const int posY) const;

    public:
        void fillCircle(const double posX, const double posY, const int radius) const;

    public:
        void fillPolygon(const int xPoints[], const int yPoints[], const int nPoints) const;

    public:
        void setColor(const QColor color);

    public:
        void show() const;

    private:
        QColor color;

    private:
        QPaintDevice * device;
};
