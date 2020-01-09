#include <cmath>

#ifdef HAVE_SSE
#include <xmmintrin.h>
#endif

#if defined( USE_FFTS )
#if defined( __WIN__ )
#include "ffts.h"
#include "ffts_attributes.h"
#else
#include <ffts/ffts.h>
#endif

#elif defined( USE_APPLEVDSP )
#include <Accelerate/Accelerate.h>

#endif

#include "fft.h"

namespace Vektorraum
{

//==============================================================================
/*! Compute the discrete Fourier transform of A using a Fast Fourier
    Transform (FFT) algorithm.
    \param x Input values.
    \param nfft Length of FFT.
*/
#if defined( USE_FFTS )
tvector<tcomplex> ifft( tvector<tcomplex> Y, tuint nfft )
{
	tvector<tcomplex> x( nfft );

    /*#ifdef HAVE_SSE
	float __attribute__ ((aligned(32))) *input = (float*)_mm_malloc(2 * nfft * sizeof(float), 32);
	float __attribute__ ((aligned(32))) *output = (float*)_mm_malloc(2 * nfft * sizeof(float), 32);
	#else
	float __attribute__ ((aligned(32))) *input = valloc(2 * nfft * sizeof(float));
	float __attribute__ ((aligned(32))) *output = valloc(2 * nfft * sizeof(float));
    #endif*/

    #if defined( __WIN__ )
    float* input = (float*)_aligned_malloc( 2 * nfft * sizeof(float), 32 );
    float* output = (float*)_aligned_malloc( 2 * nfft * sizeof(float), 32 );

    #elif defined( HAVE_SSE )
    float FFTS_ALIGN(32) *input = _mm_malloc(2 * nfft * sizeof(float), 32);
    float FFTS_ALIGN(32) *output = _mm_malloc(2 * nfft * sizeof(float), 32);

    #else
    float FFTS_ALIGN(32) *input = valloc(2 * nfft * sizeof(float));
    float FFTS_ALIGN(32) *output = valloc(2 * nfft * sizeof(float));
    #endif

  //--- load data to input buffers ---
	for( tuint ii = 0; ii < nfft; ii++ )
	{
		if( ii < length(x) )
		{
		  input[ 2*ii ]     = static_cast<float>( std::real(Y[ii]) );
			input[ 2*ii + 1 ] = static_cast<float>( std::imag(Y[ii]) );
		}
		else
		{
		  input[ 2*ii ]     = 0.0f;
		  input[ 2*ii + 1 ] = 0.0f;
		}
	}

	//--- execute FFT ---
	ffts_plan_t* p = ffts_init_1d( nfft, 1 );
	if( p )
	{
		ffts_execute( p, input, output );
		ffts_free( p );
	}
	else
	{
		std::cerr<<"[ERROR] fft(): Could not create a plan."<<std::endl;
		return Y;
	}

  //double norm = 1.0 / static_cast<double>(nfft);
  for( tuint ii = 0; ii < nfft; ii++ )
    x[ii] = tcomplex( output[ 2*ii ], output[ 2*ii+1 ] ); // * norm;

	return x;
}

#elif defined( USE_APPLEVDSP )

uint64_t ifft_getThePowerOfTwo( uint64_t value )
{
  for( tuint n = 0; n < 64; n++ )
	{
    if( value <= (1 << n) )
      return n;
  }
  return 64;
}

tvector<tcomplex> ifft( tvector<tcomplex> Y, tuint nfft )
{
  const tuint order = ifft_getThePowerOfTwo( nfft );
	tvector<tcomplex> x( nfft );

	DSPSplitComplex inout;
  inout.realp = new float[ nfft ];
  inout.imagp = new float[ nfft ];

  // load data to input buffers (zero-padding if needed)
	for( tuint ii = 0; ii < nfft; ii++ )
	{
		if( ii < length(x) )
		{
		  inout.realp[ ii ] = static_cast<float>( std::real(Y[ii]) );
			inout.imagp[ ii ] = static_cast<float>( std::imag(Y[ii]) );
		}
		else
		{
		  inout.imagp[ ii ] = 0.0f;
		  inout.imagp[ ii ] = 0.0f;
		}
	}

	FFTSetup planVDSP = vDSP_create_fftsetup( order, kFFTRadix2 );

  // execute FFT
	vDSP_fft_zip( planVDSP, &inout, 1, order, kFFTDirection_Inverse );

	for( tuint ii = 0; ii < nfft; ii++ )
    x[ii] = tcomplex( inout.realp[ ii ], inout.imagp[ ii ] ) / static_cast<double>(nfft);

  vDSP_destroy_fftsetup( planVDSP );

	delete [] inout.realp;
	delete [] inout.imagp;

	return x;
}

#else

tvector<tcomplex> ifft( tvector<tcomplex>, tuint )
{
#if !defined( __WIN__ )
	#warning fft() not implemented.
#endif
	tvector<tcomplex> x;
	return x;
}

#endif

}
