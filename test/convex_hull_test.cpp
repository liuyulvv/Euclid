/**
 * @file convex_hull_test.cpp
 * @author liuyulvv (liuyulvv@outlook.com)
 * @date 2025-09-11
 */

#include <gtest/gtest.h>

#include "algorithm/convex_hull/extreme_edge.h"
#include "algorithm/convex_hull/extreme_point.h"
#include "geometry/point.h"

using namespace euclid::geometry;
using namespace euclid::algorithm::convex_hull;

class ConvexHullTest : public ::testing::Test {
protected:
    std::vector<Point2D> points1_ = {{0, 0}, {1, 0}, {1, 1}, {0, 1}, {0, 2}};
    std::vector<Point2D> expected_points1_ = {{0, 0}, {1, 0}, {1, 1}, {0, 2}};

protected:
    void SetUp() override {}

    void TearDown() override {}
};

TEST_F(ConvexHullTest, GetConvexHullByExtremePointsTest) {
    auto convex_extreme_points = GetConvexHullByExtremePoint(points1_);
    EXPECT_EQ(convex_extreme_points.size(), 4);
    EXPECT_EQ(convex_extreme_points[0], expected_points1_[0]);
    EXPECT_EQ(convex_extreme_points[1], expected_points1_[1]);
    EXPECT_EQ(convex_extreme_points[2], expected_points1_[2]);
    EXPECT_EQ(convex_extreme_points[3], expected_points1_[3]);
}

TEST_F(ConvexHullTest, GetConvexHullByExtremeEdgeTest) {
    auto convex_extreme_points = GetConvexHullByExtremeEdge(points1_);
    EXPECT_EQ(convex_extreme_points.size(), 4);
    EXPECT_EQ(convex_extreme_points[0], expected_points1_[0]);
    EXPECT_EQ(convex_extreme_points[1], expected_points1_[1]);
    EXPECT_EQ(convex_extreme_points[2], expected_points1_[2]);
    EXPECT_EQ(convex_extreme_points[3], expected_points1_[3]);
}