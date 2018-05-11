#include "Draw/test/inc/TestDraw.hpp"
#include "Misc/main/inc/Misc.hpp"

#include <ostream>
#include <QPainter>

#define assertEquals( string, val, expected, delta ) \
        if((std::abs((val) - (expected))) > (delta)) { \
            std::cout << (string) << " " << (val) << " does not match " << (expected) << std::endl; \
        } \

TestDraw::TestDraw() {
}

/**
 * Rigourous Test :-)
 */
void TestDraw::testDraw(Drawer & drawer) {
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
    // drawer.drawRect(posX, posY, width, height);

    drawer.setColor(QColor(Qt::red));
    drawer.drawArc(posX - width / 2, posY, width, height, 0, 90);

    drawer.setColor(QColor(Qt::green));
    drawer.drawArc(posX - width / 2, posY, width, height, 0, -90);

    // drawer.setColor(QColor(Qt::cyan));
    // drawer.drawArc(posX, posY, width, height, -90, 90);

    for (int i = 0; i < 256; i++) {
        const QColor color(Misc::mix(0x00FF00, 0x0000FFF, i / 255.0));
        // System.out.println(String.format("CYAN : 0x%08X", Color.CYAN.getRGB()));
        // System.out.println(String.format("     : 0x%08X", color.getRGB()));
        // System.out.println(String.format("BLUE : 0x%08X\n", Color.BLUE.getRGB()));

        drawer.setColor(color);
        drawer.fillCircle(50.0 + i, 400.0 - i, 50);
    }
}
