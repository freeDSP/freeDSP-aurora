#pragma once

#include <string>

#include "../base/typedefs.h"
#include "../base/tvector.h"
#include "../base/tmatrix.h"

namespace Vektorraum
{

//==============================================================================
/*!
 */
tvector<double> interp1( tvector<double> X, tvector<double> Y, tvector<double> XI, std::string method );

//==============================================================================
/*! Solves a system of linear equations Ax=c.
    \param A Coefficient matrix.
    \param c Right hand side vector.
    \return Vector with solutions.
 */
tvector<double> solve( tmatrix<double> const &A, tvector<double> c );
tvector<tcomplex> solve( tmatrix<tcomplex> const &A, tvector<tcomplex> c );

//==============================================================================
/*!
 */
void wavwrite( tvector<double> sig, const char* filename );

}
