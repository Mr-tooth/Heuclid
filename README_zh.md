<div align="center">

# 🔷 Heuclid

**C++ 欧几里得几何与凸包计算库**

[![CI](https://github.com/Mr-tooth/Heuclid/actions/workflows/ci.yml/badge.svg)](https://github.com/Mr-tooth/Heuclid/actions/workflows/ci.yml)
[![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](LICENSE)
[![C++](https://img.shields.io/badge/C%2B%2B-11%2B-blue.svg)](https://en.cppreference.com/w/cpp/11)
[![CMake](https://img.shields.io/badge/CMake-3.22%2B-blue.svg)](https://cmake.org/)
[![Eigen](https://img.shields.io/badge/Eigen-3.4-blue.svg)](https://eigen.tuxfamily.org/)

[English](README.md) | [中文](#中文)

</div>

---

<a id="中文"></a>

## 概述

**Heuclid** 是一个轻量级的 header-only C++ 库，提供基础欧几里得几何原语和算法。基于 [Eigen](https://eigen.tuxfamily.org/) 构建，适用于机器人仿真、运动规划和计算几何应用。

## 特性

- **2D/3D 基础类型** — 点、向量、单位向量、四元数、位姿
- **凸包计算** — Graham 扫描和 Gift wrapping 算法，支持半空间表达 (A*x ≤ b)
- **贝塞尔曲线** — N 阶贝塞尔曲线及其解析导数
- **Eigen 互操作** — Heuclid 类型与 Eigen 矩阵无缝转换
- **Header-Only** — 无需链接，include 即用
- **C++11 兼容** — 支持所有 C++11 标准编译器
- **跨平台** — CI 测试覆盖 Linux、macOS、Windows

## 快速开始

```bash
# 克隆（含子模块）
git clone --recursive https://github.com/Mr-tooth/Heuclid.git
cd Heuclid

# 构建（自动获取 jrl-cmakemodules 和 GoogleTest）
cmake -B build -DBUILD_TESTING=ON
cmake --build build

# 运行测试
ctest --test-dir build

# 生成文档（需要 Doxygen）
cmake -B build -DBUILD_DOCUMENTATION=ON
cmake --build build --target heuclid-doc
```

## 在项目中使用

### CMake 集成

```cmake
# 方式 1: add_subdirectory
add_subdirectory(path/to/Heuclid)
target_link_libraries(your_target PRIVATE heuclid)

# 方式 2: find_package（安装 Heuclid 后）
find_package(heuclid REQUIRED)
target_link_libraries(your_target PRIVATE heuclid::heuclid)
```

### 代码示例

```cpp
#include <Heuclid/euclid/tuple2D/Point2D.h>
#include <Heuclid/euclid/tuple3D/Quaternion.h>
#include <Heuclid/geometry/ConvexHull2D.h>
#include <Heuclid/geometry/Pose3D.h>

using namespace ljh::heuclid;

// 2D 点运算
Point2D<double> p1(1.0, 2.0);
Point2D<double> p2(3.0, 4.0);
double dist = p1.distance(p2);

// 四元数旋转
Quaternion<double> q(1.0, 0.0, 0.0, 0.0);
Vector3D<double> v(1.0, 0.0, 0.0);
auto rotated = q.rotate(v);

// 凸包计算
ConvexHull2D<double> hull;
hull.addPoint(Point2D<double>(0, 0));
hull.addPoint(Point2D<double>(1, 0));
hull.addPoint(Point2D<double>(0.5, 1));
hull.compute();  // Graham 扫描
auto polygon = hull.getConvexPolygon();
```

## API 参考

### 核心类型 (`euclid/`)

| 类型 | 说明 |
|------|------|
| `Point2D<T>` | 2D 点，支持算术和距离运算 |
| `Vector2D<T>` | 2D 向量，支持点积/叉积 |
| `UnitVector2D<T>` | 归一化 2D 向量 |
| `Point3D<T>` | 3D 点 |
| `Vector3D<T>` | 3D 向量 |
| `UnitVector3D<T>` | 归一化 3D 向量 |
| `Quaternion<T>` | 四元数，用于 3D 旋转 |
| `Orientation2D<T>` | 2D 朝向（基于角度） |

### 几何 (`geometry/`)

| 类型 | 说明 |
|------|------|
| `ConvexHull2D<T>` | 凸包计算（Graham 扫描 / Gift wrapping） |
| `ConvexPolygon2D<T>` | 凸多边形，支持包含测试 |
| `Line2D<T>` | 2D 直线 |
| `Pose2D<T>` | 2D 位姿（位置 + 朝向） |
| `Pose3D<T>` | 3D 位姿（位置 + 四元数） |
| `Func<T>` | 贝塞尔曲线（N 阶，含导数） |

### 工具 (`tools/`)

| 函数 | 说明 |
|------|------|
| `HeuclidGeometryTools` | 几何计算（距离、投影等） |
| `HeuclidPolygonTools` | 多边形操作（交集、面积等） |
| `QuaternionTool` | 四元数转换（欧拉角、轴角等） |
| `HeuclidCoreTool` | 核心数学工具 |

## 依赖

| 依赖 | 版本 | 必需 | 自动获取 |
|------|------|------|---------|
| [Eigen](https://eigen.tuxfamily.org/) | 3.3+ | ✅ | ✅ (3.4.0) |
| [jrl-cmakemodules](https://github.com/jrl-umi3218/jrl-cmakemodules) | latest | ✅ | ✅ |
| [GoogleTest](https://github.com/google/googletest) | 1.14+ | 仅测试 | ✅ |
| [Doxygen](https://www.doxygen.nl/) | 1.9+ | 仅文档 | ❌ |

## 项目结构

```
Heuclid/
├── include/Heuclid/
│   ├── euclid/              # 欧几里得基础类型
│   │   ├── tuple2D/         # Point2D, Vector2D, UnitVector2D
│   │   ├── tuple3D/         # Point3D, Vector3D, UnitVector3D
│   │   ├── tuple4D/         # Quaternion
│   │   ├── orientation/     # Orientation2D
│   │   └── tools/           # CoreTool, QuaternionTool
│   └── geometry/            # 几何算法
│       ├── ConvexHull2D.h   # 凸包（Graham scan, Gift wrapping）
│       ├── Line2D.h / Pose2D.h / Pose3D.h
│       ├── curves/          # 贝塞尔曲线
│       └── tools/           # 几何/多边形工具
├── src/Test/                # GoogleTest 单元测试
└── doc/                     # Doxygen 配置
```

## 从源码构建

### 要求

- CMake 3.22+
- C++11 兼容编译器（GCC 5+、Clang 3.8+、MSVC 2017+）
- Eigen 3.3+（未找到时自动获取）

### 构建选项

| 选项 | 默认值 | 说明 |
|------|--------|------|
| `BUILD_TESTING` | `ON` | 构建单元测试 |
| `BUILD_DOCUMENTATION` | `ON` | 构建 Doxygen 文档 |

### 平台特定

```bash
# Linux / macOS
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j$(nproc)

# Windows (MSVC)
cmake -B build -G "Visual Studio 17 2022"
cmake --build build --config Release
```

## 贡献

参见 [CONTRIBUTING.md](CONTRIBUTING.md) 了解贡献指南。

## 许可证

[Apache License 2.0](LICENSE)

## 作者

**赖俊航 (Junhang Lai)** — [GitHub](https://github.com/Mr-tooth)

---

_本库是 [AStarFootstepPlanner](https://github.com/Mr-tooth/AStarFootstepPlanner) 等机器人项目的依赖库。_
