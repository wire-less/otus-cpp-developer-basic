#pragma once
#include "Painter.hpp"
#include "Point.hpp"
#include "Velocity.hpp"

class Ball {
  public:
    void setVelocity(const Velocity& velocity);
    Velocity getVelocity() const;
    void draw(Painter& painter) const;
    void setCenter(const Point& center);
    Point getCenter() const;
    double getRadius() const;
    double getMass() const;

    // Конструктор по-умолчанию
    Ball() = default;

    /*
    // Полный конструктор в олдскул стиле
    Ball(const Point& center, const Velocity& velocity, const double radius,
    const Color& color) { center_ = center; velocity_ = velocity; radius_ =
    radius; color_ = color; mass_ = M_PI * pow(radius_, 3) * 4. / 3.;
    }
    */

    // Полный конструктор в хипстерском стиле
    Ball(const Point& center, const Velocity& velocity, const double radius,
         const Color& color)
        : center_{center}, velocity_{velocity}, radius_{radius}, color_{color},
          mass_(calculateMass(radius)) {}

  private:
    Point center_;
    Velocity velocity_;
    double radius_;
    Color color_;
    double mass_;

    // Объявление приватного метода вычисления массы
    double calculateMass(const double radius) const;
};
