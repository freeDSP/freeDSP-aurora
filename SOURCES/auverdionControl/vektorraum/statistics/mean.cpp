#include <cmath>
#include <iostream>

#include "../base/typedefs.h"
#include "../base/tvector.h"

using namespace std;

namespace Vektorraum
{

//==============================================================================
/*! Average or mean value of vector A.
    \param A Vector.
    \return Mean of the elements.
 */
double mean( tvector<double>& A )
{
  double m = 0.0;
  for( tuint ii = 0; ii < length(A); ii++ )
    m += A[ii];
  return m / static_cast<double>( length(A) );
}

}
