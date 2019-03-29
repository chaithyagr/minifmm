#pragma once

#include <float.h>
#include <complex>
#include <math.h>

using TYPE=double; 
using TYPE_COMPLEX=std::complex<double>;
#define TYPE_MAX DBL_MAX
#define TYPE_ONE 1.0
#define TYPE_EPS 5.0e-8
#define TYPE_SQRT(x) sqrt(x)
#define TYPE_ZERO 0.0
#define TYPE_TWO 2.0
#define TYPE_SIN(x) sin(x)
#define TYPE_COS(x) cos(x)
#define TYPE_ATAN2(x,y) atan2(x,y)
#define TYPE_ACOS(x) acos(x)
#define TYPE_CPOW(x,y) cpow(x,y)
#define TYPE_CEXP(x) cexp(x)
#define TYPE_ABS(x) fabs(x)
#define TYPE_CONJ(x) conj(x)

