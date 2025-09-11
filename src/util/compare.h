#pragma once

/**
 * @file compare.h
 * @author liuyulvv (liuyulvv@outlook.com)
 * @date 2025-09-03
 */

#include <cmath>

namespace euclid::util {

/**
 * @brief Compare two floating-point numbers for equality within a specified tolerance.
 *
 * @param a First floating-point number.
 * @param b Second floating-point number.
 * @param eps Tolerance for comparison (default is 1e-6).
 * @return true if the numbers are considered equal within the tolerance, false otherwise.
 */
inline bool Equal(double a, double b, double eps = 1e-6) { return std::abs(a - b) < eps; }

/**
 * @brief Compare two floating-point numbers for less-than within a specified tolerance.
 *
 * @param a First floating-point number.
 * @param b Second floating-point number.
 * @param eps Tolerance for comparison (default is 1e-6).
 * @return true if a is less than b considering the tolerance, false otherwise.
 */
inline bool Less(double a, double b, double eps = 1e-6) { return a < b - eps; }

/**
 * @brief Compare two floating-point numbers for greater-than within a specified tolerance.
 *
 * @param a First floating-point number.
 * @param b Second floating-point number.
 * @param eps Tolerance for comparison (default is 1e-6).
 * @return true if a is greater than b considering the tolerance, false otherwise.
 */
inline bool Greater(double a, double b, double eps = 1e-6) { return a > b + eps; }

/**
 * @brief Compare two floating-point numbers for less-than-or-equal within a specified tolerance.
 *
 * @param a First floating-point number.
 * @param b Second floating-point number.
 * @param eps Tolerance for comparison (default is 1e-6).
 * @return true if a is less than or equal to b considering the tolerance, false otherwise
 */
inline bool LessEqual(double a, double b, double eps = 1e-6) { return Less(a, b, eps) || Equal(a, b, eps); }

/**
 * @brief Compare two floating-point numbers for greater-than-or-equal within a specified tolerance.
 *
 * @param a First floating-point number.
 * @param b Second floating-point number.
 * @param eps Tolerance for comparison (default is 1e-6).
 * @return true if a is greater than or equal to b considering the tolerance, false otherwise.
 */
inline bool GreaterEqual(double a, double b, double eps = 1e-6) { return Greater(a, b, eps) || Equal(a, b, eps); }

}  // namespace euclid::util
