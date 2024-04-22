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

            Vector2D &Add(Vector2D vec)
            {
                this->x += vec.x;
                this->y += vec.y;
            };

            Vector2D &Normalize()
            {
                float length = std::sqrt(x * 2 + y * 2);
                this->x /= length;
                this->y /= length;
            }
        };

    }

}
