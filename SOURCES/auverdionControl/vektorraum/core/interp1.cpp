#include <cmath>
#include <complex>
#include <iostream>

#include "../base/typedefs.h"
#include "../base/tvector.h"

namespace Vektorraum
{

namespace interp1_cspline
{

struct spline_t {
  double* F;
  double* s;
  double* h;
  double** m;
};

void cspline_init( spline_t* spline, tvector<double> x, tvector<double> f )
{
  tuint n = length(f);

  spline->F = new double[n+1];
  spline->h = new double[n];
  spline->s = new double[n-1];
  spline->m = new double*[n+1];
  for( tuint i = 0; i < (n+1); i++ )
    spline->m[i] = new double[n];

  double temp, sum;

  for( tuint k = 0; k < n+1; k++ )
    spline->F[k] = 0.0;
  for( tuint k = 0; k < n; k++ )
    spline->h[k] = 0.0;
  for( tuint k = 0; k < n+1; k++ )
    for( tuint l = 0; l < n; l++ )
      spline->m[k][l] = 0.0;
  for( tuint k = 0; k < n-1; k++ )
    spline->s[k] = 0.0;

  for( tuint i = n-1; i > 0; i--)
  {
    spline->F[i] = ( f[i]-f[i-1] ) / ( x[i]-x[i-1] );
    spline->h[i-1] = x[i]-x[i-1];
  }

  // --- formation of h, s , f matrix ---
  for( tuint i = 1; i < n-1; i++ )
  {
    spline->m[i][i] = 2.f*(spline->h[i-1]+spline->h[i]);
    if( i!=1 ) {
      spline->m[i][i-1] = spline->h[i-1];
      spline->m[i-1][i] = spline->h[i-1];
    }
    spline->m[i][n-1] = 6.0*(spline->F[i+1]-spline->F[i]);
  }

  // --- forward elimination ---
  for( tuint i = 1; i < n-2; i++ )
  {
    temp=(spline->m[i+1][i]/spline->m[i][i]);
    for( tuint jj = 1; jj <= n-1; jj++ )
      spline->m[i+1][jj]-=temp*spline->m[i][jj];
  }

  // --- backward substitution ---
  for( tuint i = n-2; i > 0; i-- )
  {
    sum = 0;
    for( tuint jj = i; jj <= n-2; jj++ )
      sum += spline->m[i][jj]*spline->s[jj];
    spline->s[i]=(spline->m[i][n-1]-sum)/spline->m[i][i];
  }
}

/*! \brief Interpoliert den Funktionswert an der Stelle xi für die gegebenen Stützstellen
 *         (xk|yk) mit Hilfe kubischer Splines.
 *
 * \param xi Stelle, für die der Funktionswert interpoliert werden soll.
 */
double cspline( spline_t* spline, tvector<double> x, tvector<double> f, double xi )
{
  tuint n = length(f);

  double y = 0.0;

  for( tuint i = 0; i < n-1 -1; i++ )
  {
    if( (x[i] <= xi) && (xi <= x[i+1]) )
    {
      double a = (spline->s[i+1]-spline->s[i])/(6.0*spline->h[i]);
      double b = spline->s[i]/2.0;
      double c = ( f[i+1]-f[i] )/spline->h[i] - (2.0*spline->h[i]*spline->s[i]+spline->s[i+1]*spline->h[i])/6.0;
      double d = f[i];
      double base = xi-x[i];
      y = a*std::pow( base, 3.0) + b*std::pow( base, 2.0) + c*(base) + d;
    }
  }

  return y;
}

} // namespace interp1_cspline

tvector<double> interp1( tvector<double> X, tvector<double> Y, tvector<double> XI, std::string method )
{
  tvector<double> YI( length(XI) );

  if( length(X) != length(Y) )
  {
    std::cout<<"[ERROR] "<<__FILE__<<":"<<__LINE__<<" interp1: Lenght(X) != length(Y)"<<std::endl;
    return YI;
  }

  for( tuint k = 0; k < length(X)-1; k++ )
  {
    if( X[k] >= X[k+1] )
    {
      std::cout<<"[ERROR] "<<__FILE__<<":"<<__LINE__<<" X nicht aufsteigend sortiert "<<k<<": "<<X[k]<<" "<<k+1<<": "<<X[k+1]<<std::endl;
      return YI;
    }
  }

  if( method == "spline" )
  {
    interp1_cspline::spline_t spline;

    // --- cspline interpolation ---
    interp1_cspline::cspline_init( &spline, X, Y );

    for( tuint k = 0; k < length(XI); k++ )
      YI[k] = interp1_cspline::cspline( &spline, X, Y, XI[k] );

    for( tuint i = 0; i < (length(Y)+1); i++ )
      delete [] (spline.m[i]);

    delete [] spline.m;

    delete [] spline.F;
    delete [] spline.h;
    delete [] spline.s;
  }
  else
    std::cout<<"[ERROR] "<<__FILE__<<":"<<__LINE__<<"Unbekannte Methode zur Inpterpolation"<<std::endl;

  return YI;
}

}
