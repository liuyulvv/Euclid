#include <gtest/gtest.h>

#include <iostream>

#include "algorithm/convex_hull/extreme_point.h"
#include "geometry/point.h"

using namespace euclid::geometry;
using namespace euclid::algorithm::convex_hull;

class ConvexHullTest : public ::testing::Test {
protected:
    std::vector<Point2D> points1_ = {{0, 0}, {1, 0}, {1, 1}, {0, 1}, {0, 2}};

protected:
    void SetUp() override {}

    void TearDown() override {}
};

TEST_F(ConvexHullTest, GetConvexHullByExtremePointsTest) {
    auto convex_extreme_points = GetConvexHullByExtremePoints(points1_);

    for (auto &point : convex_extreme_points) {
        std::cout << point.coords[0] << ", " << point.coords[1] << std::endl;
    }
}