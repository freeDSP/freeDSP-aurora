#pragma once

#include <cstdint>
#include <cmath>
#include <iostream>

#include "typedefs.h"

namespace Vektorraum
{

template<typename T>
class tmatrix
{
public:
  //============================================================================
  tmatrix( void )
  {
    rows = 0;
    cols = 0;
    elem = nullptr;
  }

  tmatrix( uint64_t r, uint64_t c )
  {
    rows = r;
    cols = c;
    elem = new T[rows*cols];
  }

  //============================================================================
  ~tmatrix()
  {
    if( elem != nullptr )
      delete [] elem;
  }

  //============================================================================
  tmatrix<T>& operator=( const tmatrix<T>& rhs )
  {
    if( this != &rhs )
    {
      if( elem )
        delete [] elem;
      elem = new T[ rhs.rows * rhs.cols ];
      for( uint64_t k = 0; k < rhs.rows * rhs.cols; k++ )
        elem[k] = rhs.elem[k];
    }
    return *this;
  }

  //============================================================================
  /*! Returns the element at (m,n).
      \param m Row index
      \param n Column index
   */
  T& operator()( uint64_t m, uint64_t n ) const
  {
    if( elem )
    {
      if( (m > rows) || (n > cols) )
      {
        std::cerr<<"Index ("<<m<<","<<n<<") out of range for matrix ("<<rows<<"x"<<cols<<")"<<std::endl;
        return elem[0];
      }
      else
        return elem[ m*rows + n ];
    }
    else
    {
      std::cerr<<"Empty matrix"<<std::endl;
      return elem[0];
    }
  }

  //============================================================================
  /*! \brief Returns the element at (m,n).
   *
   */
  T& at( uint64_t m, uint64_t n ) const;

private:
  T* elem;
  uint64_t rows;
  uint64_t cols;

  friend double det( tmatrix<double> const &A );
  friend tcomplex det( tmatrix<tcomplex> const &A );
  friend uint64_t size( const tmatrix<double>& A, uint64_t dim );
  friend uint64_t size( const tmatrix<tcomplex>& A, uint64_t dim );

};

//==============================================================================
/*! Calculates the determinant of a matrix.
    \param A Matrix.
    \return Determinant.
 */
double det( tmatrix<double> const &A );
tcomplex det( tmatrix<tcomplex> const &A );

//==============================================================================
/*! Returns the number of rows or columns of matrix A.
    \param A Matrix.
    \param dim Dimension. 1: Rows
                          2: Columns
    \return Number of rows or columns.
 */
uint64_t size( const tmatrix<double>& A, uint64_t dim );
uint64_t size( const tmatrix<tcomplex>& A, uint64_t dim );

}
