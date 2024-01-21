#ifndef VECTOR2D_H
#define VECTOR2D_H

struct Vector2D
{
    explicit Vector2D(int x = 0, int y = 0)
        :x(x), y(y)
    {
    }

    int x{};
    int y{};

};
#endif //VECTOR2D_H
