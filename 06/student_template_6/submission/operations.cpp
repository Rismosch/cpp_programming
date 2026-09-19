// Simon Sutoris 7542170
// Eric Berger 7064584

#include "operations.h"
#include <memory>

//------------------------------------------------------------------------------
// Operation
//------------------------------------------------------------------------------
Operation::Operation(const Shape &shape_a, const Shape &shape_b)
    : sub_shape_a{shape_a.clone()}, sub_shape_b{shape_b.clone()} {}

AABB Operation::getBounds_impl() const {
  return sub_shape_a.getBounds() + sub_shape_b.getBounds();
}

//------------------------------------------------------------------------------
// And
//------------------------------------------------------------------------------
And::And(const Shape &shape_a, const Shape &shape_b)
    : Operation(shape_a, shape_b) {}

Shape And::clone_impl() const {
  return {std::make_shared<And>(sub_shape_a.clone(), sub_shape_b.clone())};
}

bool And::isInside_impl(const Point3D &p) const {
  return sub_shape_a.isInside(p) & sub_shape_b.isInside(p);
}

//------------------------------------------------------------------------------
// Or
//------------------------------------------------------------------------------
Or::Or(const Shape &shape_a, const Shape &shape_b)
    : Operation(shape_a, shape_b) {}

Shape Or::clone_impl() const {
  return {std::make_shared<Or>(sub_shape_a.clone(), sub_shape_b.clone())};
}

bool Or::isInside_impl(const Point3D &p) const {
  return sub_shape_a.isInside(p) | sub_shape_b.isInside(p);
}

//------------------------------------------------------------------------------
// Xor
//------------------------------------------------------------------------------
Xor::Xor(const Shape &shape_a, const Shape &shape_b)
    : Operation(shape_a, shape_b) {}

Shape Xor::clone_impl() const {
  return {std::make_shared<Xor>(sub_shape_a.clone(), sub_shape_b.clone())};
}

bool Xor::isInside_impl(const Point3D &p) const {
  return sub_shape_a.isInside(p) ^ sub_shape_b.isInside(p);
}

//------------------------------------------------------------------------------
// Not
//------------------------------------------------------------------------------
Not::Not(const Shape &shape) : Operation(shape, {std::make_shared<Empty>()}) {}

Shape Not::clone_impl() const {
  return {std::make_shared<Not>(sub_shape_a.clone())};
}

bool Not::isInside_impl(const Point3D &p) const {
  return !sub_shape_a.isInside(p);
}
