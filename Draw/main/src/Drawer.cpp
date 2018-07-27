#include "Draw/main/inc/Drawer.hpp"
#include "Debug/main/inc/Logger.hpp"
#include <QPainter>
#include <QColor>
#include <QBrush>
#include <QPen>

Drawer::Drawer(QPaintDevice * device)
    : color(QColor(Qt::green))
    , device(device) {
}

Drawer::~Drawer() {
}

void Drawer::clear() const {
    //this->painter.eraseRect(this->painter.);
}

void Drawer::drawArc(const double posX, const double posY, const int width,
                     const int height, const int startAngle, const int arcAngle) const {
    QRectF rectangle(posX, posY, width, height);
    QPainter painter(device);
    QPen pen;
    pen.setColor(color);
    pen.setStyle(Qt::SolidLine);
    painter.setPen(pen);

    painter.drawArc(rectangle, startAngle * 16, arcAngle * 16);
}

void Drawer::drawDashedLine(const double posX1, const double posY1,
                            const double posX2, const double posY2) const {
    QPainter painter(device);
    QPen pen;
    pen.setColor(color);
    pen.setStyle(Qt::DashLine);
    pen.setWidth(3);
    painter.setPen(pen);

    painter.drawLine(posX1, posY1, posX2, posY2);
}

void Drawer::drawImage(const QImage & img, const double posX, const double posY) {
    QPainter painter(device);

    painter.drawImage(posX, posY, img);
}

void Drawer::drawLine(const double posX1, const double posY1,
                      const double posX2, const double posY2) const {
    QPainter painter(device);
    QPen pen;
    pen.setColor(color);
    pen.setStyle(Qt::SolidLine);
    painter.setPen(pen);

    painter.drawLine(posX1, posY1, posX2, posY2);
}

void Drawer::drawPolygon(const int xPoints[], const int yPoints[],
                         const int pointCount) const {
    QPoint points[pointCount];

    for (int i(0); i < pointCount; i++) {
        points[i].setX(xPoints[i]);
        points[i].setY(yPoints[i]);
    }

    QPainter painter(device);
    QPen pen;
    pen.setColor(color);
    pen.setStyle(Qt::SolidLine);
    painter.setPen(pen);

    painter.drawPolygon(&points[0], pointCount);
}

void Drawer::drawRect(const double posX, const double posY,
                      const int width, const int height) const {
    QPainter painter(device);
    QPen pen;
    pen.setColor(color);
    pen.setStyle(Qt::SolidLine);
    painter.setPen(pen);

    painter.drawRect(posX, posY, width, height);
}

void Drawer::drawString(const std::string string, const int posX, const int posY) const {
    const QString s(string.c_str());
    QPainter painter(device);
    QPen pen;
    pen.setColor(color);
    pen.setStyle(Qt::SolidLine);
    painter.setPen(pen);
    painter.drawText(posX, posY, s);
}

void Drawer::fillCircle(const double posX, const double posY, const int radius) const {
    QPainter painter(device);
    QPen pen;
    pen.setColor(color);
    pen.setStyle(Qt::SolidLine);
    painter.setPen(pen);

    const QBrush brush(color, Qt::SolidPattern);
    painter.setBrush(brush);

    painter.drawEllipse(posX, posY, radius, radius);
}

void Drawer::fillPolygon(const int xPoints[], const int yPoints[], const int pointCount) const {
    QPoint points[pointCount];

    for (int i(0); i < pointCount; i++) {
        points[i].setX(xPoints[i]);
        points[i].setY(yPoints[i]);
    }

    QPainter painter(device);
    QPen pen;
    pen.setColor(color);
    pen.setStyle(Qt::SolidLine);
    painter.setPen(pen);

    const QBrush brush(color, Qt::SolidPattern);
    painter.setBrush(brush);
    painter.drawPolygon(&points[0], pointCount);
}

void Drawer::setColor(const QColor color) {
    this->color = color;
}

void Drawer::show() const {
}

