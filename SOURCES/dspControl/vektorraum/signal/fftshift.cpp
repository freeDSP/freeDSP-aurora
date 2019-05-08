#include <cmath>
#include <complex>
#include <cstdint>

#include <iostream>

#include "../base/typedefs.h"
#include "../base/tvector.h"
#include "../base/tmatrix.h"

namespace Vektorraum
{

//==============================================================================
/*! Perform a shift of the vector x, for use with the 'fft' and 'ifft'
    functions, in order the move the frequency 0 to the center of the vector.
 */
tvector<double> fftshift( tvector<double> x )
{
  tuint xl = length( x );
  tuint xx = static_cast<tuint>( ceil ( static_cast<double>(xl) / 2.0) );

  tvector<double> ret( length(x) );
  tuint n = 0;
  tvector<double> x1 = x( xx, xl-1 );
  tvector<double> x2 = x(  0, xx-1 );

  for( tuint ii = 0; ii < length(x1); ii++ )
  {
    ret[n] = x1[ii];
    n++;
  }

  for( tuint ii = 0; ii < length(x2); ii++ )
  {
    ret[n] = x2[ii];
    n++;
  }

  return ret;
}

}
