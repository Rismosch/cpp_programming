// Simon Sutoris 7542170
// Eric Berger 7064584

#include "transformations.h"
#include "point3d.h"
#include <cmath>

//------------------------------------------------------------------------------
// Helper functions for rotations
//------------------------------------------------------------------------------
std::pair<float, float> rotate2D(float x, float y, float angle) {
  const float sin = std::sin(angle);
  const float cos = std::cos(angle);

  return {cos * x - sin * y, sin * x + cos * y};
}

Point3D rotate(const Point3D &p, Axis axis, float angle) {
  switch (axis) {
  case Axis::X: {
    auto [y, z] = rotate2D(p.y, p.z, angle);
    return {p.x, y, z};
  }
  case Axis::Y: {
    auto [x, z] = rotate2D(p.x, p.z, angle);
    return {x, p.y, z};
  }
  case Axis::Z: {
    auto [x, y] = rotate2D(p.x, p.y, angle);
    return {x, y, p.z};
  }
  default:
    // invalid axis, return p unmodified
    return p;
  }
}

//------------------------------------------------------------------------------
// Transformation
//------------------------------------------------------------------------------
Transformation::Transformation(const Shape &shape) : sub_shape{shape.clone()} {}

//------------------------------------------------------------------------------
// Scaled
//------------------------------------------------------------------------------
Scaled::Scaled(const Shape &shape, const Point3D &factor_)
    : Transformation(shape), factor(factor_) {}

Shape Scaled::clone_impl() const {
  return {std::make_shared<Scaled>(sub_shape.clone(), factor)};
}

bool Scaled::isInside_impl(const Point3D &p) const {
  auto scaled_p = p / factor;
  return sub_shape.isInside(scaled_p);
}

AABB Scaled::getBounds_impl() const {
  auto copy = sub_shape.getBounds();
  copy.min *= factor;
  copy.max *= factor;
  return copy;
}

//------------------------------------------------------------------------------
// Translated
//------------------------------------------------------------------------------
Translated::Translated(const Shape &shape, const Point3D &offset_)
    : Transformation(shape), offset(offset_) {}

Shape Translated::clone_impl() const {
  return {std::make_shared<Translated>(sub_shape.clone(), offset)};
}

bool Translated::isInside_impl(const Point3D &p) const {
  auto translated_p = p - offset;
  return sub_shape.isInside(translated_p);
}

AABB Translated::getBounds_impl() const {
  auto copy = sub_shape.getBounds();
  copy.min += offset;
  copy.max += offset;
  return copy;
}

//------------------------------------------------------------------------------
// Rotated
//------------------------------------------------------------------------------
Rotated::Rotated(const Shape &shape, Axis axis_, float angle_)
    : Transformation(shape), axis(axis_), angle(angle_) {}

Shape Rotated::clone_impl() const {
  return {std::make_shared<Rotated>(sub_shape.clone(), axis, angle)};
}

bool Rotated::isInside_impl(const Point3D &p) const {
  Point3D rotated_p = rotate(p, axis, -angle);
  return sub_shape.isInside(rotated_p);
}

AABB Rotated::getBounds_impl() const {
  auto aabb = sub_shape.getBounds();

  // aabbs can't be rotated, because then they wouldn't be axis aligned anymore.
  // instead, rotate all vertices of the original aabb and draw a new aabb
  // around it
  const int vertex_count = 8;
  const Point3D vertices[vertex_count] = {
      {aabb.min.x, aabb.min.y, aabb.min.z},
      {aabb.min.x, aabb.min.y, aabb.max.z},
      {aabb.min.x, aabb.max.y, aabb.min.z},
      {aabb.min.x, aabb.max.y, aabb.max.z},
      {aabb.max.x, aabb.min.y, aabb.min.z},
      {aabb.max.x, aabb.min.y, aabb.max.z},
      {aabb.max.x, aabb.max.y, aabb.min.z},
      {aabb.max.x, aabb.max.y, aabb.max.z},
  };

  AABB result;
  for (int i = 0; i < vertex_count; ++i) {
    Point3D vertex = vertices[i];
    Point3D rotated_vertex = rotate(vertex, axis, angle);
    result.extend(rotated_vertex);
  }

  return result;
}
