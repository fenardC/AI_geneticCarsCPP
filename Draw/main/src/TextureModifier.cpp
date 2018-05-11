#include "Draw/main/inc/TextureModifier.hpp"

const int TextureModifier::ANTIALIASING_HIGH = 0 /* = AffineTransformOp.TYPE_BILINEAR*/;

TextureModifier::TextureModifier()
    : angle(0)
    , antialiasing(TextureModifier::ANTIALIASING_HIGH)
    , w(0)
    , h(0)
    , color(QColor(Qt::white))
    , ratio(1) {
}
