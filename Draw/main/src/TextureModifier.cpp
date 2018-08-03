#include "Draw/main/inc/TextureModifier.hpp"

const int TextureModifier::ANTIALIASING_HIGH = 0 /* = AffineTransformOp.TYPE_BILINEAR*/;

TextureModifier::TextureModifier()
    : angle(0)
    , antialiasing(TextureModifier::ANTIALIASING_HIGH)
    , color(QColor(Qt::white))
    , h(0)
    , ratio(1)
    , w(0) {
}
