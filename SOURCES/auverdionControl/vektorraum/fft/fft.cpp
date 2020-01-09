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
tvector<tcomplex> fft( tvector<double> x, tuint nfft )
{
	tvector<tcomplex> Y(nfft);

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
		  input[ 2*ii ] = static_cast<float>(x[ii]);
		else
		  input[ 2*ii ] = 0.0f;
		input[ 2*ii + 1 ] = 0.0f;
	}

	//--- execute FFT ---
	ffts_plan_t* p = ffts_init_1d( nfft, -1 );
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

  for( tuint ii = 0; ii < nfft; ii++ )
	  Y[ii] = tcomplex( output[ 2*ii ], output[ 2*ii+1 ] );

	return Y;
}

#elif defined( USE_APPLEVDSP )

uint64_t fft_getThePowerOfTwo( uint64_t value )
{
  for( tuint n = 0; n < 64; n++ )
	{
    if( value <= (1 << n) )
      return n;
  }
  return 64;
}

tvector<tcomplex> fft( tvector<double> x, tuint nfft )
{
  const tuint order = fft_getThePowerOfTwo( nfft );
	tvector<tcomplex> Y(nfft);

	DSPSplitComplex inout;
  inout.realp = new float[ nfft ];
  inout.imagp = new float[ nfft ];

  // load data to input buffers (zero-padding if needed)
	for( tuint ii = 0; ii < nfft; ii++ )
	{
		if( ii < length(x) )
		  inout.realp[ ii ] = static_cast<float>(x[ii]);
		else
		  inout.realp[ ii ] = 0.0;
		 inout.imagp[ ii ] = 0.0;
	}

	FFTSetup planVDSP = vDSP_create_fftsetup( order, kFFTRadix2 );

  // execute FFT
	vDSP_fft_zip( planVDSP, &inout, 1, order, kFFTDirection_Forward );


	for( tuint ii = 0; ii < nfft; ii++ )
	  Y[ii] = tcomplex( inout.realp[ ii ], inout.imagp[ ii ] );

	vDSP_destroy_fftsetup( planVDSP );

	delete [] inout.realp;
	delete [] inout.imagp;

	return Y;
}

#else
tvector<tcomplex> fft( tvector<double>, tuint )
{
#if !defined( __WIN__ )
	#warning fft() not implemented.
#endif
	tvector<tcomplex> Y;
	return Y;
}

#endif

}
