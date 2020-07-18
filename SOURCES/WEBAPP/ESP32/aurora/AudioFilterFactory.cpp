#include <assert.h>
#include <cmath>

#include "AudioFilterFactory.h"

static const float pi = M_PI;

//==============================================================================
/*! Calculates the biquad coefficients for a parametric EQ.
 *
 * \param a Pointer to an array for storing the denominator coefficients.
 * \param b Pointer to an array for storing the numerator coefficients.
 * \param gain Gain of filter in dB.
 * \param fc Center frequency in Hz.
 * \param Q Q-factor (bandwidth) of filter.
 */
void AudioFilterFactory::makeParametricEQ( float a[], float b[], const float gain, const float fc, const float Q, const float fs )
{
  float A = pow( 10.0, gain / 40.0 );
  float w0 = 2.0 * pi * fc / fs;
  float BW = asinh( (1.0 / Q) / 2.0 ) / ( log(2.0) / 2.0 );
  float alpha = sin(w0) * sinh( log(2.0)/2.0 * BW * w0 / sin(w0) );
  float b0 =  1.0 + alpha * A;
  float b1 = -2.0 * cos(w0);
  float b2 =  1.0 - alpha * A;
  float a0 =  1.0 + alpha / A;
  float a1 =  2.0 * cos(w0);
  float a2 = -1.0 + alpha / A;

  b[0] = b0 / a0;
  b[1] = b1 / a0;
  b[2] = b2 / a0;
  a[0] = 1.0;
  a[1] = a1 / a0;
  a[2] = a2 / a0;
}

//==============================================================================
/*! Calculates the biquad coefficients for a low shelving filter.
 *
 * \param a Pointer to an array for storing the denominator coefficients.
 * \param b Pointer to an array for storing the numerator coefficients.
 * \param gain Gain of filter in dB.
 * \param fc Center frequency in Hz.
 * \param S Defines the slope.
 */
void AudioFilterFactory::makeLowShelv( float a[], float b[], const float gain, const float fc, const float S, const float fs )
{
  float A = pow( 10.0, gain/40.0 );
  float w0 = 2*pi*fc/fs;
  float alpha = sin(w0)/2.0 * sqrt( (A + 1.0/A) * (1.0/S - 1.0) + 2.0);

  float a0 = (A + 1.0) + (A - 1.0) * cos(w0) + 2.0 * sqrt(A) * alpha;
  float a1 = ( -2.0 * ( (A - 1.0) + (A + 1.0) * cos(w0) ) ) / a0;
  float a2 = ( (A + 1.0) + (A - 1.0) * cos(w0) - 2.0 * sqrt(A) * alpha ) / a0;
  float b0 = ( A * ( (A + 1.0) - (A - 1.0) * cos(w0) + 2.0 * sqrt(A) * alpha ) ) / a0;
  float b1 = ( 2.0 * A * ( (A - 1.0) - (A + 1.0) * cos(w0) ) ) / a0;
  float b2 = ( A * ( (A + 1.0) - (A - 1.0) * cos(w0) - 2.0 * sqrt(A) * alpha ) ) / a0;
  a0 = 1.0;
  b[0] = b0;
  b[1] = b1;
  b[2] = b2;
  a[0] = a0;
  a[1] = (-1.0)*a1;
  a[2] = (-1.0)*a2;
}

//==============================================================================
/*! Calculates the biquad coefficients for a high shelving filter.
 *
 * \param a Pointer to an array for storing the denominator coefficients.
 * \param b Pointer to an array for storing the numerator coefficients.
 * \param gain Gain of filter in dB.
 * \param fc Center frequency in Hz.
 * \param S Defines the slope.
 */
void AudioFilterFactory::makeHighShelv( float a[], float b[], const float gain, const float fc, const float S, const float fs )
{
  float A = pow( 10.0, gain/40.0 );
  float w0 = 2.0*pi*fc/fs;
  float alpha = sin(w0)/2.0 * sqrt( (A + 1.0/A) * (1.0/S - 1.0) + 2.0 );
  float a0 = (A + 1.0) - (A - 1.0) * cos(w0) + 2.0 * sqrt(A) * alpha;
  float a1 = ( 2.0 * ( (A - 1.0) - (A + 1.0) * cos(w0) ) ) / a0;
  float a2 = ( (A + 1.0) - (A - 1.0) * cos(w0) - 2.0 * sqrt(A) * alpha ) / a0;
  float b0 = ( A * ( (A + 1.0) + (A - 1.0) * cos(w0) + 2.0 * sqrt(A) * alpha ) ) / a0;
  float b1 = ( -2.0 * A * ( (A - 1.0) + (A + 1.0) * cos(w0) ) ) / a0;
  float b2 = ( A * ( (A + 1.0) + (A - 1.0) * cos(w0) - 2.0 * sqrt(A) * alpha ) ) / a0;
  a0 = 1.0;
  b[0] = b0;
  b[1] = b1;
  b[2] = b2;
  a[0] = a0;
  a[1] = (-1.0)*a1;
  a[2] = (-1.0)*a2;
}

