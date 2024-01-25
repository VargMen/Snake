#ifndef POINT_H
#define POINT_H

struct Point
{
public:
    explicit Point(int x = 0, int y = 0)
        :x{x}, y{y}
    {
    }

    inline bool operator==(const Point& vec) const { return (x == vec.x) && (y == vec.y); }

    int getX() const { return x; }
    int getY() const { return y; }

    int& setX() { return x; }
    int& setY() { return y; }
private:

    int x{};
    int y{};

};
#endif //POINT_H
