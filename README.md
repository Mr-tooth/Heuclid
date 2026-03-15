<div align="center">

# 🔷 Heuclid

**A C++ library for Euclidean geometry, convex hull, and geometric computation**

[![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](LICENSE)
[![C++](https://img.shields.io/badge/C%2B%2B-11%2B-blue.svg)](https://en.cppreference.com/w/cpp/11)
[![Build](https://img.shields.io/badge/CMake-3.22%2B-blue.svg)](https://cmake.org/)
[![Eigen](https://img.shields.io/badge/Eigen-3.x-blue.svg)](https://eigen.tuxfamily.org/)

[English](#english) | [中文](README_zh.md)

</div>

---

## English

### Overview

**Heuclid** is a lightweight, header-only C++ library providing fundamental Euclidean geometry primitives and algorithms. Built on [Eigen](https://eigen.tuxfamily.org/), it is designed for robotics simulation, motion planning, and computational geometry applications.

### Features

- **2D/3D Primitives** — Points, vectors, unit vectors, quaternions, poses
- **Convex Hull** — Graham scan and Gift wrapping algorithms with half-space representation (A*x ≤ b)
- **Bézier Curves** — N-th order Bézier with analytical derivatives
- **Eigen Interoperability** — Seamless conversion between Heuclid types and Eigen matrices
- **Header-Only** — No linking required, just include and use
- **C++11 Compatible** — Works with any C++11-compliant compiler

### Quick Start

```bash
# Clone with submodules
git clone --recursive https://github.com/Mr-tooth/Heuclid.git
cd Heuclid

# Build (fetches jrl-cmakemodules and GoogleTest automatically)
cmake -B build -DBUILD_TESTING=ON
cmake --build build

# Run tests
ctest --test-dir build
```

### Using in Your Project

```cmake
# CMakeLists.txt
add_subdirectory(path/to/Heuclid)
target_link_libraries(your_target PRIVATE heuclid)
```

```cpp
#include <Heuclid/euclid/tuple2D/Point2D.h>
#include <Heuclid/geometry/Pose3D.h>

using ljh::heuclid::Point2D;
using ljh::heuclid::Pose3D;

Point2D<double> p1(1.0, 2.0);
Point2D<double> p2(3.0, 4.0);
double dist = p1.distance(p2);

Pose3D<double> pose(0, 0, 0, 0, 0, 0);
```

### Dependencies

| Dependency | Version | Required |
|------------|---------|----------|
| [Eigen](https://eigen.tuxfamily.org/) | 3.x | ✅ Yes |
| [jrl-cmakemodules](https://github.com/jrl-umi3218/jrl-cmakemodules) | - | Auto-fetched |
| [GoogleTest](https://github.com/google/googletest) | 1.14+ | Testing only |

### Project Structure

```
Heuclid/
├── include/Heuclid/
│   ├── euclid/              # Core Euclidean primitives
│   │   ├── tuple2D/         # Point2D, Vector2D, UnitVector2D
│   │   ├── tuple3D/         # Point3D, Vector3D, UnitVector3D
│   │   ├── tuple4D/         # Quaternion
│   │   ├── orientation/     # Orientation2D
│   │   ├── tools/           # CoreTool, QuaternionTool
│   │   └── interfaces/      # ZeroTestEpsilon
│   ├── geometry/            # Geometric algorithms
│   │   ├── ConvexHull2D.h   # Convex hull (Graham scan, Gift wrapping)
│   │   ├── ConvexPolygon2D.h
│   │   ├── Line2D.h
│   │   ├── Pose2D.h / Pose3D.h
│   │   ├── curves/          # Bézier curves (Func.h)
│   │   └── tools/           # Geometry/Polygon utilities
│   └── title/               # Namespace macros
└── src/Test/                # GoogleTest unit tests
```

### License

Licensed under the [Apache License 2.0](LICENSE).

### Author

**Junhang Lai (赖俊杭)**

---

_This library is a dependency of [AStarFootstepPlanner](https://github.com/Mr-tooth/AStarFootstepPlanner) and other robotics projects._
