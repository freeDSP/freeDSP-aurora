#ifndef __AUDIOFILTERFACTORY__
#define __AUDIOFILTERFACTORY__

class AudioFilterFactory
{
public:
  enum tfilterdesign
  {
    kBessel6 = 0x00,
    kBessel12,
    kBessel18,
    kBessel24,
    kButterworth12,
    kButterworth18,
    kButterworth24,
    kLinkwitzRiley12,
    kLinkwitzRiley24,
    kLinkwitzRiley36,
    kLinkwitzRiley48,
    kNumFilterDesigns
  };

public:
  //============================================================================
  /*! Calculates the biquad coefficients for a parametric EQ.
   *
   * \param a Pointer to an array for storing the denominator coefficients.
   * \param b Pointer to an array for storing the numerator coefficients.
   * \param gain Gain of filter in dB.
   * \param fc Center frequency in Hz.
   * \param Q Q-factor (bandwidth) of filter.
   */
  static void makeParametricEQ( float a[], float b[], const float gain, const float fc, const float Q, const float fs );

  //============================================================================
  /*! Calculates the biquad coefficients for a low shelving filter.
   *
   * \param a Pointer to an array for storing the denominator coefficients.
   * \param b Pointer to an array for storing the numerator coefficients.
   * \param gain Gain of filter in dB.
   * \param fc Center frequency in Hz.
   * \param S Defines the slope.
   */
  static void makeLowShelv( float a[], float b[], const float gain, const float fc, const float S, const float fs );

  //============================================================================
  /*! Calculates the biquad coefficients for a high shelving filter.
   *
   * \param a Pointer to an array for storing the denominator coefficients.
   * \param b Pointer to an array for storing the numerator coefficients.
   * \param gain Gain of filter in dB.
   * \param fc Center frequency in Hz.
   * \param S Defines the slope.
   */
  static void makeHighShelv( float a[], float b[], const float gain, const float fc, const float S, const float fs );


  static void makeHighPass( float a[], float b[], const int design, const float fc, const float fs );
  static void makeLowPass( float a[], float b[], const int design, const float fc, const float fs );
  static void makeAllpass( float a[], float b[], const float fc, const float Q, const float fs );
};

#endif
