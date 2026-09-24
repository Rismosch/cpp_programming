// Simon Sutoris 7542170
// Eric Berger 7064584

#include "operations.h"
#include "point3d.h"
#include "shapes.h"
#include "transformations.h"
#include "voxel_grid.h"
#include <cstdint>
#include <iostream>

#include "shapes_test.h"

// example shapes
// TODO: enable this in the CMakelists.txt when you are finished with your
// implementation to see some example shapes
#ifdef ENABLE_DEMO_CODE
Shape outline(const VoxelGrid &vg) {
  constexpr float voxel_size = 1.0f / VoxelGrid::level_of_detail;
  Shape s{vg.clone()}; // create a clone - this creates a reference that can be
                       // used multiple times without copying
  return (s.translated({voxel_size, voxel_size, 0.0f}) |
          s.translated({voxel_size, -voxel_size, 0.0f}) |
          s.translated({-voxel_size, voxel_size, 0.0f}) |
          s.translated({-voxel_size, -voxel_size, 0.0f})) ^
         s;
}

Shape cpp2026() {
  const Shape o = Cylinder{} - Cylinder{}.scaled({0.5f, 0.5f, 1.0f});
  const Shape c =
      o - Cube{}.scaled({0.5f, 1.0f, 1.0f}).translated({0.5f, 0.0f, 0.0f});
  const Shape plus =
      Cube{}.scaled({0.2f, 0.6f, 1.0f}) + Cube{}.scaled({0.6f, 0.2f, 1.0f});
  const Shape cpp = c + plus.translated({0.8f, 0.0f, 0.0f}) +
                    plus.translated({2.3f, 0.0f, 0.0f});
  const Shape zero = o.scaled({0.6f, 1.0f, 1.0f});
  const Shape two =
      zero - Cube{}.scaled({0.6f, 0.5f, 1.0f}).translated({0.0f, 0.5f, 0.0f}) +
      Cube{}.scaled({0.6f, 0.15f, 1.0f}).translated({0.0f, 0.85f, 0.0f}) +
      Cube{}
          .scaled({0.6f, 0.15f, 1.0f})
          .rotated(Axis::Z, -40.0f * static_cast<float>(M_PI) / 180.0f)
          .translated({0.0f, 0.35f, 0.0f}) +
      Cylinder{}.scaled({0.15f, 0.15f, 1.0f}).translated({0.45f, 0.0f, 0.0f}) +
      Cylinder{}.scaled({0.15f, 0.15f, 1.0f}).translated({-0.45f, 0.75f, 0.0f});
  const Shape three =
      (o & Cube{}.scaled({0.5f, 0.8f, 1.0f}).translated({0.5f, 0.2f, 0.0f}))
          .scaled({1.0f, 0.6f, 1.0f})
          .translated({-0.6f, 0.4f, 0.0f}) +
      (o & Cube{}.scaled({0.5f, 0.8f, 1.0f}).translated({0.5f, -0.2f, 0.0f}))
          .scaled({1.0f, 0.6f, 1.0f})
          .translated({-0.6f, -0.4f, 0.0f});
  const Shape one =
      Cube{}.scaled({0.15f, 1.0f, 1.0f}).translated({0.15f, 0.0f, 0.0f}) +
      Cube{}
          .scaled({0.3f, 0.15f, 1.0f})
          .rotated(Axis::Z, -27.0f * static_cast<float>(M_PI) / 180.0f)
          .translated({-0.1f, -0.75f, 0.0f});
  const Shape six =
      zero -
      Cube{}.scaled({0.3f, 0.35f, 1.0f}).translated({0.4f, -0.65f, 0.0f});

  const Shape twenty_twenty_six = two + zero.translated({1.4f, 0.0f, 0.0f}) +
                                  two.translated({2.8f, 0.0f, 0.0f}) +
                                  six.translated({4.2f, 0.0f, 0.0f});

  return (cpp + twenty_twenty_six.translated({3.8f, 0.0f, 0.0f}))
      .scaled({1.0f, 1.0f, 0.1f});
}

