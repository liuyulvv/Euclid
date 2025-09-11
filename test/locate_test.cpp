/**
 * @file locate_test.cpp
 * @author liuyulvv (liuyulvv@outlook.com)
 * @date 2025-09-11
 */

#include <gtest/gtest.h>

#include "algorithm/util/location.h"
#include "geometry/point.h"
#include "geometry/triangle.h"

using namespace euclid::geometry;
using namespace euclid::algorithm::util;

class LocateTest : public ::testing::Test {
protected:
    void SetUp() override {}

    void TearDown() override {}
};

TEST_F(LocateTest, ArePointsCollinearTest) {
    Point2D p1{0, 0};
    Point2D q1{1, 1};
    Point2D r1{2, 2};
    EXPECT_TRUE(ArePointsCollinear(p1, q1, r1));

    Point2D p2{0, 0};
    Point2D q2{1, 0};
    Point2D r2{0, 1};
    EXPECT_FALSE(ArePointsCollinear(p2, q2, r2));
}

TEST_F(LocateTest, IsPointOnSegmentTest) {
    Point2D p1{0, 0};
    Point2D q1{2, 2};
    Point2D r1{1, 1};
    EXPECT_TRUE(IsPointOnSegment(r1, p1, q1));

    Point2D p2{0, 0};
    Point2D q2{2, 2};
    Point2D r2{3, 3};
    EXPECT_FALSE(IsPointOnSegment(r2, p2, q2));

    Point2D p3{0, 0};
    Point2D q3{2, 2};
    Point2D r3{-1, -1};
    EXPECT_FALSE(IsPointOnSegment(r3, p3, q3));

    Point2D p4{0, 0};
    Point2D q4{2, 0};
    Point2D r4{1, 1};
    EXPECT_FALSE(IsPointOnSegment(r4, p4, q4));
}

TEST_F(LocateTest, IsTurnLeftTest) {
    Point2D p1{0, 0};
    Point2D q1{1, 0};
    Point2D r1{0, 1};
    EXPECT_TRUE(IsTurnLeft(p1, q1, r1));

    Point2D p2{0, 0};
    Point2D q2{1, 0};
    Point2D r2{0, -1};
    EXPECT_FALSE(IsTurnLeft(p2, q2, r2));

    Point2D p3{0, 0};
    Point2D q3{1, 1};
    Point2D r3{2, 2};
    EXPECT_FALSE(IsTurnLeft(p3, q3, r3));
}

TEST_F(LocateTest, IsTurnLeftOrOnRayTest) {
    Point2D p1{0, 0};
    Point2D q1{1, 0};
    Point2D r1{0, 1};
    EXPECT_TRUE(IsTurnLeftOrOnRay(p1, q1, r1));

    Point2D p2{0, 0};
    Point2D q2{1, 0};
    Point2D r2{0, -1};
    EXPECT_FALSE(IsTurnLeftOrOnRay(p2, q2, r2));

    Point2D p3{0, 0};
    Point2D q3{1, 1};
    Point2D r3{2, 2};
    EXPECT_TRUE(IsTurnLeftOrOnRay(p3, q3, r3));

    Point2D p4{0, 0};
    Point2D q4{1, 1};
    Point2D r4{-1, -1};
    EXPECT_FALSE(IsTurnLeftOrOnRay(p4, q4, r4));

    Point2D p5{0, 0};
    Point2D q5{1, 1};
    Point2D r5{0.5, 0.5};
    EXPECT_FALSE(IsTurnLeftOrOnRay(p5, q5, r5));
}

TEST_F(LocateTest, IsPointInTriangleTest) {
    Point2D p1{0, 0};
    Point2D p2{5, 0};
    Point2D p3{0, 5};
    Triangle2D triangle{p1, p2, p3};

    Point2D inside_point{1, 1};
    EXPECT_TRUE(IsPointInTriangle(inside_point, triangle));
    EXPECT_TRUE(IsPointInTriangle(inside_point, p1, p2, p3));

    Point2D outside_point{6, 6};
    EXPECT_FALSE(IsPointInTriangle(outside_point, triangle));
    EXPECT_FALSE(IsPointInTriangle(outside_point, p1, p2, p3));

    Point2D edge_point{0, 2};
    EXPECT_FALSE(IsPointInTriangle(edge_point, triangle));
    EXPECT_FALSE(IsPointInTriangle(edge_point, p1, p2, p3));

    Point2D vertex_point{0, 0};
    EXPECT_FALSE(IsPointInTriangle(vertex_point, triangle));
    EXPECT_FALSE(IsPointInTriangle(vertex_point, p1, p2, p3));
}