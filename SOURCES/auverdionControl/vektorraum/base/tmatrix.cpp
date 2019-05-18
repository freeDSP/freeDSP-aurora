#include <complex>
#include <cmath>
#include <cstdint>

#include "typedefs.h"
#include "tvector.h"
#include "tmatrix.h"

namespace Vektorraum
{

//==============================================================================
/*! Returns the element at (m,n).
 *
 */
template <typename T>
T& tmatrix<T>::at( const uint64_t m, const uint64_t n ) const
{
  if( (m > rows) || (n > cols) )
  {
    std::cerr<<"Index ("<<m<<","<<n<<" out of range for matrix ("<<rows<<"x"<<cols<<")"<<std::endl;
    return elem[0];
  }
  else
    return (elem[ (m-1)*rows + (n-1) ]);
}

//==============================================================================
/*! Calculates the determinant of a matrix.
    \param A Matrix.
    \return Determinant.
 */
double det( tmatrix<double> const &A )
{
  double D = 0.0;
  if( (A.rows == 1) && (A.cols == 1) )
    D = A.at( 1, 1 );
  else if( (A.rows == 2) && (A.cols == 2) )
    D = A.at(1,1)*A.at(2,2) - A.at(1,2)*A.at(2,1);
  else
  {
    for( uint64_t k = 1; k <= A.cols; k++ )
    {
     tmatrix<double> D1k( A.rows-1, A.cols-1 );

     for( uint64_t r = 1; r <= A.rows - 1; r++ )
     {
       uint64_t idx = 1;
       for( uint64_t c = 1; c <= A.cols; c++ )
       {
         if( c != k )
         {
           D1k.at( r, idx ) = A.at( r + 1, c );
           idx++;
         }
       }
     }
     D += A.at( 1, k) * std::pow( -1.0, static_cast<double>( 1 + k ) ) * det( D1k );
    }
  }
  return D;
}

tcomplex det( tmatrix<tcomplex> const &A )
{
  tcomplex D = 0.0;
  if( (A.rows == 1) && (A.cols == 1) )
    D = A.at( 1, 1 );
  else if( (A.rows == 2) && (A.cols == 2) )
    D = A.at(1,1)*A.at(2,2) - A.at(1,2)*A.at(2,1);
  else
  {
    for( uint64_t k = 1; k <= A.cols; k++ )
    {
      tmatrix<tcomplex> D1k( A.rows-1, A.cols-1 );
      for( uint64_t r = 1; r <= A.rows-1; r++ )
      {
        uint64_t idx = 1;
        for( uint64_t c = 1; c <= A.cols; c++ )
        {
          if( c != k )
          {
            D1k.at( r, idx ) = A.at( r + 1, c );
            idx++;
          }
        }
     }
     D += A.at( 1, k ) * std::pow( -1.0, static_cast<double>( 1 + k ) ) * det( D1k );
    }
  }
  return D;
}

//==============================================================================
/*! Returns the number of rows or columns of matrix A.
    \param A Matrix.
    \param dim Dimension. 1: Rows
                          2: Columns
    \return Number of rows or columns.
 */
uint64_t size( const tmatrix<double>& A, uint64_t dim )
{
  if( dim == 1 )
    return A.rows;
  else if( dim == 2 )
    return A.cols;
  else
    return 0;
}

uint64_t size( const tmatrix<tcomplex>& A, uint64_t dim )
{
  if( dim == 1 )
    return A.rows;
  else if( dim == 2 )
    return A.cols;
  else
    return 0;
}

}
