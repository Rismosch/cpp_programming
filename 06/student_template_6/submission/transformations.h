// Simon Sutoris 7542170
// Eric Berger 7064584

#pragma once

#include "point3d.h"
#include "shapes.h"

#include <memory>

/// shared abstract transformation base class containing a nested shape to be
/// transformed
class Transformation : public Shape {
protected:
  Transformation(const Shape &shape);

public:
  Shape sub_shape;
};

// of course, one could implement all these transformations jointly as a single
// transformation matrix. for simplicity, we don't do that here.

class Scaled final : public Transformation {
public:
  Scaled(const Shape &shape, const Point3D &factor);

private:
  Shape clone_impl() const override;
  bool isInside_impl(const Point3D &p) const override;
  AABB getBounds_impl() const override;

  Point3D factor;
};

class Translated final : public Transformation {
public:
  Translated(const Shape &shape, const Point3D &offset);

private:
  Shape clone_impl() const override;
  bool isInside_impl(const Point3D &p) const override;
  AABB getBounds_impl() const override;

  Point3D offset;
};

class Rotated final : public Transformation {
public:
  Rotated(const Shape &shape, Axis axis, float angle);

private:
  Shape clone_impl() const override;
  bool isInside_impl(const Point3D &p) const override;
  AABB getBounds_impl() const override;

  Axis axis;
  float angle;
};
