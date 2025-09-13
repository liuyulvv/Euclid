#pragma once

/**
 * @file extreme_edge.h
 * @author liuyulvv (liuyulvv@outlook.com)
 * @date 2025-09-11
 */

#include <algorithm>
#include <utility>
#include <vector>

#include "algorithm/convex_hull/util.h"
#include "algorithm/util/location.h"
#include "geometry/point_2d.h"

namespace euclid::algorithm::convex_hull {

inline std::vector<geometry::Point2D> GetConvexHullByExtremeEdge(const std::vector<geometry::Point2D>& input_points) {
    auto points = RemoveCoincidePoints(input_points);
    if (points.size() < 3) {
        return points;
    }
    std::sort(points.begin(), points.end());
    std::vector<std::pair<geometry::Point2D, geometry::Point2D>> extreme_edges;
    for (size_t i = 0; i < points.size(); ++i) {
        for (size_t j = i + 1; j < points.size(); ++j) {
            bool is_extreme_edge = true;
            bool is_left_turn = false;
            bool is_right_turn = false;
            for (size_t k = 0; k < points.size(); ++k) {
                if (k == i || k == j) {
                    continue;
                }
                if (util::IsTurnLeft(points[i], points[j], points[k])) {
                    is_left_turn = true;
                } else if (util::ArePointsCollinear(points[i], points[j], points[k])) {
                    if (!util::IsPointOnSegment(points[k], points[i], points[j])) {
                        is_extreme_edge = false;
                        break;
                    }
                } else {
                    is_right_turn = true;
                }
                if (is_left_turn && is_right_turn) {
                    is_extreme_edge = false;
                    break;
                }
            }
            if (is_extreme_edge) {
                extreme_edges.emplace_back(points[i], points[j]);
            }
        }
    }
    if (extreme_edges.size() < 3) {
        return {};
    }
    std::vector<geometry::Point2D> extreme_points;
    for (const auto& edge : extreme_edges) {
        extreme_points.push_back(edge.first);
        extreme_points.push_back(edge.second);
    }
    extreme_points = RemoveCoincidePoints(extreme_points);
    return SortExtremePoints(extreme_points);
}

}  // namespace euclid::algorithm::convex_hull