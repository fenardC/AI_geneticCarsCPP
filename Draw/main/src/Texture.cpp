#include "Debug/main/inc/Logger.hpp"
#include "Draw/main/inc/Texture.hpp"
#include "Misc/main/inc/Vector2D.hpp"

#include <QTransform>
#include <memory>

void Texture::deInit() {
    delete image;
    image = nullptr;
    imageH = 0;
    imageW = 0;
    initDone = false;
}

void Texture::draw(Drawer & drawer, const double posX, const double posY,
                   const TextureModifier & modifier) {
    const double angle = modifier.getAngle();
    const double ratio = modifier.getRatio();
    const double deltaX = modifier.getW();
    const double deltaY = modifier.getH();

    if (DEBUG_ENABLED) {
        const Vector2D position(posX, posY);

        const Vector2D offset0(-deltaX, -deltaY);
        const std::unique_ptr<Vector2D> rotate0(Vector2D::rotate(offset0, angle));
        const std::unique_ptr<Vector2D> corner0(rotate0->multiply(ratio));
        const std::unique_ptr<Vector2D> corner0Pos(Vector2D::add(position, *corner0));

        const Vector2D offset1(deltaX, -deltaY);
        const std::unique_ptr<Vector2D> rotate1(Vector2D::rotate(offset1, angle));
        const std::unique_ptr<Vector2D> corner1(rotate1->multiply(ratio));
        const std::unique_ptr<Vector2D> corner1Pos(Vector2D::add(position, *corner1));

        const Vector2D offset2(deltaX, deltaY);
        const std::unique_ptr<Vector2D> rotate2(Vector2D::rotate(offset2, angle));
        const std::unique_ptr<Vector2D> corner2(rotate2->multiply(ratio));
        const std::unique_ptr<Vector2D> corner2Pos(Vector2D::add(position, *corner2));

        const Vector2D offset3(-deltaX, deltaY);
        const std::unique_ptr<Vector2D> rotate3(Vector2D::rotate(offset3, angle));
        const std::unique_ptr<Vector2D> corner3(rotate3->multiply(ratio));
        const std::unique_ptr<Vector2D> corner3Pos(Vector2D::add(position, *corner3));

        const int pointsX[] = {
            static_cast<int>(corner0Pos->getX()), static_cast<int>(corner1Pos->getX()),
            static_cast<int>(corner2Pos->getX()), static_cast<int>(corner3Pos->getX())
        };
        const int pointsY[] = {
            static_cast<int>(corner0Pos->getY()), static_cast<int>(corner1Pos->getY()),
            static_cast<int>(corner2Pos->getY()), static_cast<int>(corner3Pos->getY())
        };
        const int pointCount = sizeof(pointsX) / sizeof pointsX[0];

        drawer.setColor(modifier.getColor());
        drawer.fillPolygon(pointsX, pointsY, pointCount);

        drawer.setColor(QColor(Qt::black));
        drawer.drawPolygon(pointsX, pointsY, pointCount);
    }
    else {
        /* Create buffer for rotate operation to come. */
        QImage imageBuff(*image);
        /* Set some color to the car image. */
        setColor(modifier.getColor(), imageBuff);

        /* Construct sequence of transformation to come. */
        QTransform transformer;

        /* Set center of car image at position.*/
        /* Rotate. */
        transformer.rotate(angle);
        /* Adjust final position, taking into account top left corner. */

        /* Instantiate and apply transformation filter. */
        QImage imageBuffFinal = imageBuff.transformed(transformer);

        /* Display final image. */
        drawer.drawImage(imageBuffFinal, posX - imageBuffFinal.width() / 2, posY - imageBuffFinal.height() / 2);
    }
}

bool Texture::init() {
    bool result = true;

    if (!initDone && !DEBUG_ENABLED) {
        image = new QImage();
        initDone = image->load(QString(Texture::IMAGE_PNG.c_str()));

        if (initDone) {
            imageH = image->height();
            imageW = image->width();
            Logger::debug(std::string("Texture::init() with: H: ") + std::to_string(imageH) +
                          std::string(" by W: ") + std::to_string(imageW));
        }
        else {
            result = false;
        }
    }

    return result;
}

void Texture::setColor(const QColor color, QImage & image) {
    const int width = image.width() - 1;
    const int height = image.height() - 1;
    const QRgb toSet = color.rgb() ;

    for (int col = 1; col < width; col++) {
        for (int raw = 1; raw < height; raw++) {
            const QRgb ori = image.pixel(col, raw);

            /* Test against black. */
            if ((ori & 0xFFFFFF) != 0) {
                image.setPixel(col, raw, toSet);
            }
        }
    }
}

Texture::Texture() {
}

const bool Texture::DEBUG_ENABLED = false;

const QImage::Format Texture::IMAGE_TYPE = QImage::Format_ARGB32;

/* Draw/main/resources/images/car.png */
/* At top of the jar of application. */
const std::string Texture::IMAGE_PNG = ":/Draw/images/car.png";

QImage * Texture::image = nullptr;

int Texture::imageH = 0;

int Texture::imageW = 0;

bool Texture::initDone = false;

