#pragma once

#include "gtest/gtest.h"
#include "../FVM/VectorNt.hpp"

// ============================================================================
// Vector2d Construction Tests
// ============================================================================

TEST(Vector2dTest, DefaultConstruction)
{
    Vector2d vec;
    ASSERT_DOUBLE_EQ(vec[0], 0.0);
    ASSERT_DOUBLE_EQ(vec[1], 0.0);
}

TEST(Vector2dTest, ValueConstruction)
{
    Vector2d vec{3.0, 4.0};
    ASSERT_DOUBLE_EQ(vec[0], 3.0);
    ASSERT_DOUBLE_EQ(vec[1], 4.0);
}

TEST(Vector2dTest, CopyConstruction)
{
    Vector2d vec1{2.5, 3.5};
    Vector2d vec2(vec1);
    ASSERT_DOUBLE_EQ(vec2[0], 2.5);
    ASSERT_DOUBLE_EQ(vec2[1], 3.5);
}

TEST(Vector2dTest, MoveConstruction)
{
    Vector2d vec1{1.5, 2.5};
    Vector2d vec2(std::move(vec1));
    ASSERT_DOUBLE_EQ(vec2[0], 1.5);
    ASSERT_DOUBLE_EQ(vec2[1], 2.5);
}

// ============================================================================
// Vector2d Assignment Tests
// ============================================================================

TEST(Vector2dTest, CopyAssignment)
{
    Vector2d vec1{5.0, 6.0};
    Vector2d vec2;
    vec2 = vec1;
    ASSERT_DOUBLE_EQ(vec2[0], 5.0);
    ASSERT_DOUBLE_EQ(vec2[1], 6.0);
}

TEST(Vector2dTest, MoveAssignment)
{
    Vector2d vec1{7.0, 8.0};
    Vector2d vec2;
    vec2 = std::move(vec1);
    ASSERT_DOUBLE_EQ(vec2[0], 7.0);
    ASSERT_DOUBLE_EQ(vec2[1], 8.0);
}

// ============================================================================
// Vector2d Arithmetic Operations Tests
// ============================================================================

TEST(Vector2dTest, MultiplicationByScalar)
{
    Vector2d vec{2.0, 3.0};
    Vector2d result = vec * 2.0;
    ASSERT_DOUBLE_EQ(result[0], 4.0);
    ASSERT_DOUBLE_EQ(result[1], 6.0);
}

TEST(Vector2dTest, ScalarMultiplicationCommutative)
{
    Vector2d vec{2.0, 3.0};
    Vector2d result1 = vec * 2.0;
    Vector2d result2 = 2.0 * vec;
    ASSERT_DOUBLE_EQ(result1[0], result2[0]);
    ASSERT_DOUBLE_EQ(result1[1], result2[1]);
}

TEST(Vector2dTest, DivisionByScalar)
{
    Vector2d vec{6.0, 8.0};
    Vector2d result = vec / 2.0;
    ASSERT_DOUBLE_EQ(result[0], 3.0);
    ASSERT_DOUBLE_EQ(result[1], 4.0);
}

TEST(Vector2dTest, VectorAddition)
{
    Vector2d vec1{1.0, 2.0};
    Vector2d vec2{3.0, 4.0};
    Vector2d result = vec1 + vec2;
    ASSERT_DOUBLE_EQ(result[0], 4.0);
    ASSERT_DOUBLE_EQ(result[1], 6.0);
}

TEST(Vector2dTest, VectorSubtraction)
{
    Vector2d vec1{5.0, 7.0};
    Vector2d vec2{2.0, 3.0};
    Vector2d result = vec1 - vec2;
    ASSERT_DOUBLE_EQ(result[0], 3.0);
    ASSERT_DOUBLE_EQ(result[1], 4.0);
}

// ============================================================================
// Vector2d Comparison Tests
// ============================================================================

TEST(Vector2dTest, EqualityOperator)
{
    Vector2d vec1{1.5, 2.5};
    Vector2d vec2{1.5, 2.5};
    Vector2d vec3{1.5, 3.0};
    
    ASSERT_TRUE(vec1 == vec2);
    ASSERT_FALSE(vec1 == vec3);
}

TEST(Vector2dTest, InequalityOperator)
{
    Vector2d vec1{1.5, 2.5};
    Vector2d vec2{1.5, 2.5};
    Vector2d vec3{1.5, 3.0};
    
    ASSERT_FALSE(vec1 != vec2);
    ASSERT_TRUE(vec1 != vec3);
}

// ============================================================================
// Vector2d Magnitude Tests
// ============================================================================

TEST(Vector2dTest, MagnitudeOfUnitVector)
{
    Vector2d vec{1.0, 0.0};
    ASSERT_DOUBLE_EQ(vec.Magnitude(), 1.0);
}

TEST(Vector2dTest, Magnitude3_4_5Triangle)
{
    Vector2d vec{3.0, 4.0};
    ASSERT_DOUBLE_EQ(vec.Magnitude(), 5.0);
}

TEST(Vector2dTest, MagnitudeOfZeroVector)
{
    Vector2d vec{0.0, 0.0};
    ASSERT_DOUBLE_EQ(vec.Magnitude(), 0.0);
}

