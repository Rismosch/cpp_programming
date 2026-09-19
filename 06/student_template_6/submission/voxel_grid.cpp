// Simon Sutoris 7542170
// Eric Berger 7064584

#include "voxel_grid.h"

#include "operations.h"
#include "point3d.h"
#include "transformations.h"

#include <cassert>
#include <cstdint>
#include <iostream>
#include <ostream>
#include <sstream>
#include <stdint.h>

VoxelGrid::VoxelGrid(const Shape &shape) : bounds(shape.getBounds()) {
  // find resolution
  Point3D extents{bounds.extents()};
  Point3D lod{static_cast<double>(level_of_detail)};
  Point3D resolution = extents * lod;
  resolution = ::max(resolution, {1.0});
  res_x = static_cast<uint32_t>(resolution.x);
  res_y = static_cast<uint32_t>(resolution.y);
  res_z = static_cast<uint32_t>(resolution.z);

  // initialize voxels
  voxels.reserve(res_x * res_y * res_z);
  for (uint32_t iz = 0; iz < res_z; ++iz) {
    for (uint32_t iy = 0; iy < res_y; ++iy) {
      for (uint32_t ix = 0; ix < res_x; ++ix) {
        Point3D position = voxelCenter(ix, iy, iz);
        bool value = shape.isInside(position);
        voxels.push_back(value);
      }
    }
  }

  // for (uint32_t i = 0; i < voxels.capacity(); ++i) {
  //   voxels.push_back(false);
  // }
}

std::tuple<uint32_t, uint32_t, uint32_t> VoxelGrid::getResolution() const {
  return {res_x, res_y, res_z};
}

VoxelSlice VoxelGrid::extractSlice(Axis axis, uint32_t slice) const {
  switch (axis) {
  case Axis::X: {
    uint32_t x = slice;
    VoxelSlice result{res_y, res_z};

    for (uint32_t y = 0; y < res_y; ++y) {
      for (uint32_t z = 0; z < res_z; ++z) {
        if (isSet(x, y, z)) {
          result.data[z][y] = true;
        }
      }
    }

    return result;
  }
  case Axis::Y: {
    uint32_t y = slice;
    VoxelSlice result{res_x, res_z};

    for (uint32_t x = 0; x < res_x; ++x) {
      for (uint32_t z = 0; z < res_z; ++z) {
        if (isSet(x, y, z)) {
          result.data[z][x] = true;
        }
      }
    }
    return result;
  }
  case Axis::Z: {
    uint32_t z = slice;
    VoxelSlice result{res_x, res_y};
    for (uint32_t x = 0; x < res_x; ++x) {

      for (uint32_t y = 0; y < res_y; ++y) {
        if (isSet(x, y, z)) {
          result.data[y][x] = true;
        }
      }
    }
    return result;
  }
  default:
    return {0, 0};
  }
}

Shape VoxelGrid::clone_impl() const {
  return {std::make_shared<VoxelGrid>(*this)};
}

AABB VoxelGrid::getBounds_impl() const { return bounds; }

bool VoxelGrid::isInside_impl(const Point3D &p) const {
  // visualization: https://www.desmos.com/calculator/yfxbz0wdhg
  throw std::logic_error("task 6.4 f)");
  (void)p; // silence unused parameter warning
}

bool VoxelGrid::isSet(uint32_t x, uint32_t y, uint32_t z) const {
  // When running indebug mode, these will check whether the supplied indices
  // are valid or "trap" to the debugger. When no debugger is running, failing
  // the assertion will terminate the program immediately. When compiled in
  // release mode, assert() does nothing.
  assert(x < res_x);
  assert(y < res_y);
  assert(z < res_z);

  uint32_t index = x + res_x * y + res_x * res_y * z;
  if (index < voxels.capacity()) {
    return voxels[index];
  } else {
    return false;
  }
}

Point3D VoxelGrid::voxelCenter(uint32_t x, uint32_t y, uint32_t z) const {
  AABB aabb = getBounds();
  Point3D extents = aabb.extents();
  Point3D resolution{
      static_cast<float>(res_x),
      static_cast<float>(res_y),
      static_cast<float>(res_z),
  };
  Point3D stepsize = extents / resolution;
  Point3D offset{
      static_cast<float>(x + 0.5),
      static_cast<float>(y + 0.5),
      static_cast<float>(z + 0.5),
  };
  Point3D center = stepsize * offset + aabb.min;
  return center;
}

std::ostream &operator<<(std::ostream &ostream, const VoxelSlice &slice) {
  for (auto row : slice.data) {
    for (bool voxel : row) {
      ostream << (voxel ? 'X' : '.');
    }

    ostream << "\n";
  }

  return ostream;
}

std::ostream &operator<<(std::ostream &ostream, const VoxelGrid &vg) {
  uint32_t res_z;
  std::tie(std::ignore, std::ignore, res_z) = vg.getResolution();

  for (uint32_t z = 0; z < res_z; ++z) {
    auto slice = vg.extractSlice(Axis::Z, z);
    ostream << slice << std::endl;
  }
  return ostream;
}