void AudioFilterFactory::makeHighPass( float a[], float b[], const int design, const float fc, const float fs )
{
  tfilterdesign filterDesign = static_cast<tfilterdesign>(design);
  float Omega;
  float a0, a1, a2, b0, b1, b2;
  float T, T2, wn;
  float w0, alpha;
  float sa[3];
  float sb[3];
  float za[3];
  float zb[3];

  switch( filterDesign )
  {
  case kNumFilterDesigns:
    /* this shouldn't occur */
    assert(false);
    break;
  case kBessel6:
    Omega = 2.0 * pi * fc / fs;
    a1 = pow( 2.7, -Omega );
    b[0] = a1;
    b[1] = -a1;
    b[2] = 0.0;
    a[0] = 1.0;
    a[1] = a1;
    a[2] = 0.0;
    break;

  case kBessel12:
    T = 1.0/fs;
    T2 = T*T;
    Omega = 2.0 * pi * fc / fs;
    wn  = 2.0 / T * tan( Omega/2.0 );

    a0 = 0.6180;  // bi
    a1 = 1.3617;  // ai
    a2 = 1.0;
    b0 = 0.0;
    b1 = 0.0;
    b2 = 1.0;

    sa[0] = a2;
    sa[1] = a1 * wn;
    sa[2] = a0 * wn*wn;
    sb[0] = b2;
    sb[1] = b1;
    sb[2] = b0;

    zb[0] = 4.0*sb[0]    + 2.0*sb[1]*T + sb[2]*T2;
    zb[1] = 2.0*sb[2]*T2 - 8.0*sb[0];
    zb[2] = 4.0*sb[0]    - 2.0*sb[1]*T + sb[2]*T2;

    za[0] = 4.0*sa[0]    + 2.0*sa[1]*T + sa[2]*T2;
    za[1] = 2.0*sa[2]*T2 - 8.0*sa[0];
    za[2] = 4.0*sa[0]    - 2.0*sa[1]*T + sa[2]*T2;

    b[0] = zb[0] / za[0];
    b[1] = zb[1] / za[0];
    b[2] = zb[2] / za[0];
    a[0] = 1.0;
    a[1] = (-1.0)*za[1] / za[0];
    a[2] = (-1.0)*za[2] / za[0];
    break;

  case kBessel18:
    T = 1.0 / fs;
    T2 = T*T;
    Omega = 2.0 * pi * fc / fs;
    wn  = 2.0 / T * tan( Omega/2.0 );

    //--- Stage 1
    a1 = pow( 2.7, -Omega );
    b[0] = a1;
    b[1] = -a1;
    b[2] = 0.0;
    a[0] = 1.0;
    a[1] = a1;
    a[2] = 0.0;

    //--- Stage 2
    a0 = 0.4772;  // bi
    a1 = 0.9996;  // ai
    a2 = 1.0;
    b0 = 0.0;
    b1 = 0.0;
    b2 = 1.0;

    sa[0] = a2;
    sa[1] = a1 * wn;
    sa[2] = a0 * wn*wn;
    sb[0] = b2;
    sb[1] = b1;
    sb[2] = b0;

    zb[0] = 4.0*sb[0]    + 2.0*sb[1]*T + sb[2]*T2;
    zb[1] = 2.0*sb[2]*T2 - 8.0*sb[0];
    zb[2] = 4.0*sb[0]    - 2.0*sb[1]*T + sb[2]*T2;

    za[0] = 4.0*sa[0]    + 2.0*sa[1]*T + sa[2]*T2;
    za[1] = 2.0*sa[2]*T2 - 8.0*sa[0];
    za[2] = 4.0*sa[0]    - 2.0*sa[1]*T + sa[2]*T2;

    b[ 3 + 0 ] = zb[0] / za[0];
    b[ 3 + 1 ] = zb[1] / za[0];
    b[ 3 + 2 ] = zb[2] / za[0];
    a[ 3 + 0 ] = 1.0;
    a[ 3 + 1 ] = (-1.0)*za[1] / za[0];
    a[ 3 + 2 ] = (-1.0)*za[2] / za[0];
    break;

  case kBessel24:
    T = 1.0 / fs;
    T2 = T*T;
    Omega = 2.0 * pi * fc / fs;
    wn  = 2.0 / T * tan( Omega/2.0 );

    //--- Stage 1
    a0 = 0.4889;  // bi
    a1 = 1.3397;  // ai
    a2 = 1.0;
    b0 = 0.0;
    b1 = 0.0;
    b2 = 1.0;

    sa[0] = a2;
    sa[1] = a1 * wn;
    sa[2] = a0 * wn*wn;
    sb[0] = b2;
    sb[1] = b1;
    sb[2] = b0;

    zb[0] = 4.0*sb[0]    + 2.0*sb[1]*T + sb[2]*T2;
    zb[1] = 2.0*sb[2]*T2 - 8.0*sb[0];
    zb[2] = 4.0*sb[0]    - 2.0*sb[1]*T + sb[2]*T2;

    za[0] = 4.0*sa[0]    + 2.0*sa[1]*T + sa[2]*T2;
    za[1] = 2.0*sa[2]*T2 - 8.0*sa[0];
    za[2] = 4.0*sa[0]    - 2.0*sa[1]*T + sa[2]*T2;

    b[ 0 ] = zb[0] / za[0];
    b[ 1 ] = zb[1] / za[0];
    b[ 2 ] = zb[2] / za[0];
    a[ 0 ] = 1.0;
    a[ 1 ] = (-1.0)*za[1] / za[0];
    a[ 2 ] = (-1.0)*za[2] / za[0];

    //--- Stage 2
    sa[0] = 0.3890 / (wn*wn);  // bi
    sa[1] = 0.7743 / wn;       // ai
    sa[2] = 1.0;
    sb[0] = 0.0;
    sb[1] = 0.0;
    sb[2] = 1.0;

    sa[0] = a2;
    sa[1] = a1 * wn;
    sa[2] = a0 * wn*wn;
    sb[0] = b2;
    sb[1] = b1;
    sb[2] = b0;

    zb[0] = 4.0*sb[0]    + 2.0*sb[1]*T + sb[2]*T2;
    zb[1] = 2.0*sb[2]*T2 - 8.0*sb[0];
    zb[2] = 4.0*sb[0]    - 2.0*sb[1]*T + sb[2]*T2;

    za[0] = 4.0*sa[0]    + 2.0*sa[1]*T + sa[2]*T2;
    za[1] = 2.0*sa[2]*T2 - 8.0*sa[0];
    za[2] = 4.0*sa[0]    - 2.0*sa[1]*T + sa[2]*T2;

    b[ 3 + 0 ] = zb[0] / za[0];
    b[ 3 + 1 ] = zb[1] / za[0];
    b[ 3 + 2 ] = zb[2] / za[0];
    a[ 3 + 0 ] = 1.0;
    a[ 3 + 1 ] = (-1.0)*za[1] / za[0];
    a[ 3 + 2 ] = (-1.0)*za[2] / za[0];
    break;

  case kButterworth12:
    T = 1.0/fs;
    T2 = T*T;
    Omega = 2.0 * pi * fc / fs;
    wn  = 2.0 / T * tan( Omega/2.0 );

    a0 = 1.0000;  // bi
    a1 = 1.4142;  // ai
    a2 = 1.0;
    b0 = 0.0;
    b1 = 0.0;
    b2 = 1.0;

    sa[0] = a2;
    sa[1] = a1 * wn;
    sa[2] = a0 * wn*wn;
    sb[0] = b2;
    sb[1] = b1;
    sb[2] = b0;

    zb[0] = 4.0*sb[0]    + 2.0*sb[1]*T + sb[2]*T2;
    zb[1] = 2.0*sb[2]*T2 - 8.0*sb[0];
    zb[2] = 4.0*sb[0]    - 2.0*sb[1]*T + sb[2]*T2;

    za[0] = 4.0*sa[0]    + 2.0*sa[1]*T + sa[2]*T2;
    za[1] = 2.0*sa[2]*T2 - 8.0*sa[0];
    za[2] = 4.0*sa[0]    - 2.0*sa[1]*T + sa[2]*T2;

    b[0] = zb[0] / za[0];
    b[1] = zb[1] / za[0];
    b[2] = zb[2] / za[0];
    a[0] = 1.0;
    a[1] = (-1.0)*za[1] / za[0];
    a[2] = (-1.0)*za[2] / za[0];
    break;

  case kButterworth18:
    T = 1.0/fs;
    T2 = T*T;
    Omega = 2.0 * pi * fc / fs;
    wn  = 2.0/T * tan( Omega/2.0 );

    //--- Stage 1
    a1 = pow( 2.7, -Omega );
    b[0] = a1;
    b[1] = -a1;
    b[2] = 0.0;
    a[0] = 1.0;
    a[1] = a1;
    a[2] = 0.0;

    //--- Stage 2
    a0 = 1.0000;  // bi
    a1 = 1.0000;  // ai
    a2 = 1.0;
    b0 = 0.0;
    b1 = 0.0;
    b2 = 1.0;

    sa[0] = a2;
    sa[1] = a1 * wn;
    sa[2] = a0 * wn*wn;
    sb[0] = b2;
    sb[1] = b1;
    sb[2] = b0;

    zb[0] = 4.0*sb[0]    + 2.0*sb[1]*T + sb[2]*T2;
    zb[1] = 2.0*sb[2]*T2 - 8.0*sb[0];
    zb[2] = 4.0*sb[0]    - 2.0*sb[1]*T + sb[2]*T2;

    za[0] = 4.0*sa[0]    + 2.0*sa[1]*T + sa[2]*T2;
    za[1] = 2.0*sa[2]*T2 - 8.0*sa[0];
    za[2] = 4.0*sa[0]    - 2.0*sa[1]*T + sa[2]*T2;

    b[ 3 + 0 ] = zb[0] / za[0];
    b[ 3 + 1 ] = zb[1] / za[0];
    b[ 3 + 2 ] = zb[2] / za[0];
    a[ 3 + 0 ] = 1.0;
    a[ 3 + 1 ] = (-1.0)*za[1] / za[0];
    a[ 3 + 2 ] = (-1.0)*za[2] / za[0];
    break;

  case kButterworth24:
    T = 1.0/fs;
    T2 = T*T;
    Omega = 2.0 * pi * fc / fs;
    wn  = 2.0/T * tan( Omega/2.0 );

    //--- Stage 1
    a0 = 1.0000; // bi
    a1 = 1.8478; // ai
    a2 = 1.0;
    b0 = 0.0;
    b1 = 0.0;
    b2 = 1.0;

    sa[0] = a2;
    sa[1] = a1 * wn;
    sa[2] = a0 * wn*wn;
    sb[0] = b2;
    sb[1] = b1;
    sb[2] = b0;

    zb[0] = 4.0*sb[0]    + 2.0*sb[1]*T + sb[2]*T2;
    zb[1] = 2.0*sb[2]*T2 - 8.0*sb[0];
    zb[2] = 4.0*sb[0]    - 2.0*sb[1]*T + sb[2]*T2;

    za[0] = 4.0*sa[0]    + 2.0*sa[1]*T + sa[2]*T2;
    za[1] = 2.0*sa[2]*T2 - 8.0*sa[0];
    za[2] = 4.0*sa[0]    - 2.0*sa[1]*T + sa[2]*T2;

    b[0] = zb[0] / za[0];
    b[1] = zb[1] / za[0];
    b[2] = zb[2] / za[0];
    a[0] = 1.0;
    a[1] = (-1.0)*za[1] / za[0];
    a[2] = (-1.0)*za[2] / za[0];

    //--- Stage 2
    a0 = 1.0000;  // bi
    a1 = 0.7654;  // ai
    a2 = 1.0;
    b0 = 0.0;
    b1 = 0.0;
    b2 = 1.0;

    sa[0] = a2;
    sa[1] = a1 * wn;
    sa[2] = a0 * wn*wn;
    sb[0] = b2;
    sb[1] = b1;
    sb[2] = b0;

    zb[0] = 4.0*sb[0]    + 2.0*sb[1]*T + sb[2]*T2;
    zb[1] = 2.0*sb[2]*T2 - 8.0*sb[0];
    zb[2] = 4.0*sb[0]    - 2.0*sb[1]*T + sb[2]*T2;

    za[0] = 4.0*sa[0]    + 2.0*sa[1]*T + sa[2]*T2;
    za[1] = 2.0*sa[2]*T2 - 8.0*sa[0];
    za[2] = 4.0*sa[0]    - 2.0*sa[1]*T + sa[2]*T2;

    b[ 3 + 0 ] = zb[0] / za[0];
    b[ 3 + 1 ] = zb[1] / za[0];
    b[ 3 + 2 ] = zb[2] / za[0];
    a[ 3 + 0 ] = 1.0;
    a[ 3 + 1 ] = (-1.0)*za[1] / za[0];
    a[ 3 + 2 ] = (-1.0)*za[2] / za[0];
    break;

  case kLinkwitzRiley12:
    w0 = 2.0 * pi * fc / fs;
    alpha = sin(w0) / (2.0 * 0.5);
    a0 = 1.0 + alpha;
    b0 = ( ( 1.0 + cos(w0) ) * 0.5 ) / a0;
    b1 = ( -( 1.0 + cos(w0) ) ) / a0;
    b2 = ( ( 1.0 + cos(w0) ) * 0.5 ) / a0;
    a1 = (-1.0)*( -2.0 * cos(w0) ) / a0;
    a2 = (-1.0)*( 1.0 - alpha ) / a0;
    a0 = 1.0;
    b[0] = b0;
    b[1] = b1;
    b[2] = b2;
    a[0] = 1.0;
    a[1] = a1;
    a[2] = a2;
    break;

  case kLinkwitzRiley24:
    //--- Stage 1
    w0 = 2.0 * pi * fc / fs;
    alpha = sin(w0) / (2.0 * 0.71);
    a0 = 1.0 + alpha;
    b0 = ( ( 1.0 + cos(w0) ) * 0.5 ) / a0;
    b1 = ( -( 1.0 + cos(w0) ) ) / a0;
    b2 = ( ( 1.0 + cos(w0) ) * 0.5 ) / a0;
    a1 = (-1.0)*( -2.0 * cos(w0) ) / a0;
    a2 = (-1.0)*( 1.0 - alpha ) / a0;
    a0 = 1.0;
    b[0] = b0;
    b[1] = b1;
    b[2] = b2;
    a[0] = 1.0;
    a[1] = a1;
    a[2] = a2;

    //--- Stage 2
    w0 = 2.0 * pi * fc / fs;
    alpha = sin(w0) / (2.0 * 0.71);
    a0 = 1.0 + alpha;
    b0 = ( ( 1.0 + cos(w0) ) * 0.5 ) / a0;
    b1 = ( -( 1.0 + cos(w0) ) ) / a0;
    b2 = ( ( 1.0 + cos(w0) ) * 0.5 ) / a0;
    a1 = (-1.0)*( -2.0 * cos(w0) ) / a0;
    a2 = (-1.0)*( 1.0 - alpha ) / a0;
    a0 = 1.0;
    b[ 3 + 0 ]  = b0;
    b[ 3 + 1 ] = b1;
    b[ 3 + 2 ] = b2;
    a[ 3 + 0 ] = 1.0;
    a[ 3 + 1 ] = a1;
    a[ 3 + 2 ] = a2;
    break;

  case kLinkwitzRiley36:
    //--- Stage 1
    w0 = 2.0 * pi * fc / fs;
    alpha = sin(w0) / (2.0 * 0.5);
    a0 = 1.0 + alpha;
    b0 = ( ( 1.0 + cos(w0) ) * 0.5 ) / a0;
    b1 = ( -( 1.0 + cos(w0) ) ) / a0;
    b2 = ( ( 1.0 + cos(w0) ) * 0.5 ) / a0;
    a1 = (-1.0)*( -2.0 * cos(w0) ) / a0;
    a2 = (-1.0)*( 1.0 - alpha ) / a0;
    a0 = 1.0;
    b[0] = b0;
    b[1] = b1;
    b[2] = b2;
    a[0] = 1.0;
    a[1] = a1;
    a[2] = a2;

    //--- Stage 2
    w0 = 2.0 * pi * fc / fs;
    alpha = sin(w0) / (2.0 * 1.0);
    a0 = 1.0 + alpha;
    b0 = ( ( 1.0 + cos(w0) ) * 0.5 ) / a0;
    b1 = ( -( 1.0 + cos(w0) ) ) / a0;
    b2 = ( ( 1.0 + cos(w0) ) * 0.5 ) / a0;
    a1 = (-1.0)*( -2.0 * cos(w0) ) / a0;
    a2 = (-1.0)*( 1.0 - alpha ) / a0;
    a0 = 1.0;
    b[ 3 + 0 ] = b0;
    b[ 3 + 1 ] = b1;
    b[ 3 + 2 ] = b2;
    a[ 3 + 0 ] = 1.0;
    a[ 3 + 1 ] = a1;
    a[ 3 + 2 ] = a2;

    //--- Stage 3
    w0 = 2.0 * pi * fc / fs;
    alpha = sin(w0) / (2.0 * 1.0);
    a0 = 1.0 + alpha;
    b0 = ( ( 1.0 + cos(w0) ) * 0.5 ) / a0;
    b1 = ( -( 1.0 + cos(w0) ) ) / a0;
    b2 = ( ( 1.0 + cos(w0) ) * 0.5 ) / a0;
    a1 = (-1.0)*( -2.0 * cos(w0) ) / a0;
    a2 = (-1.0)*( 1.0 - alpha ) / a0;
    a0 = 1.0;
    b[ 6 + 0 ] = b0;
    b[ 6 + 1 ] = b1;
    b[ 6 + 2 ] = b2;
    a[ 6 + 0 ] = 1.0;
    a[ 6 + 1 ] = a1;
    a[ 6 + 2 ] = a2;
    break;

  case kLinkwitzRiley48:
    //--- Stage 1
    w0 = 2.0 * pi * fc / fs;
    alpha = sin(w0) / (2.0 * 0.54);
    a0 = 1.0 + alpha;
    b0 = ( ( 1.0 + cos(w0) ) * 0.5 ) / a0;
    b1 = ( -( 1.0 + cos(w0) ) ) / a0;
    b2 = ( ( 1.0 + cos(w0) ) * 0.5 ) / a0;
    a1 = (-1.0)*( -2.0 * cos(w0) ) / a0;
    a2 = (-1.0)*( 1.0 - alpha ) / a0;
    a0 = 1.0;
    b[0] = b0;
    b[1] = b1;
    b[2] = b2;
    a[0] = 1.0;
    a[1] = a1;
    a[2] = a2;

    //--- Stage 2
    w0 = 2.0 * pi * fc / fs;
    alpha = sin(w0) / (2.0 * 1.34);
    a0 = 1.0 + alpha;
    b0 = ( ( 1.0 + cos(w0) ) * 0.5 ) / a0;
    b1 = ( -( 1.0 + cos(w0) ) ) / a0;
    b2 = ( ( 1.0 + cos(w0) ) * 0.5 ) / a0;
    a1 = (-1.0)*( -2.0 * cos(w0) ) / a0;
    a2 = (-1.0)*( 1.0 - alpha ) / a0;
    a0 = 1.0;
    b[ 3 + 0 ] = b0;
    b[ 3 + 1 ] = b1;
    b[ 3 + 2 ] = b2;
    a[ 3 + 0 ] = 1.0;
    a[ 3 + 1 ] = a1;
    a[ 3 + 2 ] = a2;

    //--- Stage 3
    w0 = 2.0 * pi * fc / fs;
    alpha = sin(w0) / (2.0 * 0.54);
    a0 = 1.0 + alpha;
    b0 = ( ( 1.0 + cos(w0) ) * 0.5 ) / a0;
    b1 = ( -( 1.0 + cos(w0) ) ) / a0;
    b2 = ( ( 1.0 + cos(w0) ) * 0.5 ) / a0;
    a1 = (-1.0)*( -2.0 * cos(w0) ) / a0;
    a2 = (-1.0)*( 1.0 - alpha ) / a0;
    a0 = 1.0;
    b[ 6 + 0 ] = b0;
    b[ 6 + 1 ] = b1;
    b[ 6 + 2 ] = b2;
    a[ 6 + 0 ] = 1.0;
    a[ 6 + 1 ] = a1;
    a[ 6 + 2 ] = a2;

    //--- Stage 4
    w0 = 2.0 * pi * fc / fs;
    alpha = sin(w0) / (2.0 * 1.34);
    a0 = 1.0 + alpha;
    b0 = ( ( 1.0 + cos(w0) ) * 0.5 ) / a0;
    b1 = ( -( 1.0 + cos(w0) ) ) / a0;
    b2 = ( ( 1.0 + cos(w0) ) * 0.5 ) / a0;
    a1 = (-1.0)*( -2.0 * cos(w0) ) / a0;
    a2 = (-1.0)*( 1.0 - alpha ) / a0;
    a0 = 1.0;
    b[ 9 + 0 ] = b0;
    b[ 9 + 1 ] = b1;
    b[ 9 + 2 ] = b2;
    a[ 9 + 0 ] = 1.0;
    a[ 9 + 1 ] = a1;
    a[ 9 + 2 ] = a2;
    break;

  };

}

