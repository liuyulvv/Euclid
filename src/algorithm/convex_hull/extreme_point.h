#pragma once

/**
 * @file extreme_point.h
 * @author liuyulvv (liuyulvv@outlook.com)
 * @date 2025-09-01
 */

#include "algorithm/util/location.h"
#include "geometry/point.h"
#include <algorithm>
#include <stdexcept>
#include <vector>

namespace euclid::algorithm::convex_hull
{

std::vector<geometry::Point2D> get_convex_hull_by_extreme_point(const std::vector<geometry::Point2D>& points)
{
    if (points.size() <= 3)
    {
        return points;
    }

    std::vector<bool> is_extreme_point(points.size(), false);
    for (size_t h = 0; h < points.size(); ++h)
    {
        bool is_extreme = true;
        for (size_t i = 0; i < points.size(); ++i)
        {
            if (h == i)
            {
                continue;
            }
            if (!is_extreme)
            {
                break;
            }
            for (size_t j = 0; j < points.size(); ++j)
            {
                if (h == j || i == j)
                {
                    continue;
                }
                if (!is_extreme)
                {
                    break;
                }
                for (size_t k = j + 1; k < points.size(); ++k)
                {
                    if (k == j || k == i || k == h)
                    {
                        continue;
                    }
                    if (!is_extreme)
                    {
                        break;
                    }
                    if (util::is_point_in_triangle(points[h], points[i], points[j], points[k]))
                    {
                        is_extreme = false;
                        break;
                    }
                }
            }
        }
        is_extreme_point[h] = is_extreme;
    }

    std::vector<euclid::geometry::Point2D> extreme_points;
    extreme_points.reserve(points.size());
    for (size_t h = 0; h < points.size(); ++h)
    {
        if (is_extreme_point[h])
        {
            extreme_points.push_back(points[h]);
        }
    }
    if (extreme_points.size() <= 3)
    {
        return extreme_points;
    }

    std::sort(extreme_points.begin(), extreme_points.end());

    std::vector<euclid::geometry::Point2D> convex_hull_points;
    convex_hull_points.reserve(extreme_points.size());
    convex_hull_points.push_back(extreme_points[0]);

    std::vector<int> inserted(extreme_points.size(), -1);
    inserted[0] = 0;
    size_t num_inserted = 1;
    size_t last_extreme_point_index = 0;
    for (; num_inserted < extreme_points.size();)
    {
        for (size_t j = 0; j < extreme_points.size(); ++j)
        {
            if (inserted[j] == -1)
            {
                bool has_right = false;
                for (size_t k = 0; k < extreme_points.size(); ++k)
                {
                    if (last_extreme_point_index == k || j == k)
                    {
                        continue;
                    }
                    if (!util::is_turn_left_or_on_ray(extreme_points[last_extreme_point_index], extreme_points[j], extreme_points[k]))
                    {
                        has_right = true;
                        break;
                    }
                }
                if (!has_right)
                {
                    inserted[j] = j;
                    last_extreme_point_index = j;
                    convex_hull_points.push_back(extreme_points[j]);
                    num_inserted++;
                    break;
                }
            }
        }
    }
    return convex_hull_points;
}

} // namespace euclid::algorithm::convex_hull
