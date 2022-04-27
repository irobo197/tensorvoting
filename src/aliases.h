#ifndef __ALIASES_H
#define __ALIASES_H

#include "pointmatcher/PointMatcher.h"
#include "pointmatcher/IO.h"

typedef float myScalar;

typedef Eigen::Matrix<myScalar, 3, 1> Vector3;
typedef Eigen::Matrix<myScalar, 3, 3> Matrix3;

typedef PointMatcher<myScalar> PM;
typedef PointMatcherIO<myScalar> PMIO;

typedef PM::TransformationParameters TP;
typedef PM::DataPoints DP;

#endif
