#pragma once

#include <string>

#include "../base/typedefs.h"
#include "../base/tvector.h"
#include "../base/tmatrix.h"

#if defined( USE_FFTS ) || defined( USE_APPLEVDSP )
#define HAVE_FFT
#endif

namespace Vektorraum
{

//==============================================================================
/*!
 */
tvector<double> fftconv( tvector<double> x, tvector<double> y );

//==============================================================================
/*! Perform a shift of the vector x, for use with the 'fft' and 'ifft'
    functions, in order the move the frequency 0 to the center of the vector.
 */
tvector<double> fftshift( tvector<double> x );

}