// base case for variadic template
Shape shape_list() { return Empty{}.clone(); }

// variadic template
// you can create arbitrarily long shape lists with this, you don't have to
// understand how this works (yet)
#if __cpp_lib_concepts >= 202002L
// only available if concepts are supported by your c++ standard library
template <ShapeFullyImplemented FirstShape,
          ShapeFullyImplemented... RemainingShapes>
#else
template <typename FirstShape, typename... RemainingShapes>
#endif
Shape shape_list(FirstShape first, RemainingShapes... rest) {
  return first + shape_list(rest...).translated({2.0f, 0.0f, 0.0f});
}

Shape composite_shape() {
  return (((!(Sphere{} - Cube{}.scaled(0.5f).translated(0.5f))) & Cylinder{}) +
          Octahedron{}.scaled(0.5f).translated({0.0f, 0.0f, -0.5f}))
      .rotated(Axis::Z, -45.0f * static_cast<float>(M_PI) / 180.0f);
}

Shape example_shape() {
  // return shape_list(Cube{}, Sphere{}, Octahedron{}, Cylinder{});
  // return composite_shape();
  return outline(cpp2026());
}
#else
// fallback example shape (returns a simple cube)
Shape example_shape() {
  auto cube = Cube{}.clone();
  auto rotated = cube.rotated(Axis::Z, 0.78f);
  return rotated.clone();
}
#endif // end example shapes

