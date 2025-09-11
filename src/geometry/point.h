#pragma once

/**
 * @file point.h
 * @author liuyulvv (liuyulvv@outlook.com)
 * @date 2025-09-01
 */

#include "util/compare.h"

namespace euclid::geometry {

struct Point2D {
    double coords[2] = {0.0, 0.0};

    // Lexicographical comparison: first by y-coordinate, then by x-coordinate
    bool operator<(const Point2D& other) const {
        if (util::Less(coords[1], other.coords[1])) {
            return true;
        } else if (util::Equal(coords[1], other.coords[1])) {
            return util::Less(coords[0], other.coords[0]);
        }
        return false;
    }

    bool operator==(const Point2D& other) const { return util::Equal(this->Distance(other), 0.0); }

    double Distance(const Point2D& other) const {
        return std::sqrt((coords[0] - other.coords[0]) * (coords[0] - other.coords[0]) + (coords[1] - other.coords[1]) * (coords[1] - other.coords[1]));
    }
};

struct Point3D {
    double coords[3] = {0.0, 0.0, 0.0};

    bool operator==(const Point3D& other) const { return util::Equal(this->Distance(other), 0.0); }

    double Distance(const Point3D& other) const {
        return std::sqrt((coords[0] - other.coords[0]) * (coords[0] - other.coords[0]) + (coords[1] - other.coords[1]) * (coords[1] - other.coords[1]) +
                         (coords[2] - other.coords[2]) * (coords[2] - other.coords[2]));
    }
};

}  // namespace euclid::geometry
