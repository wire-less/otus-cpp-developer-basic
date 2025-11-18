#pragma once
#include "Point.hpp"

class Velocity {
  public:
    Velocity() = default;

    Velocity(const Point& vector) {
        setVector(vector);
    }

    void setVector(const Point& vector) {
        vec = vector;
    }

    Point vector() const {
        return vec;
    }

  private:
    Point vec;
};
