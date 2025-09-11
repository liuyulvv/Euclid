#pragma once

/**
 * @file location.h
 * @author liuyulvv (liuyulvv@outlook.com)
 * @date 2025-09-01
 */

#include "geometry/point.h"
#include "geometry/triangle.h"
#include "util/compare.h"

namespace euclid::algorithm::util {

/**
 * @brief Determines if three points are collinear.
 *
 * @param p The first point.
 * @param q The second point.
 * @param r The third point.
 * @return true if the points are collinear, false otherwise.
 */
inline bool ArePointsCollinear(const geometry::Point2D& p, const geometry::Point2D& q, const geometry::Point2D& r) {
    auto cross_value =
        p.coords[0] * q.coords[1] - p.coords[1] * q.coords[0] + q.coords[0] * r.coords[1] - q.coords[1] * r.coords[0] + r.coords[0] * p.coords[1] - r.coords[1] * p.coords[0];
    return euclid::util::Equal(cross_value, 0.0);
}

/**
 * @brief Determines if a point is on the line segment defined by two endpoints.
 *
 * @param point The point to check.
 * @param p The first endpoint of the segment.
 * @param q The second endpoint of the segment.
 * @return true if the point is on the segment, false otherwise.
 */
inline bool IsPointOnSegment(const geometry::Point2D& point, const geometry::Point2D& p, const geometry::Point2D& q) {
    auto cross_value = p.coords[0] * q.coords[1] - p.coords[1] * q.coords[0] + q.coords[0] * point.coords[1] - q.coords[1] * point.coords[0] + point.coords[0] * p.coords[1] -
                       point.coords[1] * p.coords[0];
    if (euclid::util::Equal(cross_value, 0.0)) {
        // p, q, r are collinear
        auto pq_pr_dot_value = (q.coords[0] - p.coords[0]) * (point.coords[0] - p.coords[0]) + (q.coords[1] - p.coords[1]) * (point.coords[1] - p.coords[1]);
        auto pq_pq_dot_value = (q.coords[0] - p.coords[0]) * (q.coords[0] - p.coords[0]) + (q.coords[1] - p.coords[1]) * (q.coords[1] - p.coords[1]);
        if (euclid::util::GreaterEqual(pq_pr_dot_value, 0.0) && euclid::util::LessEqual(pq_pr_dot_value, pq_pq_dot_value)) {
            // point r is on the segment pq
            return true;
        }
    }
    return false;
}

/**
 * @brief Determines if the sequence of points p, q, r makes a left turn.
 *
 * @param p The first point.
 * @param q The second point.
 * @param r The third point.
 * @return true if the turn from pq to qr is to the left, false otherwise.
 */
inline bool IsTurnLeft(const geometry::Point2D& p, const geometry::Point2D& q, const geometry::Point2D& r) {
    auto cross_value =
        p.coords[0] * q.coords[1] - p.coords[1] * q.coords[0] + q.coords[0] * r.coords[1] - q.coords[1] * r.coords[0] + r.coords[0] * p.coords[1] - r.coords[1] * p.coords[0];
    return euclid::util::Greater(cross_value, 0.0);
}

/**
 * @brief Determines if the sequence of points p, q, r makes a left turn or r is on the ray pq(not include segment pq).
 *
 * @param p The first point.
 * @param q The second point.
 * @param r The third point.
 * @return true if the turn from pq to qr is to the left(r on the ray pq but not on segment pq is consider as true), false otherwise.
 */
inline bool IsTurnLeftOrOnRay(const geometry::Point2D& p, const geometry::Point2D& q, const geometry::Point2D& r) {
    auto cross_value =
        p.coords[0] * q.coords[1] - p.coords[1] * q.coords[0] + q.coords[0] * r.coords[1] - q.coords[1] * r.coords[0] + r.coords[0] * p.coords[1] - r.coords[1] * p.coords[0];
    if (euclid::util::Equal(cross_value, 0.0)) {
        // p, q, r are collinear
        auto pq_pr_dot_value = (q.coords[0] - p.coords[0]) * (r.coords[0] - p.coords[0]) + (q.coords[1] - p.coords[1]) * (r.coords[1] - p.coords[1]);
        auto pq_pq_dot_value = (q.coords[0] - p.coords[0]) * (q.coords[0] - p.coords[0]) + (q.coords[1] - p.coords[1]) * (q.coords[1] - p.coords[1]);
        if (euclid::util::GreaterEqual(pq_pr_dot_value, 0.0) && euclid::util::LessEqual(pq_pr_dot_value, pq_pq_dot_value)) {
            // point r is on the segment pq
            return false;
        }
        if (euclid::util::Greater(pq_pr_dot_value, 0.0)) {
            // point r is on the ray pq
            return true;
        }
        // point r is ont thr ray qp
        return false;
    }
    return euclid::util::Greater(cross_value, 0.0);
}

/**
 * @brief Checks if a point is inside a given triangle.
 *
 * @param point The point to check.
 * @param triangle The triangle to check against.
 * @return true if the point is inside the triangle, false otherwise.
 */
inline bool IsPointInTriangle(const geometry::Point2D& point, const geometry::Triangle2D& triangle) {
    bool is_left_1 = IsTurnLeft(triangle.vertices[0], triangle.vertices[1], point);
    bool is_left_2 = IsTurnLeft(triangle.vertices[1], triangle.vertices[2], point);
    bool is_left_3 = IsTurnLeft(triangle.vertices[2], triangle.vertices[0], point);
    return is_left_1 == is_left_2 && is_left_2 == is_left_3;
}

/**
 * @brief Checks if a point is inside a given triangle.
 *
 * @param point The point to check.
 * @param p The first point.
 * @param q The second point.
 * @param r The third point.
 * @return true if the point is inside the triangle, false otherwise.
 */
inline bool IsPointInTriangle(const geometry::Point2D& point, const geometry::Point2D& p, const geometry::Point2D& q, const geometry::Point2D& r) {
    bool is_left_1 = IsTurnLeft(p, q, point);
    bool is_left_2 = IsTurnLeft(q, r, point);
    bool is_left_3 = IsTurnLeft(r, p, point);
    return is_left_1 == is_left_2 && is_left_2 == is_left_3;
}

}  // namespace euclid::algorithm::util
