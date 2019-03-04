#include <cmath>
#include <complex>
#include <cstdint>

#include <iostream>

#include "core.h"

#include "../base/tmatrix.h"

namespace Vektorraum
{

//==============================================================================
/*! Solves a system of linear equations Ax=c by using Cramer's rule.
    \param A Coefficient matrix.
    \param c Right hand side vector.
    \return Vector with solutions.
 */
tvector<double> solve( const tmatrix<double>& A, tvector<double> c )
{
  tvector<double> x( size( A, 1 ) );

  if( size( A, 1 ) != size( A, 2 ) )
  {
    std::cerr<<"solve(): Matrix not square"<<std::endl;
    return x;
  }
  if( size( A, 1 ) != length(c) )
  {
    std::cerr<<"solve(): Number of rows of matrix A does not match the length of vector c"<<std::endl;
    return x;
  }

  double D = det(A);
  for( uint64_t n = 1; n <= size( A, 2 ); n++ )
  {
    tmatrix<double> Ai( size( A, 1 ), size( A, 2 ) );
    Ai = A;
    for( uint64_t m = 1; m <= size( A, 1 ); m++ )
      Ai.at( m, n ) = c[m-1];
    double Di = det(Ai);
    x[n-1] = Di/D;
  }
  return x;
}

tvector<tcomplex> solve( const tmatrix<tcomplex>& A, tvector<tcomplex> c )
{
  tvector<tcomplex> x( size( A, 1 ) );

  if( size( A, 1 ) != size( A, 2 ) )
  {
    std::cerr<<"solve(): Matrix not square"<<std::endl;
    return x;
  }
  if( size( A, 1 ) != length(c) )
  {
    std::cerr<<"solve(): Number of rows of matrix A does not match the length of vector c"<<std::endl;
    return x;
  }

  tcomplex D = det(A);
  for( uint64_t n = 1; n <= size( A, 2 ); n++ )
  {
    tmatrix<tcomplex> Ai( size( A, 1 ), size( A, 2 ) );
    Ai = A;
    for( uint64_t m = 1; m <= size( A, 1 ); m++ )
      Ai.at( m, n ) = c[m-1];
    tcomplex Di = det(Ai);
    x[n-1] = Di/D;
  }
  return x;
}

}
