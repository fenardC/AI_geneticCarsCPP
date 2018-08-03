#include "CObject/main/inc/CDouble.hpp"
#include "Draw/main/inc/Texture.hpp"
#include "Draw/test/inc/TestDraw.hpp"
#include "Misc/main/inc/Misc.hpp"

TestDraw::TestDraw() {
}

void TestDraw::testDraw(Drawer & drawer) {

    bool initDone = Texture::init();
    CDouble::assertEquals(std::string("Texture::init()"), initDone ? CDouble(1.0) : CDouble(0.0), CDouble(1.0));

    TextureModifier * textureModifier = new TextureModifier();
    textureModifier->setCenter(50, 25);
    textureModifier->setAntialiasing(TextureModifier::ANTIALIASING_HIGH);

    const QColor color(Qt::red);
    textureModifier->setAngle(45.0);
    textureModifier->setRatio(0.5);
    textureModifier->setColor(color);

    drawer.setColor(QColor(Qt::white));
    Texture::draw(drawer, 50.0, 100.0, *textureModifier);
    drawer.drawRect(50.0, 100.0, 4, 4);

    textureModifier->setAngle(90.0);
    drawer.setColor(QColor(Qt::white));
    Texture::draw(drawer, 150.0, 100.0, *textureModifier);
    drawer.drawRect(150.0, 100.0, 4, 4);

    Texture::deInit();

    drawer.clear();

    drawer.setColor(QColor(Qt::green));
    drawer.drawDashedLine(50.0, 75.0, 150.0, 150.0);

    drawer.setColor(QColor(Qt::blue));
    drawer.drawLine(75.0, 150.0, 300.0, 150.0);

    drawer.setColor(QColor(Qt::red));
    const int xPoints[] = {50, 400, 150};
    const int yPoints[] = {200, 200, 400};
    const int pointCount = sizeof(xPoints) / sizeof(yPoints[0]);

    drawer.drawPolygon(xPoints, yPoints, pointCount);

    drawer.setColor(QColor(Qt::white));
    drawer.drawRect(160.0, 160.0, 250, 250);

    drawer.drawString("Testing drawString() function", 50, 50);

    drawer.fillCircle(50.0, 400.0, 50);

    drawer.fillPolygon(xPoints, yPoints, pointCount);

    const double posX = 420.0;
    const double posY = 200.0;
    const int width = 40;
    const int height = 160;

    drawer.drawRect(posX - 100.0, posY, width * 2, height);

    drawer.setColor(QColor(Qt::red));
    drawer.drawArc(posX - width / 2, posY, width, height, 0, 90);

    drawer.setColor(QColor(Qt::green));
    drawer.drawArc(posX - width / 2, posY, width, height, 0, -90);

    for (int i = 0; i < 256; i++) {
        const QColor color(Misc::mix(0x00FF00, 0x0000FFF, i / 255.0));
        drawer.setColor(color);
        drawer.fillCircle(50.0 + i, 400.0 - i, 50);
    }

    delete textureModifier;
}
