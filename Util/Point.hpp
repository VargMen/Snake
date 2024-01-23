#ifndef VECTOR2D_H
#define VECTOR2D_H

struct Point
{
    explicit Point(int x = 0, int y = 0)
        :x(x), y(y)
    {
    }

    bool operator==(const Point& vec) const { return (x == vec.x) && (y == vec.y); }
    int x{};
    int y{};

};
#endif //VECTOR2D_H
