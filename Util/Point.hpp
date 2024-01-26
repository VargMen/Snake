#ifndef POINT_H
#define POINT_H

struct Point
{
    explicit Point(int x = 0, int y = 0)
        :x{x}, y{y}
    {
    }

    inline bool operator==(const Point& vec) const { return (x == vec.x) && (y == vec.y); }

    int x{};
    int y{};

};
#endif //POINT_H
