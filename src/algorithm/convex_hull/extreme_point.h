#pragma once

/**
 * @file extreme_point.h
 * @author liuyulvv (liuyulvv@outlook.com)
 * @date 2025-09-01
 */

#include <vector>

#include "algorithm/convex_hull/util.h"
#include "algorithm/util/location.h"
#include "geometry/point_2d.h"

namespace euclid::algorithm::convex_hull {

inline std::vector<geometry::Point2D> GetConvexHullByExtremePoint(const std::vector<geometry::Point2D>& input_points) {
    auto points = RemoveCoincidePoints(input_points);
    if (points.size() < 3) {
        return {};
    }

    std::vector<bool> is_extreme_point(points.size(), false);
    for (size_t h = 0; h < points.size(); ++h) {
        bool is_extreme = true;
        for (size_t i = 0; i < points.size(); ++i) {
            if (h == i) {
                continue;
            }
            if (!is_extreme) {
                break;
            }
            for (size_t j = 0; j < points.size(); ++j) {
                if (h == j || i == j) {
                    continue;
                }
                if (!is_extreme) {
                    break;
                }
                for (size_t k = j + 1; k < points.size(); ++k) {
                    if (k == j || k == i || k == h) {
                        continue;
                    }
                    if (!is_extreme) {
                        break;
                    }
                    if (util::IsPointInTriangle(points[h], points[i], points[j], points[k])) {
                        is_extreme = false;
                        break;
                    }
                }
            }
        }
        is_extreme_point[h] = is_extreme;
    }

    std::vector<geometry::Point2D> extreme_points;
    extreme_points.reserve(points.size());
    for (size_t h = 0; h < points.size(); ++h) {
        if (is_extreme_point[h]) {
            extreme_points.push_back(points[h]);
        }
    }
    return SortExtremePoints(extreme_points);
}

}  // namespace euclid::algorithm::convex_hull
