#!/usr/bin/env python3
"""Add Apache 2.0 license headers to all Heuclid source files."""

import os
import re

PROJECT_ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

LICENSE_HEADER_C = """// Copyright 2024-2026 Junhang Lai (赖俊杭)
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
"""

# Files to process (relative to project root)
HEADER_FILES = [
    "include/Heuclid/euclid/interfaces/ZeroTestEpsilon.h",
    "include/Heuclid/euclid/orientation/Orientation2D.h",
    "include/Heuclid/euclid/tools/HeuclidCoreTool.h",
    "include/Heuclid/euclid/tools/QuaternionTool.h",
    "include/Heuclid/euclid/tuple2D/Point2D.h",
    "include/Heuclid/euclid/tuple2D/UnitVector2D.h",
    "include/Heuclid/euclid/tuple2D/Vector2D.h",
    "include/Heuclid/euclid/tuple3D/Point3D.h",
    "include/Heuclid/euclid/tuple3D/UnitVector3D.h",
    "include/Heuclid/euclid/tuple3D/Vector3D.h",
    "include/Heuclid/euclid/tuple4D/Quaternion.h",
    "include/Heuclid/geometry/ConvexHull2D.h",
    "include/Heuclid/geometry/ConvexPolygon2D.h",
    "include/Heuclid/geometry/curves/Func.h",
    "include/Heuclid/geometry/Line2D.h",
    "include/Heuclid/geometry/Pose2D.h",
    "include/Heuclid/geometry/Pose3D.h",
    "include/Heuclid/geometry/tools/HeuclidGeometryTools.h",
    "include/Heuclid/geometry/tools/HeuclidPolygonTools.h",
    "include/Heuclid/title/Title.h",
]

SOURCE_FILES = [
    "src/Heuclid/euclid/orientation/Orientation2D.cpp",
    "src/Heuclid/euclid/tools/HeuclidCoreTool.cpp",
    "src/Heuclid/geometry/ConvexPolygon2D.cpp",
    "src/Heuclid/geometry/Line2D.cpp",
    "src/Heuclid/geometry/tools/HeuclidGeometryTools.cpp",
    "src/Heuclid/geometry/tools/HeuclidPolygonTools.cpp",
]

TEST_FILES = [
    "src/Test/Foot/FootPolygon.cpp",
    "src/Test/Foot/FootPolygon.h",
    "src/Test/TestBeizer.cpp",
    "src/Test/TestConvexHull2D.cpp",
    "src/Test/test.cpp",
]

ALL_FILES = HEADER_FILES + SOURCE_FILES + TEST_FILES


def has_license_header(content: str) -> bool:
    """Check if file already has a license header."""
    # Check first 20 lines for license indicators
    first_lines = "\n".join(content.split("\n")[:20])
    return "Licensed under the Apache License" in first_lines or "SPDX-License-Identifier" in first_lines


def add_header_to_file(filepath: str) -> bool:
    """Add license header to a file. Returns True if modified."""
    with open(filepath, "r", encoding="utf-8") as f:
        content = f.read()

    if has_license_header(content):
        print(f"  SKIP (already has license): {filepath}")
        return False

    # For .h files: insert before first #pragma once, #ifndef, or /** @file
    # For .cpp files: insert at the very top
    if filepath.endswith(".h"):
        # Find the right insertion point
        # If there's a Doxygen @file block, insert before it
        # If there's #pragma once, insert before it
        lines = content.split("\n")
        insert_idx = 0

        # Look for first non-empty, non-comment line that's a preprocessor directive
        for i, line in enumerate(lines):
            stripped = line.strip()
            if stripped == "":
                continue
            if stripped.startswith("/**") or stripped.startswith("///") or stripped.startswith("//!"):
                # Doxygen block - insert before it
                insert_idx = i
                break
            if stripped.startswith("#pragma") or stripped.startswith("#ifndef") or stripped.startswith("#define"):
                insert_idx = i
                break
            # If it's something else, insert before it
            insert_idx = i
            break

        lines.insert(insert_idx, LICENSE_HEADER_C.rstrip())
        new_content = "\n".join(lines)
    else:
        # .cpp files: just prepend
        new_content = LICENSE_HEADER_C + content

    with open(filepath, "w", encoding="utf-8") as f:
        f.write(new_content)

    print(f"  ADDED: {filepath}")
    return True


def main():
    os.chdir(PROJECT_ROOT)
    modified = 0
    skipped = 0
    missing = 0

    print(f"Processing {len(ALL_FILES)} files...\n")

    for rel_path in ALL_FILES:
        if not os.path.exists(rel_path):
            print(f"  MISSING: {rel_path}")
            missing += 1
            continue

        if add_header_to_file(rel_path):
            modified += 1
        else:
            skipped += 1

    print(f"\nDone: {modified} modified, {skipped} skipped, {missing} missing")


if __name__ == "__main__":
    main()
