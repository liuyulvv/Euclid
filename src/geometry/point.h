#pragma once

/**
 * @file point.h
 * @author liuyulvv (liuyulvv@outlook.com)
 * @date 2025-09-01
 */

#include "util/compare.h"

namespace euclid::geometry
{

struct Point2D
{
    double coords[2] = {0.0, 0.0};

    // Lexicographical comparison: first by y-coordinate, then by x-coordinate
    bool operator<(const Point2D& other) const
    {
        if (util::less(coords[1], other.coords[1]))
        {
            return true;
        }
        else if (util::equal(coords[1], other.coords[1]))
        {
            return util::less(coords[0], other.coords[0]);
        }
        return false;
    }
};

struct Point3D
{
    double coords[3] = {0.0, 0.0, 0.0};
};

} // namespace euclid::geometry
