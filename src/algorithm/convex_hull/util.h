#pragma once

/**
 * @file util.h
 * @author liuyulvv (liuyulvv@outlook.com)
 * @date 2025-09-10
 */

#include "geometry/point.h"
#include <vector>

namespace euclid::algorithm::convex_hull
{

std::vector<geometry::Point2D> remove_coincide_points(const std::vector<geometry::Point2D>& points)
{
    if (points.empty())
    {
        return {};
    }
    std::vector<geometry::Point2D> unique_points;
    unique_points.reserve(points.size());
    for (const auto& pt : points)
    {
        bool is_unique = true;
        for (const auto& upt : unique_points)
        {
            if (pt == upt)
            {
                is_unique = false;
                break;
            }
        }
        if (is_unique)
        {
            unique_points.push_back(pt);
        }
    }
    return unique_points;
}

} // namespace euclid::algorithm::convex_hull