<div align="center">

# 🔷 Heuclid

**A C++ library for Euclidean geometry, convex hull, and geometric computation**

[![CI](https://github.com/bitroboticslab/Heuclid/actions/workflows/ci.yml/badge.svg)](https://github.com/bitroboticslab/Heuclid/actions/workflows/ci.yml)
[![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](LICENSE)
[![C++](https://img.shields.io/badge/C%2B%2B-11%2B-blue.svg)](https://en.cppreference.com/w/cpp/11)
[![CMake](https://img.shields.io/badge/CMake-3.22%2B-blue.svg)](https://cmake.org/)
[![Eigen](https://img.shields.io/badge/Eigen-3.4-blue.svg)](https://eigen.tuxfamily.org/)

[English](#english) | [中文](README_zh.md)

</div>

---

<a id="english"></a>

## Overview

**Heuclid** is a lightweight static C++ library providing fundamental Euclidean geometry primitives and algorithms. Built on [Eigen](https://eigen.tuxfamily.org/), it is designed for robotics simulation, motion planning, and computational geometry applications.

## Features

- **2D/3D Primitives** — Points, vectors, unit vectors, quaternions, poses
- **Convex Hull** — Graham scan and Gift wrapping algorithms with half-space representation (A*x ≤ b)
- **Convex Polygon Tools** — Point-in-polygon test, polygon intersection (SAT), polygon containment, intersection area (Sutherland-Hodgman clipping)
- **Bézier Curves** — N-th order Bézier with analytical derivatives
- **Eigen Interoperability** — Seamless conversion between Heuclid types and Eigen matrices
- **CMake Integration** — `find_package(Heuclid)` or FetchContent, link and build
- **C++11 Compatible** — Works with any C++11-compliant compiler
- **Cross-Platform** — CI-tested on Linux, macOS, and Windows

## Quick Start

```bash
# Clone with submodules
git clone --recursive https://github.com/bitroboticslab/Heuclid.git
cd Heuclid

# Build (fetches jrl-cmakemodules and GoogleTest automatically)
cmake -B build -DBUILD_TESTING=ON
cmake --build build

# Run tests
ctest --test-dir build

# Generate documentation (requires Doxygen)
cmake -B build -DBUILD_DOCUMENTATION=ON
cmake --build build --target heuclid-doc
```

## Using in Your Project

### CMake Integration

```cmake
# Option 1: add_subdirectory
add_subdirectory(path/to/Heuclid)
target_link_libraries(your_target PRIVATE heuclid)

# Option 2: find_package (after installing Heuclid)
find_package(heuclid REQUIRED)
target_link_libraries(your_target PRIVATE heuclid::heuclid)
```

### Code Example

```cpp
#include <Heuclid/euclid/tuple2D/Point2D.h>
#include <Heuclid/euclid/tuple3D/Quaternion.h>
#include <Heuclid/geometry/ConvexHull2D.h>
#include <Heuclid/geometry/Pose3D.h>

using namespace ljh::heuclid;

// 2D point operations
Point2D<double> p1(1.0, 2.0);
Point2D<double> p2(3.0, 4.0);
double dist = p1.distance(p2);

// Quaternion rotation
Quaternion<double> q(1.0, 0.0, 0.0, 0.0);
Vector3D<double> v(1.0, 0.0, 0.0);
auto rotated = q.rotate(v);

// Convex hull computation
ConvexHull2D<double> hull;
hull.addPoint(Point2D<double>(0, 0));
hull.addPoint(Point2D<double>(1, 0));
hull.addPoint(Point2D<double>(0.5, 1));
hull.compute();  // Graham scan
auto polygon = hull.getConvexPolygon();
```

## API Reference

### Core Types (`euclid/`)

| Type | Description |
|------|-------------|
| `Point2D<T>` | 2D point with arithmetic and distance operations |
| `Vector2D<T>` | 2D vector with dot/cross product |
| `UnitVector2D<T>` | Normalized 2D vector |
| `Point3D<T>` | 3D point |
| `Vector3D<T>` | 3D vector |
| `UnitVector3D<T>` | Normalized 3D vector |
| `Quaternion<T>` | Quaternion for 3D rotation |
| `Orientation2D<T>` | 2D orientation (angle-based) |

### Geometry (`geometry/`)

| Type | Description |
|------|-------------|
| `ConvexHull2D<T>` | Convex hull computation (Graham scan / Gift wrapping) |
| `ConvexPolygon2D<T>` | Convex polygon with containment & intersection tests |
| `Line2D<T>` | 2D line representation |
| `Pose2D<T>` | 2D pose (position + orientation) |
| `Pose3D<T>` | 3D pose (position + quaternion) |
| `Func<T>` | Bézier curve (N-th order with derivatives) |

### Utilities (`tools/`)

| Function | Description |
|----------|-------------|
| `HeuclidGeometryTools` | Geometric computations (distance, projection, etc.) |
| `HeuclidPolygonTools` | Polygon operations (intersection, area, etc.) |
| `QuaternionTool` | Quaternion conversions (Euler, axis-angle, etc.) |
| `HeuclidCoreTool` | Core math utilities |

## Dependencies

| Dependency | Version | Required | Auto-fetched |
|------------|---------|----------|--------------|
| [Eigen](https://eigen.tuxfamily.org/) | 3.3+ | ✅ Yes | ✅ (3.4.0) |
| [jrl-cmakemodules](https://github.com/jrl-umi3218/jrl-cmakemodules) | latest | ✅ Yes | ✅ |
| [GoogleTest](https://github.com/google/googletest) | 1.14+ | Testing only | ✅ |
| [Doxygen](https://www.doxygen.nl/) | 1.9+ | Docs only | ❌ |

## Project Structure

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
│   └── geometry/            # Geometric algorithms
│       ├── ConvexHull2D.h   # Convex hull (Graham scan, Gift wrapping)
│       ├── ConvexPolygon2D.h
│       ├── Line2D.h
│       ├── Pose2D.h / Pose3D.h
│       ├── curves/          # Bézier curves (Func.h)
│       └── tools/           # Geometry/Polygon utilities
├── src/Test/                # GoogleTest unit tests
└── doc/                     # Doxygen configuration
```

## Building from Source

### Requirements

- CMake 3.22+
- C++11 compliant compiler (GCC 5+, Clang 3.8+, MSVC 2017+)
- Eigen 3.3+ (auto-fetched if not found)

### Build Options

| Option | Default | Description |
|--------|---------|-------------|
| `BUILD_TESTING` | `ON` | Build unit tests |
| `BUILD_DOCUMENTATION` | `ON` | Build Doxygen documentation |

### Platform-Specific

```bash
# Linux / macOS
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j$(nproc)

# Windows (MSVC)
cmake -B build -G "Visual Studio 17 2022"
cmake --build build --config Release
```

## Contributing

See [CONTRIBUTING.md](CONTRIBUTING.md) for guidelines.

## License

Licensed under the [Apache License 2.0](LICENSE).

## Author

**Junhang Lai (赖俊杭)** — [GitHub](https://github.com/Mr-tooth)

---

_This library is a dependency of [AStarFootstepPlanner](https://github.com/bitroboticslab/AStarFootstepPlanner) and other robotics projects._
