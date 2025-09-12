#pragma once

/**
 * @file util.h
 * @author liuyulvv (liuyulvv@outlook.com)
 * @date 2025-09-10
 */

#include <algorithm>
#include <vector>

#include "algorithm/util/location.h"
#include "geometry/point.h"

namespace euclid::algorithm::convex_hull {

inline std::vector<geometry::Point2D> RemoveCoincidePoints(const std::vector<geometry::Point2D>& points) {
    if (points.empty()) {
        return {};
    }
    std::vector<geometry::Point2D> unique_points;
    unique_points.reserve(points.size());
    for (const auto& pt : points) {
        bool is_unique = true;
        for (const auto& upt : unique_points) {
            if (pt == upt) {
                is_unique = false;
                break;
            }
        }
        if (is_unique) {
            unique_points.push_back(pt);
        }
    }
    return unique_points;
}

inline std::vector<geometry::Point2D> SortExtremePoints(const std::vector<geometry::Point2D>& input_points) {
    if (input_points.size() < 3) {
        return {};
    }

    std::vector<geometry::Point2D> points = input_points;
    std::sort(points.begin(), points.end());

    std::vector<geometry::Point2D> convex_hull_points;
    convex_hull_points.reserve(points.size());
    convex_hull_points.push_back(points[0]);

    std::vector<int> inserted(points.size(), -1);
    inserted[0] = 0;

    size_t num_inserted = 1;
    size_t last_extreme_point_index = 0;

    for (; num_inserted < points.size();) {
        for (size_t j = 0; j < points.size(); ++j) {
            if (inserted[j] == -1) {
                bool has_right = false;
                for (size_t k = 0; k < points.size(); ++k) {
                    if (last_extreme_point_index == k || j == k) {
                        continue;
                    }
                    if (!util::IsTurnLeft(points[last_extreme_point_index], points[j], points[k])) {
                        has_right = true;
                        break;
                    }
                }
                if (!has_right) {
                    inserted[j] = j;
                    last_extreme_point_index = j;
                    convex_hull_points.push_back(points[j]);
                    num_inserted++;
                    break;
                }
            }
        }
    }
    return convex_hull_points;
}

}  // namespace euclid::algorithm::convex_hull