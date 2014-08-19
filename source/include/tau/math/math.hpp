#pragma once

// Not strictly necessary here as classes which
// need it will include it on a per-file basis.
// When we have it here, it'll give out an error
// if an invalid compiler or C++ version is used first.
#include "../compiler.hpp"


// Include other files.
#include "Matrix4.hpp"
#include "Quaternion.hpp"
#include "Scalar.hpp"
#include "Vector3.hpp"
#include "Line3.hpp"
#include "LineSegment3.hpp"
#include "Ray3.hpp"
