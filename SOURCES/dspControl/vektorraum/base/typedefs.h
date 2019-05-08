/*
  ==============================================================================

    typedefs.h
    Created: 4 May 2018 5:00:06pm
    Author:  Raphael Knoop

  ==============================================================================
*/

#include <cmath>
#include <cstdint>
#include <complex>

#pragma once

namespace Vektorraum
{

typedef double tfloat;

typedef std::complex<double> tcomplex;
typedef std::complex<float> tcomplex32;

#if defined( MATLIB_USE_UINT64 )
typedef uint64_t tuint;
#elif defined( MATLIB_USE_UINT32 )
typedef uint32_t tuint;
#else
#warning uint undefined.
typedef uint_t tuint;
#endif

}
