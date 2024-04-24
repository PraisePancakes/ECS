#pragma once
#include <cmath>

namespace Physics
{
    namespace Math
    {
        class Vector2D
        {
        public:
            float x = 0;
            float y = 0;
            Vector2D(){};
            Vector2D(int x, int y)
            {
                this->x = x;
                this->y = y;
            };

            Vector2D &AddPosition(float x, float y)
            {
                this->x = x;
                this->y = y;
                return *this;
            }

            Vector2D &AddPosition(Vector2D &vec)
            {
                this->x += vec.x;
                this->y += vec.y;
                return *this;
            }

            Vector2D &AddX(float x)
            {
                this->x += x;
                return *this;
            };
            Vector2D &AddY(float y)
            {
                this->y += y;
                return *this;
            };

            Vector2D &Normalize()
            {
                float length = std::sqrt(x * 2 + y * 2);
                this->x /= length;
                this->y /= length;
                return *this;
            }
        };

    }

}