TEST(Vector2dTest, MagnitudeOfNegativeComponents)
{
    Vector2d vec{-3.0, -4.0};
    ASSERT_DOUBLE_EQ(vec.Magnitude(), 5.0);
}

// ============================================================================
// Vector2d Dot Product Tests
// ============================================================================

TEST(Vector2dTest, DotProductOrthogonal)
{
    Vector2d vec1{1.0, 0.0};
    Vector2d vec2{0.0, 1.0};
    ASSERT_DOUBLE_EQ(vec1.Dot(vec2), 0.0);
}

TEST(Vector2dTest, DotProductParallel)
{
    Vector2d vec1{2.0, 3.0};
    Vector2d vec2{2.0, 3.0};
    ASSERT_DOUBLE_EQ(vec1.Dot(vec2), 4.0 + 9.0);  // 13.0
}

TEST(Vector2dTest, DotProductGeneral)
{
    Vector2d vec1{1.0, 2.0};
    Vector2d vec2{3.0, 4.0};
    ASSERT_DOUBLE_EQ(vec1.Dot(vec2), 11.0);  // 1*3 + 2*4 = 11
}

TEST(Vector2dTest, DotProductCommutative)
{
    Vector2d vec1{2.5, 3.5};
    Vector2d vec2{1.5, 2.5};
    ASSERT_DOUBLE_EQ(vec1.Dot(vec2), vec2.Dot(vec1));
}

// ============================================================================
// Vector2d Cross Product Tests (2D returns scalar)
// ============================================================================

TEST(Vector2dTest, CrossProductOrthogonal)
{
    Vector2d vec1{1.0, 0.0};
    Vector2d vec2{0.0, 1.0};
    ASSERT_DOUBLE_EQ(vec1.Cross(vec2), 1.0);
}

TEST(Vector2dTest, CrossProductAntiCommutative)
{
    Vector2d vec1{2.0, 3.0};
    Vector2d vec2{1.0, 4.0};
    ASSERT_DOUBLE_EQ(vec1.Cross(vec2), -vec2.Cross(vec1));
}

TEST(Vector2dTest, CrossProductParallel)
{
    Vector2d vec1{2.0, 4.0};
    Vector2d vec2{1.0, 2.0};
    ASSERT_DOUBLE_EQ(vec1.Cross(vec2), 0.0);
}

TEST(Vector2dTest, CrossProductGeneral)
{
    Vector2d vec1{3.0, 4.0};
    Vector2d vec2{2.0, 1.0};
    // 3*1 - 4*2 = 3 - 8 = -5
    ASSERT_DOUBLE_EQ(vec1.Cross(vec2), -5.0);
}

// ============================================================================
// Complex Operation Tests
// ============================================================================

TEST(Vector2dTest, ChainedOperations)
{
    Vector2d vec{2.0, 3.0};
    Vector2d result = (vec * 2.0 + Vector2d{1.0, 1.0}) / 2.0;
    
    // (2, 3) * 2 = (4, 6)
    // (4, 6) + (1, 1) = (5, 7)
    // (5, 7) / 2 = (2.5, 3.5)
    ASSERT_DOUBLE_EQ(result[0], 2.5);
    ASSERT_DOUBLE_EQ(result[1], 3.5);
}

TEST(Vector2dTest, IndexAccess)
{
    Vector2d vec{10.0, 20.0};
    ASSERT_DOUBLE_EQ(vec[0], 10.0);
    ASSERT_DOUBLE_EQ(vec[1], 20.0);
}

TEST(Vector2dTest, IndexAccessMutable)
{
    Vector2d vec{5.0, 6.0};
    vec[0] = 15.0;
    vec[1] = 25.0;
    
    ASSERT_DOUBLE_EQ(vec[0], 15.0);
    ASSERT_DOUBLE_EQ(vec[1], 25.0);
}

// ============================================================================
// Edge Cases
// ============================================================================

TEST(Vector2dTest, VerySmallMagnitude)
{
    Vector2d vec{1e-8, 1e-8};
    double mag = vec.Magnitude();
    ASSERT_GT(mag, 0.0);
    ASSERT_LT(mag, 1e-7);
}

TEST(Vector2dTest, LargeMagnitude)
{
    Vector2d vec{1e6, 1e6};
    double mag = vec.Magnitude();
    ASSERT_GT(mag, 1e6);
}

TEST(Vector2dTest, NegativeComponents)
{
    Vector2d vec{-3.0, -4.0};
    Vector2d scaled = vec * 2.0;
    
    ASSERT_DOUBLE_EQ(scaled[0], -6.0);
    ASSERT_DOUBLE_EQ(scaled[1], -8.0);
}

TEST(Vector2dTest, MixedSignComponents)
{
    Vector2d vec1{1.0, -2.0};
    Vector2d vec2{-3.0, 4.0};
    Vector2d sum = vec1 + vec2;
    
    ASSERT_DOUBLE_EQ(sum[0], -2.0);
    ASSERT_DOUBLE_EQ(sum[1], 2.0);
}
