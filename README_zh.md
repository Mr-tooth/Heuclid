<div align="center">

# 🔷 Heuclid

**C++ 欧几里得几何与凸包计算库**

[![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](LICENSE)
[![C++](https://img.shields.io/badge/C%2B%2B-11%2B-blue.svg)](https://en.cppreference.com/w/cpp/11)
[![CMake](https://img.shields.io/badge/CMake-3.22%2B-blue.svg)](https://cmake.org/)
[![Eigen](https://img.shields.io/badge/Eigen-3.x-blue.svg)](https://eigen.tuxfamily.org/)

[English](README.md) | [中文](#中文)

</div>

---

## 中文

### 概述

**Heuclid** 是一个轻量级的 header-only C++ 库，提供基础欧几里得几何原语和算法。基于 [Eigen](https://eigen.tuxfamily.org/) 构建，适用于机器人仿真、运动规划和计算几何应用。

### 特性

- **2D/3D 基础类型** — 点、向量、单位向量、四元数、位姿
- **凸包计算** — Graham 扫描和 Gift wrapping 算法，支持半空间表达 (A*x ≤ b)
- **贝塞尔曲线** — N 阶贝塞尔曲线及其解析导数
- **Eigen 互操作** — Heuclid 类型与 Eigen 矩阵无缝转换
- **Header-Only** — 无需链接，include 即用
- **C++11 兼容** — 支持所有 C++11 标准编译器

### 快速开始

```bash
# 克隆（含子模块）
git clone --recursive https://github.com/Mr-tooth/Heuclid.git
cd Heuclid

# 构建（自动获取 jrl-cmakemodules 和 GoogleTest）
cmake -B build -DBUILD_TESTING=ON
cmake --build build

# 运行测试
ctest --test-dir build
```

### 在项目中使用

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
```

### 依赖

| 依赖 | 版本 | 必需 |
|------|------|------|
| [Eigen](https://eigen.tuxfamily.org/) | 3.x | ✅ |
| [jrl-cmakemodules](https://github.com/jrl-umi3218/jrl-cmakemodules) | - | 自动获取 |
| [GoogleTest](https://github.com/google/googletest) | 1.14+ | 仅测试 |

### 项目结构

```
Heuclid/
├── include/Heuclid/
│   ├── euclid/              # 欧几里得基础类型
│   │   ├── tuple2D/         # Point2D, Vector2D, UnitVector2D
│   │   ├── tuple3D/         # Point3D, Vector3D, UnitVector3D
│   │   ├── tuple4D/         # Quaternion
│   │   ├── orientation/     # Orientation2D
│   │   └── tools/           # CoreTool, QuaternionTool
│   ├── geometry/            # 几何算法
│   │   ├── ConvexHull2D.h   # 凸包（Graham scan, Gift wrapping）
│   │   ├── Line2D.h / Pose2D.h / Pose3D.h
│   │   └── curves/          # 贝塞尔曲线
│   └── title/               # 命名空间宏
└── src/Test/                # GoogleTest 单元测试
```

### 许可证

[Apache License 2.0](LICENSE)

### 作者

**赖俊航 (Junhang Lai)**

---

_本库是 [AStarFootstepPlanner](https://github.com/Mr-tooth/AStarFootstepPlanner) 等机器人项目的依赖库。_
