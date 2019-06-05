#include <cmath>
#include <complex>
#include <cstdint>

#include <iostream>

#include "../fft/fft.h"

#include "signal.h"

namespace Vektorraum
{

#if defined( HAVE_FFT )
//==============================================================================
/*!
 */
tvector<double> fftconv( tvector<double> x, tvector<double> y )
{
  tuint nfft = 1;

  while( nfft < length(x) + length(y) - 1 )
    nfft *= 2;

/*  if( length(x) > length(y) )
    nfft = static_cast<tuint>( std::pow( 2.0 , std::ceil( std::log((double) length(x) )/std::log(2.0) ) ) );
  else
    nfft = static_cast<tuint>( std::pow( 2.0 , std::ceil( std::log((double) length(y) )/std::log(2.0) ) ) );
*/
  tvector<tcomplex> A = fft( x, nfft );
  tvector<tcomplex> B = fft( y, nfft );
  tvector<tcomplex> z = ifft( A*B, nfft ) /  static_cast<double>(nfft) ;

  tvector<double> ret( length(x) + length(y) - 1 );
  for( tuint k = 0; k < length(ret); k++ )
    ret[k] = std::real( z[k] );

  return ret;
}

#else

tvector<double> fftconv( tvector<double>, tvector<double> )
{
#if !defined( __WIN__ )
  #warning fftconv() not implemented.
#endif
  tvector<double> y;
  return y;
}

#endif

}