/// implementation of your custom shape (bonus task)
Shape your_shape() {
  return Cube{}.translated({98, 4, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({96, 6, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({102, 6, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({104, 6, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({92, 8, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({94, 8, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({104, 8, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({88, 10, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({90, 10, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({92, 10, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({104, 10, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({86, 12, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({88, 12, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({90, 12, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({92, 12, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({104, 12, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({86, 14, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({88, 14, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({90, 14, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({100, 14, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({104, 14, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({32, 16, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({34, 16, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({36, 16, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({38, 16, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({84, 16, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({86, 16, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({88, 16, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({90, 16, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({98, 16, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({104, 16, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({32, 18, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({34, 18, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({36, 18, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({38, 18, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({40, 18, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({42, 18, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({84, 18, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({86, 18, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({88, 18, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({90, 18, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({96, 18, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({104, 18, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({32, 20, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({34, 20, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({36, 20, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({38, 20, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({40, 20, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({42, 20, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({44, 20, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({46, 20, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({82, 20, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({84, 20, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({86, 20, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({88, 20, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({94, 20, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({96, 20, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({104, 20, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({32, 22, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({34, 22, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({36, 22, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({38, 22, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({40, 22, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({42, 22, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({44, 22, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({46, 22, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({48, 22, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({50, 22, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({82, 22, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({84, 22, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({86, 22, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({92, 22, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({94, 22, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({96, 22, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({98, 22, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({104, 22, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({30, 24, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({32, 24, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({34, 24, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({36, 24, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({38, 24, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({40, 24, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({42, 24, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({44, 24, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({46, 24, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({48, 24, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({50, 24, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({52, 24, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({54, 24, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({80, 24, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({82, 24, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({84, 24, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({86, 24, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({96, 24, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({104, 24, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({32, 26, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({34, 26, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({36, 26, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({38, 26, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({40, 26, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({42, 26, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({44, 26, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({46, 26, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({48, 26, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({50, 26, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({52, 26, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({54, 26, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({56, 26, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({70, 26, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({72, 26, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({80, 26, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({82, 26, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({84, 26, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({94, 26, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({96, 26, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({104, 26, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({32, 28, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({34, 28, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({36, 28, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({38, 28, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({40, 28, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({42, 28, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({44, 28, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({46, 28, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({48, 28, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({50, 28, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({52, 28, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({54, 28, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({56, 28, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({58, 28, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({60, 28, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({64, 28, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({66, 28, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({68, 28, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({78, 28, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({80, 28, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({82, 28, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({84, 28, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({92, 28, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({94, 28, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({96, 28, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({98, 28, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({104, 28, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({32, 30, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({34, 30, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({36, 30, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({38, 30, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({40, 30, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({42, 30, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({44, 30, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({46, 30, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({48, 30, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({50, 30, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({52, 30, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({54, 30, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({56, 30, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({62, 30, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({74, 30, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({78, 30, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({80, 30, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({82, 30, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({90, 30, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({92, 30, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({94, 30, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({96, 30, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({98, 30, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({104, 30, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({34, 32, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({36, 32, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({38, 32, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({40, 32, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({42, 32, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({44, 32, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({46, 32, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({52, 32, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({54, 32, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({76, 32, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({78, 32, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({80, 32, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({82, 32, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({94, 32, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({96, 32, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({102, 32, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({104, 32, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({34, 34, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({36, 34, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({38, 34, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({40, 34, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({42, 34, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({44, 34, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({76, 34, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({78, 34, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({80, 34, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({92, 34, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({94, 34, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({96, 34, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({98, 34, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({100, 34, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({104, 34, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({34, 36, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({36, 36, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({38, 36, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({40, 36, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({42, 36, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({44, 36, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({76, 36, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({78, 36, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({88, 36, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({90, 36, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({92, 36, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({94, 36, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({96, 36, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({98, 36, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({36, 38, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({38, 38, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({40, 38, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({42, 38, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({44, 38, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({78, 38, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({86, 38, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({88, 38, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({90, 38, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({92, 38, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({94, 38, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({96, 38, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({98, 38, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({106, 38, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({36, 40, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({80, 40, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({90, 40, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({92, 40, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({94, 40, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({96, 40, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({106, 40, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({36, 42, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({80, 42, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({88, 42, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({90, 42, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({92, 42, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({94, 42, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({96, 42, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({106, 42, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({36, 44, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({80, 44, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({86, 44, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({88, 44, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({90, 44, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({92, 44, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({94, 44, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({106, 44, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({80, 46, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({82, 46, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({90, 46, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({92, 46, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({94, 46, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({96, 46, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({106, 46, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({34, 48, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({88, 48, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({92, 48, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({94, 48, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({96, 48, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({84, 50, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({92, 50, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({96, 50, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({104, 50, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({32, 52, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({84, 52, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({104, 52, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({30, 54, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({86, 54, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({90, 54, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({92, 54, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({94, 54, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({96, 54, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({98, 54, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({104, 54, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({86, 56, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({104, 56, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({28, 58, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({98, 58, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({106, 58, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({98, 60, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({104, 60, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({30, 62, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({102, 62, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({106, 62, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({28, 64, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({30, 64, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({32, 64, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({58, 64, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({60, 64, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({62, 64, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({64, 64, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({66, 64, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({68, 64, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({70, 64, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({72, 64, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({100, 64, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({28, 66, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({30, 66, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({32, 66, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({34, 66, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({56, 66, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({62, 66, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({74, 66, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({76, 66, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({106, 66, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({28, 68, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({30, 68, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({32, 68, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({34, 68, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({54, 68, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({64, 68, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({76, 68, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({108, 68, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({110, 68, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({26, 70, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({28, 70, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({32, 70, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({34, 70, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({52, 70, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({54, 70, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({56, 70, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({64, 70, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({76, 70, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({28, 72, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({32, 72, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({34, 72, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({52, 72, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({54, 72, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({56, 72, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({64, 72, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({74, 72, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({108, 72, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({30, 74, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({32, 74, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({34, 74, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({50, 74, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({52, 74, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({54, 74, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({56, 74, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({64, 74, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({72, 74, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({108, 74, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({26, 76, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({28, 76, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({30, 76, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({32, 76, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({50, 76, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({52, 76, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({54, 76, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({56, 76, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({64, 76, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({70, 76, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({108, 76, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({28, 78, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({30, 78, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({50, 78, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({52, 78, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({54, 78, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({56, 78, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({64, 78, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({68, 78, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({106, 78, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({108, 78, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({28, 80, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({50, 80, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({52, 80, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({54, 80, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({56, 80, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({58, 80, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({60, 80, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({62, 80, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({64, 80, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({66, 80, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({108, 80, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({110, 80, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({26, 82, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({48, 82, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({50, 82, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({52, 82, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({54, 82, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({56, 82, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({58, 82, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({110, 82, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({24, 84, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({48, 84, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({110, 84, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({112, 84, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({22, 86, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({92, 86, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({94, 86, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({108, 86, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({20, 88, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({88, 88, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({90, 88, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({96, 88, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({98, 88, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({100, 88, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({110, 88, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({16, 90, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({82, 90, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({84, 90, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({102, 90, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({104, 90, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({106, 90, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({110, 90, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({14, 92, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({16, 92, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({18, 92, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({20, 92, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({74, 92, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({76, 92, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({78, 92, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({100, 92, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({102, 92, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({104, 92, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({106, 92, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({108, 92, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({110, 92, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({112, 92, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({10, 94, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({12, 94, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({14, 94, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({16, 94, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({18, 94, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({20, 94, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({22, 94, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({64, 94, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({66, 94, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({68, 94, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({70, 94, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({104, 94, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({8, 96, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({10, 96, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({12, 96, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({14, 96, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({16, 96, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({18, 96, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({20, 96, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({22, 96, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({56, 96, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({58, 96, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({60, 96, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({100, 96, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({102, 96, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({8, 98, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({10, 98, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({12, 98, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({14, 98, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({16, 98, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({18, 98, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({20, 98, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({22, 98, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({24, 98, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({30, 98, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({48, 98, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({50, 98, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({52, 98, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({98, 98, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({100, 98, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({8, 100, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({10, 100, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({12, 100, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({14, 100, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({16, 100, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({18, 100, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({20, 100, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({22, 100, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({24, 100, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({26, 100, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({34, 100, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({36, 100, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({42, 100, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({44, 100, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({98, 100, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({100, 100, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({102, 100, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({10, 102, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({12, 102, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({14, 102, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({16, 102, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({18, 102, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({20, 102, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({22, 102, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({24, 102, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({40, 102, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({96, 102, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({10, 104, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({12, 104, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({14, 104, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({16, 104, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({18, 104, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({20, 104, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({22, 104, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({54, 104, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({60, 104, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({62, 104, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({98, 104, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({100, 104, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({12, 106, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({14, 106, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({16, 106, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({18, 106, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({20, 106, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({52, 106, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({54, 106, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({56, 106, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({66, 106, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({68, 106, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({72, 106, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({74, 106, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({76, 106, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({78, 106, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({80, 106, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({92, 106, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({94, 106, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({96, 106, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({14, 108, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({46, 108, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({48, 108, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({50, 108, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({52, 108, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({92, 108, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({16, 110, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({42, 110, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({44, 110, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({46, 110, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({94, 110, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({96, 110, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({18, 112, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({20, 112, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({28, 112, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({30, 112, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({32, 112, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({34, 112, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({36, 112, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({38, 112, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({40, 112, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({88, 112, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({90, 112, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({94, 112, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({24, 114, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({26, 114, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({28, 114, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({30, 114, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({32, 114, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({34, 114, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({88, 114, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({92, 114, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({40, 116, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({42, 116, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({86, 116, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({90, 116, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({38, 118, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({40, 118, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({88, 118, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({92, 118, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({94, 118, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({38, 120, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({88, 120, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({90, 120, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({92, 120, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({94, 120, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({32, 122, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({36, 122, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({38, 122, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({86, 122, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({88, 122, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({96, 122, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({32, 124, 0}).scaled(1 / 16.0f) |
         Cube{}.translated({98, 124, 0}).scaled(1 / 16.0f);
}
