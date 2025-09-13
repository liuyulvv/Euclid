#pragma once

/**
 * @file graham_scan.h
 * @author liuyulvv (liuyulvv@outlook.com)
 * @date 2025-09-11
 */

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <stack>
#include <vector>

#include "algorithm/util/location.h"
#include "algorithm/util/sort.h"
#include "geometry/point_2d.h"

namespace euclid::algorithm::convex_hull {

inline std::vector<geometry::Point2D> GetConvexHullByGrahamScan(const std::vector<geometry::Point2D>& input_points) {
    if (input_points.size() < 3) {
        return {};
    }

    struct PointWithAngle {
        geometry::Point2D point;
        double angle;
    };

    auto lowest_then_leftest_index = util::GetLowestThenLeftestPointIndex(input_points);

    std::vector<geometry::Point2D> convex_hull_points(input_points.size());
    convex_hull_points[0] = input_points[lowest_then_leftest_index];

    std::vector<PointWithAngle> points_with_angles;
    for (size_t i = 0; i < input_points.size(); ++i) {
        if (i == lowest_then_leftest_index) {
            continue;
        }
        points_with_angles.emplace_back(input_points[i],
                                        std::atan2(input_points[i].coords[1] - convex_hull_points[0].coords[1],
                                                   input_points[i].coords[0] - convex_hull_points[0].coords[0]));
    }

    auto PointWithAngleComparator = [&convex_hull_points](const PointWithAngle& a, const PointWithAngle& b) {
        if (a.angle == b.angle) {
            return a.point.Distance(convex_hull_points[0]) < b.point.Distance(convex_hull_points[0]);
        }
        return a.angle < b.angle;
    };

    std::sort(points_with_angles.begin(), points_with_angles.end(), PointWithAngleComparator);

    std::stack<geometry::Point2D> potential_hull_points;
    for (size_t i = points_with_angles.size(); i > 1; --i) {
        potential_hull_points.push(points_with_angles[i - 1].point);
    }

    convex_hull_points[1] = points_with_angles[0].point;
    size_t last_index = 0;
    size_t current_index = 1;

    while (!potential_hull_points.empty()) {
        auto& last_point = convex_hull_points[last_index];
        auto& current_point = convex_hull_points[current_index];
        auto& next_point = potential_hull_points.top();

        if (util::IsTurnLeft(last_point, current_point, next_point)) {
            convex_hull_points[current_index + 1] = next_point;
            last_index++;
            current_index++;
            potential_hull_points.pop();
        } else {
            current_index--;
            last_index--;
        }
    }
    convex_hull_points.resize(current_index + 1);

    return convex_hull_points;
}

}  // namespace euclid::algorithm::convex_hull
