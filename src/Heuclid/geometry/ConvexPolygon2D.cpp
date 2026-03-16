// Copyright 2024-2026 Junhang Lai (赖俊杭)
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
#include <Heuclid/geometry/ConvexPolygon2D.h>
_LJH_EUCLID_LIB_BEGIN

void ConvexPolygon2D::setVertexBuffer(std::vector<Point2D<double> > buffer)
{
    this->vertexBuffer = buffer;
}

_LJH_EUCLID_LIB_END