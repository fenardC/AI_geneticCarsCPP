#pragma once

#include <QColor>
#include <QImage>
#include <QPixmap>
#include <string>

#include "Draw/main/inc/Drawer.hpp"
#include "Draw/main/inc/TextureModifier.hpp"
#include "Misc/main/inc/Vector2D.hpp"

class Texture {

    private:
        Texture();

    public:
        static void deInit();

    public:
        static void draw(Drawer & drawer, const double posX, const double posY,
                         const TextureModifier & modifier);

    public:
        static bool init();

    private:
        static void setcolor(const QColor color, QImage & image);

    private:
        static const bool DEBUG_ENABLED;

    private:
        static const QImage::Format IMAGE_TYPE;

    private:
        static const std::string IMAGE_PNG;

    private:
        static QPixmap * image;

    private:
        static int imageH;

    private:
        static int imageW;

    private:
        static bool initDone;
};
