// Simon Sutoris 7542170
// Eric Berger 7064584

#include "shapes.h"

#include "operations.h"
#include "point3d.h"
#include "transformations.h"

#include <memory>
#include <stdexcept>

//------------------------------------------------------------------------------
// Shape
//------------------------------------------------------------------------------
Shape::Shape(std::shared_ptr<Shape> &&shape) noexcept
    : instance{std::move(shape)} // take ownership
{}

Shape Shape::clone() const {
  // if this shape just contains a pointer, we can return a simple copy
  if (instance)
    return *this;

  // otherwise, call the derived clone implementation
  return clone_impl();
}

AABB Shape::getBounds() const {
  // call the nested shape (if any)
  if (instance)
    return instance->getBounds();

  // otherwise, call the derived getBounds implementation
  return getBounds_impl();
}

bool Shape::isInside(const Point3D &p) const {
  // call the nested shape (if any)
  if (instance)
    return instance->isInside(p);

  // otherwise, call the derived isInside implementation
  return isInside_impl(p);
}

Shape Shape::clone_impl() const {
  // no default implementation available (but cannot set = 0, since we want to
  // have instances of Shape) if you get this error, you forgot to implement the
  // override
  throw std::logic_error("clone called on an abstract shape");
}

AABB Shape::getBounds_impl() const {
  // fallback default implementation
  return AABB{-1.0f, 1.0f};
}

bool Shape::isInside_impl(const Point3D &) const {
  // no fallback implementation (but cannot set = 0, since we want to have
  // instances of Shape) if you get this error, you forgot to implement the
  // override
  throw std::logic_error("isInside called on an abstract shape");
}

//------------------------------------------------------------------------------
// Shape Operators
//------------------------------------------------------------------------------
Shape Shape::operator&(const Shape &other) const {
  return std::make_shared<And>(*this, other)->clone();
}

Shape Shape::operator|(const Shape &other) const {
  return std::make_shared<Or>(*this, other)->clone();
}

Shape Shape::operator^(const Shape &other) const {
  return std::make_shared<Xor>(*this, other)->clone();
}

Shape Shape::operator!() const { return std::make_shared<Not>(*this)->clone(); }

Shape Shape::operator+(const Shape &other) const { return *this | other; }

Shape Shape::operator-(const Shape &other) const { return *this & !other; }

//------------------------------------------------------------------------------
// Empty
//------------------------------------------------------------------------------
Shape Empty::clone_impl() const { return {std::make_shared<Empty>()}; }

bool Empty::isInside_impl(const Point3D &) const { return false; }

AABB Empty::getBounds_impl() const { return AABB{}; }

//------------------------------------------------------------------------------
// Cube
//------------------------------------------------------------------------------
Shape Cube::clone_impl() const { return {std::make_shared<Cube>()}; }

bool Cube::isInside_impl(const Point3D &p) const {
  return getBounds().contains(p);
}

//------------------------------------------------------------------------------
// Sphere
//------------------------------------------------------------------------------
Shape Sphere::clone_impl() const { return {std::make_shared<Sphere>()}; }

bool Sphere::isInside_impl(const Point3D &p) const {
  return std::sqrt(p.x * p.x + p.y * p.y + p.z * p.z) <= 1;
}

//------------------------------------------------------------------------------
// Cylinder
//------------------------------------------------------------------------------
Shape Cylinder::clone_impl() const { return {std::make_shared<Cylinder>()}; }

bool Cylinder::isInside_impl(const Point3D &p) const {
  return std::sqrt(p.x * p.x + p.y * p.y) <= 1 && p.z <= 1;
}

//------------------------------------------------------------------------------
// Octahedron
//------------------------------------------------------------------------------
Shape Octahedron::clone_impl() const {
  return {std::make_shared<Octahedron>()};
}

bool Octahedron::isInside_impl(const Point3D &p) const {
  return std::abs(p.x) + std::abs(p.y) + std::abs(p.z) <= 1;
}
