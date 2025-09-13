#pragma once

/**
 * @file sort.h
 * @author liuyulvv (liuyulvv@outlook.com)
 * @date 2025-09-11
 */

#include <cstddef>
#include <vector>

#include "geometry/point_2d.h"

namespace euclid::algorithm::util {

inline size_t GetLowestThenLeftestPointIndex(const std::vector<geometry::Point2D>& input_points) {
    if (input_points.empty()) {
        return -1;
    }
    size_t index = 0;
    for (size_t i = 1; i < input_points.size(); ++i) {
        if (euclid::util::Less(input_points[i].coords[1], input_points[index].coords[1]) ||
            (euclid::util::Equal(input_points[i].coords[1], input_points[index].coords[1]) &&
             euclid::util::Less(input_points[i].coords[0], input_points[index].coords[0]))) {
            index = i;
        }
    }
    return index;
}

}  // namespace euclid::algorithm::util