#pragma once

#include <QColor>
#include <QImage>

#include "Draw/main/inc/Drawer.hpp"
#include "Draw/main/inc/TextureModifier.hpp"
#include "Misc/main/inc/Vector2D.hpp"

class Texture {

    private:
        Texture();

    public:
        static void draw(Drawer & drawer, const double posX, const double posY,
                         const TextureModifier & modifier);

    public:
        static void init();

#if 0
    private:
        static void setcolor(const QColor color, const BufferedImage image);
#endif

    private:
        static const bool DEBUG_ENABLED;

    private:
        static const int IMAGE_TYPE;

    private:
        static const std::string IMAGE_PNG;

    private:
        static QImage image;

    private:
        static int imageH;

    private:
        static int imageW;

    private:
        static bool initDone;
};
