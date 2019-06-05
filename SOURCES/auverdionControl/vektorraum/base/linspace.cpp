/*
  ==============================================================================

    linspace.cpp
    Created: 7 May 2018 11:27:20am
    Author:  Raphael Knoop

  ==============================================================================
*/

#include <cstdint>

#include "tvector.h"

namespace Vektorraum
{

//============================================================================
/*! Returns a vector with N linearly spaced elements between base and limit.
    \param base Base value
    \param limit Limit value
    \param N Number of elements
*/
tvector<double> linspace( double base, double limit, uint64_t N )
{
  tvector<double> y( N );
#if !defined( __WIN__ )
  #warning TODO: Special cases.
#endif
  double step = (limit - base) / static_cast<double>( N - 1 );
  for( uint64_t ii = 0; ii < N; ii++ )
    y[ii] = base + static_cast<double>(ii) * step;

  return y;
}

}
