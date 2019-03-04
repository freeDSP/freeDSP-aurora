/*
  ==============================================================================

    tvector.cpp
    Created: 20 Apr 2018 10:06:54am
    Author:  Raphael Knoop

  ==============================================================================
*/
#include <cmath>
#include <iostream>

#include "typedefs.h"
#include "tvector.h"

using namespace std;

namespace Vektorraum
{

//==============================================================================
/*! Overloading of operator+
 */
tvector<double> operator+( tvector<double> a, double b )
{
  tvector<double> y( a.size );
  for( uint64_t idx = 0; idx < a.size; idx++ )
    y.elem[idx] = a.elem[idx] + b;
  return y;
}

tvector<tcomplex> operator+( tvector<double> a, tcomplex b )
{
  tvector<tcomplex> y( a.size );
  for( uint64_t idx = 0; idx < a.size; idx++ )
    y.elem[idx] = a.elem[idx] + b;
  return y;
}

tvector<double> operator+( double a, tvector<double> b )
{
  tvector<double> y( b.size );
  for( uint64_t idx = 0; idx < b.size; idx++ )
    y.elem[idx] = a + b.elem[idx];
  return y;
}

tvector<tcomplex> operator+( tcomplex a, tvector<double> b )
{
  tvector<tcomplex> y( b.size );
  for( uint64_t idx = 0; idx < b.size; idx++ )
    y.elem[idx] = a + b.elem[idx];
  return y;
}

tvector<tcomplex> operator+( tvector<tcomplex> a, double b )
{
  tvector<tcomplex> y( a.size );
  for( uint64_t idx = 0; idx < a.size; idx++ )
    y.elem[idx] = a.elem[idx] + b;
  return y;
}

tvector<tcomplex> operator+( tvector<tcomplex> a, tcomplex b )
{
  tvector<tcomplex> y( a.size );
  for( uint64_t idx = 0; idx < a.size; idx++ )
    y.elem[idx] = a.elem[idx] + b;
  return y;
}

tvector<tcomplex> operator+( double a, tvector<tcomplex> b )
{
  tvector<tcomplex> y( b.size );
  for( uint64_t idx = 0; idx < b.size; idx++ )
    y.elem[idx] = a + b.elem[idx];
  return y;
}

tvector<tcomplex> operator+( tcomplex a, tvector<tcomplex> b )
{
  tvector<tcomplex> y( b.size );
  for( uint64_t idx = 0; idx < b.size; idx++ )
    y.elem[idx] = a + b.elem[idx];
  return y;
}

tvector<double> operator+( tvector<double> a, tvector<double> b )
{
  tvector<double> y( a.size );
  if( a.size != b.size )
  {
    std::cerr<<"operator+( tvector<double> a, tvector<double> b ): Vectors do not have equal length."<<std::endl;
    return y;
  }
  for( uint64_t idx = 0; idx < a.size; idx++ )
    y.elem[idx] = a.elem[idx] + b.elem[idx];
  return y;
}

tvector<tcomplex> operator+( tvector<double> a, tvector<tcomplex> b )
{
  tvector<tcomplex> y( a.size );
  if( a.size != b.size )
  {
    std::cerr<<"operator+( tvector<double> a, tvector<double> b ): Vectors do not have equal length."<<std::endl;
    return y;
  }
  for( uint64_t idx = 0; idx < a.size; idx++ )
    y.elem[idx] = a.elem[idx] + b.elem[idx];
  return y;
}

tvector<tcomplex> operator+( tvector<tcomplex> a, tvector<double> b )
{
  tvector<tcomplex> y( a.size );
  if( a.size != b.size )
  {
    std::cerr<<"operator+( tvector<tcomplex> a, tvector<double> b ): Vectors do not have equal length."<<std::endl;
    return y;
  }
  for( uint64_t idx = 0; idx < a.size; idx++ )
    y.elem[idx] = a.elem[idx] + b.elem[idx];
  return y;
}

tvector<tcomplex> operator+( tvector<tcomplex> a, tvector<tcomplex> b )
{
  tvector<tcomplex> y( a.size );
  if( a.size != b.size )
  {
    std::cerr<<"operator+( tvector<tcomplex> a, tvector<tcomplex> b ): Vectors do not have equal length."<<std::endl;
    return y;
  }
  for( uint64_t idx = 0; idx < a.size; idx++ )
    y.elem[idx] = a.elem[idx] + b.elem[idx];
  return y;
}

//==============================================================================
/*! Overloading of operator-
 */
tvector<double> operator-( tvector<double> a, double b )
{
  tvector<double> y( a.size );
  for( uint64_t idx = 0; idx < a.size; idx++ )
    y.elem[idx] = a.elem[idx] - b;
  return y;
}

tvector<tcomplex> operator-( tvector<double> a, tcomplex b )
{
  tvector<tcomplex> y( a.size );
  for( uint64_t idx = 0; idx < a.size; idx++ )
    y.elem[idx] = a.elem[idx] - b;
  return y;
}

tvector<double> operator-( double a, tvector<double> b )
{
  tvector<double> y( b.size );
  for( uint64_t idx = 0; idx < b.size; idx++ )
    y.elem[idx] = a - b.elem[idx];
  return y;
}

tvector<tcomplex> operator-( tcomplex a, tvector<double> b )
{
  tvector<tcomplex> y( b.size );
  for( uint64_t idx = 0; idx < b.size; idx++ )
    y.elem[idx] = a - b.elem[idx];
  return y;
}

tvector<tcomplex> operator-( tvector<tcomplex> a, double b )
{
  tvector<tcomplex> y( a.size );
  for( uint64_t idx = 0; idx < a.size; idx++ )
    y.elem[idx] = a.elem[idx] - b;
  return y;
}

tvector<tcomplex> operator-( tvector<tcomplex> a, tcomplex b )
{
  tvector<tcomplex> y( a.size );
  for( uint64_t idx = 0; idx < a.size; idx++ )
    y.elem[idx] = a.elem[idx] - b;
  return y;
}

tvector<tcomplex> operator-( double a, tvector<tcomplex> b )
{
  tvector<tcomplex> y( b.size );
  for( uint64_t idx = 0; idx < b.size; idx++ )
    y.elem[idx] = a - b.elem[idx];
  return y;
}

tvector<tcomplex> operator-( tcomplex a, tvector<tcomplex> b )
{
  tvector<tcomplex> y( b.size );
  for( uint64_t idx = 0; idx < b.size; idx++ )
    y.elem[idx] = a - b.elem[idx];
  return y;
}

tvector<double> operator-( tvector<double> a, tvector<double> b )
{
  tvector<double> y( a.size );
  if( a.size != b.size )
  {
    std::cerr<<"operator-( tvector<double> a, tvector<double> b ): Vectors do not have equal length."<<std::endl;
    return y;
  }
  for( uint64_t idx = 0; idx < a.size; idx++ )
    y.elem[idx] = a.elem[idx] - b.elem[idx];
  return y;
}

tvector<tcomplex> operator-( tvector<double> a, tvector<tcomplex> b )
{
  tvector<tcomplex> y( a.size );
  if( a.size != b.size )
  {
    std::cerr<<"operator-( tvector<double> a, tvector<double> b ): Vectors do not have equal length."<<std::endl;
    return y;
  }
  for( uint64_t idx = 0; idx < a.size; idx++ )
    y.elem[idx] = a.elem[idx] - b.elem[idx];
  return y;
}

tvector<tcomplex> operator-( tvector<tcomplex> a, tvector<double> b )
{
  tvector<tcomplex> y( a.size );
  if( a.size != b.size )
  {
    std::cerr<<"operator-( tvector<tcomplex> a, tvector<double> b ): Vectors do not have equal length."<<std::endl;
    return y;
  }
  for( uint64_t idx = 0; idx < a.size; idx++ )
    y.elem[idx] = a.elem[idx] - b.elem[idx];
  return y;
}

tvector<tcomplex> operator-( tvector<tcomplex> a, tvector<tcomplex> b )
{
  tvector<tcomplex> y( a.size );
  if( a.size != b.size )
  {
    std::cerr<<"operator-( tvector<tcomplex> a, tvector<tcomplex> b ): Vectors do not have equal length."<<std::endl;
    return y;
  }
  for( uint64_t idx = 0; idx < a.size; idx++ )
    y.elem[idx] = a.elem[idx] - b.elem[idx];
  return y;
}

//==============================================================================
/*! Overloading of operator*
 */
tvector<double> operator*( tvector<double> a, double b )
{
  tvector<double> y( a.size );
  for( uint64_t idx = 0; idx < a.size; idx++ )
    y.elem[idx] = a.elem[idx] * b;
  return y;
}

tvector<tcomplex> operator*( tvector<double> a, tcomplex b )
{
  tvector<tcomplex> y( a.size );
  for( uint64_t idx = 0; idx < a.size; idx++ )
    y.elem[idx] = a.elem[idx] * b;
  return y;
}

tvector<double> operator*( double a, tvector<double> b )
{
  tvector<double> y( b.size );
  for( uint64_t idx = 0; idx < b.size; idx++ )
    y.elem[idx] = a * b.elem[idx];
  return y;
}

tvector<tcomplex> operator*( tcomplex a, tvector<double> b )
{
  tvector<tcomplex> y( b.size );
  for( uint64_t idx = 0; idx < b.size; idx++ )
    y.elem[idx] = a * b.elem[idx];
  return y;
}

tvector<tcomplex> operator*( tvector<tcomplex> a, double b )
{
  tvector<tcomplex> y( a.size );
  for( uint64_t idx = 0; idx < a.size; idx++ )
    y.elem[idx] = a.elem[idx] * b;
  return y;
}

tvector<tcomplex> operator*( tvector<tcomplex> a, tcomplex b )
{
  tvector<tcomplex> y( a.size );
  for( uint64_t idx = 0; idx < a.size; idx++ )
    y.elem[idx] = a.elem[idx] * b;
  return y;
}

tvector<tcomplex> operator*( double a, tvector<tcomplex> b )
{
  tvector<tcomplex> y( b.size );
  for( uint64_t idx = 0; idx < b.size; idx++ )
    y.elem[idx] = a * b.elem[idx];
  return y;
}

tvector<tcomplex> operator*( tcomplex a, tvector<tcomplex> b )
{
  tvector<tcomplex> y( b.size );
  for( uint64_t idx = 0; idx < b.size; idx++ )
    y.elem[idx] = a * b.elem[idx];
  return y;
}

tvector<double> operator*( tvector<double> a, tvector<double> b )
{
  tvector<double> y( a.size );
  if( a.size != b.size )
  {
    std::cerr<<"operator*( tvector<double> a, tvector<double> b ): Vectors do not have equal length."<<std::endl;
    return y;
  }
  for( uint64_t idx = 0; idx < a.size; idx++ )
    y.elem[idx] = a.elem[idx] * b.elem[idx];
  return y;
}

tvector<tcomplex> operator*( tvector<double> a, tvector<tcomplex> b )
{
  tvector<tcomplex> y( a.size );
  if( a.size != b.size )
  {
    std::cerr<<"operator*( tvector<double> a, tvector<double> b ): Vectors do not have equal length."<<std::endl;
    return y;
  }
  for( uint64_t idx = 0; idx < a.size; idx++ )
    y.elem[idx] = a.elem[idx] * b.elem[idx];
  return y;
}

tvector<tcomplex> operator*( tvector<tcomplex> a, tvector<double> b )
{
  tvector<tcomplex> y( a.size );
  if( a.size != b.size )
  {
    std::cerr<<"operator*( tvector<tcomplex> a, tvector<double> b ): Vectors do not have equal length."<<std::endl;
    return y;
  }
  for( uint64_t idx = 0; idx < a.size; idx++ )
    y.elem[idx] = a.elem[idx] * b.elem[idx];
  return y;
}

tvector<tcomplex> operator*( tvector<tcomplex> a, tvector<tcomplex> b )
{
  tvector<tcomplex> y( a.size );
  if( a.size != b.size )
  {
    std::cerr<<"operator*( tvector<tcomplex> a, tvector<tcomplex> b ): Vectors do not have equal length."<<std::endl;
    return y;
  }
  for( uint64_t idx = 0; idx < a.size; idx++ )
    y.elem[idx] = a.elem[idx] * b.elem[idx];
  return y;
}

//==============================================================================
/*! Overloading of operator/
 */
tvector<double> operator/( tvector<double> a, double b )
{
  tvector<double> y( a.size );
  for( uint64_t idx = 0; idx < a.size; idx++ )
    y.elem[idx] = a.elem[idx] / b;
  return y;
}

tvector<tcomplex> operator/( tvector<double> a, tcomplex b )
{
  tvector<tcomplex> y( a.size );
  for( uint64_t idx = 0; idx < a.size; idx++ )
    y.elem[idx] = a.elem[idx] / b;
  return y;
}

tvector<double> operator/( double a, tvector<double> b )
{
  tvector<double> y( b.size );
  for( uint64_t idx = 0; idx < b.size; idx++ )
    y.elem[idx] = a / b.elem[idx];
  return y;
}

tvector<tcomplex> operator/( tcomplex a, tvector<double> b )
{
  tvector<tcomplex> y( b.size );
  for( uint64_t idx = 0; idx < b.size; idx++ )
    y.elem[idx] = a / b.elem[idx];
  return y;
}

tvector<tcomplex> operator/( tvector<tcomplex> a, double b )
{
  tvector<tcomplex> y( a.size );
  for( uint64_t idx = 0; idx < a.size; idx++ )
    y.elem[idx] = a.elem[idx] / b;
  return y;
}

tvector<tcomplex> operator/( tvector<tcomplex> a, tcomplex b )
{
  tvector<tcomplex> y( a.size );
  for( uint64_t idx = 0; idx < a.size; idx++ )
    y.elem[idx] = a.elem[idx] / b;
  return y;
}

tvector<tcomplex> operator/( double a, tvector<tcomplex> b )
{
  tvector<tcomplex> y( b.size );
  for( uint64_t idx = 0; idx < b.size; idx++ )
    y.elem[idx] = a / b.elem[idx];
  return y;
}

tvector<tcomplex> operator/( tcomplex a, tvector<tcomplex> b )
{
  tvector<tcomplex> y( b.size );
  for( uint64_t idx = 0; idx < b.size; idx++ )
    y.elem[idx] = a / b.elem[idx];
  return y;
}

tvector<double> operator/( tvector<double> a, tvector<double> b )
{
  tvector<double> y( a.size );
  if( a.size != b.size )
  {
    std::cerr<<"operator/( tvector<double> a, tvector<double> b ): Vectors do not have equal length."<<std::endl;
    return y;
  }
  for( uint64_t idx = 0; idx < a.size; idx++ )
    y.elem[idx] = a.elem[idx] / b.elem[idx];
  return y;
}

tvector<tcomplex> operator/( tvector<double> a, tvector<tcomplex> b )
{
  tvector<tcomplex> y( a.size );
  if( a.size != b.size )
  {
    std::cerr<<"operator/( tvector<double> a, tvector<double> b ): Vectors do not have equal length."<<std::endl;
    return y;
  }
  for( uint64_t idx = 0; idx < a.size; idx++ )
    y.elem[idx] = a.elem[idx] / b.elem[idx];
  return y;
}

tvector<tcomplex> operator/( tvector<tcomplex> a, tvector<double> b )
{
  tvector<tcomplex> y( a.size );
  if( a.size != b.size )
  {
    std::cerr<<"operator/( tvector<tcomplex> a, tvector<double> b ): Vectors do not have equal length."<<std::endl;
    return y;
  }
  for( uint64_t idx = 0; idx < a.size; idx++ )
    y.elem[idx] = a.elem[idx] / b.elem[idx];
  return y;
}

tvector<tcomplex> operator/( tvector<tcomplex> a, tvector<tcomplex> b )
{
  tvector<tcomplex> y( a.size );
  if( a.size != b.size )
  {
    std::cerr<<"operator/( tvector<tcomplex> a, tvector<tcomplex> b ): Vectors do not have equal length."<<std::endl;
    return y;
  }
  for( uint64_t idx = 0; idx < a.size; idx++ )
    y.elem[idx] = a.elem[idx] / b.elem[idx];
  return y;
}

//==============================================================================
/*!
 */
ostream& operator<<( ostream& os, const tvector<double>& vec )
{
  for( uint64_t ii = 0; ii < vec.size; ii++ )
  {
    if( ii > 0 )
      os<<" "<<vec.elem[ii];
    else
      os<<vec.elem[ii];
  }
  return os;
}

//==============================================================================
/*!
 */
ostream& operator<<( ostream& os, const tvector<tcomplex>& vec )
{
  for( uint64_t ii = 0; ii < vec.size; ii++ )
  {
    if( ii > 0 )
      os<<" "<<vec.elem[ii];
    else
      os<<vec.elem[ii];
  }
  return os;
}

//==============================================================================
/*!
 */
double max( const tvector<double>& a )
{
  double ret = a.elem[0];
  for( uint64_t n = 0; n < a.size; n++ )
  {
    if( a.elem[n] > ret )
      ret = a.elem[n];
  }
  return ret;
}

//==============================================================================
/*!
 */
double min( const tvector<double>& a )
{
  double ret = a.elem[0];
  for( uint64_t n = 0; n < a.size; n++ )
  {
    if( a.elem[n] < ret )
      ret = a.elem[n];
  }
  return ret;
}

//==============================================================================
/*! Create vector of all zeros
 */
tvector<double> zeros( tuint m, tuint n )
{
  tvector<double> y( m );
  if( n != 1 )
    std::cerr << "[ERROR] zeros(): Matrix operation not implemented yet." << std::endl;
  else
  {
    for( tuint ii = 0; ii < m; ii ++ )
      y[ii] = 0.0;
  }
  return y;
}

//==============================================================================
/*!
 */
tvector<double> angle( const tvector<tcomplex>& a )
{
  tvector<double> y( a.size );
  for( uint64_t idx = 0; idx < a.size; idx++ )
    y[idx] = arg( a.elem[idx] );
  return y;
}

//==============================================================================
/*!
 */
tvector<double> sin( tvector<double> const &a )
{
  tvector<double> y( a.size );
  for( uint64_t idx = 0; idx < a.size; idx++ )
    y.elem[idx] = std::sin( a.elem[idx] );
  return y;
}

//==============================================================================
/*!
*/
tvector<double> cos( tvector<double> const &a )
{
  tvector<double> y( a.size );
  for( uint64_t idx = 0; idx < a.size; idx++ )
    y.elem[idx] = std::cos( a.elem[idx] );
  return y;
}

//==============================================================================
/*!
*/
tvector<double> tan( tvector<double> const &a )
{
  tvector<double> y( a.size );
  for( uint64_t idx = 0; idx < a.size; idx++ )
    y.elem[idx] = std::tan( a.elem[idx] );
  return y;
}

//==============================================================================
/*!
 */
tvector<double> exp( const tvector<double>& a )
{
  tvector<double> y( a.size );
  for( uint64_t idx = 0; idx < a.size; idx++ )
    y.elem[idx] = std::exp( a.elem[idx] );
  return y;
}

tvector<tcomplex> exp( const tvector<tcomplex>& a )
{
  tvector<tcomplex> y( a.size );
  for( uint64_t idx = 0; idx < a.size; idx++ )
    y.elem[idx] = exp( a.elem[idx] );
  return y;
}

//==============================================================================
/*!
 */
tvector<double> log10( const tvector<double>& a )
{
  tvector<double> y( a.size );
  for( uint64_t idx = 0; idx < a.size; idx++ )
    y[idx] = std::log10( a.elem[idx] );
  return y;
}

//==============================================================================
/*!  Returns the real part of the elements of the complex vector z.
 */
tvector<double> real( const tvector<tcomplex>& z )
{
  tvector<double> y( length(z) );
  for( tuint idx = 0; idx < length(z); idx++ )
    y[idx] = std::real( z.elem[idx] );
  return y;
}

//==============================================================================
/*!  Returns the imaginary part of the elements of the complex vector z.
 */
tvector<double> imag( const tvector<tcomplex>& z )
{
  tvector<double> y( length(z) );
  for( tuint idx = 0; idx < length(z); idx++ )
    y[idx] = std::imag( z.elem[idx] );
  return y;
}

//==============================================================================
/*!  Returns the sum of all elements of the vector.
 */
double sum( const tvector<double>& x )
{
  double ret = 0.0;
  for( tuint idx = 0; idx < length(x); idx++ )
    ret += x.elem[idx];
  return ret;
}

}
