
#include "Draw/main/inc/Texture.hpp"
#include "Misc/main/inc/Vector2D.hpp"

Texture::Texture() {
}

void Texture::draw(Drawer & drawer, const double posX, const double posY,
                   const TextureModifier & modifier) {
    const Vector2D position(posX, posY);
    const double angle = modifier.getAngle();
    const double ratio = modifier.getRatio();
    const double deltaX = modifier.getW();
    const double deltaY = modifier.getH();

    if (DEBUG_ENABLED) {
        const Vector2D offset0(-deltaX, -deltaY);
        const Vector2D * const rotate0 = Vector2D::rotate(offset0, angle);
        const Vector2D * const corner0 = rotate0->multiply(ratio);
        const Vector2D * const corner0Pos = Vector2D::add(position, *corner0);
        delete corner0;
        delete rotate0;

        const Vector2D offset1(deltaX, -deltaY);
        const Vector2D * const rotate1 = Vector2D::rotate(offset1, angle);
        const Vector2D * const corner1 = rotate1->multiply(ratio);
        const Vector2D * const corner1Pos = Vector2D::add(position, *corner1);
        delete corner1;
        delete rotate1;

        const Vector2D offset2(deltaX, deltaY);
        const Vector2D * const rotate2 = Vector2D::rotate(offset2, angle);
        const Vector2D * const corner2 = rotate2->multiply(ratio);
        const Vector2D * const corner2Pos = Vector2D::add(position, *corner2);
        delete corner2;
        delete rotate2;

        const Vector2D offset3(-deltaX, deltaY);
        const Vector2D * const rotate3 = Vector2D::rotate(offset3, angle);
        const Vector2D * const corner3 = rotate3->multiply(ratio);
        const Vector2D * const corner3Pos = Vector2D::add(position, *corner3);
        delete corner3;
        delete rotate3;

        const int pointsX[] = {
            (int) corner0Pos->getX(), (int) corner1Pos->getX(),
            (int) corner2Pos->getX(), (int) corner3Pos->getX()
        };
        const int pointsY[] = {
            (int) corner0Pos->getY(), (int) corner1Pos->getY(),
            (int) corner2Pos->getY(), (int) corner3Pos->getY()
        };
        const int pointCount = sizeof(pointsX) / sizeof pointsX[0];

        drawer.setColor(modifier.getColor());
        drawer.fillPolygon(pointsX, pointsY, pointCount);

        drawer.setColor(QColor(Qt::black));
        drawer.drawPolygon(pointsX, pointsY, pointCount);

        delete corner0Pos;
        delete corner1Pos;
        delete corner2Pos;
        delete corner3Pos;
    }

#if 0
    else {
        /* Create buffer for rotate operation to come. */
        const BufferedImage imageBuff = new BufferedImage(imageW, imageH, IMAGE_TYPE);
        const Graphics2D graphicsCtx = imageBuff.createGraphics();
        graphicsCtx.drawImage(image, 0, 0, null);
        graphicsCtx.dispose();
        /* Set some color to the car image. */
        setcolor(modifier.getColor(), imageBuff);

        /* Construct sequence of transformation to come. */
        const AffineTransform transformer = new AffineTransform();
        /* Set center of car image at position.*/
        transformer.translate(posX, posY);
        /* Rotate. */
        transformer.rotate(Math.toRadians(angle));
        /* Adjust const position, taking into account top left corner. */
        transformer.translate(-deltaX * ratio, -deltaY * ratio);

        /* Instantiate and apply transformation filter */
        const BufferedImageOp doer = new AffineTransformOp(transformer, modifier.getAntialiasing());

        const BufferedImage imageBuffFinal = doer.filter(imageBuff, null);

        /* Display const image from top (0, 0) origin. */
        drawer.drawImage(imageBuffFinal, 0, 0);
    }

#endif
}

void Texture::init() {
#if 0

    if (!initDone && !DEBUG_ENABLED) {
        try {
            image = ImageIO.read(Texture.class.getResourceAsStream(IMAGE_PNG));
        }
        catch (IOException e) {
            Logger.debug("Texture: " + e);
        }

        imageH = image.getHeight(null);
        imageW = image.getWidth(null);
        initDone = true;
    }

#endif
}
#if 0
static void Texture::setcolor(const QColor color, const BufferedImage image) {
    const int width = image.getWidth() - 1;
    const int height = image.getHeight() - 1;

    for (int col = 1; col < width; col++) {
        for (int raw = 1; raw < height; raw++) {
            const int ori = image.getRGB(col, raw);

            /* Test against black. */
            if ((ori & 0xFFFFFF) != 0) {
                image.setRGB(col, raw, color.getRGB());
            }
        }
    }
}
#endif

const bool Texture::DEBUG_ENABLED = true;

const int Texture::IMAGE_TYPE = 0/* = BufferedImage.TYPE_INT_ARGB*/;

/* Draw/src/main/resources/images/car.png */
/* At top of the jar of application. */
const std::string Texture::IMAGE_PNG = "/car.png";

QImage Texture::image;

int Texture::imageH = 0;

int Texture::imageW = 0;

bool Texture::initDone = false;