void AudioFilterFactory::makeLowPass( float a[], float b[], const int design, const float fc, const float fs )
{
  tfilterdesign filterDesign = static_cast<tfilterdesign>(design);
  float Omega;
  float a0, a1, a2, b0, b1, b2;
  float T, T2, wn;
  float w0, alpha;
  float sa[3];
  float sb[3];
  float za[3];
  float zb[3];

  switch( filterDesign )
  {
  case kNumFilterDesigns:
    /* this shouldn't occur */
    assert(false);
    break;
  case kBessel6:
    Omega = 2.0 * pi * fc / fs;
    a1 = pow( 2.7, -Omega );
    b[0] = 1.0 - a1;
    b[1] = 0.0;
    b[2] = 0.0;
    a[0] = 1.0;
    a[1] = a1;
    a[2] = 0.0;
    break;

  case kBessel12:
    Omega = 2.0 * pi * fc / fs;
    T = 1.0/fs;
    T2 = T*T;
    wn  = 2.0/T * tan( Omega/2.0 );

    sa[0] = 0.6180 / (wn*wn);  // bi
    sa[1] = 1.3617 / wn;       // ai
    sa[2] = 1.0;
    sb[0] = 0.0;
    sb[1] = 0.0;
    sb[2] = 1.0;

    zb[0] = 4.0*sb[0]    + 2.0*sb[1]*T + sb[2]*T2;
    zb[1] = 2.0*sb[2]*T2 - 8.0*sb[0];
    zb[2] = 4.0*sb[0]    - 2.0*sb[1]*T + sb[2]*T2;

    za[0] = 4.0*sa[0]    + 2.0*sa[1]*T + sa[2]*T2;
    za[1] = 2.0*sa[2]*T2 - 8.0*sa[0];
    za[2] = 4.0*sa[0]    - 2.0*sa[1]*T + sa[2]*T2;

    b[0] = zb[0] / za[0];
    b[1] = zb[1] / za[0];
    b[2] = zb[2] / za[0];
    a[0] = 1.0;
    a[1] = (-1.0)*za[1] / za[0];
    a[2] = (-1.0)*za[2] / za[0];
    break;

  case kBessel18:
    T = 1.0/fs;
    T2 = T*T;
    Omega = 2.0 * pi * fc / fs;
    wn  = 2.0/T * tan( Omega/2.0 );

    //--- Stage 1
    a1 = pow( 2.7, -Omega );
    b[0] = 1.0 - a1;
    b[1] = 0.0;
    b[2] = 0.0;
    a[0] = 1.0;
    a[1] = a1;
    a[2] = 0.0;

    //--- Stage 2
    sa[0] = 0.4772 / (wn*wn);  // bi
    sa[1] = 0.9996 / wn;       // ai
    sa[2] = 1.0;
    sb[0] = 0.0;
    sb[1] = 0.0;
    sb[2] = 1.0;

    zb[0] = 4.0*sb[0]    + 2.0*sb[1]*T + sb[2]*T2;
    zb[1] = 2.0*sb[2]*T2 - 8.0*sb[0];
    zb[2] = 4.0*sb[0]    - 2.0*sb[1]*T + sb[2]*T2;

    za[0] = 4.0*sa[0]    + 2.0*sa[1]*T + sa[2]*T2;
    za[1] = 2.0*sa[2]*T2 - 8.0*sa[0];
    za[2] = 4.0*sa[0]    - 2.0*sa[1]*T + sa[2]*T2;

    b[ 3 + 0 ] = zb[0] / za[0];
    b[ 3 + 1 ] = zb[1] / za[0];
    b[ 3 + 2 ] = zb[2] / za[0];
    a[ 3 + 0 ] = 1.0;
    a[ 3 + 1 ] = (-1.0)*za[1] / za[0];
    a[ 3 + 2 ] = (-1.0)*za[2] / za[0];
    break;

  case kBessel24:
    T = 1.0/fs;
    T2 = T*T;
    Omega = 2.0 * pi * fc / fs;
    wn  = 2.0/T * tan( Omega/2.0 );

    //--- Stage 1
    sa[0] = 0.4889 / (wn*wn);  // bi
    sa[1] = 1.3397 / wn;       // ai
    sa[2] = 1.0;
    sb[0] = 0.0;
    sb[1] = 0.0;
    sb[2] = 1.0;

    zb[0] = 4.0*sb[0]    + 2.0*sb[1]*T + sb[2]*T2;
    zb[1] = 2.0*sb[2]*T2 - 8.0*sb[0];
    zb[2] = 4.0*sb[0]    - 2.0*sb[1]*T + sb[2]*T2;

    za[0] = 4.0*sa[0]    + 2.0*sa[1]*T + sa[2]*T2;
    za[1] = 2.0*sa[2]*T2 - 8.0*sa[0];
    za[2] = 4.0*sa[0]    - 2.0*sa[1]*T + sa[2]*T2;

    b[0] = zb[0] / za[0];
    b[1] = zb[1] / za[0];
    b[2] = zb[2] / za[0];
    a[0] = 1.0;
    a[1] = (-1.0)*za[1] / za[0];
    a[2] = (-1.0)*za[2] / za[0];

    //--- Stage 2
    sa[0] = 0.3890 / (wn*wn);  // bi
    sa[1] = 0.7743 / wn;       // ai
    sa[2] = 1.0;
    sb[0] = 0.0;
    sb[1] = 0.0;
    sb[2] = 1.0;

    zb[0] = 4.0*sb[0]    + 2.0*sb[1]*T + sb[2]*T2;
    zb[1] = 2.0*sb[2]*T2 - 8.0*sb[0];
    zb[2] = 4.0*sb[0]    - 2.0*sb[1]*T + sb[2]*T2;

    za[0] = 4.0*sa[0]    + 2.0*sa[1]*T + sa[2]*T2;
    za[1] = 2.0*sa[2]*T2 - 8.0*sa[0];
    za[2] = 4.0*sa[0]    - 2.0*sa[1]*T + sa[2]*T2;

    b[ 3 + 0 ] = zb[0] / za[0];
    b[ 3 + 1 ] = zb[1] / za[0];
    b[ 3 + 2 ] = zb[2] / za[0];
    a[ 3 + 0 ] = 1.0;
    a[ 3 + 1 ] = (-1.0)*za[1] / za[0];
    a[ 3 + 2 ] = (-1.0)*za[2] / za[0];
    break;

  case kButterworth12:
    Omega = 2.0 * pi * fc / fs;
    T = 1.0/fs;
    T2 = T*T;
    wn  = 2.0/T * tan( Omega/2.0 );

    sa[0] = 1.0000 / (wn*wn);  // bi
    sa[1] = 1.4142 / wn;       // ai
    sa[2] = 1.0;
    sb[0] = 0.0;
    sb[1] = 0.0;
    sb[2] = 1.0;

    zb[0] = 4.0*sb[0]    + 2.0*sb[1]*T + sb[2]*T2;
    zb[1] = 2.0*sb[2]*T2 - 8.0*sb[0];
    zb[2] = 4.0*sb[0]    - 2.0*sb[1]*T + sb[2]*T2;

    za[0] = 4.0*sa[0]    + 2.0*sa[1]*T + sa[2]*T2;
    za[1] = 2.0*sa[2]*T2 - 8.0*sa[0];
    za[2] = 4.0*sa[0]    - 2.0*sa[1]*T + sa[2]*T2;

    b[0] = zb[0] / za[0];
    b[1] = zb[1] / za[0];
    b[2] = zb[2] / za[0];
    a[0] = 1.0;
    a[1] = (-1.0)*za[1] / za[0];
    a[2] = (-1.0)*za[2] / za[0];
    break;

  case kButterworth18:
    T = 1.0/fs;
    T2 = T*T;
    Omega = 2.0 * pi * fc / fs;
    wn  = 2.0/T * tan( Omega/2.0 );

    //--- Stage 1
    a1 = pow( 2.7, -Omega );
    b[0] = 1.0 - a1;
    b[1] = 0.0;
    b[2] = 0.0;
    a[0] = 1.0;
    a[1] = a1;
    a[2] = 0.0;

    //--- Stage 2
    sa[0] = 1.0000 / (wn*wn);  // bi
    sa[1] = 1.0000 / wn;       // ai
    sa[2] = 1.0;
    sb[0] = 0.0;
    sb[1] = 0.0;
    sb[2] = 1.0;

    zb[0] = 4.0*sb[0]    + 2.0*sb[1]*T + sb[2]*T2;
    zb[1] = 2.0*sb[2]*T2 - 8.0*sb[0];
    zb[2] = 4.0*sb[0]    - 2.0*sb[1]*T + sb[2]*T2;

    za[0] = 4.0*sa[0]    + 2.0*sa[1]*T + sa[2]*T2;
    za[1] = 2.0*sa[2]*T2 - 8.0*sa[0];
    za[2] = 4.0*sa[0]    - 2.0*sa[1]*T + sa[2]*T2;

    b[ 3 + 0 ] = zb[0] / za[0];
    b[ 3 + 1 ] = zb[1] / za[0];
    b[ 3 + 2 ] = zb[2] / za[0];
    a[ 3 + 0 ] = 1.0;
    a[ 3 + 1 ] = (-1.0)*za[1] / za[0];
    a[ 3 + 2 ] = (-1.0)*za[2] / za[0];
    break;

  case kButterworth24:
    T = 1.0/fs;
    T2 = T*T;
    Omega = 2.0 * pi * fc / fs;
    wn  = 2.0/T * tan( Omega/2.0 );

    //--- Stage 1
    sa[0] = 1.0000 / (wn*wn); // bi
    sa[1] = 1.8478 / wn;      // ai
    sa[2] = 1.0;
    sb[0] = 0.0;
    sb[1] = 0.0;
    sb[2] = 1.0;

    zb[0] = 4.0*sb[0]    + 2.0*sb[1]*T + sb[2]*T2;
    zb[1] = 2.0*sb[2]*T2 - 8.0*sb[0];
    zb[2] = 4.0*sb[0]    - 2.0*sb[1]*T + sb[2]*T2;

    za[0] = 4.0*sa[0]    + 2.0*sa[1]*T + sa[2]*T2;
    za[1] = 2.0*sa[2]*T2 - 8.0*sa[0];
    za[2] = 4.0*sa[0]    - 2.0*sa[1]*T + sa[2]*T2;

    b[0] = zb[0] / za[0];
    b[1] = zb[1] / za[0];
    b[2] = zb[2] / za[0];
    a[0] = 1.0;
    a[1] = (-1.0)*za[1] / za[0];
    a[2] = (-1.0)*za[2] / za[0];

    //--- Stage 2
    sa[0] = 1.0000 / (wn*wn);  // bi
    sa[1] = 0.7654 / wn;       // ai
    sa[2] = 1.0;
    sb[0] = 0.0;
    sb[1] = 0.0;
    sb[2] = 1.0;

    zb[0] = 4.0*sb[0]    + 2.0*sb[1]*T + sb[2]*T2;
    zb[1] = 2.0*sb[2]*T2 - 8.0*sb[0];
    zb[2] = 4.0*sb[0]    - 2.0*sb[1]*T + sb[2]*T2;

    za[0] = 4.0*sa[0]    + 2.0*sa[1]*T + sa[2]*T2;
    za[1] = 2.0*sa[2]*T2 - 8.0*sa[0];
    za[2] = 4.0*sa[0]    - 2.0*sa[1]*T + sa[2]*T2;

    b[ 3 + 0 ] = zb[0] / za[0];
    b[ 3 + 1 ] = zb[1] / za[0];
    b[ 3 + 2 ] = zb[2] / za[0];
    a[ 3 + 0 ] = 1.0;
    a[ 3 + 1 ] = (-1.0)*za[1] / za[0];
    a[ 3 + 2 ] = (-1.0)*za[2] / za[0];
    break;

  case kLinkwitzRiley12:
    w0 = 2.0 * pi * fc / fs;
    alpha = sin(w0) / (2.0 * 0.5);
    a0 = 1.0 + alpha;
    b0 = ( ( 1.0 - cos(w0) ) * 0.5 ) / a0;
    b1 = (   1.0 - cos(w0) ) / a0;
    b2 = ( ( 1.0 - cos(w0) ) * 0.5 ) / a0;
    a1 = ( -2.0 * cos(w0) ) / a0;
    a2 = ( 1.0 - alpha ) / a0;
    a0 = 1.0;
    b[0] = b0;
    b[1] = b1;
    b[2] = b2;
    a[0] = 1.0;
    a[1] = (-1.0)*a1;
    a[2] = (-1.0)*a2;
    break;

  case kLinkwitzRiley24:
    //--- Stage 1
    w0 = 2.0 * pi * fc / fs;
    alpha = sin(w0) / (2.0 * 0.71);
    a0 = 1.0 + alpha;
    b0 = ( ( 1.0 - cos(w0) ) * 0.5 ) / a0;
    b1 = (   1.0 - cos(w0) ) / a0;
    b2 = ( ( 1.0 - cos(w0) ) * 0.5 ) / a0;
    a1 = ( -2.0 * cos(w0) ) / a0;
    a2 = ( 1.0 - alpha ) / a0;
    a0 = 1.0;
    b[0] = b0;
    b[1] = b1;
    b[2] = b2;
    a[0] = 1.0;
    a[1] = (-1.0)*a1;
    a[2] = (-1.0)*a2;

    //--- Stage 2
    w0 = 2.0 * pi * fc / fs;
    alpha = sin(w0) / (2.0 * 0.71);
    a0 = 1.0 + alpha;
    b0 = ( ( 1.0 - cos(w0) ) * 0.5 ) / a0;
    b1 = (   1.0 - cos(w0) ) / a0;
    b2 = ( ( 1.0 - cos(w0) ) * 0.5 ) / a0;
    a1 = ( -2.0 * cos(w0) ) / a0;
    a2 = ( 1.0 - alpha ) / a0;
    a0 = 1.0;
    b[ 3 + 0 ] = b0;
    b[ 3 + 1 ] = b1;
    b[ 3 + 2 ] = b2;
    a[ 3 + 0 ] = 1.0;
    a[ 3 + 1 ] = (-1.0)*a1;
    a[ 3 + 2 ] = (-1.0)*a2;
    break;

  case kLinkwitzRiley36:
    //--- Stage 1
    w0 = 2.0 * pi * fc / fs;
    alpha = sin(w0) / (2.0 * 0.50);
    a0 = 1.0 + alpha;
    b0 = ( ( 1.0 - cos(w0) ) * 0.5 ) / a0;
    b1 = (   1.0 - cos(w0) ) / a0;
    b2 = ( ( 1.0 - cos(w0) ) * 0.5 ) / a0;
    a1 = ( -2.0 * cos(w0) ) / a0;
    a2 = ( 1.0 - alpha ) / a0;
    a0 = 1.0;
    b[0] = b0;
    b[1] = b1;
    b[2] = b2;
    a[0] = 1.0;
    a[1] = (-1.0)*a1;
    a[2] = (-1.0)*a2;

    //--- Stage 2
    w0 = 2.0 * pi * fc / fs;
    alpha = sin(w0) / (2.0 * 1.00);
    a0 = 1.0 + alpha;
    b0 = ( ( 1.0 - cos(w0) ) * 0.5 ) / a0;
    b1 = (   1.0 - cos(w0) ) / a0;
    b2 = ( ( 1.0 - cos(w0) ) * 0.5 ) / a0;
    a1 = ( -2.0 * cos(w0) ) / a0;
    a2 = ( 1.0 - alpha ) / a0;
    a0 = 1.0;
    b[ 3 + 0 ] = b0;
    b[ 3 + 1 ] = b1;
    b[ 3 + 2 ] = b2;
    a[ 3 + 0 ] = 1.0;
    a[ 3 + 1 ] = (-1.0)*a1;
    a[ 3 + 2 ] = (-1.0)*a2;

    //--- Stage 3
    w0 = 2.0 * pi * fc / fs;
    alpha = sin(w0) / (2.0 * 1.00);
    a0 = 1.0 + alpha;
    b0 = ( ( 1.0 - cos(w0) ) * 0.5 ) / a0;
    b1 = (   1.0 - cos(w0) ) / a0;
    b2 = ( ( 1.0 - cos(w0) ) * 0.5 ) / a0;
    a1 = ( -2.0 * cos(w0) ) / a0;
    a2 = ( 1.0 - alpha ) / a0;
    a0 = 1.0;
    b[ 6 + 0 ] = b0;
    b[ 6 + 1 ] = b1;
    b[ 6 + 2 ] = b2;
    a[ 6 + 0 ] = 1.0;
    a[ 6 + 1 ] = (-1.0)*a1;
    a[ 6 + 2 ] = (-1.0)*a2;
    break;

  case kLinkwitzRiley48:
    //--- Stage 1
    w0 = 2.0 * pi * fc / fs;
    alpha = sin(w0) / (2.0 * 0.54);
    a0 = 1.0 + alpha;
    b0 = ( ( 1.0 - cos(w0) ) * 0.5 ) / a0;
    b1 = (   1.0 - cos(w0) ) / a0;
    b2 = ( ( 1.0 - cos(w0) ) * 0.5 ) / a0;
    a1 = ( -2.0 * cos(w0) ) / a0;
    a2 = ( 1.0 - alpha ) / a0;
    a0 = 1.0;
    b[0] = b0;
    b[1] = b1;
    b[2] = b2;
    a[0] = 1.0;
    a[1] = (-1.0)*a1;
    a[2] = (-1.0)*a2;

    //--- Stage 2
    w0 = 2.0 * pi * fc / fs;
    alpha = sin(w0) / (2.0 * 1.34);
    a0 = 1.0 + alpha;
    b0 = ( ( 1.0 - cos(w0) ) * 0.5 ) / a0;
    b1 = (   1.0 - cos(w0) ) / a0;
    b2 = ( ( 1.0 - cos(w0) ) * 0.5 ) / a0;
    a1 = ( -2.0 * cos(w0) ) / a0;
    a2 = ( 1.0 - alpha ) / a0;
    a0 = 1.0;
    b[ 3 + 0 ] = b0;
    b[ 3 + 1 ] = b1;
    b[ 3 + 2 ] = b2;
    a[ 3 + 0 ] = 1.0;
    a[ 3 + 1 ] = (-1.0)*a1;
    a[ 3 + 2 ] = (-1.0)*a2;

    //--- Stage 3
    w0 = 2.0 * pi * fc / fs;
    alpha = sin(w0) / (2.0 * 0.54);
    a0 = 1.0 + alpha;
    b0 = ( ( 1.0 - cos(w0) ) * 0.5 ) / a0;
    b1 = (   1.0 - cos(w0) ) / a0;
    b2 = ( ( 1.0 - cos(w0) ) * 0.5 ) / a0;
    a1 = ( -2.0 * cos(w0) ) / a0;
    a2 = ( 1.0 - alpha ) / a0;
    a0 = 1.0;
    b[ 6 + 0 ] = b0;
    b[ 6 + 1 ] = b1;
    b[ 6 + 2 ] = b2;
    a[ 6 + 0 ] = 1.0;
    a[ 6 + 1 ] = (-1.0)*a1;
    a[ 6 + 2 ] = (-1.0)*a2;

    //--- Stage 4
    w0 = 2.0 * pi * fc / fs;
    alpha = sin(w0) / (2.0 * 1.34);
    a0 = 1.0 + alpha;
    b0 = ( ( 1.0 - cos(w0) ) * 0.5 ) / a0;
    b1 = (   1.0 - cos(w0) ) / a0;
    b2 = ( ( 1.0 - cos(w0) ) * 0.5 ) / a0;
    a1 = ( -2.0 * cos(w0) ) / a0;
    a2 = ( 1.0 - alpha ) / a0;
    a0 = 1.0;
    b[ 9 + 0 ] = b0;
    b[ 9 + 1 ] = b1;
    b[ 9 + 2 ] = b2;
    a[ 9 + 0 ] = 1.0;
    a[ 9 + 1 ] = (-1.0)*a1;
    a[ 9 + 2 ] = (-1.0)*a2;
    break;
  }
}

void AudioFilterFactory::makeAllpass( float a[], float b[], const float fc, const float Q, const float fs )
{
  float w0 = 2.0 * pi * fc / fs;
  float alpha = sin(w0) / (2.0 * Q);

  float a0 = 1.0 + alpha;
  float b0 = (1.0 - alpha) / a0;
  float b1 = -2.0 * cos(w0) / a0;
  float b2 = ( 1.0 + alpha ) / a0;
  float a1 = ( -2.0 * cos(w0) ) / a0;
  float a2 = ( 1.0 - alpha ) / a0;
  a0 = 1.0;
  b[0] = b0;
  b[1] = b1;
  b[2] = b2;
  a[0] = 1.0;
  a[1] = (-1.0)*a1;
  a[2] = (-1.0)*a2;
}

