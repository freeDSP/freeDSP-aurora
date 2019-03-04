#pragma once

#include "../base/typedefs.h"
#include "../base/tvector.h"

namespace Vektorraum
{

//==============================================================================
/*! Compute the discrete Fourier transform of A using a Fast Fourier
    Transform (FFT) algorithm.
    \param x Input values.
    \param nfft Length of FFT.
*/
tvector<tcomplex> fft( tvector<double> x, tuint nfft );

//==============================================================================
/*! Compute the inverse discrete Fourier transform of A using a Fast Fourier
    Transform (FFT) algorithm.
    \param x Input values.
    \param nfft Length of FFT.
*/
tvector<tcomplex> ifft( tvector<tcomplex> Y, tuint nfft );

}
