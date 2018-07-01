

#include "Debug/main/inc/Logger.hpp"
#include "Misc/main/inc/Vector2D.hpp"
#include "Misc/main/inc/Misc.hpp"
#include <ostream>


#define assertEquals( string, val, expected, delta ) \
        if((std::abs((val) - (expected))) > (delta)) { \
            std::cout << (string) << " " << (val) << " does not match " << (expected) << std::endl; \
        } \

static void testApp() {
    const double delta = 1E-15;
    const double sqrtOf2 = sqrt(2.0);

    Misc::init();

    {
        const Vector2D * vector1 = new Vector2D(0.0, 1.0);
        const Vector2D * vector1Same = new Vector2D(*vector1);
        Logger::debug(vector1->toString());
        Logger::debug(vector1Same->toString());
        assertEquals("Vector2D()", vector1Same->getX(), vector1->getX(), delta);
        assertEquals("Vector2D()", vector1Same->getY(), vector1->getY(), delta);
        delete vector1;
        delete vector1Same;
    }

    {
        const Vector2D * vector1 = new Vector2D(1.0, 1.0);
        const Vector2D * vector2 = new Vector2D(-1.0, -1.0);
        const Vector2D * vector12 = Vector2D::add(*vector1, *vector2);
        assertEquals("add()", vector12->getX(), 0.0, delta);
        assertEquals("add()", vector12->getY(), 0.0, delta);
        delete vector1;
        delete vector2;
        delete vector12;
    }

    {
        const Vector2D * vector1 = new Vector2D(1.1, 1.1);
        const Vector2D * vector2 = new Vector2D(1.0, 1.0);
        const Vector2D * vector12 = Vector2D::substract(*vector1, *vector2);
        assertEquals("substract()", vector12->getX(), 0.1, delta);
        assertEquals("substract()", vector12->getY(), 0.1, delta);
        delete vector1;
        delete vector2;
        delete vector12;
    }

    {
        const Vector2D * vector1 = new Vector2D(0.0, 1.0);
        const Vector2D * vector1Same = Vector2D::getVector2DFromValueAngle(1.0, 90.0);
        assertEquals("getVector2DFromValueAngle()", vector1Same->getX(), vector1->getX(), delta);
        assertEquals("getVector2DFromValueAngle()", vector1Same->getY(), vector1->getY(), delta);
        const double v1Orientation = vector1->getOrientation();
        assertEquals("getOrientation()", v1Orientation, 90.0, delta);
        delete vector1;
        delete vector1Same;
    }

    {
        const Vector2D * vector1 = new Vector2D(0.0, 4.0);
        const Vector2D * vector1Normalized = Vector2D::normalize(*vector1);
        assertEquals("normalize()", vector1Normalized->getX(), 0.0, delta);
        assertEquals("normalize()", vector1Normalized->getY(), 1.0, delta);

        const double len = vector1->length();
        assertEquals("length()", len, 4.0, delta);

        const double lenSquared = vector1->lengthSquared();
        assertEquals("lengthSquared()", lenSquared, 16.0, delta);
        delete vector1;
        delete vector1Normalized;
    }

    {
        const Vector2D * vector1 = new Vector2D(0.0, 2.0);
        const Vector2D * vector1Rotated = Vector2D::rotate(*vector1, 45.0);
        assertEquals("rotate()", vector1Rotated->getX(), -sqrtOf2, delta);
        assertEquals("rotate()", vector1Rotated->getY(), sqrtOf2, delta);
        delete vector1;
        delete vector1Rotated;
    }

    {
        const Vector2D * vector1 = new Vector2D(2.0, 2.0);
        const Vector2D * vector1Multiplied = vector1->multiply(0.5);
        assertEquals("multiply()", vector1Multiplied->getX(), 1.0, delta);
        assertEquals("multiply()", vector1Multiplied->getY(), 1.0, delta);

        const Vector2D * vector1Multipli2ed = vector1->multiply2(0.5);
        assertEquals("multiply2()", vector1Multipli2ed->getX(), 1.0, delta);
        assertEquals("multiply2()", vector1Multipli2ed->getY(), 1.0, delta);
        delete vector1;
        delete vector1Multiplied;
        delete vector1Multipli2ed;
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
