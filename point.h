#pragma once

/**
 * @brief Класс, представляющий точку на плоскости.
 * @param x координата x
 * @param y координата y
 */
class Point {
private:
    const double x; 
   const double y; 

public: 
    Point() : x(0.0), y(0.0) {}

    Point(double x_val, double y_val) : x(x_val), y(y_val) {}

    double getX() const { return x; }
    double getY() const { return y; }

    void setX(double x_val) { x = x_val; }
    void setY(double y_val) { y = y_val; }
};
