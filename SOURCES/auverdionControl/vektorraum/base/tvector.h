/*
  ==============================================================================

    tvector.h
    Created: 19 Apr 2018 10:43:13am
    Author:  Raphael Knoop

  ==============================================================================
*/

#pragma once

#include <cstdint>
#include <iostream>

#include "typedefs.h"

namespace Vektorraum
{

template<typename T>
class tvector;

//==============================================================================
/*! Compute the magnitude for each element of A.
    \param A Input vector.
    \return Vector with magnitudes.
 */
template <typename T> tvector<double> abs( const tvector<T>& A );

//==============================================================================
/*! Clears the vector.
    \param a Vector to be cleared.
*/
template <typename T> void clear( tvector<T>& a );

//==============================================================================
/*!
 */
//template <typename T> tuint length( const tvector<T>& a );
template <typename T> tuint length( const tvector<T>& a );

//==============================================================================
/*! Flip vector up to down
    \param A Input vector
    \return A with its rows flipped in the up-down direction
 */
template <typename T> tvector<T> flipud( const tvector<T>& A );

//==============================================================================
/*! Flip vector left to right
    \param A Input vector
    \return A with its columns flipped in the left-right direction
 */
template <typename T> tvector<T> fliplr( const tvector<T>& A );

//==============================================================================
/*! Raises each element of A to the corresponding power in exponent.
 */
template <typename T> tvector<T> pow( const tvector<T>& A, const double exponent );

//==============================================================================
/*! Raises x to the corresponding power for each element in exponent.
 */
template <typename T> tvector<T> pow( const double x, const tvector<T>&  exponent );

//==============================================================================
template<typename T> class tvector
{
public:
  tvector( void )
  {
    size = 0;
    elem = nullptr;
  }

  // copy constructor
  tvector( const tvector& a )
  {
    size = a.size;
    elem = new T[a.size];
    for( uint64_t k = 0; k < a.size; k++ )
      elem[k] = a.elem[k];
  }

  tvector( uint64_t length )
  {
    size = length;
    elem = new T[size];
    for( uint64_t k = 0; k < size; k++ )
      elem[k] = 0.0;
  }

  tvector( tvector<T> a, tvector<T> b )
  {
    size = length(a) + length(b);
    elem = new T[size];
    for( uint64_t k = 0; k < length(a); k++ )
      elem[k] = a[k];
    for( uint64_t k = 0; k < length(b); k++ )
      elem[ length(a) + k ] = b[k];
  }

  ~tvector()
  {
    if( (elem != nullptr ) && (size > 0) )
      delete elem;
  }

  T& operator[]( uint64_t idx )
  {
    if( idx < size )
      return elem[idx];
    else
    {
      throw std::invalid_argument( "Index out of range" );
      std::cerr<<"tvector[]: Index ("<<idx<<") out of range."<<std::endl;
    }

    return elem[0];
  }

  //============================================================================
  /*!
   */
  tvector<T> operator()( const tuint a, const tuint b )
  {
    tvector<T> y( b - a + 1 );
    tuint idx = 0;
    for( tuint ii = a; ii <= b; ii++ )
    {
      y[idx] = (*this)[ii];
      idx++;
    }
    return y;
  }

  //============================================================================
  /*!
   */
  tvector<T> operator()( const tvector<tuint>& idx )
  {
    tvector<T> y( length(idx) );
    for( tuint ii = 0; ii < length(idx); ii++ )
    {
      if( idx.at(ii) < size )
        y[ii] = elem[ idx.at(ii) ];
      else
        std::cerr<<"tvector<T> operator(): Index ("<<idx.at(ii)<<") out of range."<<std::endl;
    }
    return y;
  }

  //============================================================================
  /*! Copy assignment
  */
  tvector<T>& operator=( const tvector<T>& rhs )
  {
    if( this != &rhs )
    {
      if( rhs.size != size ) {
        if( elem != nullptr )
          delete[] elem;
        elem = new T[rhs.size];
        size = rhs.size;
      }
      for( uint64_t k = 0; k < rhs.size; k++ )
        elem[k] = rhs.elem[k];
    }
    return *this;
  }

  //============================================================================
  T at( tuint idx ) const
  {
    return elem[idx];
  }

private:
  uint64_t size;
  T* elem;

  friend tvector<double>   operator+( tvector<double> a, double b );
  friend tvector<tcomplex> operator+( tvector<double> a, tcomplex b );
  friend tvector<double>   operator+( double a, tvector<double> b );
  friend tvector<tcomplex> operator+( tcomplex a, tvector<double> b );
  friend tvector<tcomplex> operator+( tvector<tcomplex> a, double b );
  friend tvector<tcomplex> operator+( tvector<tcomplex> a, tcomplex b );
  friend tvector<tcomplex> operator+( double a, tvector<tcomplex> b );
  friend tvector<tcomplex> operator+( tcomplex a, tvector<tcomplex> b );
  friend tvector<double>   operator+( tvector<double> a, tvector<double> b );
  friend tvector<tcomplex> operator+( tvector<double> a, tvector<tcomplex> b );
  friend tvector<tcomplex> operator+( tvector<tcomplex> a, tvector<double> b );
  friend tvector<tcomplex> operator+( tvector<tcomplex> a, tvector<tcomplex> b );

  friend tvector<double>   operator-( tvector<double> a, double b );
  friend tvector<tcomplex> operator-( tvector<double> a, tcomplex b );
  friend tvector<double>   operator-( double a, tvector<double> b );
  friend tvector<tcomplex> operator-( tcomplex a, tvector<double> b );
  friend tvector<tcomplex> operator-( tvector<tcomplex> a, double b );
  friend tvector<tcomplex> operator-( tvector<tcomplex> a, tcomplex b );
  friend tvector<tcomplex> operator-( double a, tvector<tcomplex> b );
  friend tvector<tcomplex> operator-( tcomplex a, tvector<tcomplex> b );
  friend tvector<double>   operator-( tvector<double> a, tvector<double> b );
  friend tvector<tcomplex> operator-( tvector<double> a, tvector<tcomplex> b );
  friend tvector<tcomplex> operator-( tvector<tcomplex> a, tvector<double> b );
  friend tvector<tcomplex> operator-( tvector<tcomplex> a, tvector<tcomplex> b );

  friend tvector<double>   operator*( tvector<double> a, double b );
  friend tvector<tcomplex> operator*( tvector<double> a, tcomplex b );
  friend tvector<double>   operator*( double a, tvector<double> b );
  friend tvector<tcomplex> operator*( tcomplex a, tvector<double> b );
  friend tvector<tcomplex> operator*( tvector<tcomplex> a, double b );
  friend tvector<tcomplex> operator*( tvector<tcomplex> a, tcomplex b );
  friend tvector<tcomplex> operator*( double a, tvector<tcomplex> b );
  friend tvector<tcomplex> operator*( tcomplex a, tvector<tcomplex> b );
  friend tvector<double>   operator*( tvector<double> a, tvector<double> b );
  friend tvector<tcomplex> operator*( tvector<double> a, tvector<tcomplex> b );
  friend tvector<tcomplex> operator*( tvector<tcomplex> a, tvector<double> b );
  friend tvector<tcomplex> operator*( tvector<tcomplex> a, tvector<tcomplex> b );

  friend tvector<double>   operator/( tvector<double> a, double b );
  friend tvector<tcomplex> operator/( tvector<double> a, tcomplex b );
  friend tvector<double>   operator/( double a, tvector<double> b );
  friend tvector<tcomplex> operator/( tcomplex a, tvector<double> b );
  friend tvector<tcomplex> operator/( tvector<tcomplex> a, double b );
  friend tvector<tcomplex> operator/( tvector<tcomplex> a, tcomplex b );
  friend tvector<tcomplex> operator/( double a, tvector<tcomplex> b );
  friend tvector<tcomplex> operator/( tcomplex a, tvector<tcomplex> b );
  friend tvector<double>   operator/( tvector<double> a, tvector<double> b );
  friend tvector<tcomplex> operator/( tvector<double> a, tvector<tcomplex> b );
  friend tvector<tcomplex> operator/( tvector<tcomplex> a, tvector<double> b );
  friend tvector<tcomplex> operator/( tvector<tcomplex> a, tvector<tcomplex> b );

  friend std::ostream& operator<<( std::ostream&, const tvector<double>& );
  friend std::ostream& operator<<( std::ostream&, const tvector<tcomplex>& );

  friend tvector<double> abs<T>( const tvector<T>& A );
  friend void clear<T>( tvector<T>& a );
  friend tuint length<T>( const tvector<T>& a );
  friend tvector flipud<T>( const tvector<T>& A );
  friend tvector fliplr<T>( const tvector<T>& A );
  friend tvector pow<T>( const tvector<T>& A, const double exponent );
  friend tvector pow<T>( const double x, const tvector<T>&  exponent );




  friend double max( const tvector<double>& a );
  friend double min( const tvector<double>& a );

  //friend tvector<double> abs( const tvector<tcomplex>& a );
  //friend tvector<double> abs( const tvector<double>& a );
  friend tvector<double> angle( const tvector<tcomplex>& a );

  friend tvector<double> sin( tvector<double> const &a );
  friend tvector<double> cos( tvector<double> const &a );
  friend tvector<double> tan( tvector<double> const &a );

  friend tvector<double> exp( tvector<double> const &a );
  friend tvector<tcomplex> exp( const tvector<tcomplex>& a );
  friend tvector<double> log10( const tvector<double>& a );


  friend tvector<double> real( const tvector<tcomplex>& z );
  friend tvector<double> imag( const tvector<tcomplex>& z );

  friend double sum( const tvector<double>& x );
};

//==============================================================================
/*! Overloading of operator+
 */
tvector<double>   operator+( tvector<double> a, double b );
tvector<tcomplex> operator+( tvector<double> a, tcomplex b );
tvector<double>   operator+( double a, tvector<double> b );
tvector<tcomplex> operator+( tcomplex a, tvector<double> b );
tvector<tcomplex> operator+( tvector<tcomplex> a, double b );
tvector<tcomplex> operator+( tvector<tcomplex> a, tcomplex b );
tvector<tcomplex> operator+( double a, tvector<tcomplex> b );
tvector<tcomplex> operator+( tcomplex a, tvector<tcomplex> b );
tvector<double>   operator+( tvector<double> a, tvector<double> b );
tvector<tcomplex> operator+( tvector<double> a, tvector<tcomplex> b );
tvector<tcomplex> operator+( tvector<tcomplex> a, tvector<double> b );
tvector<tcomplex> operator+( tvector<tcomplex> a, tvector<tcomplex> b );

//==============================================================================
/*! Overloading of operator-
 */
tvector<double>   operator-( tvector<double> a, double b );
tvector<tcomplex> operator-( tvector<double> a, tcomplex b );
tvector<double>   operator-( double a, tvector<double> b );
tvector<tcomplex> operator-( tcomplex a, tvector<double> b );
tvector<tcomplex> operator-( tvector<tcomplex> a, double b );
tvector<tcomplex> operator-( tvector<tcomplex> a, tcomplex b );
tvector<tcomplex> operator-( double a, tvector<tcomplex> b );
tvector<tcomplex> operator-( tcomplex a, tvector<tcomplex> b );
tvector<double>   operator-( tvector<double> a, tvector<double> b );
tvector<tcomplex> operator-( tvector<double> a, tvector<tcomplex> b );
tvector<tcomplex> operator-( tvector<tcomplex> a, tvector<double> b );
tvector<tcomplex> operator-( tvector<tcomplex> a, tvector<tcomplex> b );

//==============================================================================
/*! Overloading of operator*
 */
tvector<double>   operator*( tvector<double> a, double b );
tvector<tcomplex> operator*( tvector<double> a, tcomplex b );
tvector<double>   operator*( double a, tvector<double> b );
tvector<tcomplex> operator*( tcomplex a, tvector<double> b );
tvector<tcomplex> operator*( tvector<tcomplex> a, double b );
tvector<tcomplex> operator*( tvector<tcomplex> a, tcomplex b );
tvector<tcomplex> operator*( double a, tvector<tcomplex> b );
tvector<tcomplex> operator*( tcomplex a, tvector<tcomplex> b );
tvector<double>   operator*( tvector<double> a, tvector<double> b );
tvector<tcomplex> operator*( tvector<double> a, tvector<tcomplex> b );
tvector<tcomplex> operator*( tvector<tcomplex> a, tvector<double> b );
tvector<tcomplex> operator*( tvector<tcomplex> a, tvector<tcomplex> b );

//==============================================================================
/*! Overloading of operator/
 */
tvector<double>   operator/( tvector<double> a, double b );
tvector<tcomplex> operator/( tvector<double> a, tcomplex b );
tvector<double>   operator/( double a, tvector<double> b );
tvector<tcomplex> operator/( tcomplex a, tvector<double> b );
tvector<tcomplex> operator/( tvector<tcomplex> a, double b );
tvector<tcomplex> operator/( tvector<tcomplex> a, tcomplex b );
tvector<tcomplex> operator/( double a, tvector<tcomplex> b );
tvector<tcomplex> operator/( tcomplex a, tvector<tcomplex> b );
tvector<double>   operator/( tvector<double> a, tvector<double> b );
tvector<tcomplex> operator/( tvector<double> a, tvector<tcomplex> b );
tvector<tcomplex> operator/( tvector<tcomplex> a, tvector<double> b );
tvector<tcomplex> operator/( tvector<tcomplex> a, tvector<tcomplex> b );

std::ostream& operator<<( std::ostream&, const tvector<double>& );
std::ostream& operator<<( std::ostream&, const tvector<tcomplex>& );


//==============================================================================
/*! Compute the magnitude for each element of A.
    \param A Input vector.
    \return Vector with magnitudes.
 */
template <typename T>
tvector<double> abs( const tvector<T>& A )
{
  tvector<double> y( A.size );
  for( uint64_t idx = 0; idx < A.size; idx++ )
    y[idx] = std::abs( A.elem[idx] );
  return y;
}

//==============================================================================
/*! Clears the vector.
    \param a Vector to be cleared.
*/
template <typename T>
void clear( tvector<T>& a )
{
  if( a.elem )
    delete [] a.elem;
  a.elem = nullptr;
  a.size = 0;
}

//==============================================================================
/*! Flip vector up to down
    \param A Input vector
    \return A with its rows flipped in the up-down direction
 */
template <typename T>
tvector<T> flipud( const tvector<T>& A )
{
  tuint len = A.size;
  tvector<T> B( len );
  for( tuint idx = 0; idx < A.size; idx++ )
    B[len-1-idx] = A.elem[idx];
  return B;
}

//==============================================================================
/*! Flip vector left to right
    \param A Input vector
    \return A with its columns flipped in the left-right direction
 */
template <typename T>
tvector<T> fliplr( const tvector<T>& A )
{
  tuint len = A.size;
  tvector<T> B( len );
  for( tuint idx = 0; idx < A.size; idx++ )
    B[len-1-idx] = A.elem[idx];
  return B;
}

//==============================================================================
/*!
 */
template <typename T>
tuint length( const tvector<T>& a )
{
  return a.size;
}

//==============================================================================
/*! Raises each element of A to the corresponding power in exponent.
 */
template <typename T>
tvector<T> pow( const tvector<T>& A, const double exponent )
{
  tvector<T> y( A.size );
  for( tuint idx = 0; idx < A.size; idx++ )
    y[idx] = std::pow( A.elem[idx], exponent );
  return y;
}

//==============================================================================
/*! Raises x to the corresponding power for each element in exponent.
 */
template <typename T>
tvector<T> pow( const double x, const tvector<T>&  exponent )
{
  tvector<T> y( exponent.size );
  for( tuint idx = 0; idx < exponent.size; idx++ )
    y[idx] = std::pow( x, exponent.elem[idx] );
  return y;
}








//==============================================================================
/*!
 */
double max( const tvector<double>& a );

//==============================================================================
/*!
 */
double min( const tvector<double>& a );

//==============================================================================
/*! Create vector of all zeros
 */
tvector<double> zeros( tuint m, tuint n );

//==============================================================================
/*!
 */
tvector<double> angle( const tvector<tcomplex>& a );

//==============================================================================
//
// sin/cos/tan etc.
//
//==============================================================================
/*!
*/
tvector<double> sin( tvector<double> const &a );

/*!
*/
tvector<double> cos( tvector<double> const &a );

/*!
*/
tvector<double> tan( tvector<double> const &a );

//==============================================================================
//
// exp/log etc.
//
//==============================================================================
/*!
*/
tvector<double> exp( tvector<double> const &a );
tvector<tcomplex> exp( const tvector<tcomplex>& a );

//==============================================================================
/*!
*/
tvector<double> log10( const tvector<double>& a );

//==============================================================================
//
// Complex numbers
//
//==============================================================================
/*!  Returns the real part of the elements of the complex vector z.
 */
tvector<double> real( const tvector<tcomplex>& z );

//==============================================================================
/*!  Returns the imaginary part of the elements of the complex vector z.
 */
tvector<double> imag( const tvector<tcomplex>& z );

//==============================================================================
/*!  Returns the sum of all elements of the vector.
 */
double sum( const tvector<double>& x );

}
