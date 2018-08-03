#include "CObject/main/inc/CDouble.hpp"
#include "CObject/main/inc/CInteger.hpp"
#include "Debug/main/inc/Logger.hpp"
#include "Misc/main/inc/Vector2D.hpp"
#include "Misc/main/inc/Misc.hpp"

#include <memory>

static void testApp() {

    const double sqrtOf2 = sqrt(2.0);

    const CDouble four(4.0);
    const CInteger four2(4.0);

    CDouble::assertEquals(std::string("CDouble::equals()"),  four.equals(CDouble(4.0)) ? CDouble(1.0) : CDouble(0.0),
                          CDouble(1.0));

    /* Equals between CDouble and CInteger is expected to fail in current implementation. */
    CDouble::assertEquals(std::string("CDouble::equals()"),  four.equals(CInteger(4.0)) ? CDouble(1.0) : CDouble(0.0),
                          CDouble(1.0));

    /* Equals between CInteger and CDouble is expected to fail in current implementation. */
    CInteger::assertEquals(std::string("CInteger::equals()"),  four2.equals(CDouble(4.0)) ? CInteger(1.0) : CInteger(0.0),
                           CInteger(1.0));

    {
        const auto vector1 = std::make_unique<Vector2D>(0.0, 1.0);
        const auto vector1Same = std::make_unique<Vector2D>(*vector1);
        Logger::info(vector1->toString());
        Logger::info(vector1Same->toString());
        CDouble::assertEquals(std::string("Vector2D()"), CDouble(vector1Same->getX()), CDouble(vector1->getX()));
        CDouble::assertEquals(std::string("Vector2D()"), CDouble(vector1Same->getY()), CDouble(vector1->getY()));
    }

    {
        const auto vector1 = std::make_unique<Vector2D>(1.0, 1.0);
        const auto vector2 = std::make_unique<Vector2D>(-1.0, -1.0);
        const auto vector12 = std::unique_ptr<Vector2D>(Vector2D::add(*vector1, *vector2));
        CDouble::assertEquals(std::string("Vector2D()::add()"), CDouble(vector12->getX()), CDouble(0.0));
        CDouble::assertEquals(std::string("Vector2D()::add()"), CDouble(vector12->getY()), CDouble(0.0));
    }

    {
        const auto vector1 = std::make_unique<Vector2D>(1.1, 1.1);
        const auto vector2 = std::make_unique<Vector2D>(1.0, 1.0);
        const auto vector12 = std::unique_ptr<Vector2D>(Vector2D::substract(*vector1, *vector2));
        CDouble::assertEquals(std::string("Vector2D()::substract()"), CDouble(vector12->getX()), CDouble(0.1));
        CDouble::assertEquals(std::string("Vector2D()::substract()"), CDouble(vector12->getY()), CDouble(0.1));
    }

    {
        const auto vector1 = std::make_unique<Vector2D>(0.0, 1.0);
        const auto vector1Same = std::unique_ptr<Vector2D>(Vector2D::getVector2DFromValueAngle(1.0, 90.0));
        CDouble::assertEquals(std::string("Vector2D()::getVector2DFromValueAngle()"),
                              CDouble(vector1Same->getX()), CDouble(vector1->getX()));
        CDouble::assertEquals(std::string("Vector2D()::getVector2DFromValueAngle()"),
                              CDouble(vector1Same->getY()), CDouble(vector1->getY()));
        const double v1Orientation = vector1->getOrientation();
        CDouble::assertEquals(std::string("Vector2D()::getOrientation()"), CDouble(v1Orientation), CDouble(90.0));
    }

    {
        const auto vector1 = std::make_unique<Vector2D>(0.0, 4.0);
        const auto vector1Normalized = std::unique_ptr<Vector2D>(Vector2D::normalize(*vector1));
        CDouble::assertEquals(std::string("Vector2D()::normalize()"), CDouble(vector1Normalized->getX()), CDouble(0.0));
        CDouble::assertEquals(std::string("Vector2D()::normalize()"), CDouble(vector1Normalized->getY()), CDouble(1.0));

        const double len = vector1->length();
        CDouble::assertEquals(std::string("Vector2D()::length()"), CDouble(len), CDouble(4.0));

        const double lenSquared = vector1->lengthSquared();
        CDouble::assertEquals(std::string("Vector2D()::lengthSquared()"), CDouble(lenSquared), CDouble(16.0));
    }

    {
        const auto vector1 = std::make_unique<Vector2D>(0.0, 2.0);
        const auto vector1Rotated = std::unique_ptr<Vector2D>(Vector2D::rotate(*vector1, 45.0));
        CDouble::assertEquals(std::string("Vector2D()::rotate()"), CDouble(vector1Rotated->getX()), CDouble(-sqrtOf2));
        CDouble::assertEquals(std::string("Vector2D()::rotate()"), CDouble(vector1Rotated->getY()), CDouble(sqrtOf2));
    }

    {
        const auto vector1 = std::make_unique<Vector2D>(2.0, 2.0);
        const auto vector1Multiplied = std::unique_ptr<Vector2D>(vector1->multiply(0.5));
        CDouble::assertEquals(std::string("Vector2D()::multiply()"), CDouble(vector1Multiplied->getX()), CDouble(1.0));
        CDouble::assertEquals(std::string("Vector2D()::multiply()"), CDouble(vector1Multiplied->getY()), CDouble(1.0));

        const auto vector1Multipli2ed = std::unique_ptr<Vector2D>(vector1->multiply2(0.5));
        CDouble::assertEquals(std::string("Vector2D()::multiply2()"), CDouble(vector1Multipli2ed->getX()), CDouble(1.0));
        CDouble::assertEquals(std::string("Vector2D()::multiply2()"), CDouble(vector1Multipli2ed->getY()), CDouble(1.0));
    }

    {
        for (int i = 0; i < 10 ; i++) {
            bool res = Misc::random(50.0);
            std::cout << std::string("Misc::random(50.0) returned: ") << std::boolalpha << res << std::noboolalpha << std::endl;
        }
    }

    {
        for (int i = 0; i < 10 ; i++) {
            double res = Misc::random(0.0, 5.0);
            std::cout << std::string("Misc::random(double, double) returned: ") + std::to_string(res) << std::endl;
        }
    }

    {
        for (int i = 0; i < 10 ; i++) {
            int res = Misc::random(0, 5);
            std::cout << std::string("Misc::random(int, int) returned: ") + std::to_string(res) << std::endl;
        }
    }

}

int main() {
    testApp();
    return 0;
}
